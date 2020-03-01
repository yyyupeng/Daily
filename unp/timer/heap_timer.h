#ifndef _HEAP_TIMER_H
#define _HEAP_TIMER_H

#include <iostream>
#include <netinet/in.h>
#include <time.h>
#define BUFFER_SIZE 64
using std::exception;

class heap_timer;

/* 绑定socket和定时器 */
struct client_data
{
    sockaddr_in address;
    int sockfd;
    char buf[ BUFFER_SIZE ];
    heap_timer* timer;
};

/* 定时器类 */
class heap_timer
{
public:
    heap_timer( int delay )
    {
        expire = time( NULL ) + delay;
    }

public:
   time_t expire;                   //定时器生效的绝对时间
   void (*cb_func)( client_data* ); //定时器的回调函数
   client_data* user_data;          //用户数据
};

#endif

