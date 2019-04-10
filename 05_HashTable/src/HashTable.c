/*
 ============================================================================
 Name        : hashTableDemo.c
 Author      : Frame
 Version     :
 Copyright   : Your copyright notice
 Description : C语言实现散列表，因为python的字典(dict)已经实现，此处采用的是如果发生冲突时，采用
            线性列表添加
 ============================================================================
 */
#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/**
 * @name: initHashNode(...)
 * @brief: 初始化散列表存储的节点
 * @param HashNode * pNode  指向HashNode类型的节点指针 
 * @return: 
 */
static void initHashNode(HashNode *pNode)
{
    pNode->pNext = NULL;
    pNode->key = NULL;
    pNode->value = NULL;
    pNode->free_value = NULL;
}
/**
 * @name: freeHashNode(...)
 * @brief: 释放/删除无用的节点
 * @param HashNode * pNode  指向HashNode类型的节点指针 
 * @return: 
 */
static void freeHashNode(HashNode *pNode)
{
    if (pNode)
    {
        if (pNode->free_value)
        {
            pNode->free_value(pNode->value);
        }
        free(pNode->key);
        pNode->key = NULL;
        free(pNode);
    }
}
/**
 * @name: strHash
 * @brief: 字符串hash产生函数，采用Times33算法
 * @param key 键
 * @return: 返回得到key对应的hash值
 */
unsigned int strHash(const char *key)
{
    unsigned int hash = 0;
    while (*key)
    {
        hash = (hash << 5) + hash + *key++;
    }
    return hash;
}

/**
 * @name: hashTableNew()
 * @brief: 创建/初始化一个hashTble实例
 * @param None
 * @return: 指向一个HasHTable类型的指针
 */
HashTable *hashTableNew()
{
    HashTable *ht = malloc(sizeof(HashTable));
    if (ht == NULL)
    {
        hashTableDelete(ht);
        return NULL;
    }
    ht->table = malloc(sizeof(HashNode *) * HASH_TABLE_SIZE);
    if (ht->table == NULL)
    {
        hashTableDelete(ht);
        return NULL;
    }
    memset(ht->table, 0, sizeof(HashNode *) * HASH_TABLE_SIZE);

    return ht;
}
/**
 * @name: hashTableDelete(...)
 * @brief: 释放/删除HashTable表
 * @param 指向一个HasHTable类型的指针 
 * @return: None
 */
void hashTableDelete(HashTable *ht)
{
    if (ht)
    {
        if (ht->table)
        {
            int i = 0;
            for (i = 0; i < HASH_TABLE_SIZE; i++)
            {
                HashNode *pNode = ht->table[i];
                HashNode *qNode = NULL;
                while (pNode)
                {
                    qNode = pNode->pNext;
                    free(pNode);
                    pNode = qNode;
                }
            }
            free(ht->table);
            ht->table = NULL;
        }
        free(ht);
    }
}
/**
 * @name: hashTableInsert(...)
 * @brief: 插入新的键值对，如果已存在key 则更新value,如果冲突则添加链表
 * @param: 
 *          HashTable *ht,     目的散列表 
 *          char *key, void *value, 键-值对
 *          void (*free_value)(void *) 自动释放的值
 * @return: 
 */
Status hashTableInsert(HashTable *ht, char *key, void *value, void (*free_value)(void *))
{
    int pos = strHash(key) % HASH_TABLE_SIZE;
    HashNode *pNode = ht->table[pos];
    HashNode *preNode = pNode;

    while (pNode)
    {
        /* 如果key已经存在，则更新value的值 */
        if (strcmp(pNode->key, key) == 0)
        {
            if (pNode->free_value)
            {
                pNode->free_value(pNode->value);
            }
            pNode->value = value;
            pNode->free_value = free_value;
            break;
        }
        preNode = pNode;
        pNode = pNode->pNext;
    }
    /* 如果key没有存在过，则添加 */
    if (pNode == NULL)
    {
        char *kstr = malloc(strlen(key) + 1);
        if (kstr == NULL)
        {
            return UNSUCCESS;
        }
        HashNode *pNode = malloc(sizeof(HashNode));
        if (NULL == pNode)
        {
            free(kstr);
            kstr = NULL;
            return UNSUCCESS;
        }
        initHashNode(pNode);
        pNode->pNext = NULL;
        strcpy(kstr, key);
        pNode->key = kstr;
        pNode->value = value;
        pNode->free_value = free_value;

        if (preNode == NULL)
        {
            ht->table[pos] = pNode;
        }
        else
        {
            preNode->pNext = pNode;
        }
    }
    return SUCCESS;
}
/**
 * @name: hashTableGet(...)
 * @brief: get函数，由指定的key得到对应的value
 * @param 
 *          HashTable *ht,  目的散列表 
 *          char *key       键
 * @return: 如果存在key,则返回对应的指向value的指针，如果没有则返回NULL
 */
void *hashTableGet(HashTable *ht, char *key)
{
    int pos = strHash(key) % HASH_TABLE_SIZE;
    HashNode *pNode = ht->table[pos];
    while (pNode)
    {
        if (strcmp(key, pNode->key) == 0)
        {
            return pNode->value;
        }
        pNode = pNode->pNext;
    }
    return NULL;
}
/**
 * @name: hashTableRemove(...)
 * @brief: 删除对应键的元素
 * @param 
 *          HashTable *ht,  目的散列表 
 *          char *key       键
 * @return: 
 */
void hashTableRemove(HashTable *ht, char *key)
{
    int pos = strHash(key) % HASH_TABLE_SIZE;
    HashNode *pNode = ht->table[pos];
    HashNode *preNode = pNode;
    while (pNode)
    {
        if (strcmp(key, pNode->key) == 0)
        {
            freeHashNode(pNode);
            if (pNode == preNode)
            {
                ht->table[pos] = NULL;
            }
            else
            {
                preNode->pNext = pNode->pNext;
            }
        }
        preNode = pNode;
        pNode = pNode->pNext;
    }
}

