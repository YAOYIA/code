#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>
#include <stdbool.h>

///< 任务的结构体
typedef struct task
{
    void (*function)(void* arg);//任务函数指针
    void *args;                 //任务参数
    struct task *next;          //下一个任务指针
}task_t;

///< 线程池结构体
typedef struct thread_pool
{
    pthread_mutex_t lock;             ///< 互斥锁
    pthread_cond_t  notify;           ///< 条件变量
    pthread_t       *threads;         ///< 工作线程数组
    pthread_t       sentinel_thread;  ///< 哨兵线程
    task_t          *task_queue_head; ///< 任务队列头
    task_t          *task_queue_tail; ///< 任务队列尾
    int             thread_count;     ///< 工作线程的数量
    int             queue_size;       ///< 任务队列的大小
    bool            shutdown;         ///< 关闭标志
    int             active_threads;   ///< 活跃线程计数
}thread_pool_t;

///< 函数声明
///< 创建线程池
thread_pool_t *thread_pool_create(int thread_count);

///< 添加任务到线程池
int thread_pool_add_task(thread_pool_t *pool, void(*function)(void*), void *arg);

///< 销毁线程池
int thread_pool_destory(thread_pool_t* pool, bool graceful);

///< 获取线程池的状态
void thread_pool_get_status(thread_pool_t *pool, int *queue_size, int *active_threads);
#endif