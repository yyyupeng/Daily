#include <cstdio>
#include <cstdlib>
#include <queue>

/* 邻接表（dfs + bfs）*/

#define MAXVEX 100

int book[MAXVEX];  //访问标志的数组

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
            dfs(G, i);
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
//无向图
int main()
{
    Graph G;
    printf("***建立邻接表***\n");
    CreatALGraph(&G);
    printf("***深度优先遍历***\n");
    dfsTraverse(G);
    printf("***广度优先遍历***\n");
    bfsTraverse(G);
    return 0;
}

