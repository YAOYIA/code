#ifndef __IMS_H
#define __IMS_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Product
{
    int    id;             ///< 产品ID
    char   name[100];      ///< 产品名称
    char   category[50];   ///< 产品类别
    double price;          ///< 价格
    int    quantity;       ///< 数量
    char   supplier[100];  ///< 供应商
    char   date_added[20]; ///< 添加日期
    char   last_update[20];///< 最后更新日期
}Product_t;

///< 库存管理结构体
typedef struct Inventory
{
    Product_t *produces;   ///< 产品数组
    int       count;       ///< 当前产品数量
    int       capacity;    ///< 总容量
    int       next_id;     ///< 下一个可用的产品ID
}Inventory_t;

///< 销售记录结构体
typedef struct SalesRecord
{
    int                record_id;         ///< 记录ID
    int                product_id;        ///< 产品ID
    char               product_name[100]; ///< 产品名称
    int                quantity_sold;     ///< 销售数量
    double             total_amount;      ///< 总金额
    char               sale_date[20];     ///< 销售日期
    struct SalesRecord *next;
}SalesRecord_t;

///< 库存统计结构体
typedef struct CategoryStats
{
    char   category[50];    ///< 类别
    int    total_quantity;  ///< 总数量
    double total_value;     ///< 总价值
    int    product_count;   ///< 产品数量
}CategoryStats_t;

Inventory_t *createInventory(int capacity);
void destoryInventory(Inventory_t *inventory);
void destorySalesRecords(SalesRecord_t *head);
char *getCurrentDateTime();
int addProduct(Inventory_t* Inventory, const char *name,const char *category, double price, int quantuty, const char* supplier);

#endif