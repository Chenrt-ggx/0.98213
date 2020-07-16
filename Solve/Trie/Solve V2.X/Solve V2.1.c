#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")

#include <stdio.h>
#include <ctype.h>
#include <string.h>

FILE *in,*out;
char r[50],s1[3000010][50],s2[3000010][50];
struct {int flag,son,vis,con1,con2,s[26];} a[3000010];
int head,pool,t,n,len1,len2,top1,top2,sum1,same1,sum2,same2;
int fst1[20000],nxt1[3000010],fst2[20000],nxt2[3000010],ecl[3000010];

int read()
{
	register int cnt=0;
	register char c=fgetc(in);
	if (c==EOF) return 0;
	while (!isalpha(c))
	{
		c=fgetc(in);
		if (c==EOF)
		return 0;
	}
	while (isalpha(c))
	{
		r[cnt++]=c;
		c=fgetc(in);
	}
	r[cnt]=0;
	return 1;
}

void ins()
{
	register int tmp=head;
	for (register int i=0;r[i];i++)
	{
		t=tolower(r[i])-'a';
		if (!a[tmp].s[t])
		a[tmp].s[t]=++pool;
		tmp=a[tmp].s[t];
	}
	a[tmp].flag=1;
	return;
}

void del()
{
	register int tmp=head;
	for (register int i=0;r[i];i++)
	{
		t=tolower(r[i])-'a';
		if (!a[tmp].s[t]) return;
		else tmp=a[tmp].s[t];
	}
	a[tmp].flag=0;
	return;
}

void count1()
{
	register int tmp=head;
	for (register int i=0;r[i];i++)
	{
		a[tmp].son=1;
		t=tolower(r[i])-'a';
		if (!a[tmp].s[t]) return;
		else tmp=a[tmp].s[t];
	}
	a[tmp].son=1;
	if (a[tmp].flag)
	a[tmp].con1++;
	return;
}

void count2()
{
	register int tmp=head;
	for (register int i=0;r[i];i++)
	{
		a[tmp].son=1;
		t=tolower(r[i])-'a';
		if (!a[tmp].s[t]) return;
		else tmp=a[tmp].s[t];
	}
	a[tmp].son=1;
	if (a[tmp].flag)
	a[tmp].con2++;
	return;
}

void dfs(int pos,int num)
{
	if (!a[num].son) return;
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
			strcpy(s1[num],r),len1++;
			if (a[num].con1>top1)
			top1=a[num].con1;
		}
		if (a[num].con2)
		{
			nxt2[num]=fst2[a[num].con2];
			fst2[a[num].con2]=num;
			strcpy(s2[num],r),len2++;
			if (a[num].con2>top2)
			top2=a[num].con2;
		}
	}
	return;
}

void solve()
{
	register int tmp;
	memset(r,0,sizeof(r)); 
	dfs(0,0),scanf("%d",&n);
	if (n>len1) n=len1;
	if (n>len2) n=len2;
	tmp=0; while (tmp<n)
	for (register int i=top1;i && tmp<n;i--)
	for (register int j=fst1[i];j && tmp<n;j=nxt1[j])
	{
		sum1+=a[j].con1;
		tmp++,ecl[j]=1;
	}
	tmp=0; while (tmp<n)
	for (register int i=top2;i && tmp<n;i--)
	for (register int j=fst2[i];j && tmp<n;j=nxt2[j])
	{
		sum2+=a[j].con2,tmp++;
		if (ecl[j]) same1+=a[j].con1,same2+=a[j].con2;
	}
	return;
}

void print()
{
	register int tmp;
	double pro1=(double)same1/(double)sum1;
	double pro2=(double)same2/(double)sum2;
	double ans=(pro1<pro2?pro1:pro2)/(pro1>pro2?pro1:pro2);
	printf("%.5lf\n",ans);
	fprintf(out,"%.5lf\n",ans);
	fputc('\n',out); tmp=0; while (tmp<n)
	{
		for (register int i=top1;i && tmp<n;i--)
		for (register int j=fst1[i];j && tmp<n;j=nxt1[j])
		fprintf(out,"%s %d\n",s1[j],a[j].con1),tmp++;
	}
	fputc('\n',out); tmp=0; while (tmp<n)
	{
		for (register int i=top2;i && tmp<n;i--)
		for (register int j=fst2[i];j && tmp<n;j=nxt2[j])
		fprintf(out,"%s %d\n",s2[j],a[j].con2),tmp++;
	}
	return;
}

int main()
{
	in=fopen("dictionary.txt","r");
	while (fscanf(in,"%s",r)!=EOF) ins(); fclose(in);
	in=fopen("stopwords.txt","r");
	while (fscanf(in,"%s",r)!=EOF) del(); fclose(in);
	in=fopen("article1.txt","r");
	while (read()) count1(); fclose(in);
	in=fopen("article2.txt","r");
	while (read()) count2(); fclose(in);
	out=fopen("results.txt","w");
	solve(),print(),fclose(out);
	return 0;
}