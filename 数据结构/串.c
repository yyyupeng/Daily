#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//KMP模式匹配算法
void get_nextval(char b[],int *nextval)
{
	int i,j;
	i = 0;
	j = -1;
	nextval[0] = -1;
	int len = strlen(b);
	while(i < len - 1)
	{
		if(j == -1 || b[i] == b[j])
		{
			++i;
			++j;
			if(nextval[i] == nextval[j])
				nextval[i] = nextval[j];
			else
				nextval[i] = j;
		}
		else
			j = nextval[j];
	}
}

int KMP(char a[], char b[])
{
	int i,j;
	int len1,len2;
	int nextval[20];
	i = j = 0;
	len1 = strlen(a);
	len2 = strlen(b);
	get_nextval(b,nextval);
	while(i < len1 && j < len2)
	{
		if(j == -1 || a[i] == b[j])
		{
			++i;
			++j;
		}
		else
			j = nextval[j];
	}
	if(j == len2)
		return i - j;
	else
		return -1;
}

int main()
{
	char a[20],b[20];
	scanf("%s %s", a,b);
    int n = KMP(a,b);
	printf("%d\n",n);
	return 0;
}
