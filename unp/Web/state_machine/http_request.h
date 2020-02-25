#ifndef _HTTP_REQUEST_H
#define _HTTP_REQUEST_H

#include <iostream>
#include "../webserver/include.h"

#define BUFFER_SIZE 4096

/* 主状态机的两种可能 */
enum CHECK_STATE 
{
    CHECK_STATE_REQUESTLINE = 0,    //正在分析请求行
    CHECK_STATE_HEADER              //正在分析头部字段
};

/* 从状态机有三种可能的状态 */
enum LINE_STATUS
{
    LINE_OK = 0,                    //完整请求
    LINE_BAD,                       //请求出错
    LINE_OPEN                       //行数据不完整
};

/* 服务器处理HTTP请求的结果 */
enum HTTP_CODE
{
    NO_REQUEST,                     //请求不完整
    GET_REQUEST,                    //完整的请求
    BAD_REQUEST,                    //请求含有语法错误
    FORBIDDEN_REQUEST,              //用户对资源没有权限
    INTERNAI_ERROR,                 //服务器内部错误
    CLOSED_CONNETCTION              //客户端关闭连接
};

/* 对客户端的简单回复 */
static const char * szret[] = { "I get a correct result\n", "Something wrong\n" };

/* 从状态机，用于分离出一行内容 */
/* checked_index:已经分析完的，read_index:已经读到的位置 */
LINE_STATUS parse_line(char *buffer, int &checked_index, int &read_index)
{
    char temp;
    
    //逐个字节分析
    for(; checked_index < read_index; checked_index++)
    {   
        temp = buffer[checked_index];

        //如果当前是'\r',则表示可能读到一个完整的行 
        if(temp == '\r')
        {
            if((checked_index + 1) == read_index)       //'\r'是最后一个字符
            {   
                return LINE_OPEN;
            }
            else if(buffer[checked_index + 1] == '\n')  //下一个字符是'\n'
            {   
                buffer[checked_index++] = '\0';
                buffer[checked_index++] = '\0';
                return LINE_OK;
            }
            else        //请求语法错误
            {   
                return LINE_BAD;
            }
        }
        //如果当前是'\n',也有可能读到一个完整的行 
        else if(temp == '\n')
        {
            if((checked_index > 1) && buffer[checked_index - 1] == '\r')
            {
                buffer[checked_index - 1] = '\0';
                buffer[checked_index++] = '\0';
                return LINE_OK;
            }
        }

    }
    return LINE_OPEN;
}

/* 分析请求行 */
HTTP_CODE parse_requestline(char *temp, CHECK_STATE& checkstate)
{
    //找到第一个空格
    char *url = strpbrk(temp," \t");

    //如果请求中没有空格,说明请求有问题
    if(!url)
    {
        return BAD_REQUEST;
    }

    *url++ = '\0';      //把空格变为'\0'结束符

    char *method = temp;
    std::cout << "Method:" << method << std::endl;
    if(strcasecmp(method,"GET") == 0)
    {   
        std::cout << "The request is GET\n" << std::endl;
    }
    else
    {
        return BAD_REQUEST;
    }

    url += strspn(url," \t");
    char *version = strpbrk(url," \t");
    if(!version)
    {
        return BAD_REQUEST;
    }
    *version++ = '\0';
    version += strspn(version," \t");

    //仅支持HTTP/1.1 
    std::cout << "The version is " << version << std::endl;
    if(strcasecmp(version,"HTTP/1.1") != 0)
    {
        return BAD_REQUEST;
    }

    //检查URL是否合法 
    if(strncasecmp(url,"http://",7) == 0)
    {
        url += 7;
        url = strchr(url,'/');
    }

    if(!url || url[0] != '/')
    {
        return BAD_REQUEST;
    }

    std::cout << "The request url is:" << url << std::endl;
    checkstate = CHECK_STATE_HEADER;    //状态转移
    return NO_REQUEST;
}

/* 分析头部字段 */
HTTP_CODE parse_headers(char *temp)
{
    //遇到一个空行说明是一个HTTP请求
    if(temp[0] == '\0')
    {
        return GET_REQUEST;
    }
    else if(strncasecmp(temp,"Host:",5) == 0)
    {
        temp += 5;
        temp += strspn(temp," \t");
        std::cout << "The request host is:" << temp << std::endl;
    }
    else
    {
        std::cout << "I can't handle this header\n" << std::endl;
    }
    return NO_REQUEST;
}

/* 分析HTTP请求的入口函数 */
HTTP_CODE parse_content(char *buffer, int &checked_index, CHECK_STATE &checkstate, int &read_index, int &start_line)
{
    LINE_STATUS linestatus = LINE_OK;       //记录当前行的读取状态
    HTTP_CODE retcode = NO_REQUEST;         //记录HTTP请求的处理结果

    //主状态机用来从buffer中取出所有完整的行 
    while((linestatus = parse_line(buffer,checked_index,read_index)) == LINE_OK)
    {
        char *temp = buffer + start_line;   //startline是行在buffer中的位置
        start_line = checked_index;         //记录下一行的起始位置

        //checkstate记录主状态机当前的状态 
        switch(checkstate)
        {
        case CHECK_STATE_REQUESTLINE:       //第一个状态，分析请求行
            {
               retcode = parse_requestline(temp,checkstate);
               if(retcode == BAD_REQUEST)
               {
                   return BAD_REQUEST;
               }
               break;
            }
        case CHECK_STATE_HEADER:            //第二个状态分析头部字段
            {
                retcode = parse_headers(temp);
                if(retcode == BAD_REQUEST)
                {
                    return BAD_REQUEST;
                }
                else if(retcode == GET_REQUEST )
                {
                    return GET_REQUEST;
                }
                break;
            }
        default:
            return INTERNAI_ERROR;
        }
    }

    //如果没有读取到一个完整的行，则需要继续读取客户数据 
    if(linestatus == LINE_OPEN)
    {
        return NO_REQUEST;
    }
    else
    {
        return BAD_REQUEST;
    }
}

#endif

