/*
 * @Descripttion: 散列表头文件
 * @version: 
 * @Author: Frame
 * @LastEditors: Frame
 * @Date: 2019-04-10 10:58:15
 * @LastEditTime: 2019-04-10 11:13:43
 */
#ifndef __HashTable_H__
#define __HashTable_H__


/* 定义状态值 */
typedef enum
{
    UNSUCCESS = 0x00,
    SUCCESS = 0x01,
} Status;

#define HASH_TABLE_SIZE 1024*1024 // 定义散列表的长度

/* 定义散列表某一节点的数据结构 */
typedef struct
{
    HashNode *pNext;
    char *key;
    void *value;
    void (*free_value)(void *);

}HashNode;

/* 定义hashTable */
typedef struct
{
    HashNode **table;
} HashTable;

/***********************************************************/
unsigned int strHash(const char *key);
HashTable *hashTableNew();
void hashTableDelete(HashTable *ht);
Status hashTableInsert(HashTable *ht, char *key, void *value, void (*free_value)(void *));
void *hashTableGet(HashTable *ht, char *key);
void hashTableRemove(HashTable *ht, char *key);

#endif