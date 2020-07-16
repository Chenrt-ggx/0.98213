#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ri register int
#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))

typedef struct {char s[50]; int art1,art2;} word;
FILE *in,*out; char newword[50]; int n,which,topdict,topstop,topart1,topart2;
word dict[500000],stop[1000],article1[500000],beifen1[500000],article2[500000],beifen2[500000];

int getword() {
	int len=0; char ch=(fgetc(in)|32); if (ch==EOF) return EOF;
	while (!('a'<=ch && ch<='z')) {ch=(fgetc(in)|32); if (ch==EOF) return EOF;}
	while ('a'<=ch && ch<='z') newword[len++]=ch,ch=(fgetc(in)|32);
	newword[len]=0; return len;
}

int count(word in[],char flag) {
	int l=0,mid,temp,r=flag?topdict:topstop;
	while (l<=r) {
		mid=(l+r)>>1;
		temp=strcmp(newword,in[mid].s);
		if (temp>0) l=mid+1;
		else if (temp<0) r=mid-1;
		else if (!flag) return 1;
		else if (!which) return ++in[mid].art1;
		else return ++in[mid].art2;
	}
	return 0;
}

int compare(const void *a,const void *b) {
	word x=*(word*)a,y=*(word*)b;
	if (which==1) return (y.art1-x.art1)?(y.art1-x.art1):strcmp(x.s,y.s);
	if (which==2) return (y.art2-x.art2)?(y.art2-x.art2):strcmp(x.s,y.s);
	return strcmp(x.s,y.s);
}

int main() {
	in=fopen("dictionary.txt","r"); while (fscanf(in,"%s",dict[topdict++].s)!=EOF);
	in=fopen("stopwords.txt","r"); while (fscanf(in,"%s",stop[topstop++].s)!=EOF);
	which=0,in=fopen("article1.txt","r"); while (~getword()) if (!count(stop,0)) count(dict,1);
	which=1,in=fopen("article2.txt","r"); while (~getword()) if (!count(stop,0)) count(dict,1);
	for (ri i=0;i<topdict;++i) {
		if (dict[i].art1) article1[topart1++]=dict[i];
		if (dict[i].art2) article2[topart2++]=dict[i];
	}
	which=1,qsort(article1,topart1,sizeof(*article1),compare);
	which=2,qsort(article2,topart2,sizeof(*article2),compare);
	which=0,scanf("%d",&n),n=min(min(n,topart1),topart2);
	int same1=0,same2=0,count1=0,count2=0;
	for (ri i=0;i<n;++i) {
		beifen1[i]=article1[i],count1+=article1[i].art1;
		beifen2[i]=article2[i],count2+=article2[i].art2;
	}
	qsort(beifen1,n,sizeof(*beifen1),compare);
	qsort(beifen2,n,sizeof(*beifen2),compare);
	for (ri temp,i=0,j=0;i<n && j<n;) {
		temp=strcmp(beifen1[i].s,beifen2[j].s);
		if (!temp) same1+=beifen1[i].art1,same2+=beifen2[j].art2;
		i+=temp<=0,j+=temp>=0;
	}
	out=fopen("results.txt","w");
	double pro1=1.0*same1/count1,pro2=1.0*same2/count2;
	double ans=min(pro1,pro2)/max(pro1,pro2);
	printf("%.5lf\n",ans),fprintf(out,"%.5lf\n",ans);
	fputc('\n',out); for (ri i=0;i<n;i++)
	fprintf(out,"%s %d\n",article1[i].s,article1[i].art1);
	fputc('\n',out); for (ri i=0;i<n;i++)
	fprintf(out,"%s %d\n",article2[i].s,article2[i].art2);
	fclose(out); return 0;
}