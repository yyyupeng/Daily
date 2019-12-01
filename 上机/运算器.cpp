#include <iostream>
#include <bits/stdc++.h>

#define MAXSIZE 1000
using namespace std;

/* 稀疏矩阵运算器 */

typedef struct
{
    int row, col;
    int value;
}Triple;
typedef struct
{
    Triple data[MAXSIZE];
    int rows, cols, nums;
}TSMatrix;

//输入
void Input(TSMatrix& t)
{
    cout << "请输入矩阵的行数和列数：";
    cin >> t.rows >> t.cols;
    cout << "请按行优先输入三元组（（0，0，0）结束）：" << endl;
    for(t.nums = 1; ; ++t.nums)
    {
        cin >> t.data[t.nums].row >> t.data[t.nums].col >> t.data[t.nums].value;
        if(t.data[t.nums].row == 0)
            break;
    }
}

//输出
void Output(TSMatrix& t)
{
    int num = 1;
    for(int i = 1; i <= t.rows; ++i)
    {
        for(int j = 1; j <= t.cols; ++j)
        {
            if(i == t.data[num].row && j == t.data[num].col)
            {
                cout << t.data[num].value << " ";
                ++num;
            }
            else
                cout << "0" << " ";
        }
        cout << endl;
    }
}

//一次定位快速转置
void FastTransposeTSMatrix()
{
    int num[MAXSIZE], pos[MAXSIZE];
    TSMatrix A, B;
    Input(A);
    Output(A); 
    B.rows = A.cols;
    B.cols = A.rows;
    B.nums = A.nums;
    if(B.nums)
    {
        // 1
        for(int col = 1; col <= A.cols; ++col)
            num[col] = 0;
        for(int n = 1; n <= A.nums; ++n)
            num[A.data[n].col]++;
        // 2
        pos[1] = 1;
        for(int col = 2; col <= A.cols; ++col)
            pos[col] = pos[col - 1] + num[col - 1];
        // 3
        for(int n = 1; n <= A.nums; ++n)
        {
            int col = A.data[n].col;
            int p = pos[col];
            B.data[p].row = A.data[n].col;
            B.data[p].col = A.data[n].row;
            B.data[p].value = A.data[n].value;
            pos[col]++;
        }
    }
    cout << "转置后为：";
    Output(B);
}

//矩阵加减
void AddorSub(int flag)
{
    TSMatrix A,B,sum;
    cout << "请输入第一个矩阵（A）：" << endl;
    Input(A);
    cout << "请输入第二个矩阵（B）：" << endl;
    Input(B);

    if(A.rows != B.rows || A.cols != B.cols)
    {
        cout << "格式错误!" << endl;
        return;
    }
    memset(&sum, 0, sizeof(TSMatrix));
    sum.rows = A.rows;
    sum.cols = A.cols;

    int num = 1;
    if(flag == 2)
    {
        for(int i = 1; i <= A.rows; ++i)
        {
            for(int j = 1; j <= A.cols; ++j)
            {
                int ffalg = 0;
                for(int k = 1; k <= A.nums; ++k)
                {
                    if(A.data[k].row == i && A.data[k].col == j)
                    {
                        sum.data[num].row = i;
                        sum.data[num].col = j;
                        sum.data[num].value = A.data[k].value;
                        ffalg = 1;
                        break;
                    }
                }
                for(int k = 1; k <= A.nums; ++k)
                {
                    if(B.data[k].row == i && B.data[k].col == j)
                    {
                        sum.data[num].row = i;
                        sum.data[num].col = j;
                        sum.data[num].value += B.data[k].value;
                        ffalg = 1;
                        break;
                    }
                }
                if(ffalg == 1)
                    ++num;
            }
        }
    }
    else
    {
        for(int i = 1; i <= A.rows; ++i)
        {
            for(int j = 1; j <= A.cols; ++j)
            {
                int ffalg = 0;
                for(int k = 1; k <= A.nums; ++k)
                {
                    if(A.data[k].row == i && A.data[k].col == j)
                    {
                        sum.data[num].row = i;
                        sum.data[num].col = j;
                        sum.data[num].value = A.data[k].value;
                        ffalg = 1;
                        break;
                    }
                }
                for(int k = 1; k <= A.nums; ++k)
                {
                    if(B.data[k].row == i && B.data[k].col == j)
                    {
                        sum.data[num].row = i;
                        sum.data[num].col = j;
                        sum.data[num].value -= B.data[k].value;
                        ffalg = 1;
                        break;
                    }
                }
                if(ffalg == 1)
                    ++num;
            }
        }
    }
    if(flag == 2)
        cout << "A + B = " << endl;
    else
        cout << "A - B = " << endl;
    Output(sum);
}

//寻找特定位置的元素
int Search(TSMatrix T, int i, int j)
{
    for(int k = 1; k <= T.nums; ++k)
    {
        if(T.data[k].row == i && T.data[k].col == j)
            return T.data[k].value;
    }
    return 0;
}

//矩阵相乘
void Multiplication()
{
    TSMatrix A,B;
    cout << "请输入第一个矩阵（A）：" << endl;
    Input(A);
    cout << "请输入第二个矩阵（B）：" << endl;
    Input(B);

    if(A.cols != B.rows)
    {
        cout << "格式错误" << endl;
        return;
    }
    cout << "A x B = " << endl;
    for(int i = 1; i <= A.rows; ++i)
    {
        for(int j = 1; j <= B.cols; ++j)
        {
            int sum = 0;
            int a,b;
            for(int k = 1; k <= A.cols; ++k)
            {
                a = Search(A, i, k);
                b = Search(B, k, j);
                sum += a * b;
            }
            cout << sum << " ";
        }
        cout << endl;
    }
}

int main()
{
    int flag = -1;
    while(flag != 0)
    {
        cout << "***稀疏矩阵运算器***" << endl;
        cout << "   1.矩阵转置" << endl;
        cout << "   2.矩阵相加" << endl;
        cout << "   3.矩阵相减" << endl;
        cout << "   4.矩阵相乘" << endl;
        cout << "   0.退出    " << endl;
        cout << "请选择：";
        cin >> flag;
        switch(flag)
        {
            case 1: FastTransposeTSMatrix();    break;
            case 2: AddorSub(flag);             break;
            case 3: AddorSub(flag);             break;
            case 4: Multiplication();           break;
        }
    }
    return 0;
}
