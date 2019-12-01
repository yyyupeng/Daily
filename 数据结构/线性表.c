#include <stdio.h>
#include <stdlib.h>


//单链表练习
struct student
{
    char name[20];
    int number;//学号
    struct student *next;
};

int count;//链表长度
struct student *create(struct student *pHead);//创建链表
void print(struct student *pHead);//遍历链表
struct student *Insert(struct student *pHead);//表头插入
struct student *InsertTwo(struct student *pHead);//表尾插入
struct student *InsertThree(struct student *pHead, int number);//表中插入
void Delete(struct student *pHead, int index);//删除
void change(struct student *pHead);//修改
struct student *inversion(struct student *pHead);//逆序
struct student *inversion2(struct student *pHead);//逆序-2

void find(struct student *pHead, int n);//查找倒数第n个结点
struct student *linksort(struct student *pHead);//排序
int main()
{
    struct student *pHead = NULL;
    struct student *pTemp = NULL;
    pHead = create(pHead);
    print(pHead);

    //pHead = linksort(pHead);
    //print(pHead);
    //pHead = Insert(pHead);
    //pHead = InsertTwo(pHead);
    //pHead = InsertThree(pHead,3);
    //change(pHead);
    //Delete(pHead,3);
    pTemp = inversion2(pHead);
    print(pTemp);
    //find(pHead,2);
    return 0;
}

struct student *create(struct student *pHead)
{
    struct student *pEnd,*pNew;
    int n;
    int i;
    printf("创建几个节点: ");
    scanf("%d",&n);
    for(i = 0; i < n; i++)
    {
        pNew = (struct student *)malloc(sizeof(struct student));
        printf("输入:");
        scanf("%s",pNew->name);
        scanf("%d",&pNew->number);
        pNew->next = NULL;
        if(pHead == NULL)
            pHead = pNew;
        else
            pEnd->next = pNew;
        pEnd = pNew;
        count++;
    }
    return pHead;
}

void print(struct student *pHead)
{
    struct student *pTemp;//循环用临时指针
    pTemp = pHead;
    int index = 1;//结点序号
    printf("**********本名单有%d个学生.**********\n",count);
    while(pTemp != NULL)
    {
        printf("NO.%d\t%s\t%d\n",index,pTemp->name,pTemp->number);
        pTemp = pTemp->next;
        index++;
    }
}

struct student *Insert(struct student *pHead)
{
    struct student *pNew;
    pNew = (struct student *)malloc(sizeof(struct student));
    printf("请输入学生的姓名和学号(表头): \n");
    scanf("%s",pNew->name);
    scanf("%d",&pNew->number);
    pNew->next = pHead;
    pHead = pNew;
    count++;
    return pHead;
}

struct student *InsertTwo(struct student *pHead)
{
    struct student *pNew,*p = pHead;
    pNew = (struct student *)malloc(sizeof(struct student));
    while(p && p->next != NULL) p = p->next;
    printf("请输入学生的姓名和学号(表尾): \n");
    scanf("%s",pNew->name);
    scanf("%d",&pNew->number);
    p->next = pNew;
    pNew->next = NULL;
    count++;
    return pHead;
}

struct student *InsertThree(struct student *pHead, int iNumber)
{
    struct student *pNew,*p = pHead;
    pNew = (struct student *)malloc(sizeof(struct student));
    while(p && p->number != iNumber) p = p->next;
    printf("请输入学生的姓名和学号(表中): \n");
    scanf("%s",pNew->name);
    scanf("%d",&pNew->number);
    pNew->next = p->next;
    p->next = pNew;
    count++;
    return pHead;
}

void Delete(struct student *pHead, int index)
{
    int i;
    struct student *pTemp = pHead;
    struct student *ptr;//删除结点前的结点
    printf("**********删除第%d个学生.**********\n",index);
    for(i = 1; i < index; i++)
    {
        ptr = pTemp;
        pTemp = pTemp->next;
    }
    ptr->next = pTemp->next;
    free(pTemp);
    count--;
}

void change(struct student *pHead)
{
    int i = 1,index;
    struct student *pTemp = pHead;
    printf("请确定你要修改第几个学生的信息.");
    scanf("%d",&index);
    while(i < index && pTemp->next != NULL)
    {
        pTemp = pTemp->next;
        i++;
    }
    if(pTemp)
    {
        printf("请输入要修改的信息:(姓名以及学号)\n");
        scanf("%s",pTemp->name);
        scanf("%d",&pTemp->number);
    }
    else
    {
        printf("对不起,没有找到!\n");
    }
}

struct student *inversion(struct student *pHead)
{
    struct student *pTemp,*q;
    pTemp = NULL;
    while(pHead)
    {
        q = pHead->next;
        pHead->next = pTemp;
        pTemp = pHead;
        pHead = q;
    }
    return pTemp;
}

struct student *inversion2(struct student *pHead)
{
	struct student *pTemp = NULL;
	if(pHead == NULL || pHead->next == NULL)
		return pHead;
	pTemp = inversion2(pHead->next);//递归
	pHead->next->next = pHead;	//回溯
	pHead->next = NULL;
	return pTemp;

}

void find(struct student *pHead, int n)
{
    struct student *p,*q;
    p = q = pHead;
    int m = n;
    while(pHead == NULL || n < 0)
        return;
    while(n > 0)
    {
        p = p->next;
        n--;
    }
    while(p)
    {
        p = p->next;
        q = q->next;
    }
    printf("倒数第%d个结点信息: \n",m);
    printf("姓名:%s\n",q->name);
    printf("学号:%d\n",q->number);
}

struct student *linksort(struct student *pHead)
{
    struct student *p = NULL;
    struct student *q = NULL;
    struct student *r = NULL;
    struct student n;
    for(p = pHead; p; p = p->next)
    {
        for(q = p->next; q; q = q->next)
        {
            if(p->number > q->number)
            {
                n = *p;
                *p = *q;
                *q = n;
                r = p->next;
                p->next = q->next;
                q->next = r;
            }
        }
    }
    return pHead;
}



/*
//循环链表练习
typedef struct _node
{
    int data;
    struct _node *next;
}Node;

int count = 0;//结点数

Node *create(Node *pHead)
{
    Node *pEnd,*pNew;
    int n;
    int i;
    printf("创建几个节点: ");
    scanf("%d",&n);
    for(i = 0; i < n; i++)
    {
        pNew = (Node *)malloc(sizeof(Node));
        printf("输入:");
        scanf("%d",&pNew->data);
        pNew->next = NULL;
        if(pHead == NULL)
            pHead = pNew;
        else
            pEnd->next = pNew;
        pEnd = pNew;
        count++;
    }
    pEnd->next = pHead;
    return pHead;
}

void print(Node *pHead)     //遍历
{
    Node *pTemp = pHead;
    int n = count * 2;
    int i = 0;
    printf("打印: \n");
    while(pTemp)
    {
        i++;
        printf("%d\t",pTemp->data);
        pTemp = pTemp->next;
        if(i == n)
            break;
    }
}

int main()
{
    Node *pHead = NULL;
    pHead = create(pHead);
    print(pHead);
    return 0;
}
*/



/*
//双链表练习
typedef struct _node
{
    int data;
    struct _node *pre;
    struct _node *next;
}Node;

int count = 0;  //结点数

Node *Create(Node *pHead)  //创建双向链表
{
    Node *pEnd,*pNew;
    int n;
    int i;
    printf("创建几个结点: ");
    scanf("%d",&n);
    for(i = 0; i < n; i++)
    {
        count++;
        pNew = (Node *)malloc(sizeof(Node));
        printf("输入: ");
        scanf("%d",&pNew->data);
        pNew->next = NULL;
        if(pHead == NULL)
        {
            pNew->pre = NULL;
            pHead = pNew;
        }
        else
        {
            pEnd->next = pNew;
            pNew->pre = pEnd;
        }
        pEnd = pNew;
    }
    return pHead;
}

void print(Node *pHead)     //遍历
{
    Node *pTemp = pHead;
    Node *p = pHead;
    printf("打印: \n");
    while(pTemp)
    {
        printf("%d\t",pTemp->data);
        pTemp = pTemp->next;
    }

    while(p && p->next != NULL)
    print(pHead);
        p = p->next;
    printf("\n");
    while(p)
    {
        printf("%d\t",p->data);
        p = p->pre;
    }
}

int main()
{
    Node *pHead = NULL;
    pHead = Create(pHead);
    print(pHead);
    return 0;
}
*/
