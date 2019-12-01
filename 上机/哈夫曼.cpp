#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>

using namespace std;

#define Lnum 49

/* 哈夫曼编码 */

typedef struct
{
    double weight;  //权值
    int parent,lchild,rchild; //父结点，孩子结点
}HuffmanTree;

typedef struct
{
    int node_num;         
    double weight;
}Node;

typedef struct
{
    char ch;        //储存字符
    char bits[Lnum];   //编码位串
}HuffmanCode;

int n,m;    //全局变量（n—叶子结点数，m—总结点数）

bool cmp(Node& a, Node& b)
{
    return a.weight < b.weight;
}

//寻找权值最小和次小的结点
void SearchMin(HuffmanTree *T, int flag, int *p1, int *p2)
{
    Node N[m];
    int j = 0;
    for(int i = 0; i < flag; ++i)
    {
        if(T[i].parent == -1)   //如果还没有被合并
        {
            N[j].node_num = i;
            N[j].weight = T[i].weight;
            ++j;
        }
    }
    sort(N, N + j, cmp);    //按权值从小到大排序
    //前面两个是所需要的结点
    *p1 = N[0].node_num;
    *p2 = N[1].node_num;
}

//创建哈夫曼树
void CreatHuffmanTree(HuffmanTree *T)
{
    int p1,p2;
    //初始化哈夫曼树
    //将2n-1个结点里的三个指针均置为空(即置为-1)，权值置为0
    for(int i = 0; i < m; ++i)
    {
        T[i].weight = 0;
        T[i].parent = -1;
        T[i].lchild = -1;
        T[i].rchild = -1;
    }

    cout << "请输入" << n << "个叶子结点的权值：";
    for(int i = 0; i < n; i++)
        cin >> T[i].weight;

    for(int i = n; i < m; i++)
    {
        //合并结点（每次取权值最小和次小的结点），合并m - n(==n - 1)次
        SearchMin(T, i, &p1, &p2);
        T[p1].parent = T[p2].parent = i;
        T[i].lchild = p1;   //权值最小的结点为左孩子
        T[i].rchild = p2;
        T[i].weight = T[p1].weight + T[p2].weight;
    }
}

//哈夫曼编码
void HuffmanCoding(HuffmanTree *T, HuffmanCode *C)
{
    int p_child,p_parent;   //指向孩子及父结点
    char temp[n];           //临时存放编码
    int begin;              //标记编码在temp中开始的位置（因为是从下往上回溯）
    temp[n - 1] = '\0';

    cout << "请输入" << n << "个叶子结点所代表的字符：";
    for(int i = 0; i < n; i++)
    {
        cin >> C[i].ch;
        begin = n - 1;
        //开始从下往上回溯
        p_child = i;
        while((p_parent = T[p_child].parent) != -1)
        {
            if(T[p_parent].lchild == p_child)   //左孩子
                temp[--begin] = '0';
            else
                temp[--begin] = '1';
            p_child = p_parent;     //继续往上回溯
        }
        strcpy(C[i].bits, &temp[begin]);    //复制格式正确的编码
    }
}

int main()
{
    cout << "确定有几个叶子结点：";
    cin >> n;
    m = 2 * n - 1;  //总结点数
    HuffmanTree T[m];
    HuffmanCode C[n];
    CreatHuffmanTree(T);
    HuffmanCoding(T, C);

    cout << "哈夫曼编码：" << endl;
    for(int i = 0; i < n; i++)
        printf("字符: %c, 编码: %s\n", C[i].ch, C[i].bits);

    string ss;
    cout << "输入你想要进行译码的字符串：";
    cin >> ss;
    for(int i = 0; i < ss.size(); ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(ss[i] == C[j].ch)
            {
                cout << C[j].bits;
                break;
            }
        }
    }
    cout << endl;

    return 0;
}


