#include <stdio.h>
#include <string.h>

char s1[]="\tscanf(\"%d\",&n),n=min(min(n,len1),len2);";
char s2[]="\tprintf(\"%.5lf\\n\",ans),fprintf(out,\"%.5lf\\n\",ans);";
char s3[]="\tn=min(min(1000,len1),len2);";
char s4[]="\tfprintf(out,\"%.5lf\\n\",ans);";

int main()
{
	puts(s2);
	int tot=0;
	char in[111],out[111],r[555];
	for (int i=0;i<13;i++)
	for (int j=0;j<13;j++)
	{
		sprintf(in,"Solve V2.%d.%d.c",i,j);
		sprintf(out,"V1.%d.c",tot++);
		freopen(in,"r",stdin);
		freopen(out,"w",stdout);
		while (gets(r))
		{
			if (strcmp(s1,r)==0)
			{puts(s3); continue;}
			if (strcmp(s2,r)==0)
			{puts(s4); continue;}
			puts(r);
		}
	}
	return 0;
}