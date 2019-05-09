/*
 * @Descripttion: C语言实现LRU（最近最少使用策略缓存淘汰算法
 * @LastEditors: Frame
 * @Author: Frame
 * @LastEditTime: 2019-05-08 11:58:28
 * @Date: 2019-05-08 11:55:00
 * @LastEditTime: 2019-05-09 08:53:53
 * ------------------------------------
 * LRU缓存淘汰算法思路
 *      1）维护一个有序的单链表，越靠近尾部的结点是越早之前访问的，热度是最小的
 *      2）如果向该缓存区存入一个数据：
 *          * 如果此数据之前已经被缓存在链表中：
 *                 * 我们遍历得到这个数据对应的结点
 *                 * 将其从原来的位置删除
 *                 * 然后在插入到链表的头部
 *          * 如果此数据之前没有存在
 *              * 如果缓存区未满，则将此结点直接插入到链表的头部
 *              * 如果缓存区已满，则链表尾结点删除，将新的数据结点插入链表的头部
 */

#define LinkListUse 1
#define ArrayList 0

#if LinkListUse

#include "LinkList.c"

#elif ArrayList

#include "array.c"

#endif

#define LRU_CACHE_SIZE 20 // LRU缓存区最大值
int LRUDataNum = 0;       // 缓存区已经缓存的元素个数

#if LinkListUse
/**
 * @name: LRU_Cache_BasedLinkList(...)
 * @brief: 基于单链表实现的LRU缓存淘汰算法
 * @param  
 *          L 指向已经存在的有序的单链表
 *          e 需要存入缓存区的元素
 * @return: 
 */
void LRU_Cache_BasedLinkList(LinkList *L, ElemType e)
{
    ElemType temp;
    // 查找是新的数据是否已经存在，若是0则不存在，否则是存在的
    int eleIndex = LocateElem(*L, e);
    if (eleIndex != 0) // 之前的元素存在
    {
        // 将元素从原来的位置删除掉
        ListDelete(L, eleIndex, &temp);
        // 将新元素插入到链表头部
        ListInsert(L, 1, e);
    }
    else // 之前的元素不存在
    {
        if (LRUDataNum < LRU_CACHE_SIZE) // LRU缓存区未满
        {
            // 将新元素插入到链表的头部
            ListInsert(L, 1, e);
            // 更新缓存区大小
            LRUDataNum++;
        }
        else // 缓存区已经满了
        {
            // 将列表的尾部结点删除
            ListDelete(L, LRUDataNum, &temp);
            // 将新元素插入到链表头部
            // 将新元素插入到链表头部
            ListInsert(L, 1, e);
        }
    }
}
#endif

#if ArrayList
/**
 * @name: LRU_Cache_BasedArray(...)
 * @brief: 基于数组实现LRU缓存淘汰算法
 * @param 
 *          L 指向已经存在的有序的单链表
 *          e 需要存入缓存区的元素 
 * @return: 
 */
void LRU_Cache_BasedArray(SqList *L, ElemType e)
{
    ElemType temp;
    // 查找是新的数据是否已经存在，若是0则不存在，否则是存在的
    int eleIndex = LocateArrayElem(*L, e);
    if (eleIndex != 0) // 之前的元素存在
    {
        // 将元素从原来的位置删除掉
        ArrayListDelete(L, eleIndex, &temp);
        // 将新元素插入到链表头部
        ArrayListInsert(L, 1, e);
    }
    else // 之前的元素不存在
    {
        if (LRUDataNum < LRU_CACHE_SIZE) // LRU缓存区未满
        {
            // 将新元素插入到链表的头部
            ArrayListInsert(L, 1, e);
            // 更新缓存区大小
            LRUDataNum++;
        }
        else // 缓存区已经满了
        {
            // 将列表的尾部结点删除
            ArrayListDelete(L, LRUDataNum, &temp);
            // 将新元素插入到链表头部
            // 将新元素插入到链表头部
            ArrayListInsert(L, 1, e);
        }
    }
}
#endif

//-------------------------------------------
int main(void)
{
#if LinkListUse
    LinkList L;

    // 初始化链表
    InitList(&L);
    // 模拟生成一个有序的单链表
    for (int i = 1; i <= LRU_CACHE_SIZE / 2; i++)
    {
        ListInsert(&L, i, i);
        // 记录元素的个数
        LRUDataNum++;
    }
    ListToString(L);
    
    // LRU_Cache_BasedLinkList(&L, 6);// 更新缓存，已经存在的元素
    // ListToString(L);
    
    // LRU_Cache_BasedLinkList(&L, 11);// 存入未存在的元素
    // ListToString(L);
    
    // LRU_Cache_BasedLinkList(&L, 12);// 存入未存在的元素
    // L = ListReverse(&L);
    L = ListReverse_1(&L);
    printf("-----执行链表反转----\n");
    ListToString(L);
#endif

#if ArrayList

    SqList L;
    // 初始化链表
    InitArrayList(&L);
    // 模拟生成一个有序的单链表
    for (int i = 1; i <= LRU_CACHE_SIZE / 2; i++)
    {
        ArrayListInsert(&L, i, i);
        // 记录元素的个数
        LRUDataNum++;
    }
    ArrayListToString(L);
    // 更新缓存，已经存在的元素
    LRU_Cache_BasedArray(&L, 6);
    ArrayListToString(L);
    // 存入未存在的元素
    LRU_Cache_BasedArray(&L, 11);
    ArrayListToString(L);
    // 存入未存在的元素
    LRU_Cache_BasedArray(&L, 12);
    ArrayListToString(L);
#endif
}