#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[111]; int tot=0;
	for (int i=0;i<13;i++)
	for (int j=0;j<13;j++)
	{
		sprintf(s,"gcc V2.%d.%d.c -o V1.%d.exe -std=c99",i,j,tot);
		system(s); tot++;
	}
	return 0;
}