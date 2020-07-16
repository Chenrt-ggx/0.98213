#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {char s[111]; double ans;} stu;
clock_t start,finish; char s[200][20]; stu a[200];

int cmp(const void *a,const void *b)
{
	stu x=*(stu*)a;
	stu y=*(stu*)b;
	if (x.ans>y.ans) return 1;
	if (x.ans<y.ans) return -1;
	return 0;
}

int main()
{
	for (int i=0;i<169;i++)
	sprintf(s[i],"V1.%d.exe",i);
	for (int i=0;i<20;i++)
	{
		for (int j=0;j<169;j++)
		{
			start=clock(),system(s[j]),finish=clock();
			a[j].ans+=(((double)finish-(double)start)/1000);
		}
		printf("%d/20\n",i+1);
	}
	puts("");
	for (int i=0;i<13;i++)
	{
		for (int j=0;j<13;j++)
		sprintf(a[i*13+j].s,"V2.%-2d.%-2d times : %.3lf",i,j,a[i*13+j].ans),
		puts(a[i*13+j].s); puts("");
	}
	qsort(a,169,sizeof(stu),cmp);
	for (int i=0;i<169;i++)
	puts(a[i].s); return 0;
}