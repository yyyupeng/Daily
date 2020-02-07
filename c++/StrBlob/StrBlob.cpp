#include <iostream>
#include "StrBlob.h"
using namespace std;

//初始化列表
StrBlob::StrBlob() : data(make_shared<vector<string>> ()) {}
StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>> (il)) {}

//检查操作
void StrBlob::check(size_type i, const string &msg) const
{
    if(i >= data->size())
        throw out_of_range(msg);
}

//如果vector为空，check会抛出一个异常
void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}
string& StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}
string& StrBlob::back()
{
    check(0, "pop_back on empty StrBlob");
    return data->back();
}
