#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tree
{
	int flag,con[2];
	struct tree *s[26];
};

typedef struct tree stu;
typedef struct tree* ptr;
typedef struct {int num; char s[50];} dict;

char r[50];
FILE *in,*out;
dict a[2][500000];
dict b[2][500000];
int n,same[2],sum[2],len[2];

double min(double a,double b) {return a<b?a:b;}
double max(double a,double b) {return a>b?a:b;}

ptr newnode()
{
	ptr p=(ptr)malloc(sizeof(stu));
	for (int i=0;i<26;i++) p->s[i]=NULL;
	p->flag=p->con[0]=p->con[1]=0;
	return p;
}

int read()
{
	int cnt=0;
	memset(r,0,sizeof(r));
	char c=fgetc(in);
	if (c==EOF) return 0;
	while (!isalpha(c))
	{
		c=fgetc(in);
		if (c==EOF)
		return 0;
	}
	while (isalpha(c))
	{
		r[cnt++]=c;
		c=fgetc(in);
	}
	return 1;
}

void ins(ptr head)
{
	int t;
	for (int i=0;r[i];i++)
	{
		t=tolower(r[i])-'a';
		if (head->s[t]==NULL)
		head->s[t]=newnode();
		head=head->s[t];
	}
	head->flag=1;
	return;
}

void del(ptr head)
{
	int t;
	for (int i=0;r[i];i++)
	{
		t=tolower(r[i])-'a';
		if (head->s[t]==NULL) return;
		else head=head->s[t];
	}
	head->flag=0;
	return;
}

void count(ptr head,int f)
{
	int t;
	for (int i=0;r[i];i++)
	{
		t=tolower(r[i])-'a';
		if (head->s[t]==NULL) return;
		else head=head->s[t];
	}
	if (head->flag)
	head->con[f]++;
	return;
}

void dfs(ptr head,int num)
{
	if (head==NULL) return;
	if (head->flag)
	{
		for (int i=0;i<2;i++) if (head->con[i])
		{
			a[i][len[i]].num=head->con[i];
			sprintf(a[i][len[i]++].s,"%s",r);
		}
	}
	for (int i=0;i<26;i++)
	{
		if (head->s[i])
		{
			r[num]=i+'a';
			dfs(head->s[i],num+1);
			r[num]=0;
		}
	}
	return;
}

int cmp1(const void *a,const void *b)
{
	dict *x=(dict*)a;
	dict *y=(dict*)b;
	if (x->num<y->num) return 1;
	if (x->num>y->num) return -1;
	return strcmp(x->s,y->s);
}

int cmp2(const void *a,const void *b)
{
	dict *x=(dict*)a;
	dict *y=(dict*)b;
	return strcmp(x->s,y->s);
}

void solve()
{
	for (int i=0;i<2;i++)
	qsort(a[i],len[i],sizeof(dict),cmp1);
	for (int i=0;i<2;i++)
	{
		for (int j=0;j<n;j++)
		b[i][j]=a[i][j],sum[i]+=a[i][j].num;
	}
	for (int i=0;i<2;i++)
	qsort(b[i],n,sizeof(dict),cmp2);
	int i=0,j=0;
	while (i<n && j<n)
	{
		if (strcmp(b[0][i].s,b[1][j].s)<0) i++;
		else if (strcmp(b[0][i].s,b[1][j].s)>0) j++;
		else same[0]+=b[0][i].num,same[1]+=b[1][j].num,i++,j++;
	}
	return;
}

void print()
{
	double pro1=(double)same[0]/(double)sum[0];
	double pro2=(double)same[1]/(double)sum[1];
	double ans=min(pro1,pro2)/max(pro1,pro2);
	printf("%.5lf\n",ans);
	fprintf(out,"%.5lf\n",ans);
	fputc('\n',in); for (int i=0;i<n;i++)
	fprintf(out,"%s %d\n",a[0][i].s,a[0][i].num);
	fputc('\n',in); for (int i=0;i<n;i++)
	fprintf(out,"%s %d\n",a[1][i].s,a[1][i].num);
	return;
}

int main()
{
	ptr head=newnode();
	in=fopen("dictionary.txt","r");
	while (fscanf(in,"%s",r)!=EOF)
		ins(head); fclose(in);
	in=fopen("stopwords.txt","r");
	while (fscanf(in,"%s",r)!=EOF)
		del(head); fclose(in);
	in=fopen("article1.txt","r");
	while (read()) count(head,0); fclose(in);
	in=fopen("article2.txt","r");
	while (read()) count(head,1); fclose(in);
	scanf("%d",&n);
	out=fopen("results.txt","w");
	memset(r,0,sizeof(r));
	dfs(head,0);
	if (n>len[0]) n=len[0];
	if (n>len[1]) n=len[1];
	solve(),print();
	return 0;
}