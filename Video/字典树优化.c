#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <stdio.h>

typedef struct
{
	unsigned int s[26];
	unsigned int con1,con2;
} stu;
stu pol[500000];
unsigned char *s1[500000],*s2[500000];
unsigned char buffer[10000000],print[100000];
unsigned int tot,len1,len2,top1,top2,vis[500000];
unsigned int fst1[40000],lst1[40000],nxt1[500000],fst2[40000],lst2[40000],nxt2[500000];

int read()
{
	unsigned int ans=0;
	char c=getchar();
	while ('0'<=c && c<='9')
	{
		ans=(ans<<3)+(ans<<1)+(c^48);
		c=getchar();
	}
	return ans;
}

void printdigit(unsigned int x)
{
	if (x>9) printdigit(x/10);
	print[tot++]=x%10^48;
	return;
}

int main()
{
	FILE *in,*out;
	register unsigned char* pos;
	unsigned int n,i,j,k=0,same1=0,same2=0,con1=0,con2=0;
	const unsigned char ascii[260]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	const unsigned char alpha[260]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
	in=fopen("article1.txt","rb");
	n=fread(buffer,1,10000000,in);
	for (buffer[n]=i=j=0;buffer[i];)
	{
		while (ascii[buffer[i]])
		{
			if (!pol[j].s[alpha[buffer[i]]])
			pol[j].s[alpha[buffer[i]]]=++k;
			j=pol[j].s[alpha[buffer[i++]]];
		}
		pol[j].con1++,j=0;
		while (buffer[i] && !ascii[buffer[i]]) ++i;
	}
	fclose(in);
	in=fopen("article2.txt","rb");
	n=fread(buffer,1,10000000,in);
	for (buffer[n]=i=j=0;buffer[i];)
	{
		while (ascii[buffer[i]])
		{
			if (!pol[j].s[alpha[buffer[i]]])
			pol[j].s[alpha[buffer[i]]]=++k;
			j=pol[j].s[alpha[buffer[i++]]];
		}
		pol[j].con2++,j=0;
		while (buffer[i] && !ascii[buffer[i]]) ++i;
	}
	fclose(in);
	in=fopen("stopwords.txt","rb");
	n=fread(buffer,1,10000000,in);
	for (buffer[n]=i=j=0;buffer[i];)
	{
		while (ascii[buffer[i]])
		{
			if (!pol[j].s[alpha[buffer[i]]])
			{
				while (ascii[buffer[i]]) ++i;
				j=0; break;
			}
			j=pol[j].s[alpha[buffer[i++]]];
		}
		if (j) j=pol[j].con1=pol[j].con2=0;
		while (buffer[i] && !ascii[buffer[i]]) ++i;
	}
	fclose(in);
	in=fopen("dictionary.txt","rb");
	n=fread(buffer,1,10000000,in);
	for (buffer[n]=i=j=0;buffer[i];)
	{
		pos=&buffer[i];
		while (ascii[buffer[i]])
		{
			if (!pol[j].s[alpha[buffer[i]]])
			{
				while (ascii[buffer[i]]) ++i;
				j=0; break;
			}
			j=pol[j].s[alpha[buffer[i++]]];
		}
		if (j)
		{
			if (pol[j].con1)
			{
				nxt1[lst1[pol[j].con1]]=j;
				lst1[pol[j].con1]=j;
				s1[j]=pos,len1++;
				if (pol[j].con1>top1) top1=pol[j].con1;
				if (!fst1[pol[j].con1]) fst1[pol[j].con1]=j;
			}
			if (pol[j].con2)
			{
				nxt2[lst2[pol[j].con2]]=j;
				lst2[pol[j].con2]=j;
				s2[j]=pos,len2++;
				if (pol[j].con2>top2) top2=pol[j].con2;
				if (!fst2[pol[j].con2]) fst2[pol[j].con2]=j;
			}
			j=0;
		}
		while (buffer[i] && !ascii[buffer[i]]) ++i;
	}
	fclose(in);
	n=read();
	if (n>len1) n=len1;
	if (n>len2) n=len2;
	print[tot++]='\n';
	for (i=top1,k=0;i && k<n;--i)
	{
		for (j=fst1[i];j && k<n;j=nxt1[j])
		{
			pos=s1[j];
			while (ascii[*pos]) print[tot++]=*pos++;
			print[tot++]=32;
			printdigit(i);
			print[tot++]='\n';
			con1+=i,k++,vis[j]=i;
		}
	}
	print[tot++]='\n';
	for (i=top2,k=0;i && k<n;--i)
	{
		for (j=fst2[i];j && k<n;j=nxt2[j])
		{
			pos=s2[j];
			while (ascii[*pos]) print[tot++]=*pos++;
			print[tot++]=32;
			printdigit(i);
			print[tot++]='\n';
			con2+=i,k++;
			if (vis[j])
			{
				same1+=vis[j];
				same2+=i;
			}
		}
	}
	out=fopen("results.txt","w");
	double pro1=1.0*same1/con1,pro2=1.0*same2/con2;
	double ans=(pro1<pro2?pro1:pro2)/(pro1>pro2?pro1:pro2);
	printf("%.5lf\n",ans),fprintf(out,"%.5lf\n",ans);
	fwrite(print,1,tot,out),fclose(out);
	return 0;
}