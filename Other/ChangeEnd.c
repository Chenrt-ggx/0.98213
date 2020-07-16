#include <stdio.h>

int main()
{
	freopen("article2.txt","r",stdin);
	freopen("ans.txt","w",stdout);
	char c; while ((c=getchar())!=EOF)
	{
		if (c=='\n') putchar('\r');
		putchar(c);
	}
	return 0;
}