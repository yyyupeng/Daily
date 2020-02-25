#ifndef _LOCKER_H
#define _LOCKER_H

/* 线程同步机制包装类 */

#include <pthread.h>
#include <semaphore.h>
#include <exception>

/* 互斥锁的类 */
class mutex_locker
{
public:
    //创建并初始化
    mutex_locker()
    {
        if(pthread_mutex_init(&m_mutex, NULL) != 0)   
        {
            throw std::exception();
        }
    }
    //销毁
    ~mutex_locker()
    {
        pthread_mutex_destroy(&m_mutex);
    }

    //获取互斥锁
    bool lock()
    {
        return pthread_mutex_lock(&m_mutex) == 0;
    }
    //释放互斥锁
    bool unlock()
    {
        return pthread_mutex_unlock(&m_mutex) == 0;
    }

private:
    pthread_mutex_t m_mutex;
};

/* 条件变量的类 */
class cond_locker
{
public:
    //创建并初始化
    cond_locker()
    {
        if(pthread_mutex_init(&m_mutex, NULL) != 0)
        {
            throw std::exception();
        }
        if(pthread_cond_init(&m_cond, NULL) != 0)
        {
            //释放已分配资源
            pthread_mutex_destroy(&m_mutex);
            throw std::exception();
        }
    }
    //销毁
    ~cond_locker()
    {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_cond);
    }

    //等待条件变量
    bool wait()
    {
        int ret = 0;
        pthread_mutex_lock(&m_mutex);
        ret = pthread_cond_wait(&m_cond, &m_mutex);
        pthread_mutex_unlock(&m_mutex);
        return ret == 0;
    }
    //唤醒等待条件变量的线程
    bool signal()
    {
        return pthread_cond_signal(&m_cond) == 0;
    }
    //唤醒所有等待条件变量的线程
    bool broadcast()
    {
        return pthread_cond_broadcast(&m_cond) == 0;
    }

private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
};

/* 信号量的类 */
class sem_locker
{
public:
    //创建并初始化
    sem_locker() 
    {
        if(sem_init(&m_sem, 0, 0) != 0)
        {
            //构造函数没有返回值，抛出异常来报告错误
            throw std::exception();
        }
    }
    //销毁
    ~sem_locker() 
    {
        sem_destroy(&m_sem);
    }

    //等待信号量
    bool wait()
    {
        return sem_wait(&m_sem) == 0;
    }
    //添加信号量
    bool add()
    {
        return sem_post(&m_sem) == 0;
    }

private:
    sem_t m_sem;
};

#endif


