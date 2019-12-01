#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>

using namespace std;


#define Lnum 99

//哈夫曼编码 
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

int n,m;    //全局变量（n—叶子结点树，m—总结点数）

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

    return 0;
}




/*
//线索二叉树
typedef enum {Link,Thread} Tag;

typedef struct node
{
    char data;
    Tag lTag,rTag;
    struct node *lchild,*rchild;
}BiThrTree;

//前序建树
void CreatBiThrTree(BiThrTree **root)
{
    char ch;
    scanf("%c",&ch);
    if(ch == '#')
        *root = NULL;
    else
    {
        *root = (BiThrTree *)malloc(sizeof(BiThrTree));
        (*root)->data = ch;
        (*root)->lTag = Link;
        (*root)->rTag = Link;
        CreatBiThrTree(&(*root)->lchild);
        CreatBiThrTree(&(*root)->rchild);
    }
}

//中序线索化
BiThrTree *pre = NULL;
void InThreading(BiThrTree *root)
{
    if(root)
    {
        InThreading(root->lchild);
        if(!root->lchild)
        {
            root->lTag = Thread;
            root->lchild = pre;
        }
        if(pre && !pre->rchild)
        {
            pre->rTag = Thread;
            pre->rchild = root;
        }
        pre = root;
        InThreading(root->rchild);
    }
}

//中序遍历
void InOrderTraThr(BiThrTree *root)
{
    if(root == NULL)
        return;
    BiThrTree *temp = root;
    while(temp)
    {
        while(temp->lTag == Link)   
            temp = temp->lchild;
        printf("%c ",temp->data);
        while(temp && temp->rTag == Thread) 
        {
            temp = temp->rchild;
            printf("%c ",temp->data);
        }
        temp = temp->rchild;    
    }
}

//销毁
void DeleteThrTree(BiThrTree *root)
{
    BiThrTree *temp = NULL;
    if(root == NULL)
        return;
    while(root->lTag == Link)
        root = root->lchild;
    while(root)
    {
        temp = root->rchild;
        free(root);
        root = temp;
    }
    root = NULL;
}

int main()
{
    BiThrTree *m_root = NULL;

    printf("前序建树: ");
    CreatBiThrTree(&m_root);

    printf("中序遍历(中序线索化): ");
    InThreading(m_root);
    InOrderTraThr(m_root);
    printf("\n");

    DeleteThrTree(m_root);
    return 0;
}
*/



/*
//二叉树
typedef struct node
{
	char data;
	struct node *lchild,*rchild;
}Tree;

//创建二叉树
void CreatBiTree(Tree **root)
{
	char ch;
	scanf("%c",&ch);
	if(ch == '#')
		*root = NULL;
	else
	{
		*root = (Tree *)malloc(sizeof(Tree));
		(*root)->data = ch;
		CreatBiTree(&(*root)->lchild);
		CreatBiTree(&(*root)->rchild);
	}
}

//树状打印
void PrintTree(Tree *root, int h)
{
    Tree *p = root;
    if(p == NULL)
        return;
    PrintTree(p->rchild, h + 1);
    for(int i = 0; i < h; ++i)
        printf(" ");
    printf("%c\n", p->data);
    PrintTree(p->lchild, h + 1);
}

//前序遍历
void PreOrderTra(Tree *root)
{
	Tree *p = root;
	if(p == NULL)
		return;
	printf("%c ",p->data);
	PreOrderTra(p->lchild);
	PreOrderTra(p->rchild);
}

//非递归
void PreOrderTra_fdg(Tree *root)
{
    stack<Tree *> s;
    Tree *p = root;
    while(p || !s.empty())
    {
        if(p)
        {
            printf("%c ",p->data);
            s.push(p);      //入栈
            p = p->lchild;  //沿左子树
        }
        else
        {
            p = s.top();    //取出
            s.pop();        //出栈
            p = p->rchild;  //向右
        }
    }
}

//中序遍历
void InOrderTra(Tree *root)
{
    Tree *p = root;
    if(p == NULL)
        return;
    InOrderTra(p->lchild);
    printf("%c ",p->data);
    InOrderTra(p->rchild);
}

//非递归
void InOrderTra_fdg(Tree *root)
{
    stack<Tree *> s;
    Tree *p = root;
    while(p || !s.empty())
    {
        if(p)
        {
            s.push(p);      //入栈
            p = p->lchild;
        }
        else
        {
            p = s.top();    //取出
            printf("%c ",p->data);
            s.pop();        //出栈
            p = p->rchild;
        }
    }
}

//后序遍历
void PostOrderTra(Tree *root)
{
    Tree *p = root;
    if(p == NULL)
        return;
    PostOrderTra(p->lchild);
    PostOrderTra(p->rchild);
    printf("%c ",p->data);
}

//非递归
//对于任一结点P，先将其入栈。如果P不存在左孩子和右孩子，或者都已被访问过了，就可以直接访问该结点。
//如果有孩子未访问，将P的右孩子和左孩子依次入栈
void PostOrderTra_fdg(Tree *root)
{
    stack<Tree *> s;
    Tree *p,*q;
    p = q = NULL;
    s.push(root);
    while(!s.empty())
    {
        p = s.top();
        if((p->lchild == NULL && p->rchild == NULL) || (q != NULL && (q == p->lchild || q == p->rchild)))
        {
            printf("%c ",p->data);  //如果当前结点没有孩子或者孩子结点都已被访问过
            s.pop();    //出栈
            q = p;      //记录上一次访问的结点
        }
        else    //分别放入右左孩子
        {   
            if(p->rchild != NULL)
                s.push(p->rchild);
            if(p->lchild != NULL)
                s.push(p->lchild);
        }
    }
}

//层序遍历-（数组）
void LevelTra(Tree *root)
{
    Tree *t[20];    //指针数组，存放二叉树结构体指针
    int in,out;
    in = out = 0;
    t[in++] = root; //先保存根结点
    while(in > out)
    {
        if(t[out])
        {
            printf("%c ",t[out]->data);
            t[in++] = t[out]->lchild;
            t[in++] = t[out]->rchild;
        }
        out++;
    }
}

//层序遍历-（队列）
void LevelTra_dl(Tree *root)
{
    queue<Tree *> s;
    Tree *p = NULL;
    if(root)
        s.push(root);           //根结点入队

    while(!s.empty())
    {
        p = s.front();
        printf("%c ",p->data);
        
        if(p->lchild != NULL)
            s.push(p->lchild);
        if(p->rchild != NULL)
            s.push(p->rchild);

        s.pop();
    }
}

//求结点个数
int GetNodeNum(Tree *root)
{
    if(root == NULL)
        return 0;
    int lNum = GetNodeNum(root->lchild);
    int rNum = GetNodeNum(root->rchild);
    //printf("%d %d\n",lNum,rNum);
    return lNum + rNum + 1;     
}

//求二叉树深度
int GetTreeDepth(Tree *root)
{
    if(root == NULL)
        return 0;
    int lDepth = GetTreeDepth(root->lchild);
    int rDepth = GetTreeDepth(root->rchild);
    //printf("%d %d\n",lDepth,rDepth);
    return lDepth > rDepth ? (lDepth + 1) : (rDepth + 1);
}

//求叶子结点数
int GetLeafNodeNum(Tree *root)
{
    if(root == NULL)
        return 0;
    if(root->lchild == NULL && root->rchild == NULL)
        return 1;
    int lNum = GetLeafNodeNum(root->lchild);
    int rNum = GetLeafNodeNum(root->rchild);
    return (lNum + rNum);
}

//求第几层结点个数
int GetNodeNumLevel(Tree *root, int k)
{
    if(root == NULL || k < 1)
        return 0;
    if(k == 1)
        return 1;
    int lNum = GetNodeNumLevel(root->lchild,k - 1);
    int rNum = GetNodeNumLevel(root->rchild,k - 1);
    return (lNum + rNum);
}

//销毁二叉树
void DeleteTree(Tree *root)
{
    if(root == NULL)
        return;
    DeleteTree(root->lchild);
    DeleteTree(root->rchild);
    free(root);
}

int main()
{
	Tree *m_root = NULL;
    int k;
    int NodeNum,TreeDepth,LeafNodeNum,NodeNumLevel;
    
    printf("创建二叉树: ");
	CreatBiTree(&m_root);

    printf("树状打印：\n");
    PrintTree(m_root, 0);
    printf("前序遍历（递归）: ");
	PreOrderTra(m_root);
	printf("\n");
    printf("前序遍历（非递归）: ");
    PreOrderTra_fdg(m_root);
    printf("\n");

    printf("中序遍历（递归）: ");
    InOrderTra(m_root);
    printf("\n");
    printf("中序遍历（非递归）: ");
    InOrderTra_fdg(m_root);
    printf("\n");

    printf("后序遍历（递归）: ");
    PostOrderTra(m_root);
    printf("\n");
    printf("后序遍历（非递归）: ");
    PostOrderTra_fdg(m_root);
    printf("\n");

    printf("层序遍历（数组）: ");
    LevelTra(m_root);
    printf("\n");
    printf("层序遍历（队列）: ");
    LevelTra_dl(m_root);
    printf("\n");

    printf("树的结点数: ");
    NodeNum = GetNodeNum(m_root);
    printf("%d\n",NodeNum);

    printf("树的深度: ");
    TreeDepth = GetTreeDepth(m_root);
    printf("%d\n",TreeDepth);

    printf("树的叶子结点数: ");
    LeafNodeNum = GetLeafNodeNum(m_root);
    printf("%d\n",LeafNodeNum);

    printf("获取第几层的结点数: ");
    scanf("%d",&k);
    NodeNumLevel = GetNodeNumLevel(m_root,k);
    printf("第%d层结点数为: %d\n",k,NodeNumLevel);

	DeleteTree(m_root);
    m_root = NULL;    //防止野指针
	return 0;
}
*/



/*
//堆
int h[101];
int n;

//交换结点
void Swap(int x, int y)
{
	int t;
	t = h[x];
	h[x] = h[y];
	h[y] = t;
	return;
}

//向下调整
void Siftdown(int i)
{
	int t,flag = 0;	//flag标记是否需要继续向下调整
	while(i * 2 <= n && flag == 0)
	{
		if(h[i] < h[i * 2])  //判断与左儿子关系
			t = i * 2;
		else
			t = i;
		if(i * 2 + 1 <= n)  //判断与右儿子关系
		{
			if(h[t] < h[i * 2 + 1])
				t = i * 2 + 1;
		}
		if(t != i)
		{
			Swap(t,i);
			i = t;	//交换结点编号，以便下次调整
		}
		else
			flag = 1;
	}
	return;
}

//建堆-最大堆
void Creat()
{
	int i;
	for(i = n / 2; i >= 1; i--)
		Siftdown(i);
	return;
}

//堆排序
void HeapSort()
{
	while(n > 1)
	{
		Swap(1,n);
		n--;
		Siftdown(1);
	}
	return;
}

int main()
{
	int i;
	scanf("%d",&n);
	for(i = 1; i <= n; i++)
		scanf("%d",&h[i]);
	int num = n;
	Creat();
	HeapSort();
	for(i = 1; i <= num; i++)
		printf("%d ",h[i]);
	printf("\n");
	return 0;
}
*/
