#pragma once
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <termios.h>
#include <assert.h>
#include <errno.h>
#include <algorithm>
#include <stack>
#include <queue>
#include <mysql/mysql.h>
#include "Mysql.h"

#define MAXVEX 100
#define INF 65535

//边表结点
typedef struct EdgeNode     
{
    int adjvex;             //邻接点域，储存顶点对应的序号
    int weight;             //权值
    struct  EdgeNode *next_; 
}EdgeNode;

//顶点表结点
typedef struct VertexNode
{
    int id;               
    char name[30];
    int x, y;
    char info[100];
    EdgeNode *firstedge;    //边表头结点
}VertexNode, AdjList[MAXVEX];

//边集数组
typedef struct
{
    int begin;
    int end; ;
    int weight;
}Edge;

class map;

bool cmp(const Edge& , const Edge& );
int Find(int * , int );
void BFS(map& , int , int);
void DFS(map& , int , int , int );

class map : public Mysql
{
public:
    map() = default;
    ~map() {}
    void CreatALGraph(map& );
    void DeleteEdge(map& );
    void SearchAllDfs(map& , std::string, std::string );
    void SearchShortBfs(map& , std::string , std::string );
    void Dijkstra(map& , std::string , std::string );
    void show(map& );
    void AddPlace(map& , VertexNode& );
    void RevPlace(map&, std::string );
    void SearchPlace(map& , std::string );
    void AddRoad(map& , std::string , std::string , int );
    void DelRoad(map& , std::string, std::string );

private:
    AdjList adiList;
    int vernum, edgenum;
    
    friend void BFS(map&, int , int );
    friend void DFS(map& , int , int , int );
};

//创建地图
inline void map::CreatALGraph(map& G)
{
    EdgeNode *e;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char query_str[1000];
    int rows;

    if(MysqlInit() == -1)
    {
        std::cout << "数据库出错！！！" << std::endl;
        exit(-1);
    }
    sprintf(query_str, "select * from place");
    mysql_real_query(&mysql, query_str, strlen(query_str));
    res = mysql_store_result(&mysql);
    rows = mysql_num_rows(res);
    G.vernum = rows;        //地点数
    int i;
    while((row = mysql_fetch_row(res))) 
    {
        i = atoi(row[0]);
        G.adiList[i].id = atoi(row[0]);
        sprintf(G.adiList[i].name, "%s", row[1]);
        G.adiList[i].x = atoi(row[2]);
        G.adiList[i].y = atoi(row[3]);
        sprintf(G.adiList[i].info, "%s", row[4]);
        G.adiList[i].firstedge = nullptr;
    }

    sprintf(query_str, "select * from road");
    mysql_real_query(&mysql, query_str, strlen(query_str));
    res = mysql_store_result(&mysql);
    rows = mysql_num_rows(res);
    G.edgenum = rows;       //道路数
    while((row = mysql_fetch_row(res))) 
    {
        int j = atoi(row[0]);
        int k = atoi(row[1]);
        int w = atoi(row[2]);

        e = new EdgeNode;
        e->adjvex = k;
        e->weight = w;
        e->next_ = G.adiList[j].firstedge;
        G.adiList[j].firstedge = e;

        e = new EdgeNode;
        e->adjvex = j;
        e->weight = w;
        e->next_ = G.adiList[k].firstedge;
        G.adiList[k].firstedge = e;
    }
    MysqlClose();
}

//销毁
inline void map::DeleteEdge(map& G)
{
    EdgeNode *e;
    for(int i = 1; i <= G.vernum; ++i)
    {
        while(G.adiList[i].firstedge != nullptr)
        {
            e = G.adiList[i].firstedge;
            G.adiList[i].firstedge = e->next_;
            delete e;
        }
    }
}

//所有简单路径
int S[MAXVEX];
int visited[MAXVEX];
int count_;
void map::SearchAllDfs(map& G, std::string name1, std::string name2)
{
    int p1, p2;
    for(int i = 1; i <= G.vernum; ++i)
    {
        if(name1 == G.adiList[i].name)
            p1 = G.adiList[i].id;
        if(name2 == G.adiList[i].name)
            p2 = G.adiList[i].id;
    }
    if(p1 == p2)
    {
        std::cout << "\n\t\t" << "您想要原地打转吗？" << std::endl;
        return;
    }

    std::cout << "\n\t\t" << name1 << "到" << name2 << "的所有简单路径为：" << std::endl;
    int m = 2;
    S[1] = p1;
    visited[p1] = 1;
    DFS(G, m, p1, p2);

    bzero(S, sizeof(S));
    bzero(visited, sizeof(visited));
    count_ = 0;
}
void DFS(map& G, int m, int p1, int p2)
{
    EdgeNode *e = G.adiList[p1].firstedge;
    while(e)
    {
        if(visited[e->adjvex] == 0)
        {
            visited[e->adjvex] = 1;
            if(e->adjvex == p2)
            {
                ++count_;
                std::cout << "\t\t" << count_ << ' ';
                for(int i = 1; i < m; ++i)
                    std::cout << G.adiList[S[i]].name << " ---> ";
                std::cout << G.adiList[p2].name << std::endl;
                visited[e->adjvex] = 0;
            }
            else
            {
                S[m] = e->adjvex;
                ++m;
                DFS(G, m, e->adjvex, p2);
                --m;
                visited[e->adjvex] = 0;
            }
        }
        e = e->next_;
    }
}

//最短简单路径
void map::SearchShortBfs(map& G, std::string name1, std::string name2)
{
    int p1, p2;
    for(int i = 1; i <= G.vernum; ++i)
    {
        if(name1 == G.adiList[i].name)
            p1 = G.adiList[i].id;
        if(name2 == G.adiList[i].name)
            p2 = G.adiList[i].id;
    }
    if(p1 == p2)
    {
        std::cout << "\n\t\t" << "您想要原地打转吗？" << std::endl;
        return;
    }

    EdgeNode *e = G.adiList[p1].firstedge;
    while(e)
    {
        if(e->adjvex == p2)
        {
            std::cout << "\n\t\t" << name1 << "可以直接到" << name2 << "哦" << std::endl;
            return;
        }
        e = e->next_;
    }
    
    std::cout << "\n\t\t" << name1 << "到" << name2 << "中转次数最少的路线为：" << std::endl;
    std::cout << "\t\t";
    BFS(G, p1, p2);
    std::cout << name2 << std::endl;
}
void BFS(map& G, int p1, int p2)
{
    int book[MAXVEX];
    std::queue<int> Q;
    bzero(book, sizeof(book));
    book[p1] = 1;
    Q.push(p1);

    if(p1 == p2)
        return;
    while(!Q.empty())
    {
        int v = Q.front();
        Q.pop();
        EdgeNode *e = G.adiList[v].firstedge;
        while(e)
        {
            if(e->adjvex == p2)
            {
                BFS(G, p1, v);
                std::cout << G.adiList[v].name << " ---> ";
                return;
            }
            Q.push(e->adjvex);
            e = e->next_;
        }
    }
}

//最佳访问路线
inline void map::Dijkstra(map& G, std::string name1, std::string name2)
{
    std::stack<std::string> name;
    int book[MAXVEX];       //标记
    int P[MAXVEX];          //储存最短路径下标
    int W[MAXVEX];          //储存到各点最短路径权值和
    int V, v;
    int i, j, k, min_;
    bzero(book, sizeof(book));
    for(i = 0; i <= G.vernum; ++i)
    {
        P[i] = 1;
        W[i] = INF;
    }
    
    for(i = 1; i <= G.vernum; ++i)
    {
        if(name1 == G.adiList[i].name)
            V = G.adiList[i].id;
        if(name2 == G.adiList[i].name)
            v = G.adiList[i].id;
    }
    if(V == v)
    {
        std::cout << "\n\t\t" << "您想要原地打转吗？" << std::endl;
        return;
    }
    book[V] = 1;            //自己到自己不用求路径
    W[V] = 0;               //自己到自己为0

    EdgeNode *e = G.adiList[V].firstedge;
    while(e)
    {
        W[e->adjvex] = e->weight;   //将与V有边的定点加上权值
        e = e->next_;
    }
    for(i = 1; i <= G.vernum; ++i)
    {
        if(i == V)      //跳过自己到自己
            continue;
        min_ = INF;
        for(j = 1; j <= G.vernum; ++j)   //寻找离V最近的顶点
        {
            if(!book[j] && W[j] < min_)
            {
                k = j;          //存储最近顶点的下标
                min_ = W[j];     //存储最近顶点的权值
            }
        }
        book[k] = 1;    //标记
        e = G.adiList[k].firstedge;       //更新当前最短路径及距离
        while(e != nullptr)
        {
            //如果经过V顶点的路径比现在这条路径的权值小就更新
            if(!book[e->adjvex] && min_ + e->weight < W[e->adjvex])
            {
                W[e->adjvex] = min_ + e->weight;
                P[e->adjvex] = k;
            }
            e = e->next_;
        }
    }

    k = v;
    while(v != V)
    {
        name.push(G.adiList[v].name);
        v = P[v];
    }
    name.push(G.adiList[v].name);
    std::cout << "\n\t\t" << name1 << " ------> " << name2 << "的最佳访问路线：" << std::endl;
    std::cout << "\t\t";
    while(!name.empty())
    {
        std::cout << name.top();
        if(name.top() != name2)
            std::cout << " ---> ";
        name.pop();
    }
    std::cout << "\t" << "路径长度：" << W[k] << std::endl;
}

//总览信息（最佳布网方案）
bool cmp(const Edge& a, const Edge& b)
{
    return a.weight < b.weight;
}
//查找连线顶点的尾部（该顶点所在连通子图的尾部）下标
int Find(int *parent, int f)
{
    while(parent[f] > 0)
        f = parent[f];
    return f;
}
inline void map::show(map& G)
{
    Edge edges[MAXVEX];
    int parent[MAXVEX];
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char query_str[1000];
    int rows;

    std::cout << "\n\t\t" << "地点：" << std::endl;
    for(int i = 1; i <= G.vernum; ++i)
        std::cout << "\t\t" << G.adiList[i].id << " " << G.adiList[i].name << " " << G.adiList[i].info << std::endl;

    if(MysqlInit() == -1)
    {
        std::cout << "数据库出错！！！" << std::endl;
        exit(-1);
    }
    sprintf(query_str, "select * from road");
    mysql_real_query(&mysql, query_str, strlen(query_str));
    res = mysql_store_result(&mysql);
    rows = mysql_num_rows(res);
    int k = 0;
    std::cout << "\n\t\t" << "道路：" << std::endl;
    while((row = mysql_fetch_row(res))) 
    {
        int i = atoi(row[0]);
        int j = atoi(row[1]);
        int w = atoi(row[2]);

        std::cout << "\t\t" << i << " <------> " << j << "\t" << w << std::endl;
        
        edges[k].begin = i;
        edges[k].end = j;
        edges[k].weight = w;
        ++k;
    }
    MysqlClose();
    std::sort(edges, edges + G.edgenum, cmp);

    bzero(parent, sizeof(parent));
    std::cout << "\n\t\t" << "最佳布网方案：" << std::endl;
    for(k = 0; k < G.edgenum; ++k)
    {
        int n = Find(parent, edges[k].begin);
        int m = Find(parent, edges[k].end);
        if(n != m)      //没有形成回路
        {
            parent[n] = m;      //将此边的结尾顶点加入，表示此顶点已在生成树集合中
            std::cout << "\t\t" << edges[k].begin << " <------> " << edges[k].end << "\t" << edges[k].weight << std::endl;
        }
    }
}

//增添地点
void map::AddPlace(map& G, VertexNode& N)
{
    for(int i = 1; i <= G.vernum; ++i)
    {
        if((N.x == G.adiList[i].x) && (N.y == G.adiList[i].y))
        {
            std::cout << "\n\t\t" << "该坐标已有建筑，请重新选择！" << std::endl;
            return;
        }
    }
    N.id = ++G.vernum;      //地点总数++
    std::memcpy(&G.adiList[G.vernum], &N, sizeof(VertexNode));
    
    char query_str[1000];
    if(MysqlInit() == -1)
    {
        std::cout << "数据库出错！！！" << std::endl;
        exit(-1);
    }
    memset(query_str, 0, strlen(query_str));
    sprintf(query_str, "insert into place values(%d, '%s',%d, %d, '%s')",N.id, N.name, N.x, N.y, N.info);
    mysql_real_query(&mysql, query_str, strlen(query_str));
    MysqlClose();
    std::cout << "\n\t\t" << "增添地点成功！" << std::endl;
}

//修改地点信息
void map::RevPlace(map& G, std::string name)
{
    int i;
    char query_str[1000];

    for(i = 1; i <= G.vernum; ++i)
    {
        if(name == G.adiList[i].name)
        {
            break;
        }
    }
    if(i > G.vernum)
    {
        std::cout << "\n\t\t" << "该地点不存在！" << std::endl;
        return;
    }
    std::cout << "\n\t\t" << "原信息为：" << G.adiList[i].name << ' ' << G.adiList[i].info << std::endl;
    std::cout << "\t\t" << "新名称：";
    std::cin >> G.adiList[i].name;
    std::cout << "\t\t" << "新介绍信息：";
    std::cin >> G.adiList[i].info;

    if(MysqlInit() == -1)
    {
        std::cout << "数据库出错！！！" << std::endl;
        exit(-1);
    }
    memset(query_str, 0, strlen(query_str));
    sprintf(query_str, "update place set name='%s' where id=%d", G.adiList[i].name, G.adiList[i].id);
    mysql_real_query(&mysql, query_str, strlen(query_str));
    memset(query_str, 0, strlen(query_str));
    sprintf(query_str, "update place set info='%s' where id=%d", G.adiList[i].info, G.adiList[i].id);
    mysql_real_query(&mysql, query_str, strlen(query_str));
    MysqlClose();

    std::cout << "\n\t\t" << "修改地点信息成功！" << std::endl;
}

//查询地点
inline void map::SearchPlace(map& G, std::string name)
{   
    int i;
    EdgeNode *e;
    for(i = 1; i <= G.vernum; ++i)
    {
        if(G.adiList[i].name == name)
        {
            std::cout << "\t\t" << G.adiList[i].id << ' ' << G.adiList[i].name << ' ' << G.adiList[i].info << std::endl;
            break;    
        }
    }
    if(i > G.vernum)
    {
        std::cout << "\t\t" << "该地点不存在！" << std::endl;
        return;
    }

    e = G.adiList[i].firstedge;
    while(e)
    {
        for(i = 1; i <= G.vernum; ++i)
        {
            if(G.adiList[i].id == e->adjvex)
            {
                std::cout << "\t\t" << name << " <------> " << G.adiList[i].name << "\t" << e->weight << std::endl;
                break;
            }
        }
        e = e->next_;
    }
}

//增添道路
void map::AddRoad(map& G, std::string name1, std::string name2, int w)
{
    int p1, p2;
    for(int i = 1; i <= G.vernum; ++i)
    {
        if(name1 == G.adiList[i].name)
            p1 = G.adiList[i].id;
        if(name2 == G.adiList[i].name)
            p2 = G.adiList[i].id;
    }
    if(p1 == p2)
    {
        std::cout << "\t\t" << "输入错误！" << std::endl;
        return;
    }

    EdgeNode *e = new EdgeNode;
    e->adjvex = p2;
    e->weight = w;
    e->next_ = G.adiList[p1].firstedge;
    G.adiList[p1].firstedge = e;

    e = new EdgeNode;
    e->adjvex = p1;
    e->weight = w;
    e->next_ = G.adiList[p2].firstedge;
    G.adiList[p2].firstedge = e;

    char query_str[1000];
    if(MysqlInit() == -1)
    {
        std::cout << "数据库出错！！！" << std::endl;
        exit(-1);
    }
    memset(query_str, 0, strlen(query_str));
    sprintf(query_str, "insert into road values(%d, %d, %d)",p1, p2, w);
    mysql_real_query(&mysql, query_str, strlen(query_str));
    MysqlClose();
    ++G.edgenum;        //道路总数++
    std::cout << "\n\t\t" << "增添道路成功！" << std::endl;
}

//撤销道路
void map::DelRoad(map& G, std::string name1, std::string name2)
{
    int p1, p2;
    for(int i = 1; i <= G.vernum; ++i)
    {
        if(name1 == G.adiList[i].name)
            p1 = G.adiList[i].id;
        if(name2 == G.adiList[i].name)
            p2 = G.adiList[i].id;
    }
    if(p1 == p2)
    {
        std::cout << "\t\t" << "输入错误！" << std::endl;
        return;
    }

    EdgeNode *e = G.adiList[p1].firstedge;
    if(e->adjvex == p2)
    {
        G.adiList[p1].firstedge = e->next_;
        delete e;
    }
    else
    {
        while(e->next_)
        {
            if(e->next_->adjvex == p2)
            {
                EdgeNode *temp = e->next_;
                e->next_ = temp->next_;
                delete temp;
                temp = nullptr;
                break;
            }
        }
    }
    
    e = G.adiList[p2].firstedge;
    if(e->adjvex == p1)
    {
        G.adiList[p2].firstedge = e->next_;
        delete e;
    }
    else
    {
        while(e->next_)
        {
            if(e->next_->adjvex == p1)
            {
                EdgeNode *temp = e->next_;
                e->next_ = temp->next_;
                delete temp;
                temp = nullptr;
                break;
            }
        }
    }

    char query_str[1000];
    if(MysqlInit() == -1)
    {
        std::cout << "数据库出错！！！" << std::endl;
        exit(-1);
    }
    memset(query_str, 0, strlen(query_str));
    sprintf(query_str, "delete from road where (place1=%d and place2=%d) or (place2=%d and place1=%d)", p1, p2, p1, p2);
    mysql_real_query(&mysql, query_str, strlen(query_str));
    MysqlClose();
    --G.edgenum;        //道路总数--
    std::cout << "\n\t\t" << "撤销道路成功！" << std::endl;
}
