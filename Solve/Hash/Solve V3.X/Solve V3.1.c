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

typedef struct {unsigned char *s; unsigned int con1,con2;} stu; stu a[500000];
unsigned char art1[10000000],art2[10000000],buffer[10000000],*s1[500000],*s2[500000];
inline int smp(unsigned char* a,unsigned char* b) {while (!(*a-*b) && *b) a++,b++; return *a==*b;}
unsigned int tot,len1,len2,top1,top2,vis[500000],src[524300],dst[500000],fst1[40000],nxt1[500000],fst2[40000],nxt2[500000];
unsigned char alpha[260]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

int read()
{
	register int q=0;
	register char c=getchar();
	while (c>='0' && c<='9')
	q=(q<<3)+(q<<1)+(c^48),
	c=getchar(); return q;
}

void print(unsigned int x)
{
	if (x>9) print(x/10);
	buffer[tot++]=x%10^'0';
	return;
}

int main()
{
	register unsigned char* pos;
	unsigned int n,sum1=0,sum2=0,same1=0,same2=0;
	FILE *in,*out; register unsigned int i,j,k,tmp=0;
	in=fopen("article1.txt","rb");
	n=fread(art1+1,1,10000000,in); art1[n+1]=0;
	i=n+1; while (i)
	{
		while (i && !alpha[art1[i]]) --i; k=art1[i+1]=0;
		while (alpha[art1[i]]) k=k*65599+(art1[i--]|=32);
		pos=&art1[i+1],k&=524287;
		for (j=src[k];j;j=dst[j])
		{
			if (smp(a[j].s,pos))
			{a[j].con1++,pos=NULL; break;}
		}
		if (!pos) continue;
		a[++tmp].s=pos,dst[tmp]=src[k];
		src[k]=tmp,a[tmp].con1++;
	}
	fclose(in),in=fopen("article2.txt","rb");
	n=fread(art2+1,1,10000000,in); art2[n+1]=0;
	i=n+1; while (i)
	{
		while (i && !alpha[art2[i]]) --i; k=art2[i+1]=0;
		while (alpha[art2[i]]) k=k*65599+(art2[i--]|=32);
		pos=&art2[i+1],k&=524287;
		for (j=src[k];j;j=dst[j])
		{
			if (smp(a[j].s,pos))
			{a[j].con2++,pos=NULL; break;}
		}
		if (!pos) continue;
		a[++tmp].s=pos,dst[tmp]=src[k];
		src[k]=tmp,a[tmp].con2++;
	}
	fclose(in),in=fopen("stopwords.txt","rb");
	n=fread(buffer+1,1,10000000,in); buffer[n+1]=0;
	i=n; while (buffer[i])
	{
		while (!alpha[buffer[i]]) --i; k=buffer[i+1]=0;
		while (alpha[buffer[i]]) k=k*65599+(buffer[i--]|=32);
		pos=&buffer[i+1],k&=524287;
		for (j=src[k];j;j=dst[j])
		{
			if (smp(a[j].s,pos))
			{a[j].con1=a[j].con2=0; break;}
		}
	}
	fclose(in),in=fopen("dictionary.txt","rb");
	n=fread(buffer+1,1,10000000,in); buffer[n+1]=0;
	i=n,tmp=0; while (buffer[i])
	{
		while (!alpha[buffer[i]]) --i; k=buffer[i+1]=0;
		while (alpha[buffer[i]]) k=k*65599+(buffer[i--]|=32);
		pos=&buffer[i+1],k&=524287;
		for (j=src[k];j;j=dst[j])
		if (smp(a[j].s,pos))
		{
			++tmp;
			if (a[j].con1)
			{
				nxt1[tmp]=fst1[a[j].con1],fst1[a[j].con1]=tmp;
				s1[tmp]=a[j].s,len1++; if (a[j].con1>top1) top1=a[j].con1;
			}
			if (a[j].con2)
			{
				nxt2[tmp]=fst2[a[j].con2],fst2[a[j].con2]=tmp;
				s2[tmp]=a[j].s,len2++; if (a[j].con2>top2) top2=a[j].con2;
			}
			break;
		}
	}
	fclose(in),n=read(),buffer[tot++]='\n';
	if (n>len1) n=len1; if (n>len2) n=len2;
	k=0; while (k<n)
	for (i=top1;i && k<n;i--)
	for (j=fst1[i];j && k<n;j=nxt1[j])
	{
		pos=s1[j]; while (*pos) buffer[tot++]=*pos++;
		buffer[tot++]=32,print(i),buffer[tot++]='\n';
		sum1+=i,k++,vis[j]=i;
	}
	buffer[tot++]='\n';
	k=0; while (k<n)
	for (i=top2;i && k<n;i--)
	for (j=fst2[i];j && k<n;j=nxt2[j])
	{
		pos=s2[j]; while (*pos) buffer[tot++]=*pos++;
		buffer[tot++]=32,print(i),buffer[tot++]='\n';
		sum2+=i,k++; if (vis[j]) same1+=vis[j],same2+=i;
	}
	out=fopen("results.txt","w");
	double pro1=(double)same1/(double)sum1;
	double pro2=(double)same2/(double)sum2;
	double ans=(pro1<pro2?pro1:pro2)/(pro1>pro2?pro1:pro2);
	printf("%.5lf\n",ans),fprintf(out,"%.5lf\n",ans);
	fwrite(buffer,1,tot,out);
	fclose(out); return 0;
}