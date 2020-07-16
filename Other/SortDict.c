#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tot=0;
char s[1000000][100];

int cmp(const void *a,const void *b)
{
	return strcmp((char*)a,(char*)b);
}

int main()
{
	freopen("dictionary.txt","r",stdin);
	freopen("dictionary","w",stdout);
	while (gets(s[tot++])) s[tot-1][50]=0;
	qsort(s,tot,sizeof(s[0]),cmp);
	for (int i=0;i<tot;i++) puts(s[i]);
	return 0;
}