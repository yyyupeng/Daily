#ifndef _MY_STRING_H
#define _MY_STRING_H

#include <iostream>
#include <cstring>
using namespace std;

class my_string
{
    friend ostream& operator << (ostream& os, my_string& cstr);
    friend istream& operator >> (istream& is, my_string& cstr);

public:
    my_string();
    my_string(const char *cstr);
    my_string(const int n, const char c);
    my_string(const my_string& cstr);
    ~my_string() { delete [] m_data; }

    my_string& operator=(const my_string& cstr);
    my_string operator+(const my_string& cstr);
    my_string& operator+=(const my_string& cstr);
    bool operator==(const my_string& cstr);
    bool operator!=(const my_string& cstr);
    bool operator>(const my_string& cstr);
    bool operator>=(const my_string& cstr);
    bool operator<(const my_string& cstr);
    bool operator<=(const my_string& cstr);
    char& operator[](const int n);
    int find(char c, int pos = 0);
    int find(char *cstr, int pos = 0);
    int find(my_string& cstr, int pos = 0);
    
    char *get_cstr() const { return m_data; }
    size_t size() const { return strlen(m_data); }
    size_t length() const { return strlen(m_data); }
    bool empty();
    void resize(const int len, const char c);
    char *substr(const int pos, const int n);
    void swap(my_string& cstr);

private:
    char *m_data;

public:
    class my_iterator
    {
    public:
        my_iterator();
        my_iterator(const my_iterator& mi);
        my_iterator(const my_string *ms, int n = 0);
        ~my_iterator() { it = nullptr; index = 0; }

        char operator*() { return *(it->get_cstr() + index); }
        my_iterator operator++();
        my_iterator operator--();
        bool operator==(const my_iterator& mi);
        my_iterator operator+(const int n);
        my_iterator operator-(const int n);
        bool operator<(const my_iterator& mi);

    private:
        const my_string *it;
        size_t index;
    };
    
    //my_string类中，my_iterator类外
    my_iterator begin() const { return my_iterator(this, 0); }
    my_iterator end() const { return my_iterator(this, this->size()); }
};

inline my_string::my_string()
{
    m_data = new char[1];
    *m_data = '\0';
}

inline my_string::my_string(const char *cstr)
{
    if(!cstr)
    {
        m_data = new char[1];
        *m_data = '\0';
    }
    else    
    {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
    }
}

inline my_string::my_string(const int n, const char c)
{
    m_data = new char[n + 1];
    for(int i = 0; i < n; ++i)
    {
        m_data[i] = c;
    }
    m_data[n] = '\0';
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
    /*
    if(this == &cstr)    //检查自我赋值
        return *this;

    delete [] m_data;
    m_data = new char[strlen(cstr.m_data) + 1];
    strcpy(m_data, cstr.m_data);
    return *this;
    */
    if(this != &cstr) 
    {
        my_string Temp(cstr);
        char *pTemp = Temp.m_data;
        Temp.m_data = m_data;
        m_data = pTemp;
    }
    return *this;
}

//重载+
inline my_string my_string::operator + (const my_string& cstr)
{
    my_string New;
    New.m_data = new char[this->size() + cstr.size() + 1];
    strcpy(New.m_data, m_data);
    strcat(New.m_data, cstr.m_data);
    return New;
}

//重载+=
inline my_string& my_string::operator += (const my_string& cstr)
{
    char *New = new char[this->size() + cstr.size() + 1];
    strcpy(New, m_data);
    strcat(New, cstr.m_data);
    delete [] m_data;
    m_data = New;
    return *this;
}

//重载==
inline bool my_string::operator == (const my_string& cstr)
{
    if(this->size() != cstr.size())
        return false;
    return strcmp(m_data, cstr.m_data) ? false : true;
}

//重载!=
inline bool my_string::operator != (const my_string& cstr)
{
    if(strcmp(m_data, cstr.m_data) == 0)
    {
        return false;
    }
    return true;
}

//重载>
inline bool my_string::operator > (const my_string& cstr)
{
    if(this->size() > cstr.size())
    {
        return true;
    }
    else
    {
        if(strcmp(m_data, cstr.m_data) > 0)
            return true;
    }
    return false;
}

//重载>=
inline bool my_string::operator >= (const my_string& cstr)
{
    if(this->size() > cstr.size())
    {
        return true;
    }
    else
    {
        if(strcmp(m_data, cstr.m_data) >= 0)
            return true;
    }
    return false;
}

//重载<
inline bool my_string::operator < (const my_string& cstr)
{
    if(this->size() < cstr.size())
    {
        return true;
    }
    else
    {
        if(strcmp(m_data, cstr.m_data) < 0)
            return true;
    }
    return false;
}

//重载>
inline bool my_string::operator <= (const my_string& cstr)
{
    if(this->size() < cstr.size())
    {
        return true;
    }
    else
    {
        if(strcmp(m_data, cstr.m_data) <= 0)
            return true;
    }
    return false;
}

//重载[]
inline char& my_string::operator [] (const int n)
{
    if(n < 0 || n >= this->size())    //越界
    {
        return m_data[0];
    }
    else
    {
        return m_data[n];
    }
}

//从pos开始查找字符c在当前字符串的位置
inline int my_string::find(char c, int pos)
{
    if(pos < 0 || pos > this->empty())
        return -1;
    for(int i = pos; i < this->empty(); ++i)
    {
        if(m_data[i] == c)
            return i;
    }
    return -1;
}

//从pos开始查找字符串cstr在当前串中的位置
inline int my_string::find(char *cstr, int pos)
{
    size_t size = strlen(cstr);
    if(pos < 0 || pos + size > this->empty())
        return -1;
    char *p = new char[this->empty() - size + 1];
    memcpy(p, m_data + pos - 1, this->empty() - pos + 1);   
    char *q = strstr(p, cstr);
    size = q - p + pos - 1;
    delete [] p;
    return size;
}
inline int my_string::find(my_string& cstr, int pos)
{
    size_t size = cstr.empty();
    if(pos < 0 || pos + size > this->empty())
        return -1;
    char *p = new char[this->empty() - size + 1];
    memcpy(p, m_data + pos, this->empty() - pos + 1);   
    char *q = strstr(p, cstr.m_data);
    if(q == nullptr)
        return -1;
    size = q - p + pos;
    delete [] p;
    return size;
}

//是否为空
inline bool my_string::empty()
{
    if(m_data == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//把字符串当前大小置为len，并用字符c
inline void my_string::resize(const int len, const char c)
{
    delete [] m_data;
    m_data = new char[len];
    for(int i = 0; i < len; ++i)
    {
        m_data[i] = c;
    }
}

//返回pos开始的n个字符组成的字符串
inline char* my_string::substr(const int pos, const int n)
{
    char *Temp = new char[n];
    int k = 0;
    for(int i = pos; i < pos + n; ++i)
    {
        Temp[k] = m_data[i];
        ++k;
    }
    Temp[k] = '\0';
    return Temp;
}

//交换
inline void my_string::swap(my_string& cstr)
{
    char *s1 = new char[strlen(m_data) + 1];
    char *s2 = new char[strlen(cstr.m_data) + 1];
    strcpy(s1, cstr.m_data);
    strcpy(s2, m_data);
    delete [] m_data;
    delete [] cstr.m_data;
    m_data = s1;
    cstr.m_data = s2;
}

//重载<<
inline ostream& operator << (ostream& os, my_string& cstr)
{
    return os << cstr.get_cstr();
}

//重载>>
inline istream& operator >> (istream& is, my_string& cstr)
{
    my_string Temp;
    is >> Temp.m_data;
    cstr.m_data = new char[strlen(Temp.m_data) + 1];
    strcpy(cstr.m_data, Temp.m_data);
    return is;
}

//迭代器构造函数
inline my_string::my_iterator::my_iterator()
{
    it = nullptr;
    index = 0;
}
inline my_string::my_iterator::my_iterator(const my_iterator& mi)
{
    it = mi.it;
    index = mi.index;
}
inline my_string::my_iterator::my_iterator(const my_string *ms, int n)
{
    it = ms;
    index = n;
}

//重载++
inline my_string::my_iterator my_string::my_iterator::operator ++ ()
{
    my_iterator copy(*this);
    if(it == nullptr)
    {
        cout << "error!" << endl;
        exit(1);
    }

    if(++index > it->length())
        it = nullptr;
    return copy;
}

//重载--
inline my_string::my_iterator my_string::my_iterator::operator -- ()
{
    my_iterator copy(*this);
    if(it == nullptr)
    {
        cout << "error!" << endl;
        exit(1);
    }

    if(--index > it->length() || index < 0)
        it = nullptr;
    return copy;
}

//重载==
inline bool my_string::my_iterator::operator == (const my_iterator& mi)
{
    if(it != mi.it)
    {
        cout << "迭代器不同!" << endl;
        exit(1);
    }
    return (it == mi.it && index == mi.index);
}

//重载+
inline my_string::my_iterator my_string::my_iterator::operator + (const int n)
{
    if(it == nullptr)
    {
        cout << "error!" << endl;
        exit(1);
    }
    return my_iterator(it, index + n);
}

//重载-
inline my_string::my_iterator my_string::my_iterator::operator - (const int n)
{
    if(it == nullptr)
    {
        cout << "error!" << endl;
        exit(1);
    }
    return my_iterator(it, index - n);
}

//重载<
inline bool my_string::my_iterator::operator < (const my_iterator& mi)
{
    if(it != mi.it)
    {
        cout << "迭代器不同!" << endl;
        exit(1);
    }
    return (index < mi.index);
}

#endif
