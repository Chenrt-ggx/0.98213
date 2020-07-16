#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tree
{
	struct tree *s[26];
	int flag,vis,con[2];
};

typedef struct tree stu;
typedef struct tree* ptr;
typedef struct {int num; char s[50];} dict;

char r[50];
FILE *in,*out;
dict a[2][500000],tmp;
int n,same[2],sum[2],len[2];

int ls(int x) {return x<<1;}
int rs(int x) {return x<<1|1;}
double fmin(double a,double b) {return a<b?a:b;}
double fmax(double a,double b) {return a>b?a:b;}
void swap(dict *x,dict*y){dict t=*x; *x=*y,*y=t; return;}

int judge(dict x,dict y)
{
	if (x.num<y.num) return 1;
	if (x.num>y.num) return 0;
	return strcmp(x.s,y.s)>0;
}

void siftup(int i,int f)
{
	while (i!=1 && judge(a[f][i],a[f][i>>1]))
	swap(&a[f][i],&a[f][i>>1]),i>>=1; return;
}

void siftdown(int i,int f,int size)
{
	int t;
	while (ls(i)<=size)
	{
		if (!judge(a[f][i],a[f][ls(i)])) t=ls(i); else t=i;
		if (rs(i)<=size && !judge(a[f][t],a[f][rs(i)])) t=rs(i);
		if (t==i) return; else swap(&a[f][i],&a[f][t]),i=t;
	}
	return;
}

int read()
{
	int cnt=0;
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
	r[cnt]=0;
	return 1;
}

ptr newnode()
{
	ptr p=(ptr)malloc(sizeof(stu));
	for (int i=0;i<26;i++) p->s[i]=NULL;
	p->flag=p->con[0]=p->con[1]=0;
	p->vis=-1; return p;
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
			tmp.num=head->con[i];
			if (len[i]<n)
			{
				strcpy(tmp.s,r);
				a[i][++len[i]]=tmp;
				siftup(len[i],i);
			}
			else if (judge(a[i][1],tmp))
			{
				strcpy(tmp.s,r);
				a[i][1]=tmp,siftdown(1,i,len[i]);
			}
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

void add(ptr head,dict now)
{
	int t;
	for (int i=0;now.s[i];i++)
	{
		t=tolower(now.s[i])-'a';
		head=head->s[t];
	}
	head->vis=now.num;
	return;
}

int fnd(ptr head,dict now)
{
	int t;
	for (int i=0;now.s[i];i++)
	{
		t=tolower(now.s[i])-'a';
		if (head->s[t]==NULL) return -1;
		else head=head->s[t];
	}
	return head->vis;
}

void solve(ptr head)
{
	int size;
	size=n; while (size-1)
	{
		swap(&a[0][1],&a[0][size--]);
		siftdown(1,0,size);
	}
	size=n; while (size-1)
	{
		swap(&a[1][1],&a[1][size--]);
		siftdown(1,1,size);
	}
	for (int i=1;i<=n;i++)
	{
		sum[0]+=a[0][i].num;
		add(head,a[0][i]);
	}
	for (int i=1;i<=n;i++)
	{
		sum[1]+=a[1][i].num;
		size=fnd(head,a[1][i]);
		if (size!=-1)
		same[0]+=size,
		same[1]+=a[1][i].num;
	}
	return;
}

void print()
{
	double pro1=(double)same[0]/(double)sum[0];
	double pro2=(double)same[1]/(double)sum[1];
	double ans=fmin(pro1,pro2)/fmax(pro1,pro2);
	printf("%.5lf\n",ans);
	fprintf(out,"%.5lf\n",ans);
	fputc('\n',in); for (int i=1;i<=n;i++)
	fprintf(out,"%s %d\n",a[0][i].s,a[0][i].num);
	fputc('\n',in); for (int i=1;i<=n;i++)
	fprintf(out,"%s %d\n",a[1][i].s,a[1][i].num);
	return;
}

int main()
{
	ptr head=newnode();
	in=fopen("dictionary.txt","r");
	while (fscanf(in,"%s",r)!=EOF) ins(head); fclose(in);
	in=fopen("stopwords.txt","r");
	while (fscanf(in,"%s",r)!=EOF) del(head); fclose(in);
	in=fopen("article1.txt","r");
	while (read()) count(head,0); fclose(in);
	in=fopen("article2.txt","r");
	while (read()) count(head,1); fclose(in);
	scanf("%d",&n),out=fopen("results.txt","w");
	memset(r,0,sizeof(r)),dfs(head,0);
	if (n>len[0]) n=len[0];
	if (n>len[1]) n=len[1];
	solve(head),print(),fclose(out);
	return 0;
}