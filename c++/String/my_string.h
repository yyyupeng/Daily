#ifndef _MY_STRING_H
#define _MY_STRING_H

#include <iostream>
#include <cstring>
using namespace std;

class my_string
{
public:
    my_string();
    my_string(const char *cstr);
    my_string(const my_string& cstr);
    my_string& operator=(const my_string& cstr);
    ~my_string() { delete [] m_data; }
    char *get_c_str() const { return m_data; }

private:
    char *m_data;
};

inline my_string::my_string()
{
    m_data = nullptr;
}

inline my_string::my_string(const char *cstr)
{
    if(cstr)
    {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
    }
    else    //未指定初值
    {
        m_data = nullptr;
    }
}

//拷贝构造
inline my_string::my_string(const my_string& cstr)
{
    m_data = new char[strlen(cstr.m_data) + 1];
    strcpy(m_data, cstr.m_data);
}

//拷贝赋值
inline my_string& my_string::operator = (const my_string& cstr)
{
    if(this == &cstr)    //检查自我赋值
        return *this;

    delete [] m_data;
    m_data = new char[strlen(cstr.m_data) + 1];
    strcpy(m_data, cstr.m_data);
    return *this;
}

//重载<<
inline ostream& operator << (ostream& os, my_string& cstr)
{
    return os << cstr.get_c_str();
}

#endif
