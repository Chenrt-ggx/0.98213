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

struct
{
	unsigned char* s;
	unsigned int art1,art2;
} dict[500000];
unsigned char *s1[500000],*s2[500000];
unsigned char dictionary[10000000],del[100000],buffer[10000000],*stop[1000];
unsigned int nxt1[500000],nxt2[500000],vis[500000];
unsigned int tot,len1,len2,top1,top2,topdict,topstop,fst1[40000],fst2[40000];
unsigned char alpha[260]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

inline int smp(unsigned char* a,unsigned char* b)
{
	while (!(*a-*b) && *b) a++,b++;
	return *a-*b;
}

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
	buffer[tot++]=x%10^'0';
	return;
}

int main()
{
	FILE *in,*out;
	unsigned char* pos;
	unsigned int i,j,k,mid; int tmp;
	unsigned int n,same1=0,same2=0,con1=0,con2=0;
	in=fopen("dictionary.txt","rb");
	n=fread(dictionary,1,10000000,in);
	dictionary[n]=0;
	for (i=0;dictionary[i];)
	{
		pos=&dictionary[i];
		while (alpha[dictionary[i]]) ++i;
		dictionary[i++]=0;
		dict[topdict++].s=pos;
		while (dictionary[i] && !alpha[dictionary[i]]) ++i;
	}
	fclose(in);
	in=fopen("stopwords.txt","rb");
	n=fread(del,1,100000,in);
	del[n]=0;
	for (i=0;del[i];)
	{
		pos=&del[i];
		while (alpha[del[i]]) ++i;
		del[i++]=0;
		stop[topstop++]=pos;
		while (del[i] && !alpha[del[i]]) ++i;
	}
	fclose(in);
	in=fopen("article1.txt","rb");
	n=fread(buffer,1,10000000,in);
	buffer[n]=i=0;
	while (buffer[i] && !alpha[buffer[i]]) ++i;
	while (buffer[i])
	{
		pos=&buffer[i];
		while (alpha[buffer[i]]) buffer[i++]|=32;
		buffer[i++]=0;
		while (buffer[i] && !alpha[buffer[i]]) ++i;
		j=0,k=topstop-1;
		while (j<=k)
		{
			mid=(j+k)>>1;
			tmp=smp(pos,stop[mid]);
			if (tmp>0) j=mid+1;
			else if (tmp<0) k=mid-1;
			else
			{
				pos=NULL;
				break;
			}
		}
		if (!pos) continue;
		j=0,k=topdict-1;
		while (j<=k)
		{
			mid=(j+k)>>1;
			tmp=smp(pos,dict[mid].s);
			if (tmp>0) j=mid+1;
			else if (tmp<0) k=mid-1;
			else
			{
				++dict[mid].art1;
				break;
			}
		}
	}
	fclose(in);
	in=fopen("article2.txt","rb");
	n=fread(buffer,1,10000000,in);
	buffer[n]=i=0;
	while (buffer[i] && !alpha[buffer[i]]) ++i;
	while (buffer[i])
	{
		pos=&buffer[i];
		while (alpha[buffer[i]]) buffer[i++]|=32;
		buffer[i++]=0;
		while (buffer[i] && !alpha[buffer[i]]) ++i;
		j=0,k=topstop-1;
		while (j<=k)
		{
			mid=(j+k)>>1;
			tmp=smp(pos,stop[mid]);
			if (tmp>0) j=mid+1;
			else if (tmp<0) k=mid-1;
			else
			{
				pos=NULL;
				break;
			}
		}
		if (!pos) continue;
		j=0,k=topdict-1;
		while (j<=k)
		{
			mid=(j+k)>>1;
			tmp=smp(pos,dict[mid].s);
			if (tmp>0) j=mid+1;
			else if (tmp<0) k=mid-1;
			else
			{
				++dict[mid].art2;
				break;
			}
		}
	}
	fclose(in);
	for (i=topdict-1;i+1;i--)
	{
		if (dict[i].art1)
		{
			nxt1[i]=fst1[dict[i].art1];
			fst1[dict[i].art1]=i;
			s1[i]=dict[i].s; len1++;
			if (dict[i].art1>top1) top1=dict[i].art1;
		}
		if (dict[i].art2)
		{
			nxt2[i]=fst2[dict[i].art2];
			fst2[dict[i].art2]=i;
			s2[i]=dict[i].s; len2++;
			if (dict[i].art2>top2) top2=dict[i].art2;
		}
	}
	n=read();
	if (n>len1) n=len1;
	if (n>len2) n=len2;
	buffer[tot++]='\n';
	for (i=top1,k=0;i && k<n;--i)
	{
		for (j=fst1[i];j && k<n;j=nxt1[j])
		{
			pos=s1[j];
			while (*pos) buffer[tot++]=*pos++;
			buffer[tot++]=32;
			printdigit(i);
			buffer[tot++]='\n';
			con1+=i,k++,vis[j]=i;
		}
	}
	buffer[tot++]='\n';
	for (i=top2,k=0;i && k<n;--i)
	{
		for (j=fst2[i];j && k<n;j=nxt2[j])
		{
			pos=s2[j];
			while (*pos) buffer[tot++]=*pos++;
			buffer[tot++]=32;
			printdigit(i);
			buffer[tot++]='\n';
			con2+=i,k++;
			if (vis[j]) same1+=vis[j],same2+=i;
		}
	}
	out=fopen("results.txt","w");
	double pro1=1.0*same1/con1,pro2=1.0*same2/con2;
	double ans=(pro1<pro2?pro1:pro2)/(pro1>pro2?pro1:pro2);
	printf("%.5lf\n",ans),fprintf(out,"%.5lf\n",ans);
	fwrite(buffer,1,tot,out),fclose(out);
	return 0;
}