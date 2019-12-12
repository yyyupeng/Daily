#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXVEX 100
#define INF 65535

//边表结点
typedef struct EdgeNode     
{
    int adjvex;             //邻接点域，储存顶点对应的下标
    int weight;             //权值
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
        printf("输入边上的顶点序号及权值：");
        scanf("%d %d %d", &i, &j, &w);

        //无向图，两次插入（头插法）
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = j;
        e->weight = w;
        e->next = G->adjList[i].firstedge;      //将e指向当前顶点指向的结点
        G->adjList[i].firstedge = e;            //将当前顶点指向e

        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = i;
        e->weight = w;
        e->next = G->adjList[j].firstedge;      //将e指向当前顶点指向的结点
        G->adjList[j].firstedge = e;            //将当前顶点指向e
    }
}

void Dijkstra(Graph G, int V, int *P, int *W)
{
    int book[MAXVEX];       //标记
    int i, j, k, min;
    bzero(book, sizeof(book));
    book[V] = 1;            //自己到自己不用求路径
    W[V] = 0;               //自己到自己为0
    EdgeNode *e = G.adjList[V].firstedge;
    while(e)
    {
        W[e->adjvex] = e->weight;   //将与V有边的定点加上权值
        e = e->next;
    }
    for(i = 0; i < G.vernum; ++i)
    {
        if(i == V)      //跳过自己到自己
            continue;
        min = INF;
        for(j = 0; j < G.vernum; ++j)   //寻找离V最近的顶点
        {
            if(!book[j] && W[j] < min)
            {
                k = j;          //存储最近顶点的下标
                min = W[j];     //存储最近顶点的权值
            }
        }
        book[k] = 1;    //标记
        e = G.adjList[k].firstedge;       //更新当前最短路径及距离
        while(e)
        {
            //如果经过V顶点的路径比现在这条路径的权值小就更新
            if(!book[e->adjvex] && min + e->weight < W[e->adjvex])
            {
                W[e->adjvex] = min + e->weight;
                P[e->adjvex] = k;
            }
            e = e->next;
        }
    }
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

int main()
{
    int Path[MAXVEX];               //储存最短路径下标
    int ShortPathWeight[MAXVEX];    //储存到各点最短路径权值和
    Graph G;

    memset(Path, 0, sizeof(Path));
    CreatALGraph(&G);
    for(int i = 0; i < G.vernum; ++i)
        ShortPathWeight[i] = INF;
    Dijkstra(G, G.adjList[0].data, Path, ShortPathWeight);

    printf("\nPath: ");
    for(int i = 0; i < G.vernum; ++i)
        printf("%d ", Path[i]);
    printf("\nShortPathWeight: ");
    for(int i = 0; i < G.vernum; ++i)
        printf("%d ", ShortPathWeight[i]);
    printf("\n");
    
    DeleteEdge(&G);

    return 0;
}

