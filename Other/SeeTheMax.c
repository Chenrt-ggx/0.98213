#include <stdio.h>
#include <string.h>

FILE *in; char r[100];

int read()
{
	int len=0;
	char c=(fgetc(in));
	if (c==EOF) return 0;
	while (!('a'<=c && c<='z'))
	{
		c=(fgetc(in));
		if (c==EOF) return 0;
	}
	while ('a'<=c && c<='z')
	r[len++]=c,c=(fgetc(in));
	r[len]=0; return 1;
}

int main()
{
	int tot,max,len;
	in=fopen("dictionary.txt","r"),tot=max=0;
	while (read())
	{
		len=strlen(r),tot++;
		if (len>max) max=len;
	}
	fclose(in);
	printf("dictionary tot=%d max=%d\n",tot,max);
	in=fopen("stopwords.txt","r"),tot=max=0;
	while (read())
	{
		len=strlen(r),tot++;
		if (len>max) max=len;
	}
	fclose(in);
	printf("stopwords tot=%d max=%d\n",tot,max);
	in=fopen("article1.txt","r"),tot=max=0;
	while (read())
	{
		len=strlen(r),tot++;
		if (len>max) max=len;
	}
	fclose(in);
	printf("article1 tot=%d max=%d\n",tot,max);
	in=fopen("article2.txt","r"),tot=max=0;
	while (read())
	{
		len=strlen(r),tot++;
		if (len>max) max=len;
	}
	fclose(in);
	printf("article2 tot=%d max=%d\n",tot,max);
	return 0;
}