#include "IMS.h"


Inventory_t *createInventory(int capacity)
{
    if (capacity == 0)
    {
        return NULL;
    }
    
    Inventory_t *new_inventory = (Inventory_t*)malloc(sizeof(Inventory_t));
    if (!new_inventory)
    {
        return NULL;
    }
    
    new_inventory->capacity = capacity;
    new_inventory->count    = 0;
    new_inventory->next_id  = 1;
    new_inventory->produces = (Product_t*)malloc(sizeof(Product_t) * capacity);

    return new_inventory;
}

char *getCurrentDateTime()
{
    static char buffer[20];
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(buffer,sizeof(buffer),"%Y-%m-%d %H:%M:%S",t);
    return buffer; 
}

void destoryInventory(Inventory_t *inventory)
{
    ///< 在释放的时候，先释放掉结构体中的申请的内存，再去释放整个结构体内存
    if (inventory)
    {
        if (inventory->produces)
        {
            free(inventory->produces);
        }
        free(inventory);
    }
}

void destorySalesRecords(SalesRecord_t *head)
{
    while (head)
    {
        SalesRecord_t *temp = head;
        head = head->next;
        free(temp);
    }
}

int addProduct(Inventory_t* inventory, const char *name,const char *category, double price, int quantuty, const char* supplier)
{
    if (!inventory || !name || !category || !supplier || price<0 || quantuty<0)
    {
        return 0;
    }
    
    for (int i = 0; i < inventory->count; i++)
    {
        if (strcmp(inventory->produces[i].name,name) == 0)
        {
            return 0;
        }
    }
    
    ///< 如果有必要扩展容量
    if (inventory->count >= inventory->capacity)
    {
        int new_capacity = inventory->capacity * 2;
        Product_t* newProduct = (Product_t*)realloc(inventory->produces,sizeof(Product_t)*new_capacity);

        if (!newProduct)
        {
            return 0;
        }
        
    }
    
    Product_t *newProduct = &inventory->produces[inventory->count];
    newProduct->id = inventory->next_id++;
    strncpy(newProduct->name,name,sizeof(newProduct->name)-1);
    strncpy(newProduct->category,category,sizeof(newProduct->category)-1);
    newProduct->price = price;
    newProduct->quantity = quantuty;
    strncpy(newProduct->supplier,supplier,sizeof(newProduct->supplier)-1);

    char *current_time = getCurrentDateTime();
    strncpy(newProduct->date_added, current_time, sizeof(newProduct->date_added)-1);
    strncpy(newProduct->last_update, current_time , sizeof(newProduct->last_update)-1);
    
    inventory->count++;
    return newProduct->id;
}