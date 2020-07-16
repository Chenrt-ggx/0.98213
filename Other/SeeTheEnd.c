#include <stdio.h>

int main()
{
	char c;
	freopen("stopwords.txt","r",stdin);
	while ((c=getchar())!=EOF)
	{
		printf("%3d ",c);
		if (c=='\n') puts("");
	}
	return 0;
}