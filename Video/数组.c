#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ri register int

FILE *in,*out;
char newword[50];
int topdict,topstop,topart1,topart2,n,which;
typedef struct
{
	char s[50];
	int art1,art2;
} word;
word dict[500000],stop[1000];
word article1[500000],article2[500000];
word beifen1[500000],beifen2[500000];

inline double max(double a,double b)
{return a>b?a:b;}

inline double min(double a,double b)
{return a<b?a:b;}

int read()
{
	int len=0;
	char c=(fgetc(in)|32);
	if (c==EOF) return 0;
	while (!('a'<=c && c<='z'))
	{
		c=(fgetc(in)|32);
		if (c==EOF) return 0;
	}
	while ('a'<=c && c<='z')
	{
		newword[len++]=c;
		c=(fgetc(in)|32);
	}
	newword[len]=0;
	return 1;
}

int change(word in[],char flag)
{
	int l=0,mid,tmp,r=flag?topdict:topstop;
	while (l<=r)
	{
		mid=(l+r)>>1;
		tmp=strcmp(newword,in[mid].s);
		if (tmp>0) l=mid+1;
		else if (tmp<0) r=mid-1;
		else if (!flag) return 1;
		else if (!which)
		{
			++in[mid].art1;
			return 1;
		}
		else
		{
			++in[mid].art2;
			return 1;
		}
	}
	return 0;
}

int cmp(const void *a,const void *b)
{
	word *x=(word*)a,*y=(word*)b;
	if (which==1) return (y->art1-x->art1)?(y->art1-x->art1):strcmp(x->s,y->s);
	if (which==2) return (y->art2-x->art2)?(y->art2-x->art2):strcmp(x->s,y->s);
	return strcmp(x->s,y->s);
}

int main()
{
	in=fopen("dictionary.txt","r");
	while (~fscanf(in,"%s",dict[topdict++].s)); fclose(in);
	in=fopen("stopwords.txt","r");
	while (~fscanf(in,"%s",stop[topstop++].s)); fclose(in);
	which=0,in=fopen("article1.txt","r");
	while (read()) if (!change(stop,0)) change(dict,1); fclose(in);
	which=1,in=fopen("article2.txt","r");
	while (read()) if (!change(stop,0)) change(dict,1); fclose(in);
	for (ri i=0;i<topdict;++i)
	{
		if (dict[i].art1) article1[topart1++]=dict[i];
		if (dict[i].art2) article2[topart2++]=dict[i];
	}
	which=1,qsort(article1,topart1,sizeof(*article1),cmp);
	which=2,qsort(article2,topart2,sizeof(*article2),cmp);
	which=0,scanf("%d",&n);
	if (n>topart1) n=topart1;
	if (n>topart2) n=topart2;
	int same1=0,same2=0,con1=0,con2=0;
	for (ri i=0;i<n;i++)
	{
		beifen1[i]=article1[i],con1+=article1[i].art1;
		beifen2[i]=article2[i],con2+=article2[i].art2;
	}
	qsort(beifen1,n,sizeof(*beifen1),cmp);
	qsort(beifen2,n,sizeof(*beifen2),cmp);
	for (ri tmp,i=0,j=0;i<n && j<n;)
	{
		tmp=strcmp(beifen1[i].s,beifen2[j].s);
		if (!tmp)
		{
			same1+=beifen1[i].art1;
			same2+=beifen2[j].art2;
			++i,++j;
		}
		else if (tmp>0) ++j;
		else ++i;
	}
	out=fopen("results.txt","w");
	double pro1=1.0*same1/con1,pro2=1.0*same2/con2;
	double ans=min(pro1,pro2)/max(pro1,pro2);
	printf("%.5lf\n",ans),fprintf(out,"%.5lf\n",ans);
	fputc('\n',out);
	for (ri i=0;i<n;i++)
	fprintf(out,"%s %d\n",article1[i].s,article1[i].art1);
	fputc('\n',out);
	for (ri i=0;i<n;i++)
	fprintf(out,"%s %d\n",article2[i].s,article2[i].art2);
	fclose(out); return 0;
}