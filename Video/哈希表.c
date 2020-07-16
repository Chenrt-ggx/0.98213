#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ri register int

FILE *in,*out;
char newword[50];
typedef struct
{
	char s[50];
	int con1,con2;
} stu;
stu pol[500000];
typedef struct
{
	int num;
	char s[50];
} word;
word article1[500000],article2[500000];
word beifen1[500000],beifen2[500000];
int n,tot,topart1,topart2;
int fst[8400000],nxt[500000];

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

int hash(char* s)
{
	register unsigned int ans=0;
	while (*s) ans=(ans<<6)-ans+*s++;
	return ans&8388607;
}

int cmp1(const void *a,const void *b)
{
	if (((word*)b)->num-((word*)a)->num)
		return ((word*)b)->num-((word*)a)->num;
	return strcmp(((word*)a)->s,((word*)b)->s);
}

int cmp2(const void *a,const void *b)
{
	return strcmp(((word*)a)->s,((word*)b)->s);
}

int main()
{
	int num,tmp;
	in=fopen("article1.txt","r");
	while (read())
	{
		num=hash(newword);
		for (tmp=fst[num];tmp;tmp=nxt[tmp])
		{
			if (strcmp(pol[tmp].s,newword)==0)
			{
				pol[tmp].con1++;
				newword[0]=0;
				break;
			}
		}
		if (!newword[0]) continue;
		strcpy(pol[++tot].s,newword);
		nxt[tot]=fst[num];
		fst[num]=tot,pol[tot].con1++;
	}
	fclose(in);
	in=fopen("article2.txt","r");
	while (read())
	{
		num=hash(newword);
		for (tmp=fst[num];tmp;tmp=nxt[tmp])
		{
			if (strcmp(pol[tmp].s,newword)==0)
			{
				pol[tmp].con2++;
				newword[0]=0;
				break;
			}
		}
		if (!newword[0]) continue;
		strcpy(pol[++tot].s,newword);
		nxt[tot]=fst[num];
		fst[num]=tot,pol[tot].con2++;
	}
	fclose(in);
	in=fopen("stopwords.txt","r");
	while (~fscanf(in,"%s",newword))
	{
		num=hash(newword);
		for (tmp=fst[num];tmp;tmp=nxt[tmp])
		{
			if (strcmp(pol[tmp].s,newword)==0)
			{
				pol[tmp].con1=pol[tmp].con2=0;
				break;
			}
		}
	}
	fclose(in);
	in=fopen("dictionary.txt","r");
	while (~fscanf(in,"%s",newword))
	{
		num=hash(newword);
		for (tmp=fst[num];tmp;tmp=nxt[tmp])
		{
			if (strcmp(pol[tmp].s,newword)==0)
			{
				if (pol[tmp].con1)
				{
					article1[topart1].num=pol[tmp].con1;
					strcpy(article1[topart1++].s,pol[tmp].s);
				}
				if (pol[tmp].con2)
				{
					article2[topart2].num=pol[tmp].con2;
					strcpy(article2[topart2++].s,pol[tmp].s);
				}
				break;
			}
		}
	}
	fclose(in);
	scanf("%d",&n);
	if (n>topart1) n=topart1;
	if (n>topart2) n=topart2;
	int same1=0,same2=0,con1=0,con2=0;
	qsort(article1,topart1,sizeof(word),cmp1);
	qsort(article2,topart2,sizeof(word),cmp1);
	for (int i=0;i<n;i++)
	{
		beifen1[i]=article1[i],con1+=article1[i].num;
		beifen2[i]=article2[i],con2+=article2[i].num;
	}
	qsort(beifen1,n,sizeof(word),cmp2);
	qsort(beifen2,n,sizeof(word),cmp2);
	for (ri i=0,j=0;i<n && j<n;)
	{
		tmp=strcmp(beifen1[i].s,beifen2[j].s);
		if (!tmp)
		{
			same1+=beifen1[i].num;
			same2+=beifen2[j].num;
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
	fprintf(out,"%s %d\n",article1[i].s,article1[i].num);
	fputc('\n',out);
	for (ri i=0;i<n;i++)
	fprintf(out,"%s %d\n",article2[i].s,article2[i].num);
	fclose(in); return 0;
}