#include <iostream>
#include <stack>
#include <cstring>
#include <algorithm>

using namespace std;

/* 马踏棋盘 */

typedef struct _horse
{
    int x;  //横坐标
    int y;  //纵坐标
    int s;  //下一步的方向
    int step;   //下一步的权值
    int flag;  //特殊点用
}HORSE;

int chessboard[8][8];   //棋盘
int Next[8][2] = {{2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1}};  //方向
int cnt = 1;            //计数器
stack<HORSE> horse;

//判别
bool judge(int a, int b)
{
    if(a < 0 || a > 7 || b < 0 || b > 7)    //边界
        return false;
    return true;
}

//从小到大排序
bool cmp(HORSE& a, HORSE& b)
{
    return a.step < b.step;
}

//计算权值
int steps(int a, int b)
{
    int sum = 0;
    for(int i = 0; i < 8; i++)
    {
        int x = a + Next[i][0];
        int y = b + Next[i][1];
        if(judge(x,y) && chessboard[x][y] == 0)
            ++sum;
    }
    return sum;
}

//执行过程
void Horse(int x, int y)
{
    HORSE temp;
    int a,b;    //记录当前马位置附近的坐标
    chessboard[x][y] = cnt; //标记当前起始位置已被访问 
    temp.x = x; //记录当前马的位置
    temp.y = y;
    while(cnt < 64)
    {
        int h_min = 8;      //权值最小的点
        int tx,ty,ti;       //记录权值最小的点的信息
        for(int i = 0; i < 8; i++)
        {
            a = temp.x + Next[i][0];
            b = temp.y + Next[i][1];
            if(judge(a,b) && chessboard[a][b] == 0)     //判断
            {
                int step = steps(a,b);   //计算权值
                if(step < h_min)         //更新权值最小的点
                {
                    h_min = step;    
                    tx = a;
                    ty = b;
                    ti = i;
                }            
            }
        }
        //直接走权值最小的点
        chessboard[tx][ty] = ++cnt;
        temp.s = ti;
        //temp.step = h_min;
        horse.push(temp);
        memset(&temp, 0, sizeof(HORSE));
        temp.x = tx;
        temp.y = ty;
    }
}

//特殊点执行过程（2，4）
void Horse_2(int x, int y)
{
    HORSE temp;
    HORSE horse_2[8];
    memset(horse_2, 0, sizeof(HORSE));
    int a,b;
    int flag = 0;   //记录该走那一个点了
    chessboard[x][y] = cnt;
    temp.x = x;
    temp.y = y;
    while(cnt < 64)
    {
        int k = 0;
        for(int i = 0; i < 8; i++)
        {
            a = temp.x + Next[i][0];
            b = temp.y + Next[i][1];
            if(judge(a,b) && chessboard[a][b] == 0)     //找出可走的点
            {
                int step = steps(a,b);
                horse_2[k].x = a;
                horse_2[k].y = b;
                horse_2[k].s = i;
                horse_2[k].step = step;
                ++k;
            }
        }
        sort(horse_2, horse_2 + k, cmp);    //按权值从小到大排序
        for(int i = 0; i < k; i++)
            horse_2[i].flag = i;    

        if(k > 0 && flag < k)   //有路可走
        {
            chessboard[horse_2[flag].x][horse_2[flag].y] = ++cnt;
            temp.s = horse_2[flag].s;
            temp.step = horse_2[flag].step;
            temp.flag = horse_2[flag].flag;
            horse.push(temp);
            memset(&temp, 0, sizeof(HORSE));
            temp.x = horse_2[flag].x;
            temp.y = horse_2[flag].y;
            flag = 0;
        }
        else    //回溯
        {
            --cnt;
            chessboard[temp.x][temp.y] = 0;
            HORSE tt = horse.top();
            horse.pop();
            temp.x = tt.x;
            temp.y = tt.y;
            flag = tt.flag;
            ++flag; //走下一个点
        }
    }
}

//输出
void print()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
            cout << chessboard[i][j] << ' ';
        cout << endl;
    }
}

int main()
{
    int x,y;
    cout << "从那个点开始: ";
    cin >> x >> y;
    if(x == 2 && y == 4)
        Horse_2(x,y);
    else
        Horse(x,y);
    print();
    return 0;
}

