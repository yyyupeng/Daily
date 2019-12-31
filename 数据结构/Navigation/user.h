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
#include <mysql/mysql.h>
#include "Mysql.h"

#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)

class user : public Mysql
{
public:
    user() = default;
    ~user() {}
    void registe();
    int login();
    void set_disp_mode(int , int );
    void getpasswd(char *, int );
    
private:
    char name[20];
    char passwd[20];
};

inline void user::registe()
{
    printf("\t\t输入你想要注册账号的名称：");
    std::cin >> name;
    printf("\t\t输入你想要注册账号的密码：");
    std::cin >> passwd;

    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char query_str[1000];
    int rows;
    int fields;

    if(MysqlInit() == -1)
    {
        std::cout << "数据库出错！！！" << std::endl;
        exit(-1);
    }
    sprintf(query_str, "select * from user");
    mysql_real_query(&mysql, query_str, strlen(query_str));
    res = mysql_store_result(&mysql);
    rows = mysql_num_rows(res);
    fields = mysql_num_fields(res);
    while((row = mysql_fetch_row(res)))
    {
        if(strcmp(name, row[0]) == 0)
        {
            std::cout << "\t\t" << "该用户已存在，请重新注册！" << std::endl;
            MysqlClose();
            return;
        }
    }
    memset(query_str, 0, strlen(query_str));
    sprintf(query_str, "insert into user values('%s', '%s')", name, passwd);
    mysql_real_query(&mysql, query_str, strlen(query_str));
    std::cout << "\t\t" << "注册成功！" << std::endl;
    MysqlClose();
}

inline int user::login()
{
    printf("\t\t请输入账号名称：");
    scanf("%s",name);
    getchar();                          //将回车符屏蔽掉
    set_disp_mode(STDIN_FILENO,0);      //关闭输出回显
    printf("\t\t请输入账号密码：");
    getpasswd(passwd, 20);
    set_disp_mode(STDIN_FILENO,1);
    system("clear");

    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char query_str[1000];
    int rows;
    int fields;

    if(MysqlInit() == -1)
    {
        std::cout << "数据库出错！！！" << std::endl;
        exit(-1);
    }
    sprintf(query_str, "select * from user");
    mysql_real_query(&mysql, query_str, strlen(query_str));
    res = mysql_store_result(&mysql);
    rows = mysql_num_rows(res);
    fields = mysql_num_fields(res);
    while((row = mysql_fetch_row(res)))
    {
        if(strcmp(name, row[0]) == 0 && strcmp(passwd, row[1]) == 0)
        {
            std::cout << "\t\t" << "登录成功！" << std::endl;
            MysqlClose();
            return 1;
        }
    }
    std::cout << "\t\t" << "登录失败！" << std::endl;
    MysqlClose();
    return 0;
}

inline void user::set_disp_mode(int fd, int option)
{
    int err;
    struct termios term;
    if(tcgetattr(fd,&term) == -1)
    {
        perror("Cannot get the attribution of the terminal");
        exit(-1);
    }
    if(option)
        term.c_lflag |= ECHOFLAGS;
    else
        term.c_lflag &= ~ECHOFLAGS;
    err = tcsetattr(fd,TCSAFLUSH,&term);
    if(err == -1 && err == CINTR)
    {
        perror("Cannot set the attribution of the terminal");
        exit(-1);
    }
}

inline void user::getpasswd(char *passwd, int size)
{
    int c;
    int n = 0;
    do
    {
        c = getchar();
        if (c != '\n')
        {
            passwd[n++] = c;
        }
    }while(c != '\n' && n < (size - 1));
    passwd[n] = '\0';
}
