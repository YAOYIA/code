#include "thread_pool.h"
#include <stdlib.h>
#include <stdio.h>
///< 创建线程池
thread_pool_t *thread_pool_create(int thread_count)
{
    thread_pool_t *pool = (thread_pool_t*)malloc(sizeof(thread_pool_t));
    if (pool == NULL)
    {
        fprintf(stderr,"创建线程池失败！");
        return NULL;
    }

    pool->thread_count    = thread_count;
    pool->queue_size      = 0;
    pool->active_threads  = 0;
    pool->shutdown        = false;
    pool->task_queue_head = NULL;
    pool->task_queue_tail = NULL;    
    return pool;
}

///< 添加任务到线程池
int thread_pool_add_task(thread_pool_t *pool, void(*function)(void*), void *arg)
{
    
}

///< 销毁线程池
int thread_pool_destory(thread_pool_t* pool, bool graceful);

///< 获取线程池的状态
void thread_pool_get_status(thread_pool_t *pool, int *queue_size, int *active_threads);