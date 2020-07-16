#include <time.h>
#include <stdio.h>
#include <stdlib.h>
clock_t start,finish;
char s[100][10]; double ans[100];

void f(int tim,int num,int f)
{
	for (int i=0;i<num;i++)
	sprintf(s[i],"V1.%d.exe",i+1);
	for (int i=0;i<tim;i++) for (int j=0;j<num;j++)
	{
		start=clock(),system(s[j]),finish=clock();
		ans[j]+=(((double)finish-(double)start)/1000);
	}
	if (!f) return;
	for (int i=0;i<num;i++)
	printf("%s %d times : %.3lf\n",s[i],tim,ans[i]);
	return;
}

int main()
{
	f(10,7,1);
	return 0;
}