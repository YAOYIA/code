#include "mem_pool.h"

/**
 * 创建内存池,预分配指定大小和数量的内存块
 * @param block_size 每个内存块的大小
 * @param num_blocks 内存块的数量
 * @return 成功返回内存池，失败返回NULL
 */
memPool_t *memPoolInit(size_t block_size,size_t num_blocks)
{
    if (block_size < sizeof(memBlock_t) || num_blocks==0)
    {
        fprintf(stderr,"Invalid block size or number of blocks\n.");
        return NULL;
    }
    
    size_t total_size  = num_blocks * block_size + sizeof(memPool_t);
    
    ///< 因为malloc分配的一块连续的内存地址，这块内存包含两部分：
    ///< 1.存储内存池的管理结构  2.用作实际分配给用户的内存块
    ///< 先将返回值存为 void* 可以清晰表示这是整个内存池的起始地址
    ///< 之后再转换为memorypool，则明确表示 从这个起始地址开始，前半部分是管理结构体
    ///< 这种代码逻辑更直观：先拿到整块内存，再“切分”出管理的部分
    void *newpool = malloc(total_size);
    
    if (!newpool)
    {
        fprintf(stderr,"failed to alloc memory for pool.\n");
        return NULL;
    }
    
    memPool_t *pool = (memPool_t*)newpool;
    pool->block_size = block_size;
    pool->free_block = NULL;
    pool->pool_start = (char*)newpool + sizeof(memPool_t);
    pool->total_blocks = num_blocks;
    pool->used_blocks = 0;
    
    ///< 初始化空闲链表\
    ///< 核心作用是初始化内存池中的所有内存块，并将他们组织成一个单链表
    ///< free_blocks -> 块3 -> 块2 -> 块1 -> NULL
    char* current = pool->pool_start;
    for (size_t i = 0; i < num_blocks; i++)
    {
        ///< 将当前的current指向的内存块强制转换为memBlcok_t的类型
        ///< memoryblock结构体中只有一个next指针，用于链接其他的空闲块
        memBlock_t *block = (memBlock_t*)current;
        ///< 将当前块的next指针指向链表的“当前头部”，初始时pool->free_block=NULL，第一块的next设置为NULL
        block->next = pool->free_block;
        ///< 更新链表头部为当前块，相当于将当前块“插入”到空闲链表的头部
        pool->free_block = block;
        current += block_size;
    }

    return pool;
}

/**
 * 从内存池分配内存
 * @param pool 内存池指针
 * @return 成功返回分配的内存指针，失败返回NULL
 */
void *memPoolAlloc(memPool_t *mempool)
{
    if (!mempool || mempool->free_block == 0)
    {
        fprintf(stderr,"no memory!");
        return NULL;
    }

    memBlock_t *block = mempool->free_block;
    mempool->free_block = block->next;
    mempool->used_blocks++;

    return (void*)block;
}

/**
 * 将内存释放回内存池
 * @param pool 内存池指针
 * @param ptr 要释放的内存指针
 */
void memPoolFree(memPool_t *pool, void *ptr)
{
    if (!pool || !ptr)
    {
        return;
    }
    
    char *p = (char*)ptr;
    if (p < pool->pool_start || p>=pool->pool_start + pool->block_size*pool->total_blocks)
    {
        fprintf(stderr,"invalid pointer to free.\n");
        return;
    }

    //将块重新加入空闲链表
    memBlock_t *block = (memBlock_t*)ptr;
    block->next=pool->free_block;
    pool->free_block = block;
    pool->used_blocks--;
}



void destory_mempool(memPool_t *pool)
{
    if (pool)
    {
        free(pool);
    }
}

void print_pool_status(memPool_t* pool)
{
    printf("Memory pool status:\n");
    printf("Block size: %zu bytes\n",pool->block_size);
    printf("Total blocks: %zu\n",pool->total_blocks);
    printf("Used blocks: %zu\n",pool->used_blocks);
    printf("Free blocks:%zu\n",pool->total_blocks-pool->used_blocks);
}