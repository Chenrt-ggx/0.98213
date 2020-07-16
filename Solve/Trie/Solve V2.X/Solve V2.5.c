#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")

#include <stdio.h>
#include <string.h>

FILE *in,*out;
char buffer[10000100];
char r[50],s1[3000010][50],s2[3000010][50];
struct {int flag,con1,con2,s[26];} a[3000010];
int head,pool,n,outlen,len1,len2,top1,top2,sum1,same1,sum2,same2;
int fst1[20000],nxt1[3000010],fst2[20000],nxt2[3000010],ecl[3000010];

void ins1()
{
	register int i,t,tmp=head;
	for (i=0;buffer[i];i++)
	{
		if (('a'<=buffer[i] && buffer[i]<='z')
		|| ('A'<=buffer[i] && buffer[i]<='Z'))
		{
			t=(buffer[i]|32)-'a';
			if (!a[tmp].s[t])
			a[tmp].s[t]=++pool;
			tmp=a[tmp].s[t];
		}
		else if (tmp)
		{
			a[tmp].con1++;
			tmp=head;
		}
	}
	if (tmp)
	{
		a[tmp].con1++;
		tmp=head;
	}
	return;
}

void ins2()
{
	register int i,t,tmp=head;
	for (i=0;buffer[i];i++)
	{
		if (('a'<=buffer[i] && buffer[i]<='z')
		|| ('A'<=buffer[i] && buffer[i]<='Z'))
		{
			t=(buffer[i]|32)-'a';
			if (!a[tmp].s[t])
			a[tmp].s[t]=++pool;
			tmp=a[tmp].s[t];
		}
		else if (tmp)
		{
			a[tmp].con2++;
			tmp=head;
		}
	}
	if (tmp)
	{
		a[tmp].con2++;
		tmp=head;
	}
	return;
}

void del()
{
	register int i,t,tmp=head;
	for (i=0;buffer[i];i++)
	{
		flagA:
		if (('a'<=buffer[i] && buffer[i]<='z')
		|| ('A'<=buffer[i] && buffer[i]<='Z'))
		{
			t=(buffer[i]|32)-'a';
			if (!a[tmp].s[t])
			{
				while (('a'<=buffer[i] && buffer[i]<='z')
				|| ('A'<=buffer[i] && buffer[i]<='Z')) i++;
				if (!buffer[i]) return;
				tmp=head; goto flagA;
				return;
			}
			tmp=a[tmp].s[t];
		}
		else if (tmp)
		{
			a[tmp].con1=a[tmp].con2=0;
			tmp=head;
		}
	}
	if (tmp)
	{
		a[tmp].con1=a[tmp].con2=0;
		tmp=head;
	}
	return;
}

void chk()
{
	register int i,t,tmp=head;
	for (i=0;buffer[i];i++)
	{
		flagB:
		if (('a'<=buffer[i] && buffer[i]<='z')
		|| ('A'<=buffer[i] && buffer[i]<='Z'))
		{
			t=(buffer[i]|32)-'a';
			if (!a[tmp].s[t])
			{
				while (('a'<=buffer[i] && buffer[i]<='z')
				|| ('A'<=buffer[i] && buffer[i]<='Z')) i++;
				if (!buffer[i]) return;
				tmp=head; goto flagB;
			}
			tmp=a[tmp].s[t];
		}
		else if (tmp)
		{
			a[tmp].flag=1;
			tmp=head;
		}
	}
	if (tmp)
	{
		a[tmp].flag=1;
		tmp=head;
	}
	return;
}

void init()
{
	in=fopen("article1.txt","rb");
	n=fread(buffer,1,10000000,in); buffer[n]=0; ins1(); fclose(in);
	in=fopen("article2.txt","rb");
	n=fread(buffer,1,10000000,in); buffer[n]=0; ins2(); fclose(in);
	in=fopen("stopwords.txt","rb");
	n=fread(buffer,1,10000000,in); buffer[n]=0; del(); fclose(in);
	in=fopen("dictionary.txt","rb");
	n=fread(buffer,1,10000000,in); buffer[n]=0; chk(); fclose(in);
	return;
}

void dfs(int pos,int num)
{
	for (register int i=25;i+1;i--)
	{
		if (a[num].s[i])
		{
			r[pos]=i+'a';
			dfs(pos+1,a[num].s[i]);
			r[pos]=0;
		}
	}
	if (a[num].flag)
	{
		if (a[num].con1)
		{
			nxt1[num]=fst1[a[num].con1];
			fst1[a[num].con1]=num;
			memcpy(s1[num],r,pos),len1++;
			if (a[num].con1>top1)
			top1=a[num].con1;
		}
		if (a[num].con2)
		{
			nxt2[num]=fst2[a[num].con2];
			fst2[a[num].con2]=num;
			memcpy(s2[num],r,pos),len2++;
			if (a[num].con2>top2)
			top2=a[num].con2;
		}
	}
	return;
}

void adddigit(int x)
{
	if (x>9) adddigit(x/10);
	buffer[outlen++]=x%10+'0';
	return;
}

void solve()
{
	register int tmp;
	dfs(0,0),scanf("%d",&n);
	if (n>len1) n=len1;
	if (n>len2) n=len2;
	buffer[outlen++]='\n';
	tmp=0; while (tmp<n)
	for (register int i=top1;i && tmp<n;i--)
	for (register int j=fst1[i];j && tmp<n;j=nxt1[j])
	{
		for (register int k=0;s1[j][k];k++)
		buffer[outlen++]=s1[j][k];
		buffer[outlen++]=32;
		adddigit(a[j].con1);
		buffer[outlen++]='\n';
		sum1+=a[j].con1;
		tmp++,ecl[j]=1;
	}
	buffer[outlen++]='\n';
	tmp=0; while (tmp<n)
	for (register int i=top2;i && tmp<n;i--)
	for (register int j=fst2[i];j && tmp<n;j=nxt2[j])
	{
		for (register int k=0;s2[j][k];k++)
		buffer[outlen++]=s2[j][k];
		buffer[outlen++]=32;
		adddigit(a[j].con2);
		buffer[outlen++]='\n';
		sum2+=a[j].con2,tmp++;
		if (ecl[j]) same1+=a[j].con1,same2+=a[j].con2;
	}
	return;
}

void print()
{
	out=fopen("results.txt","w");
	double pro1=(double)same1/(double)sum1;
	double pro2=(double)same2/(double)sum2;
	double ans=(pro1<pro2?pro1:pro2)/(pro1>pro2?pro1:pro2);
	printf("%.5lf\n",ans);
	fprintf(out,"%.5lf\n",ans);
	fwrite(buffer,1,outlen,out);
	fclose(out); return;
}

int main()
{
	init(),solve(),print();
	return 0;
}