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

/**
 * @brief 销毁销售记录链条
 */
void destorySalesRecords(SalesRecord_t *head)
{
    while (head)
    {
        SalesRecord_t *temp = head;
        head = head->next;
        free(temp);
    }
}

/**
 * @brief 添加产品
 */
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

int updateProduct(Inventory_t* Inventory, int id, const char *name, const char *category, double price, int quantuty, const char* supplier)
{
    if (!Inventory || !name || !category || !supplier || price<0 || quantuty<0)
    {
        return 0;
    }

    Product_t *product = findProductById(Inventory, id);
    if (!product)
    {
        return 0;
    }
    
    ///< 检查名称是否与其他冲突
    for (size_t i = 0; i < Inventory->count; i++)
    {
        if (Inventory->produces[i].id !=id && strcmp(Inventory->produces[i].name, name) == 0)
        {
            return 0;
        }
    }

    strncpy(product->name, name, sizeof(product->name)-1);
    strncpy(product->category, category, sizeof(product->category)-1);
    product->price = price;
    product->quantity = quantuty;
    strncpy(product->supplier, supplier, sizeof(product->supplier)-1);

    char *current_time = getCurrentDateTime();
    strncpy(product->last_update, current_time, sizeof(product->last_update)-1);

    return 1;
}

/**
 * 删除产品
 */
int deleteProduct(Inventory_t* Inventory, int id)
{
    if(! Inventory)
    {
        return 0;
    }

    for (size_t i = 0; i < Inventory->count; i++)
    {
        if (Inventory->produces[i].id == id)
        {
            for (int j = i; j < Inventory->count; j++)
            {
                Inventory->produces[j] = Inventory->produces[j++];
            }
            Inventory->count--;
            return 1;
        }
    }

    return 0;
}

Product_t *findProductById(const Inventory_t* Inventory, int id)
{
    if (! Inventory)
    {
        return NULL;
    }

    for (int i = 0; i < Inventory->count; i++)
    {
        if (Inventory->produces->id == id)
        {
            return &Inventory->produces[i];
        }
    }
    
    return NULL; 
}

Product_t *findProductByName(const Inventory_t* Inventory, const char *name)
{
    if (!Inventory || ! name)
    {
        return NULL;
    }
    
    for (int i = 0; i < Inventory->count; i++)
    {
        if (strcmp(Inventory->produces[i].name,name) == 0)
        {
            return &Inventory->produces[i];
        }
    }
    
    return NULL;
}

Product_t *findProductByCategory(const Inventory_t *Inventory, const char *category, int *result_count)
{
    if (!Inventory || ! category || ! result_count)
    {
        return NULL;
    }

    *result_count = 0;

    //计算匹配的数量
    for (int i = 0; i < Inventory->count; i++)
    {
        if (strcmp(Inventory->produces[i].category,category) == 0)
        {
            (*result_count)++;
        }
    }

    if (*result_count == 0)
    {
        return NULL;
    }
    
    ///< 分配结果数组
    Product_t** product = NULL;

}

int sellProduct(Inventory_t *Inventory, int product_id, int quantity, SalesRecord_t** sales_head)
{

}

int restockProduct(Inventory_t *Inventory, int product_id, int quantity)
{

}

double calculateInventoryValue(const Inventory_t* inventory)
{

}

CategoryStats_t* getCategoryStats(const Inventory_t* inventory, int* stats_count)
{

}

void generateInventoryReport(const Inventory_t* inventory, const char* filename)
{

}

void generateSalesReport(const SalesRecord_t* sales_head, const char* filename)
{

}

SalesRecord_t* filterSalesByDate(const SalesRecord_t* head, const char* start_date, const char* end_date);
void sortProductsByPrice(Inventory_t* inventory, int ascending);
void sortProductsByQuantity(Inventory_t* inventory, int ascending);
int saveInventoryToFile(const Inventory_t* inventory, const char* filename);
int loadInventoryFromFile(Inventory_t* inventory, const char* filename);
int saveSalesToFile(const SalesRecord_t* head, const char* filename);
SalesRecord_t* loadSalesFromFile(const char* filename);
void displayProduct(const Product_t* product)
{
    if (!product)
    {
        fprintf(stderr,"产品不存在！\n");
        return;
    }

    printf("ID: %d\n", product->id);
    printf("名称: %s\n", product->name);
    printf("类别: %s\n", product->category);
    printf("价格: ¥%.2f\n", product->price);
    printf("数量: %d\n", product->quantity);
    printf("供应商: %s\n", product->supplier);
    printf("添加日期: %s\n", product->date_added);
    printf("最后更新: %s\n", product->last_update);
    printf("----------------------------------------\n");
}

void displayInventory(const Inventory_t* inventory)
{
    if (!inventory)
    {
        fprintf(stderr,"库存系统未初始化！\n");
        return;
    }
    
    printf("\n=== 库存清单 ===\n");
    printf("%-5s %-20s %-15s %-10s %-8s %-15s\n", 
           "ID", "名称", "类别", "价格", "数量", "供应商");
    printf("------------------------------------------------------------------------\n");
    
    for (int i = 0; i < inventory->count; i++) {
        const Product_t* p = &inventory->produces[i];
        printf("%-5d %-20s %-15s ¥%-9.2f %-8d %-15s\n", 
               p->id, p->name, p->category, p->price, p->quantity, p->supplier);
    }
    
    double total_value = calculateInventoryValue(inventory);
    printf("------------------------------------------------------------------------\n");
    printf("总计: %d 种产品, 库存总价值: ¥%.2f\n", inventory->count, total_value);
}
void displaySalesRecords(const SalesRecord_t* head)
{

}