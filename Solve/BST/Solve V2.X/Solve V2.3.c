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

unsigned char art1[7000000],art2[7000000],buffer[8000100],*s1[3000010],*s2[3000010];
unsigned int pol,len1,len2,top1,top2,vis[3000010],fst1[40000],nxt1[3000010],fst2[40000],nxt2[3000010];
typedef struct tree {struct tree *ls,*rs; unsigned char *s; unsigned int con1,con2;} stu,*ptr; stu a[3000000];
unsigned char alpha[260]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

int read() {
	register int q=0;
	register char c=getchar();
	while (c>='0' && c<='9')
	q=(q<<3)+(q<<1)+(c^48),
	c=getchar(); return q;
}

void print(unsigned int x) {
	if (x>9) print(x/10);
	art1[pol++]=x%10^'0';
	return;
}

inline int smp(unsigned char* a,unsigned char* b) {
	while (!(*a-*b) && *b) a--,b--;
	return *a-*b;
}

void ins1(ptr* now,unsigned char* word) {
	if (*now==NULL) {
		*now=&a[pol++],(*now)->s=word;
		(*now)->con1++; return;
	}
	int t=smp(word,(*now)->s);
	if (t<0) {ins1(&(*now)->ls,word); return;}
	if (t>0) {ins1(&(*now)->rs,word); return;}
	(*now)->con1++; return;
}

void ins2(ptr* now,unsigned char* word) {
	if (*now==NULL) {
		*now=&a[pol++],(*now)->s=word;
		(*now)->con2++; return;
	}
	int t=smp(word,(*now)->s);
	if (t<0) {ins2(&(*now)->ls,word); return;}
	if (t>0) {ins2(&(*now)->rs,word); return;}
	(*now)->con2++; return;
}

void del(ptr* now,unsigned char* word) {
	if (*now==NULL) return;
	int t=smp(word,(*now)->s);
	if (t<0) {del(&(*now)->ls,word); return;}
	if (t>0) {del(&(*now)->rs,word); return;}
	if ((*now)->ls==NULL) {*now=(*now)->rs; return;}
	if ((*now)->rs==NULL) {*now=(*now)->ls; return;}
	ptr cng=(*now)->rs; while (cng->ls) cng=cng->ls;
	(*now)->con1=cng->con1,(*now)->con2=cng->con2;
	(*now)->s=cng->s,del(&(*now)->rs,cng->s); return;
}

void add(ptr now,unsigned char* word,unsigned char* pos) {
	if (now==NULL) return;
	int t=smp(word,now->s);
	if (t<0) {add(now->ls,word,pos); return;}
	if (t>0) {add(now->rs,word,pos); return;}
	++pol; if (now->con1) {
		nxt1[pol]=fst1[now->con1],fst1[now->con1]=pol;
		s1[pol]=pos,len1++; if (now->con1>top1) top1=now->con1;
	}
	if (now->con2) {
		nxt2[pol]=fst2[now->con2],fst2[now->con2]=pol;
		s2[pol]=pos,len2++; if (now->con2>top2) top2=now->con2;
	}
	return;
}

int main() {
	ptr root=NULL;
	register unsigned char *pos,*rpos;
	FILE *in,*out; register unsigned int i,j,k;
	unsigned int n,sum1=0,sum2=0,same1=0,same2=0;
	in=fopen("article1.txt","rb");
	n=fread(art1+1,1,7000000,in); art1[n+1]=0;
	i=n+1; while (i) {
		while (!alpha[art1[i]]) --i; pos=&art1[i];
		while (alpha[art1[i]]) art1[i--]|=32;
		art1[i]=0; ins1(&root,pos);
	}
	fclose(in),in=fopen("article2.txt","rb");
	n=fread(art2+1,1,7000000,in); art2[n+1]=0;
	i=n+1; while (i) {
		while (!alpha[art2[i]]) --i; pos=&art2[i];
		while (alpha[art2[i]]) art2[i--]|=32;
		art2[i]=0; ins2(&root,pos);
	}
	fclose(in),in=fopen("stopwords.txt","rb");
	n=fread(buffer+1,1,8000000,in); buffer[n+1]=0;
	i=n+1; while (i) {
		while (!alpha[buffer[i]]) --i; pos=&buffer[i];
		while (alpha[buffer[i]]) --i; buffer[i]=0; del(&root,pos);
	}
	fclose(in),in=fopen("dictionary.txt","rb");
	n=fread(buffer+1,1,8000000,in); buffer[n+1]=0;
	i=n+1,pol=0; while (i) {
		while (!alpha[buffer[i]]) --i;
		pos=&buffer[i],buffer[i+1]=0;
		while (alpha[buffer[i]]) --i;
		rpos=&buffer[i+1],buffer[i]=0;
		add(root,pos,rpos);
	}
	fclose(in),pol=0,n=read(),art1[pol++]='\n';
	if (n>len1) n=len1; if (n>len2) n=len2;
	k=0; while (k<n)
	for (i=top1;i && k<n;i--)
	for (j=fst1[i];j && k<n;j=nxt1[j]) {
		pos=s1[j]; while (*pos) art1[pol++]=*pos++;
		art1[pol++]=32,print(i),art1[pol++]='\n';
		sum1+=i,k++,vis[j]=i;
	}
	art1[pol++]='\n';
	k=0; while (k<n)
	for (i=top2;i && k<n;i--)
	for (j=fst2[i];j && k<n;j=nxt2[j]) {
		pos=s2[j]; while (*pos) art1[pol++]=*pos++;
		art1[pol++]=32,print(i),art1[pol++]='\n';
		sum2+=i,k++; if (vis[j]) same1+=vis[j],same2+=i;
	}
	out=fopen("results.txt","w");
	double pro1=(double)same1/(double)sum1;
	double pro2=(double)same2/(double)sum2;
	double ans=(pro1<pro2?pro1:pro2)/(pro1>pro2?pro1:pro2);
	printf("%.5lf\n",ans),fprintf(out,"%.5lf\n",ans);
	fwrite(art1,1,pol,out);
	fclose(out); return 0;
}