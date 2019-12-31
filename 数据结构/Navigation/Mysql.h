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

class Mysql
{
public:
    Mysql() = default;
    ~Mysql() {}
    int MysqlInit();
    void MysqlClose()  { mysql_close(&mysql); }

protected:
    MYSQL mysql;
};

inline int Mysql::MysqlInit()
{
    if(mysql_init(&mysql) == NULL)
    {
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        return -1;
    }
    if(mysql_real_connect(&mysql,NULL,"root","Lyp20000617","Navigation",0,NULL,0) == NULL)
    {
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));
        return -1;
    }
    return 0;
}


