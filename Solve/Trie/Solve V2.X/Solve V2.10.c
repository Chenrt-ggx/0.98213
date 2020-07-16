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

struct {unsigned int con1,con2,s[26];} a[3000010];
unsigned char ecl[3000010],buffer[8000100],print[100100];
unsigned int outlen,len1,len2,top1,top2,s1[3000010],fst1[40000],lst1[40000],nxt1[3000010],s2[3000010],fst2[40000],lst2[40000],nxt2[3000010];
unsigned char ascii[260]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
unsigned char alpha[260]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};

int read()
{
	register int q=0; register char c=getchar();
	while (c>='0' && c<='9') q=(q<<3)+(q<<1)+(c^48),
	c=getchar(); return q;
}

void digit(unsigned int x)
{
	if (x>9) digit(x/10);
	print[outlen++]=x%10+'0';
	return;
}

int main()
{
	register unsigned int tmp,n,i,j,k=0;
	FILE *in,*out; int sum1=0,sum2=0,same1=0,same2=0;
	in=fopen("article1.txt","rb");
	n=fread(buffer,1,8000000,in); buffer[n]=0;
	tmp=i=0; while (buffer[i])
	{
		while (ascii[buffer[i]])
		{
			if (!a[tmp].s[alpha[buffer[i]]])
			a[tmp].s[alpha[buffer[i]]]=++k;
			tmp=a[tmp].s[alpha[buffer[i++]]];
		}
		a[tmp].con1++,tmp=0;
		while (buffer[i] && !ascii[buffer[i]]) ++i;
	}
	fclose(in),in=fopen("article2.txt","rb");
	n=fread(buffer,1,8000000,in); buffer[n]=0;
	tmp=i=0; while (buffer[i])
	{
		while (ascii[buffer[i]])
		{
			if (!a[tmp].s[alpha[buffer[i]]])
			a[tmp].s[alpha[buffer[i]]]=++k;
			tmp=a[tmp].s[alpha[buffer[i++]]];
		}
		a[tmp].con2++,tmp=0;
		while (buffer[i] && !ascii[buffer[i]]) ++i;
	}
	fclose(in),in=fopen("stopwords.txt","rb");
	n=fread(buffer,1,8000000,in); buffer[n]=0;
	tmp=i=0; while (buffer[i])
	{
		while (ascii[buffer[i]])
		{
			if (!a[tmp].s[alpha[buffer[i]]])
			{
				while (ascii[buffer[i]])
				++i; tmp=0; break;
			}
			tmp=a[tmp].s[alpha[buffer[i++]]];
		}
		if (tmp) tmp=a[tmp].con1=a[tmp].con2=0;
		while (buffer[i] && !ascii[buffer[i]]) ++i;
	}
	fclose(in),in=fopen("dictionary.txt","rb");
	n=fread(buffer,1,8000000,in); buffer[n]=0;
	k=tmp=i=0; while (buffer[i])
	{
		k=i; while (ascii[buffer[i]])
		{
			if (!a[tmp].s[alpha[buffer[i]]])
			{
				while (ascii[buffer[i]])
				++i; tmp=0; break;
			}
			tmp=a[tmp].s[alpha[buffer[i++]]];
		}
		if (tmp)
		{
			if (a[tmp].con1)
			{
				if (!fst1[a[tmp].con1]) fst1[a[tmp].con1]=tmp;
				nxt1[lst1[a[tmp].con1]]=tmp,lst1[a[tmp].con1]=tmp;
				s1[tmp]=k,len1++; if (a[tmp].con1>top1) top1=a[tmp].con1;
			}
			if (a[tmp].con2)
			{
				if (!fst2[a[tmp].con2]) fst2[a[tmp].con2]=tmp;
				nxt2[lst2[a[tmp].con2]]=tmp,lst2[a[tmp].con2]=tmp;
				s2[tmp]=k,len2++; if (a[tmp].con2>top2) top2=a[tmp].con2;
			}
			tmp=0;
		}
		while (buffer[i] && !ascii[buffer[i]]) ++i;
	}
	fclose(in),n=read();
	if (n>len1) n=len1;
	if (n>len2) n=len2;
	print[outlen++]='\n';
	tmp=0; while (tmp<n)
	for (i=top1;i && tmp<n;i--)
	for (j=fst1[i];j && tmp<n;j=nxt1[j])
	{
		for (k=s1[j];ascii[buffer[k]];k++)
		print[outlen++]=buffer[k]; print[outlen++]=32;
		digit(a[j].con1),print[outlen++]='\n';
		sum1+=a[j].con1,tmp++,ecl[j]=1;
	}
	print[outlen++]='\n';
	tmp=0; while (tmp<n)
	for (i=top2;i && tmp<n;i--)
	for (j=fst2[i];j && tmp<n;j=nxt2[j])
	{
		for (k=s2[j];ascii[buffer[k]];k++)
		print[outlen++]=buffer[k]; print[outlen++]=32;
		digit(a[j].con2),print[outlen++]='\n',sum2+=a[j].con2,tmp++;
		if (ecl[j]) same1+=a[j].con1,same2+=a[j].con2;
	}
	out=fopen("results.txt","w");
	double pro1=(double)same1/(double)sum1;
	double pro2=(double)same2/(double)sum2;
	double ans=(pro1<pro2?pro1:pro2)/(pro1>pro2?pro1:pro2);
	printf("%.5lf\n",ans);
	fprintf(out,"%.5lf\n",ans);
	fwrite(print,1,outlen,out);
	fclose(out); return 0;
}