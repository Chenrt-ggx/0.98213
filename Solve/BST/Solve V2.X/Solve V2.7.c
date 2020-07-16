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

unsigned char vis[3000010],art1[7000000],art2[7000000],buffer[8000000];
unsigned int pol,len1,len2,top1,top2,fst1[40000],nxt1[3000010],fst2[40000],nxt2[3000010];
typedef struct tree {struct tree *ls,*rs,*fa; unsigned char *s; unsigned int color,con1,con2;} stu,*ptr; stu a[3000000]; ptr root,nil,s1[3000010],s2[3000010];
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
	buffer[pol++]=x%10^'0';
	return;
}

inline int smp(unsigned char* a,unsigned char* b) {
	while (!(*a-*b) && *b) a++,b++;
	return *a-*b;
}

void left(ptr now) {
	ptr y=now->rs; now->rs=y->ls;
	if (y->ls!=nil) y->ls->fa=now;
	y->fa=now->fa;
	if (now->fa==nil) root=y;
	else if (now==now->fa->rs) now->fa->rs=y;
	else now->fa->ls=y;
	y->ls=now,now->fa=y; return;
}

void right(ptr now) {
	ptr y=now->ls; now->ls=y->rs;
	if (y->rs!=nil) y->rs->fa=now;
	y->fa=now->fa;
	if (now->fa==nil) root=y;
	else if (now==now->fa->rs) now->fa->rs=y;
	else now->fa->ls=y;
	y->rs=now,now->fa=y; return;
}

void fixins(ptr now) {
	ptr f,g,u;
	while (now->fa->color) {
		f=now->fa,g=f->fa;
		if (f==g->ls) {
			u=g->rs;
			if (u->color) {
				u->color=f->color=0;
				g->color=1,now=g;
			} else {
				if (now==f->rs) now=f,left(now);
				now->fa->color=0;
				now->fa->fa->color=1,right(g);
			}
		}
		else {
			u=g->ls;
			if (u->color) {
				u->color=f->color=0;
				g->color=1,now=g;
			} else {
				if (now==f->ls) now=f,right(now);
				now->fa->color=0;
				now->fa->fa->color=1,left(g);
			}
		}
	}
	root->color=0; return;
}

void ins1(unsigned char* word) {
	ptr x=root,y=nil;
	int j; while (x!=nil) {
		y=x,j=smp(word,x->s);
		if (j<0) x=x->ls;
		else if (j>0) x=x->rs;
		else {x->con1++; return;}
	}
	x=&a[pol++],x->s=word,x->con1++;
	x->color++,x->fa=y,x->ls=x->rs=nil;
	if (y==nil) root=x;
	else {
		j=smp(word,y->s);
		if (j<0) y->ls=x;
		else y->rs=x;
	}
	fixins(x); return;
}

void ins2(unsigned char* word) {
	ptr x=root,y=nil;
	int j; while (x!=nil) {
		y=x,j=smp(word,x->s);
		if (j<0) x=x->ls;
		else if (j>0) x=x->rs;
		else {x->con2++; return;}
	}
	x=&a[pol++],x->s=word,x->con2++;
	x->color++,x->fa=y,x->ls=x->rs=nil;
	if (y==nil) root=x;
	else {
		j=smp(word,y->s);
		if (j<0) y->ls=x;
		else y->rs=x;
	}
	fixins(x); return;
}

void trans(ptr u,ptr v) {
	v->fa=u->fa;
	if (u->fa==nil) root=v;
	else if (u==u->fa->rs) u->fa->rs=v;
	else u->fa->ls=v; return;
}

void fixdel(ptr now) {
	ptr f,c;
	while (now!=root && now->color==0) {
		f=now->fa;
		if (now==f->ls) {
			c=f->rs; if (c->color) {
				f->color=1,c->color=0;
				left(f),c=f->rs;
			}
			if (c->ls->color==0 && c->rs->color==0) 
			c->color=1,now=now->fa; else {
				if (c->rs->color==0) {
					c->color=1,c->ls->color=0;
					right(c),c=f->rs;
				}
				c->color=f->color;
				f->color=c->rs->color=0;
				left(c->fa),now=root;
			}
		} else {
			c=f->ls; if (c->color) {
				f->color=1,c->color=0;
				right(f),c=f->ls;
			}
			if (c->ls->color==0 && c->rs->color==0) 
			c->color=1,now=now->fa; else {
				if (c->ls->color==0) {
					c->color=1,c->rs->color=0;
					left(c),c=f->ls;
				}
				c->color=f->color;
				f->color=c->ls->color=0;
				right(c->fa),now=root;
			}
		}
	}
	now->color=0; return;
}

void del(unsigned char* word) {
	ptr x,y,z=root,w=nil;
	int fix,j; while (z!=nil) {
		w=z,j=smp(word,z->s);
		if (j<0) z=z->ls;
		else if (j>0) z=z->rs;
		else break;
	}
	if (z!=nil) {
		y=z,fix=y->color;
		if (z->ls==nil) x=z->rs,trans(z,z->rs);
		else if (z->rs==nil) x=z->ls,trans(z,z->ls);
		else {
			y=z->rs;
			while (y->ls!=nil) y=y->ls;
			fix=y->color,x=y->rs;
			if (y->fa==z) x->fa=y;
			else {
				trans(y,y->rs),y->rs=z->rs;
				y->rs->fa=y;
			}
			trans(z,y),y->ls=z->ls,y->ls->fa=y;
			y->color=z->color;
		}
		if (fix==0) fixdel(x);
	}
	return;
}

void add(unsigned char* pos) {
	ptr now=root;
	int j; while (now!=nil) {
		j=smp(pos,now->s); if (j<0) now=now->ls;
		else if (j>0) now=now->rs; else break;
	}
	if (now==nil) return;
	++pol; if (now->con1) {
		nxt1[pol]=fst1[now->con1],fst1[now->con1]=pol;
		s1[pol]=now,len1++; if (now->con1>top1) top1=now->con1;
	}
	if (now->con2) {
		nxt2[pol]=fst2[now->con2],fst2[now->con2]=pol;
		s2[pol]=now,len2++; if (now->con2>top2) top2=now->con2;
	}
	return;
}

int main() {
	register unsigned char* pos;
	nil=&a[pol++],root=nil,root->fa=nil;
	FILE *in,*out; register unsigned int i,j,k;
	unsigned int n,sum1=0,sum2=0,same1=0,same2=0;
	in=fopen("article1.txt","rb");
	n=fread(art1,1,7000000,in); art1[n]=0;
	i=0; while (art1[i]) {
		pos=&art1[i]; while (alpha[art1[i]]) art1[i++]|=32;
		art1[i++]=0; ins1(pos);
		while (art1[i] && !alpha[art1[i]]) ++i;
	}
	fclose(in),in=fopen("article2.txt","rb");
	n=fread(art2,1,7000000,in); art2[n]=0;
	i=0; while (art2[i]) {
		pos=&art2[i]; while (alpha[art2[i]]) art2[i++]|=32;
		art2[i++]=0; ins2(pos);
		while (art2[i] && !alpha[art2[i]]) ++i;
	}
	fclose(in),in=fopen("stopwords.txt","rb");
	n=fread(buffer,1,8000000,in); buffer[n]=0;
	i=0; while (buffer[i]) {
		pos=&buffer[i]; while (alpha[buffer[i]])
		++i; buffer[i++]=0; del(pos);
	}
	fclose(in),in=fopen("dictionary.txt","rb");
	n=fread(buffer+1,1,8000000,in); buffer[0]=buffer[n+1]=0;
	i=n,pol=0; while (buffer[i]) {
		while (!alpha[buffer[i]]) --i; buffer[i+1]=0;
		while (alpha[buffer[i]]) --i;
		add(&buffer[i+1]);
	}
	fclose(in),pol=0,n=read(),buffer[pol++]='\n';
	if (n>len1) n=len1; if (n>len2) n=len2;
	k=0; while (k<n)
	for (i=top1;i && k<n;i--)
	for (j=fst1[i];j && k<n;j=nxt1[j]) {
		pos=s1[j]->s; while (*pos) buffer[pol++]=*pos++;
		buffer[pol++]=32,print(i),buffer[pol++]='\n';
		sum1+=i,k++,vis[j]=1;
	}
	buffer[pol++]='\n';
	k=0; while (k<n)
	for (i=top2;i && k<n;i--)
	for (j=fst2[i];j && k<n;j=nxt2[j]) {
		pos=s2[j]->s; while (*pos) buffer[pol++]=*pos++;
		buffer[pol++]=32,print(i),buffer[pol++]='\n';
		sum2+=i,k++; if (vis[j]) same1+=s2[j]->con1,same2+=i;
	}
	out=fopen("results.txt","w");
	double pro1=(double)same1/(double)sum1;
	double pro2=(double)same2/(double)sum2;
	double ans=(pro1<pro2?pro1:pro2)/(pro1>pro2?pro1:pro2);
	printf("%.5lf\n",ans),fprintf(out,"%.5lf\n",ans);
	fwrite(buffer,1,pol,out);
	fclose(out); return 0;
}