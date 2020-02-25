#ifndef _THREADPOOL_H
#define _THREADPOOL_H

/* 半同步/半反应堆线程池 */
/* 使用互斥锁和条件变量保护任务队列 */

#include <iostream>
#include <cstdio>
#include <queue>
#include "locker.h"

template<typename T>
class threadpool
{
public:
    threadpool(int num = 10); 
    ~threadpool();
    bool appjob(T *task);

private:
    mutex_locker MutexQueue;
    cond_locker CondQueue;
    int thread_num;             //线程池中线程数
    pthread_t *threads;          //线程数组
    std::queue<T *> TaskQueue;  //任务队列
    bool m_stop;                //是否结束线程

    //工作线程所运行函数
    static void *worker(void *arg);     //静态
    void run();
    T *getTask();
};

template<typename T>
threadpool<T>::threadpool(int num) : thread_num(num), threads(nullptr), m_stop(false)
{
    if(thread_num <= 0)
    {
        std::cout << "thread_num <= 0" << std::endl;
        throw std::exception();
    }
     
    threads = new pthread_t[thread_num];
    if(!threads)
    {
        std::cout << "threads is nullptr" << std::endl;
        throw std::exception();
    }

    //创建线程，并设置它们为脱离线程
    for(int i = 0; i < thread_num; ++i)
    {
        std::cout << "create the " << i << "th thread" << std::endl;
        if(pthread_create(&threads[i], NULL, worker, this) != 0)
        {
            //创建失败释放已分配资源
            delete [] threads;
            throw std::exception();
        }
        if(pthread_detach(threads[i]))
        {
            delete [] threads;
            throw std::exception();
        }
    }
}

template<typename T>
threadpool<T>::~threadpool()
{
    delete [] threads;
    m_stop = true;
    CondQueue.broadcast();
}

template<typename T>
bool threadpool<T>::appjob(T *task)
{
    //添加任务是记得上锁，并判断队列是否为空
    MutexQueue.lock();
    bool flag = TaskQueue.empty();
    TaskQueue.push(task);
    MutexQueue.unlock();

    //如果队列为空，需要唤醒某个线程
    if(flag)
    {
        CondQueue.signal();
    }
    return true;
}

template<typename T>
void *threadpool<T>::worker(void *arg)
{
    threadpool *pool = (threadpool *)arg;
    pool->run();
    return pool;
}

template<typename T>
void threadpool<T>::run()
{
    while(!m_stop)
    {
        T *task = getTask();
        if(task == NULL)
            CondQueue.wait();
        else
        {
            task->doit();
            delete task;    //之前new的，手动free
        }
    }
}

template<typename T>
T *threadpool<T>::getTask()
{
    T *task = NULL;
    MutexQueue.lock();
    //队列不为空
    if(!TaskQueue.empty())
    {
        task = TaskQueue.front();
        TaskQueue.pop();
    }
    MutexQueue.unlock();
    return task;
}

#endif
