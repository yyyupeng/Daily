#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
//栈——解密回文
int main()
{
	char a[10],b[5];
	int len;//长度
	int m,n;
	int i;
	int top = 0;//初始化栈

	gets(a);
	len = strlen(a);//字符串长度
	m = len / 2;//中点

	for(i = 0; i < m; i++)
		b[++top] = a[i];

	if(len % 2 == 0)
		n = m;
	else
		n = m + 1;

	for(i = n; i < len; i++)
	{
		if(a[i] != b[top])
			break;
		top--;
	}

	if(top == 0)
		printf("栈已清空,这是一个回文字符串\n");
	else
		printf("栈未清空,这不是一个回文字符串\n");
		
	return 0;
}
*/

/*
//队列——解密qq——循环队列
typedef struct _queue
{
	int data[9];
	int head;//队首
	int tail;//队尾
}queue;
int main()
{
	queue t;
	int i;
	t.head = 0;
	t.tail = 0;

	printf("输入9个数: ");;
	for(i = 0; i < 9; i++)
	{
		scanf("%d",&t.data[t.tail]);
		t.tail++;
	}
	while(t.head != t.tail)
	{
		printf("%d",t.data[t.head]);
		t.head++;
		if(t.tail == 9)
			t.tail = 0;
		if(t.head == 9)
			t.head = 0;
		t.data[t.tail] = t.data[t.head];
		t.tail++;
		t.head++;	
	}
	printf("\n");
	return 0;
}
*/
