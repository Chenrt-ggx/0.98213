#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))

typedef struct tree {struct tree *ls,*rs; char s[50]; int con1,con2,exist;} stu,*ptr;
FILE *in,*out; ptr root; stu pol[500000]; typedef struct {int num; char s[50];} dic;
int n,top,len1,len2; char r[50]; dic in1[500000],in2[500000],cpy1[500000],cpy2[500000];

int read() {
	int cnt=0; char c=(fgetc(in)|32); if (c==EOF) return 0;
	while (!('a'<=c && c<='z')) {c=(fgetc(in)|32); if (c==EOF) return 0;}
	while ('a'<=c && c<='z') {r[cnt++]=c; c=(fgetc(in)|32);}
	r[cnt]=0; return 1;
}

void ins(ptr* now,int f) {
	if (*now==NULL) {
		*now=&pol[top++],strcpy((*now)->s,r);
		(*now)->con1+=!f,(*now)->con2+=f; return;
	}
	int t=strcmp(r,(*now)->s);
	if (t>0) {ins(&(*now)->rs,f); return;}
	if (t<0) {ins(&(*now)->ls,f); return;}
	(*now)->con1+=!f,(*now)->con2+=f; return;
}

void change(ptr now,int f) {
	if (now==NULL) return;
	int t=strcmp(r,now->s);
	if (t>0) {change(now->rs,f); return;}
	if (t<0) {change(now->ls,f); return;}
	now->exist=f; return;
}

void init() {
	in=fopen("article1.txt","r"); while (read()) ins(&root,0); fclose(in);
	in=fopen("article2.txt","r"); while (read()) ins(&root,1); fclose(in);
	in=fopen("dictionary.txt","r"); while (fscanf(in,"%s",r)!=EOF) change(root,1); fclose(in);
	in=fopen("stopwords.txt","r"); while (fscanf(in,"%s",r)!=EOF) change(root,0); fclose(in);
	scanf("%d",&n); return;
}

void dfs(ptr now) {
	if (now->exist && now->con1) in1[len1].num=now->con1,strcpy(in1[len1++].s,now->s);
	if (now->exist && now->con2) in2[len2].num=now->con2,strcpy(in2[len2++].s,now->s);
	if (now->ls) dfs(now->ls); if (now->rs) dfs(now->rs); return;
}

int cmp1(const void *a,const void *b) {
	if (((dic*)a)->num<((dic*)b)->num) return 1;
	if (((dic*)a)->num>((dic*)b)->num) return -1;
	return strcmp(((dic*)a)->s,((dic*)b)->s);
}

int cmp2(const void *a,const void *b)
{return strcmp(((dic*)a)->s,((dic*)b)->s);}

void print(int sum1,int sum2,int sam1,int sam2) {
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

void solve() {
	int sum1=0,sum2=0,sam1=0,sam2=0;
	dfs(root),n=min(min(n,len1),len2);
	qsort(in1,len1,sizeof(dic),cmp1);
	qsort(in2,len2,sizeof(dic),cmp1);
	for (int i=0;i<n;i++) cpy1[i]=in1[i],sum1+=in1[i].num;
	for (int i=0;i<n;i++) cpy2[i]=in2[i],sum2+=in2[i].num;
	qsort(cpy1,n,sizeof(dic),cmp2);
	qsort(cpy2,n,sizeof(dic),cmp2);
	int i=0,j=0,tmp; while (i<n && j<n) {
		tmp=strcmp(cpy1[i].s,cpy2[j].s);
		if (tmp<0) i++; else if (tmp>0) j++;
		else sam1+=cpy1[i].num,sam2+=cpy2[j].num,i++,j++;
	}
	print(sum1,sum2,sam1,sam2); return;
}

int main() {init(),solve(); return 0;}