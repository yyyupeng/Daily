#include <iostream>
#include <cstdio>

using namespace std;

/*
 * 二 ？
//定义结点
typedef struct _josephus
{
    int num;
    struct _josephus *next;
}josephus;

int n;  //记录结点

//创建结点
josephus *Creat(josephus *pHead)
{
    josephus *pEnd,*pNew;
    int i;
    printf("人数：");
    cin >> n;
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
josephus *fun(josephus *pHead, int m)
{
    josephus *temp = pHead;
    josephus *p = NULL;     //指向要删除结点
    int i;

    printf("exept: ");
    //删除结点
    while(n > 1)
    {
        p = temp;
        for(i = 1; i < m; i++)
        {
            temp = p;
            p = p->next;
        }
        printf("%d ",p->num);
        temp->next = p->next;   //将要删除结点前后连接起来
        free(p);
        temp = temp->next;      //temp指向被删除结点的下一个结点
        n--;
    }
    return temp;
}

int main()
{
    int m;

    josephus *pHead = NULL;
    pHead = Creat(pHead);

    cout << "m ? ";
    cin >> m;
    pHead = fun(pHead,m);

    cout << pHead->num << endl;
    free(pHead);
    pHead = NULL;   //防止产生野指针
    return 0;
}
*/



/*
 * 一
//定义结点
typedef struct _josephus
{
    int num;
    int data;
    struct _josephus *next;
}josephus;

int n;  //记录人数
int m;  //出列值

//创建结点
josephus *Creat(josephus *pHead)
{
    josephus *pEnd,*pNew;
    for(int i = 1; i <= n; i++)
    {
        pNew = (josephus *)malloc(sizeof(josephus));
        pNew->num = i;
        printf("第%d个人的密码为: ", i);
        cin >> pNew->data;
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

//执行函数
void fun(josephus *pHead)
{
    josephus *temp = pHead;  //指向要出列结点的前一个结点
    josephus *p = NULL;     //指向要出列的结点

    cout << "exept: ";
    //循环判断
    while(n > 1)
    {
        p = temp;
        for(int i = 1; i < m; i++)
        {
            temp = p;
            p = p->next;
        }
        cout << p->num << ",";
        if(n == 2)
            cout << p->next->num << endl;
        m = p->data;
        temp->next = p->next;   //将要出列的结点前后连接起来
        free(p);
        temp = temp->next;      //temp指向被删除结点的下一个结点
        n--;
    }
    free(temp);
    pHead = NULL;
}
int main()
{
    josephus *pHead = NULL;
    printf("m初值 = ? n = ?\n");
    cin >> m >> n;
    pHead = Creat(pHead);
    fun(pHead);

    return 0;
}
*/
