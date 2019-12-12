#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <stack>

/* 邻接表（dfs + bfs）*/

#define MAXVEX 100

int book[MAXVEX];   //访问标志的数组
int flag = 0;       //记录连通分量的个数

//边表结点
typedef struct EdgeNode     
{
    int adjvex;             //邻接点域，储存顶点对应的下标
    //int weight;             //权值
    struct  EdgeNode *next; 
}EdgeNode;

//顶点表结点
typedef struct VertexNode
{
    int data;               //储存顶点信息
    EdgeNode *firstedge;    //边表头结点
}VertexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int vernum, edgenum;    //当前顶点数，结点数
}Graph;

//建立邻接表
void CreatALGraph(Graph *G)
{
    int i, j, k, w;
    EdgeNode *e;
    printf("输入顶点数和边数：");
    scanf("%d %d", &G->vernum, &G->edgenum);

    //建立顶点表
    printf("输入顶点：");
    for(i = 0; i < G->vernum; ++i)
    {
        scanf("%d", &G->adjList[i].data);
        G->adjList[i].firstedge = NULL;
    }

    //建立边表
    for(k = 0; k < G->edgenum; ++k)
    {
        printf("输入边上的顶点序号：");
        scanf("%d %d", &i, &j);

        //无向图，两次插入（头插法）
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = j;
        //e->weight = w;
        e->next = G->adjList[i].firstedge;      //将e指向当前顶点指向的结点
        G->adjList[i].firstedge = e;            //将当前顶点指向e

        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = i;
        //e->weight = w;
        e->next = G->adjList[j].firstedge;      //将e指向当前顶点指向的结点
        G->adjList[j].firstedge = e;            //将当前顶点指向e
    }
}

//dfs
void dfs(Graph G, int i)
{
    book[i] = 1;
    printf("%d ", G.adjList[i].data);
    EdgeNode *e = G.adjList[i].firstedge;
    while(e)
    {
        if(!book[e->adjvex])
            dfs(G, e->adjvex);
        e = e->next;
    }
}
void dfsTraverse(Graph G)
{
    int i;
    for(i = 0; i < G.vernum; ++i)
        book[i] = 0;
    for(i = 0; i < G.vernum; ++i)
    {
        if(!book[i])    //未被访问
        {
            dfs(G, i);
            ++flag;
        }
    }
    printf("\n");
}

//dfs——非递归
void dfs_(Graph G)
{
    memset(book, 0, MAXVEX);
    std::stack<int> S;
    int i;
    for(i = 0; i < G.vernum; ++i)
    {
        if(!book[i])
        {
            S.push(G.adjList[i].data);
            while(!S.empty())
            {
                int n = S.top();
                S.pop();
                if(!book[n])
                {
                    book[n] = 1;
                    printf("%d ", G.adjList[n].data);
                }
                EdgeNode *e = G.adjList[n].firstedge;
                while(e)
                {
                    if(!book[e->adjvex])
                        S.push(e->adjvex);
                    e = e->next;
                }
            }
        }
    }
    printf("\n");
}

void bfsTraverse(Graph G)
{
    int i;
    EdgeNode *e;
    std::queue<int> Q;
    for(i = 0; i < G.vernum; ++i)
        book[i] = 0;

    for(i = 0; i < G.vernum; ++i)
    {
        if(!book[i])
        {
            book[i] = 1;
            printf("%d ", G.adjList[i].data);
            Q.push(i);
            while(!Q.empty())
            {
                i = Q.front();
                Q.pop();
                e = G.adjList[i].firstedge;     //当前顶点边表头指针
                while(e)
                {
                    if(!book[e->adjvex])
                    {
                        book[e->adjvex] = 1;
                        printf("%d ", G.adjList[e->adjvex].data);
                        Q.push(e->adjvex);
                    }
                    e = e->next;    //指向下一邻接点
                }
            }
        }
    }
    printf("\n");
}

void DeleteEdge(Graph *G)
{
    EdgeNode *e;
    for(int i = 0; i < G->vernum; ++i)
    {
        while(G->adjList[i].firstedge != NULL)
        {
            e = G->adjList[i].firstedge;
            G->adjList[i].firstedge = e->next;
            free(e);
        }
    }
}

//无向图
int main()
{
    Graph G;
    printf("***建立邻接表***\n");
    CreatALGraph(&G);
    printf("***深度优先遍历***\n");
    printf("---递归---\n");
    dfsTraverse(G);
    printf("---非递归---\n");
    dfs_(G);
    printf("***广度优先遍历***\n");
    bfsTraverse(G);
    if(flag == 1)
        printf("这是一个连通图，连通分量为%d\n", flag);
    else
        printf("这不是一个连通图，连通分量为%d\n", flag);
    DeleteEdge(&G);
    return 0;
}

