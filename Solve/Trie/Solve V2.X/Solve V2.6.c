#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")

#include <stdio.h>
#include <string.h>

FILE *in,*out;
unsigned char ecl[3000010];
unsigned char buffer[10000100];
unsigned char r[50],s1[3000010][50],s2[3000010][50];
unsigned int fst1[30000],nxt1[3000010],fst2[30000],nxt2[3000010];
unsigned int pool,n,outlen,len1,len2,top1,top2,sum1,sum2,same1,same2;
struct {unsigned char flag; unsigned int con1,con2,s[26];} a[3000010];
unsigned char alpha[128]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,0,0,0,0,0};

void digit(unsigned int x)
{
	if (x>9) digit(x/10);
	buffer[outlen++]=x%10+'0';
	return;
}

void dfs(unsigned char pos,unsigned int num)
{
	for (register unsigned int i=25;i+1;i--)
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

int main()
{
	register unsigned int i,j,k,tmp=0;
	in=fopen("article1.txt","rb");
	n=fread(buffer,1,10000000,in); buffer[n]=0;
	for (i=0;buffer[i];i++)
	{
		if (('a'<=buffer[i] && buffer[i]<='z')
		|| ('A'<=buffer[i] && buffer[i]<='Z'))
		{
			if (!a[tmp].s[alpha[buffer[i]]])
			a[tmp].s[alpha[buffer[i]]]=++pool;
			tmp=a[tmp].s[alpha[buffer[i]]];
		}
		else if (tmp) a[tmp].con1++,tmp=0;
	}
	if (tmp) a[tmp].con1++;
	fclose(in);
	in=fopen("article2.txt","rb");
	n=fread(buffer,1,10000000,in); buffer[n]=0;
	for (i=0;buffer[i];i++)
	{
		if (('a'<=buffer[i] && buffer[i]<='z')
		|| ('A'<=buffer[i] && buffer[i]<='Z'))
		{
			if (!a[tmp].s[alpha[buffer[i]]])
			a[tmp].s[alpha[buffer[i]]]=++pool;
			tmp=a[tmp].s[alpha[buffer[i]]];
		}
		else if (tmp) a[tmp].con2++,tmp=0;
	}
	if (tmp) a[tmp].con2++;
	fclose(in);
	in=fopen("stopwords.txt","rb");
	n=fread(buffer,1,10000000,in); buffer[n]=0;
	for (i=0;buffer[i];i++)
	{
		if (('a'<=buffer[i] && buffer[i]<='z')
		|| ('A'<=buffer[i] && buffer[i]<='Z'))
		{
			if (!a[tmp].s[alpha[buffer[i]]])
			{
				while (('a'<=buffer[i] && buffer[i]<='z')
				|| ('A'<=buffer[i] && buffer[i]<='Z')) i++;
				if (!buffer[i]) goto flagA;
				tmp=0; continue;
			}
			tmp=a[tmp].s[alpha[buffer[i]]];
		}
		else if (tmp) tmp=a[tmp].con1=a[tmp].con2=0;
	}
	if (tmp) a[tmp].con1=a[tmp].con2=0;
	flagA:
	fclose(in);
	in=fopen("dictionary.txt","rb");
	n=fread(buffer,1,10000000,in); buffer[n]=0;
	for (i=0;buffer[i];i++)
	{
		if (('a'<=buffer[i] && buffer[i]<='z')
		|| ('A'<=buffer[i] && buffer[i]<='Z'))
		{
			if (!a[tmp].s[alpha[buffer[i]]])
			{
				while (('a'<=buffer[i] && buffer[i]<='z')
				|| ('A'<=buffer[i] && buffer[i]<='Z')) i++;
				if (!buffer[i]) goto flagB;
				tmp=0; continue;
			}
			tmp=a[tmp].s[alpha[buffer[i]]];
		}
		else if (tmp) a[tmp].flag=1,tmp=0;
	}
	if (tmp) a[tmp].flag=1;
	flagB:
	fclose(in);
	dfs(0,0),scanf("%u",&n);
	if (n>len1) n=len1;
	if (n>len2) n=len2;
	buffer[outlen++]='\n';
	tmp=0; while (tmp<n)
	for (i=top1;i && tmp<n;i--)
	for (j=fst1[i];j && tmp<n;j=nxt1[j])
	{
		for (k=0;s1[j][k];k++)
		buffer[outlen++]=s1[j][k];
		buffer[outlen++]=32;
		digit(a[j].con1);
		buffer[outlen++]='\n';
		sum1+=a[j].con1;
		tmp++,ecl[j]=1;
	}
	buffer[outlen++]='\n';
	tmp=0; while (tmp<n)
	for (i=top2;i && tmp<n;i--)
	for (j=fst2[i];j && tmp<n;j=nxt2[j])
	{
		for (k=0;s2[j][k];k++)
		buffer[outlen++]=s2[j][k];
		buffer[outlen++]=32;
		digit(a[j].con2);
		buffer[outlen++]='\n';
		sum2+=a[j].con2,tmp++;
		if (ecl[j]) same1+=a[j].con1,same2+=a[j].con2;
	}
	out=fopen("results.txt","w");
	double pro1=(double)same1/(double)sum1;
	double pro2=(double)same2/(double)sum2;
	double ans=(pro1<pro2?pro1:pro2)/(pro1>pro2?pro1:pro2);
	printf("%.5lf\n",ans);
	fprintf(out,"%.5lf\n",ans);
	fwrite(buffer,1,outlen,out);
	fclose(out); return 0;
}