#include "mem_pool.h"

int main()
{
    memPool_t* pool = memPoolInit(32,10);
    if (!pool)
    {
        return 1;
    }
    
    print_pool_status(pool);

    void* ptr1 = memPoolAlloc(pool);
    void* ptr2 = memPoolAlloc(pool);
    void* ptr3 = memPoolAlloc(pool);

    ///< use memory
    if (ptr1)
    {
        strcpy(ptr1,"first block!");
    }
    if (ptr2)
    {
        strcpy(ptr2,"second block!");
    }
    if (ptr3)
    {
        strcpy(ptr3,"third block!");
    }
    
    ///<print
    if (ptr1) printf("ptr1: %s\n", (char*)ptr1);
    if (ptr2) printf("ptr2: %s\n", (char*)ptr2);
    if (ptr3) printf("ptr3: %s\n", (char*)ptr3);

    memPoolFree(pool,ptr2);
    printf("\n after freeing ptr2\n");
    print_pool_status(pool);

    // 再分配一个块
    void* ptr4 = memPoolAlloc(pool);
    if (ptr4) strcpy((char*)ptr4, "Fourth block");
    printf("\nAfter allocating ptr4:\n");
    print_pool_status(pool);
    if (ptr4) printf("ptr4: %s\n", (char*)ptr4);

    // 释放所有块
    memPoolFree(pool, ptr1);
    memPoolFree(pool, ptr3);
    memPoolFree(pool, ptr4);
    printf("\nAfter freeing all blocks:\n");
    print_pool_status(pool);

    // 销毁内存池
    destory_mempool(pool);
    return 0;

}