#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))

FILE *in,*out; char r[50]; int len1,len2,fst[33554500],nxt[500000];
typedef struct base {char s[50]; int con1,con2;} stu; stu a[500000];
typedef struct {int num; char s[50];} dic; dic in1[500000],in2[500000],cpy1[500000],cpy2[500000];

int read()
{
	int cnt=0;
	char c=(fgetc(in)|32);
	if (c==EOF) return 0;
	while (!(97<=c && c<=122))
	{
		c=(fgetc(in)|32);
		if (c==EOF) return 0;
	}
	while (97<=c && c<=122)
	{
		r[cnt++]=c;
		c=(fgetc(in)|32);
	}
	r[cnt]=0; return 1;
}

//MineHash
int hash(char *s)
{
	register unsigned int ans=0;
	while (*s) ans=(ans<<6)-ans+*s++;
	return ans&33554431;
}

void ready()
{
	int num; register int tmp,i=0;
	in=fopen("article1.txt","r");
	while (read())
	{
		num=hash(r);
		for (tmp=fst[num];tmp;tmp=nxt[tmp])
		{
			if (strcmp(a[tmp].s,r)==0)
			{a[tmp].con1++,r[0]=0; break;}
		}
		if (!r[0]) continue;
		strcpy(a[++i].s,r);
		nxt[i]=fst[num];
		fst[num]=i,a[i].con1++;
	}
	fclose(in);
	in=fopen("article2.txt","r");
	while (read())
	{
		num=hash(r);
		for (tmp=fst[num];tmp;tmp=nxt[tmp])
		{
			if (strcmp(a[tmp].s,r)==0)
			{a[tmp].con2++,r[0]=0; break;}
		}
		if (!r[0]) continue;
		strcpy(a[++i].s,r);
		nxt[i]=fst[num];
		fst[num]=i,a[i].con2++;
	}
	fclose(in);
	in=fopen("stopwords.txt","r");
	while (fscanf(in,"%s",r)!=EOF)
	{
		num=hash(r);
		for (i=fst[num];i;i=nxt[i])
		{
			if (strcmp(a[i].s,r)==0)
			{a[i].con1=a[i].con2=0; break;}
		}
	}
	fclose(in);
	in=fopen("dictionary.txt","r");
	while (fscanf(in,"%s",r)!=EOF)
	{
		num=hash(r);
		for (i=fst[num];i;i=nxt[i])
		{
			if (strcmp(a[i].s,r)==0)
			{
				if (a[i].con1)
				{
					in1[len1].num=a[i].con1;
					strcpy(in1[len1++].s,a[i].s);
				}
				if (a[i].con2)
				{
					in2[len2].num=a[i].con2;
					strcpy(in2[len2++].s,a[i].s);
				}
				break;
			}
		}
	}
	fclose(in); return;
}

int cmp1(const void *a,const void *b)
{
	if (((dic*)a)->num<((dic*)b)->num) return 1;
	if (((dic*)a)->num>((dic*)b)->num) return -1;
	return strcmp(((dic*)a)->s,((dic*)b)->s);
}

int cmp2(const void *a,const void *b)
{return strcmp(((dic*)a)->s,((dic*)b)->s);}

void goooo()
{
	int n; register int i,j,tmp;
	int sum1=0,sum2=0,sam1=0,sam2=0;
	scanf("%d",&n),n=min(min(n,len1),len2);
	qsort(in1,len1,sizeof(dic),cmp1);
	qsort(in2,len2,sizeof(dic),cmp1);
	for (int i=0;i<n;i++) cpy1[i]=in1[i],sum1+=in1[i].num;
	for (int i=0;i<n;i++) cpy2[i]=in2[i],sum2+=in2[i].num;
	qsort(cpy1,n,sizeof(dic),cmp2);
	qsort(cpy2,n,sizeof(dic),cmp2);
	i=j=0; while (i<n && j<n)
	{
		tmp=strcmp(cpy1[i].s,cpy2[j].s);
		if (tmp<0) i++; else if (tmp>0) j++;
		else sam1+=cpy1[i].num,sam2+=cpy2[j].num,i++,j++;
	}
	out=fopen("results.txt","w");
	double pro1=(double)sam1/(double)sum1;
	double pro2=(double)sam2/(double)sum2;
	double ans=min(pro1,pro2)/max(pro1,pro2);
	printf("%.5lf\n",ans),fprintf(out,"%.5lf\n",ans);
	fputc('\n',in); for (int i=0;i<n;i++)
	fprintf(out,"%s %d\n",in1[i].s,in1[i].num);
	fputc('\n',in); for (int i=0;i<n;i++)
	fprintf(out,"%s %d\n",in2[i].s,in2[i].num);
	fclose(out); return;
}

int main()
{
	ready();
	goooo();
	return 0;
}