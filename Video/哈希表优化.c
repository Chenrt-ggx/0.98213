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
	unsigned char *s;
	unsigned int con1,con2;
} stu;
stu pol[500000];
unsigned char *s1[500000],*s2[500000];
unsigned char art1[10000000],art2[10000000],buffer[10000000];
unsigned int tot,len1,len2,top1,top2,vis[500000],src[524300],dst[500000];
unsigned int fst1[40000],lst1[40000],nxt1[500000],fst2[40000],lst2[40000],nxt2[500000];
unsigned char alpha[260]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

inline int smp(unsigned char* a,unsigned char* b)
{
	while (!(*a-*b) && *b) a++,b++;
	return *a==*b;
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
	buffer[tot++]=x%10^48;
	return;
}

int main()
{
	FILE *in,*out;
	register unsigned char* pos;
	unsigned int n,i,j,k,tmp=0,same1=0,same2=0,con1=0,con2=0;
	in=fopen("article1.txt","rb");
	n=fread(art1,1,10000000,in);
	art1[n]=i=0;
	while (art1[i] && !alpha[art1[i]]) ++i;
	while (art1[i])
	{
		pos=&art1[i],k=0;
		while (alpha[art1[i]])
		k=k*13131+(art1[i++]|=32);
		art1[i++]=0,k&=524287;
		while (art1[i] && !alpha[art1[i]]) ++i;
		for (j=src[k];j;j=dst[j])
		{
			if (smp(pol[j].s,pos))
			{
				pol[j].con1++;
				pos=NULL;
				break;
			}
		}
		if (!pos) continue;
		pol[++tmp].s=pos;
		pol[tmp].con1++;
		dst[tmp]=src[k];
		src[k]=tmp;
	}
	fclose(in);
	in=fopen("article2.txt","rb");
	n=fread(art2,1,10000000,in);
	art2[n]=i=0;
	while (art2[i] && !alpha[art2[i]]) ++i;
	while (art2[i])
	{
		pos=&art2[i],k=0;
		while (alpha[art2[i]])
		k=k*13131+(art2[i++]|=32);
		art2[i++]=0,k&=524287;
		while (art2[i] && !alpha[art2[i]]) ++i;
		for (j=src[k];j;j=dst[j])
		{
			if (smp(pol[j].s,pos))
			{
				pol[j].con2++;
				pos=NULL;
				break;
			}
		}
		if (!pos) continue;
		pol[++tmp].s=pos;
		pol[tmp].con2++;
		dst[tmp]=src[k];
		src[k]=tmp;
	}
	fclose(in);
	in=fopen("stopwords.txt","rb");
	n=fread(buffer,1,10000000,in);
	for (i=buffer[n]=0;buffer[i];)
	{
		pos=&buffer[i],k=0;
		while (alpha[buffer[i]])
		k=k*13131+buffer[i++];
		buffer[i++]=0,k&=524287;
		while (buffer[i] && !alpha[buffer[i]]) ++i;
		for (j=src[k];j;j=dst[j])
		{
			if (smp(pol[j].s,pos))
			{
				pol[j].con1=0;
				pol[j].con2=0;
				break;
			}
		}
	}
	fclose(in);
	in=fopen("dictionary.txt","rb");
	n=fread(buffer,1,10000000,in);
	for (tmp=i=buffer[n]=0;buffer[i];)
	{
		pos=&buffer[i],k=0;
		while (alpha[buffer[i]])
		k=k*13131+buffer[i++];
		buffer[i++]=0,k&=524287;
		while (buffer[i] && !alpha[buffer[i]]) ++i;
		for (j=src[k];j;j=dst[j])
		{
			if (smp(pol[j].s,pos))
			{
				++tmp;
				if (pol[j].con1)
				{
					nxt1[lst1[pol[j].con1]]=tmp;
					lst1[pol[j].con1]=tmp;
					s1[tmp]=pol[j].s,len1++;
					if (pol[j].con1>top1) top1=pol[j].con1;
					if (!fst1[pol[j].con1]) fst1[pol[j].con1]=tmp;
				}
				if (pol[j].con2)
				{
					nxt2[lst2[pol[j].con2]]=tmp;
					lst2[pol[j].con2]=tmp;
					s2[tmp]=pol[j].s,len2++;
					if (pol[j].con2>top2) top2=pol[j].con2;
					if (!fst2[pol[j].con2]) fst2[pol[j].con2]=tmp;
				}
				break;
			}
		}
	}
	fclose(in);
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
	fwrite(buffer,1,tot,out),fclose(out);
	return 0;
}