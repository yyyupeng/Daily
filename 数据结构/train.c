#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//linux c编程实战 
//P:106——约瑟夫问题

josephus *Creat(josephus *);

//定义结点
typedef struct _josephus
{
    int num;
    struct _josephus *next;
}josephus;

int n;  //全局变量，记录共有几名犯人（结点）

//犯人数目（创建结点）
josephus *Creat(josephus *pHead)
{
    josephus *pEnd,*pNew;
    int i;
    printf("犯人数：");
    scanf("%d",&n);
    for(i = 1; i <= n; i++)
    {
        pNew = (josephus *)malloc(sizeof(josephus));
        pNew->num = i;
        pNew->next = NULL;
        if(pHead == NULL)
            pHead = pNew;
        else
            pEnd->next = pNew;
        pEnd = pNew;
    }
    pEnd->next = pHead;     //令尾指针指向头结点
    return pHead;
}

//处决函数
josephus *fun(josephus *pHead, int s, int m)
{
    josephus *temp = pHead;
    josephus *p = NULL;     //指向要处决的犯人（结点）
    int i;

    //遍历寻找到起始位置
    for(i = 1; i < s; i++)
        temp = temp->next;

    printf("kill: ");
    //循环判断处决犯人（删除结点）
    while(n > 1)
    {
        p = temp;
        for(i = 1; i < m; i++)
        {
            temp = p;
            p = p->next;
        }
        printf("%d ",p->num);
        temp->next = p->next;   //将要处决的犯人（结点）前后连接起来
        free(p);
        temp = temp->next;      //处决完一次后，还要继续处决到只剩一个犯人，因此temp指向被删除结点的下一个结点
        n--;
    }
    printf("\n");
    return temp;
}

int main()
{
    int s,m;
    
    josephus *pHead = NULL;
    pHead = Creat(pHead);
    
    printf("s,m: ");
    scanf("%d %d",&s,&m);
    pHead = fun(pHead,s,m);
    
    printf("存活: %d\n",pHead->num);
    free(pHead);
    pHead = NULL;   //防止产生野指针
    return 0;
}



/*
//合根植物-并查集
int getf(int *f, int x)
{
	if(f[x] == x)
		return x;
	else
	{
		f[x] = getf(f,f[x]);
		return f[x];
	}
}
void merge(int *f, int x, int y)
{
	int b1,b2;
	b1 = getf(f,x);
	b2 = getf(f,y);
	if(b1 != b2)
		f[b2] = b1;
	return;
}
int main()
{
	int f[1000001] = {0};
	int n,m,k,sum = 0;
	int i;
	int x,y;
	scanf("%d %d",&n,&m);
	scanf("%d",&k);
	for(i = 1; i <= n * m; i++)
		f[i] = i;
	for(i = 1; i <= k; i++)
	{
		scanf("%d %d",&x,&y);
		merge(f,x,y);
	}
	for(i = 1; i <= n * m; i++)
	{
		if(f[i] == i)
			sum++;
	}
	printf("%d\n",sum);
	return 0;
}
*/



/*
//二进制转换为其他进制
int main()
{
	char a[8];
	int s = 0;
	int n;
	int i;
	gets(a);
	n = strlen(a);
	for(i = 0; i < n; i++)
	{
		if(a[i] == '1')
			s += pow(2,n - i - 1);//核心
		else
			continue;
	}
	printf("十进制为: %d\n",s);
	printf("八进制为: %o\n",s);
	printf("十六进制为: %x\n",s);
	return 0;
}
*/
