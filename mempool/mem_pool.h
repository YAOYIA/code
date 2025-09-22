#ifndef MY_MEM_POOL_H
#define MY_MEM_POOL_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
/*
 * 内存池是内存管理技术，通过预先分配一块大的内存，然后由程序员自己管理这块内存的分配和释放，
 * 而不是每次都直接向操作系统申请内存
 * 传统的内存分配缺点
 *  1.malloc、free需要系统调用，设计内核态和用户态的切换，性能开销大
 *  2.内存碎片：频繁分配和释放不同大小的内存块会导致内存碎片
 *  3.不可预测性：系统调用的时间开销不确定，对实时的系统不友好
 *  4.同步开销：在多线程的环境下，系统级的内存分配需要加锁
 *  ###################################################
 *  内存池基本思想
 *  1.预先分配：一次性向操作系统申请一大块连续内存
 *  2.自主管理：程序自己管理这块内存的分配和释放
 *  3.减少系统调用：只在初始化和销毁的时候与操作系统交互
 */

/*
    +-------------------+      +----------------------+
| 初始化内存池         |      | 从内存池分配内存        |
| - 申请大块内存       |----->| - 在池中寻找空闲块     |
| - 设置管理结构       |      | - 标记为已使用         |
+-------------------+      +----------------------+
         ^                          |
         |                          v
+-------------------+      +----------------------+
| 销毁内存池          |<-----| 释放内存到内存池       |
| - 释放整块内存       |      | - 标记块为空闲        |
| - 释放管理结构       |      | - 合并相邻空闲块      |
+-------------------+      +----------------------+
*/
typedef struct memBlolk
{
    struct memBlolk *next;//指向下一个内存块
}memBlock_t;

typedef struct
{
    size_t block_size;///<每个内存块的大小
    memBlock_t *free_block;///<空闲块的链表
    char *pool_start;///< 内存池的起始结构
    size_t total_blocks;///< 总块数
    size_t used_blocks;///< 已经使用的块数
}memPool_t;


memPool_t *memPoolInit(size_t block_size,size_t num_blocks);

void *memPoolAlloc(memPool_t *mempool);

void memPoolFree(memPool_t *pool, void *ptr);

void destory_mempool(memPool_t *pool);

void print_pool_status(memPool_t* pool);
#endif