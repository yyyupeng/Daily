#include <iostream>
#include <stack>
#include <string>

using namespace std;

/* 魔王语言 */

class explain
{
public:
    int init(char x, string y)
    {
        c = x;
        s = y;
        lenth = y.size();
        return 0;
    }
    char c;
    string s;
    int lenth;
};

int main()
{
    class explain ep[2];
    ep[0].init('B', "tAdA");
    ep[1].init('A', "sae");

    string word;
    cin >> word;

    stack<char> s,s1,s2,s3,s_true;
    int temp = 0;
    for(int i = word.size() - 1; i >= 0; i--)
    {
        s.push(word[i]);    //倒叙压入s
        if(word[i] == '(')
            temp++;
    }
    
    char flag;
    while(temp--)
    {
        while(s.top() != ')')   
        {
            s1.push(s.top());
            s.pop();
        }
        s.pop();

        while(s1.top() != '(')
        {
            s2.push(s1.top());
            s1.pop();
        }
        s1.pop();

        flag = s2.top();
        s2.pop();

        while(!s2.empty())
        {
            s3.push(s2.top());
            s2.pop();
        }
        while(!s3.empty())
        {
            s1.push(flag);
            s1.push(s3.top());
            s3.pop();
        }
        s1.push(flag);
    }

    while(!s.empty())
    {
        s1.push(s.top());
        s.pop();
    }
    while(!s1.empty())
    {
        s_true.push(s1.top());
        s1.pop();
    }
    
    string ss;
    while(!s_true.empty())
    {
        ss += s_true.top();
        s_true.pop();
    }
    
    for(int i = 0; i < ss.size(); i++)
    {
        if(ss[i] == ep[0].c)
            ss = ss.substr(0, i) + ep[0].s + ss.substr(i + 1);
        if(ss[i] == ep[1].c)
            ss = ss.substr(0, i) + ep[1].s + ss.substr(i + 1);
    }

    cout << ss << endl;
    for(int i = 0; i < ss.size(); i++)
    {
        switch(ss[i])
        {
        case 't':
            cout << "天";
            break;
        case 'd':
            cout << "地";
            break;
        case 's':
            cout << "上";
            break;
        case 'a':
            cout << "一只";
            break;
        case 'e':
            cout << "鹅";
            break;
        case 'z':
            cout << "追";
            break;
        case 'g':
            cout << "赶";
            break;
        case 'x':
            cout << "下";
            break;
        case 'n':
            cout << "蛋";
            break;
        case 'h':
            cout << "恨";
            break;
        }
    }
    cout << endl;
    return 0;
}

