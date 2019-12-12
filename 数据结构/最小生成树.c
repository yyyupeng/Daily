#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define MAXVEX 100      //最大顶点数
#define INF 65535  //极大

typedef struct 
{
    int vexs[MAXVEX];           //顶点表
    int arc[MAXVEX][MAXVEX];    //邻接矩阵
    int vex_num, edge_num;      //顶点数，边数
}MGraph;
//边集数组
typedef struct
{
    int begin;
    int end; ;
    int weight;
}Edge;

bool cmp(const Edge& a, const Edge& b)
{
    return a.weight < b.weight;
}

//无向图
void CreateMGraph(MGraph *G)
{
    int i, j, k ,w;
    printf("输入顶点数和边数：");
    scanf("%d %d", &G->vex_num, &G->edge_num);
    
    //建立顶点表
    printf("输入顶点：");
    for(i = 0; i < G->vex_num; ++i)
        scanf("%d", &G->vexs[i]);

    //建立邻接矩阵
    for(i = 0; i < G->vex_num; ++i)
        for(j = 0; j < G->vex_num; ++j)
            G->arc[i][j] = INF;
    for(k = 0; k < G->edge_num; ++k)
    {
        printf("输入边的下标（i , j）及权值：");
        scanf("%d %d %d", &i, &j, &w);
        G->arc[i][j] = G->arc[j][i] = w;    //矩阵对称
    }
}

//查找连线顶点的尾部（该顶点所在连通子图的尾部）下标
int Find(int *parent, int f)
{
    while(parent[f] > 0)
        f = parent[f];
    return f;
}

void MiniSpanTree_Kruskal(MGraph G)
{
    int i, j, k, n, m;
    Edge edges[G.edge_num];     //定义边集数组
    int parent[G.vex_num];      //判断是否能形成回路
    
    //将邻接矩阵转化为边集数组并按权值大小排序
    k = 0;
    for(i = 0; i < G.vex_num; ++i)
    {
        for(j = i + 1; j < G.vex_num; ++j)  //只处理上三角形
        {
            if(G.arc[i][j] != INF)
            {
                edges[k].begin = i;
                edges[k].end = j;
                edges[k].weight = G.arc[i][j];
                ++k;
            }
        }
    }
    std::sort(edges, edges + G.edge_num, cmp);

    for(i = 0; i < G.vex_num; ++i)
        parent[i] = 0;
    //循环判断每一条边
    printf("最小生成树：\n");
    for(i = 0; i < G.edge_num; ++i)
    {
        n = Find(parent, edges[i].begin);
        m = Find(parent, edges[i].end);
        if(n != m)      //没有形成回路
        {
            parent[n] = m;      //将此边的结尾顶点加入，表示此顶点已在生成树集合中
            printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
        }
    }
}

int main()
{
    MGraph G;    
    CreateMGraph(&G);
    MiniSpanTree_Kruskal(G);
    return 0;
}

