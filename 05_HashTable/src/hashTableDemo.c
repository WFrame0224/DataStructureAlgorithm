/*
 ============================================================================
 Name        : hashTableDemo.c
 Author      : Frame
 Version     :
 Copyright   : Your copyright notice
 Description : C语言实现散列表，因为python的字典(dict)已经实现
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* 定义状态值 */
typedef enum
{
    UNSUCCESS = 0x00,
    SUCCESS = 0x01,
} Status;

#define HASH_TABLE_MAX_SIZE 10000 // 定义散列表的长度

/* 定义散列表某一节点的数据结构 */
typedef struct
{
    char *skey;
    int nValue;
    HashNode *pNext;
} HashNode;

HashNode *hashTable[HASH_TABLE_MAX_SIZE]; // 创建一定大小的哈希数组，每个数组的元素是一个hashNode
int hashTableSize = 0;                    // hash table 中的key-value对数

/**
 * @name: initHashTable
 * @brief: 散列表初始化，分配内存，指定散列表大小
 * @param HashTable *H ： 散列表
 * @return: 状态
 */
Status initHashTable()
{
    hash_table_size = 0;
    // 初始化数组缓存区
    meset(hashTable, 0, sizeof(HashNode*) * HASH_TABLE_MAX_SIZE);
}

int main(void)
{
    puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
    return EXIT_SUCCESS;
}
