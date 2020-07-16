#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")

#include <stdio.h>

FILE *in,*out;
struct {unsigned int con1,con2,s[26];} a[3000010];
unsigned char ecl[3000010],buffer[10000100],write[100100];
unsigned int pool,n,outlen,len1,len2,top1,top2,sum1,sum2,same1,same2;
unsigned int s1[3000010],s2[3000010],fst1[30000],nxt1[3000010],fst2[30000],nxt2[3000010];
void printdigit(unsigned int x) {if (x>9) printdigit(x/10); write[outlen++]=x%10+'0'; return;}
unsigned char alpha[128]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,0,0,0,0,0};

int main()
{
	register unsigned int i,j,k,tmp;
	in=fopen("article1.txt","rb");
	n=fread(buffer,1,10000000,in); buffer[n]=0;
	for (tmp=0,i=n-1;i+1;i--)
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
	if (tmp) a[tmp].con1++; fclose(in);
	in=fopen("article2.txt","rb");
	n=fread(buffer,1,10000000,in); buffer[n]=0;
	for (tmp=0,i=n-1;i+1;i--)
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
	if (tmp) a[tmp].con2++; fclose(in);
	in=fopen("stopwords.txt","rb");
	n=fread(buffer,1,10000000,in); buffer[n]=0;
	for (tmp=0,i=n-1;i+1;i--)
	{
		if (('a'<=buffer[i] && buffer[i]<='z')
		|| ('A'<=buffer[i] && buffer[i]<='Z'))
		{
			if (!a[tmp].s[alpha[buffer[i]]])
			{
				while (('a'<=buffer[i] && buffer[i]<='z')
				|| ('A'<=buffer[i] && buffer[i]<='Z')) i--;
				tmp=0; continue;
			}
			tmp=a[tmp].s[alpha[buffer[i]]];
		}
		else if (tmp) tmp=a[tmp].con1=a[tmp].con2=0;
	}
	if (tmp) a[tmp].con1=a[tmp].con2=0;
	fclose(in); in=fopen("dictionary.txt","rb");
	n=fread(buffer,1,10000000,in); buffer[n]=0;
	for (tmp=0,i=n-1;i+1;i--)
	{
		if (('a'<=buffer[i] && buffer[i]<='z')
		|| ('A'<=buffer[i] && buffer[i]<='Z'))
		{
			if (!a[tmp].s[alpha[buffer[i]]])
			{
				while (('a'<=buffer[i] && buffer[i]<='z')
				|| ('A'<=buffer[i] && buffer[i]<='Z')) i--;
				tmp=0; continue;
			}
			tmp=a[tmp].s[alpha[buffer[i]]];
		}
		else if (tmp)
		{
			if (a[tmp].con1)
			{
				nxt1[tmp]=fst1[a[tmp].con1];
				fst1[a[tmp].con1]=tmp,s1[tmp]=i+1,len1++;
				if (a[tmp].con1>top1) top1=a[tmp].con1;
			}
			if (a[tmp].con2)
			{
				nxt2[tmp]=fst2[a[tmp].con2];
				fst2[a[tmp].con2]=tmp,s2[tmp]=i+1,len2++;
				if (a[tmp].con2>top2) top2=a[tmp].con2;
			}
			tmp=0;
		}
	}
	if (tmp)
	{
		if (a[tmp].con1)
		{
			nxt1[tmp]=fst1[a[tmp].con1];
			fst1[a[tmp].con1]=tmp,s1[tmp]=i+1,len1++;
			if (a[tmp].con1>top1) top1=a[tmp].con1;
		}
		if (a[tmp].con2)
		{
			nxt2[tmp]=fst2[a[tmp].con2];
			fst2[a[tmp].con2]=tmp,s2[tmp]=i+1,len2++;
			if (a[tmp].con2>top2) top2=a[tmp].con2;
		}
	}
	fclose(in),scanf("%u",&n);
	if (n>len1) n=len1; if (n>len2) n=len2;
	write[outlen++]='\n',tmp=0; while (tmp<n)
	for (i=top1;i && tmp<n;i--)
	for (j=fst1[i];j && tmp<n;j=nxt1[j])
	{
		for (k=s1[j];('a'<=buffer[k] && buffer[k]<='z')
		|| ('A'<=buffer[k] && buffer[k]<='Z');k++)
		write[outlen++]=buffer[k]; write[outlen++]=32;
		printdigit(a[j].con1),write[outlen++]='\n';
		sum1+=a[j].con1,tmp++,ecl[j]=1;
	}
	write[outlen++]='\n',tmp=0; while (tmp<n)
	for (i=top2;i && tmp<n;i--)
	for (j=fst2[i];j && tmp<n;j=nxt2[j])
	{
		for (k=s2[j];('a'<=buffer[k] && buffer[k]<='z')
		|| ('A'<=buffer[k] && buffer[k]<='Z');k++)
		write[outlen++]=buffer[k]; write[outlen++]=32;
		printdigit(a[j].con2),write[outlen++]='\n';
		if (ecl[j]) same1+=a[j].con1,same2+=a[j].con2;
		sum2+=a[j].con2,tmp++;
	}
	out=fopen("results.txt","w");
	double pro1=(double)same1/(double)sum1;
	double pro2=(double)same2/(double)sum2;
	double ans=(pro1<pro2?pro1:pro2)/(pro1>pro2?pro1:pro2);
	printf("%.5lf\n",ans);
	fprintf(out,"%.5lf\n",ans);
	fwrite(write,1,outlen,out);
	fclose(out); return 0;
}