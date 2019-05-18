/*
 * @Descripttion: 链表实现队列(带头结点的队列)
 * @version: 
 * @Author: Frame
 * @LastEditors: Frame
 * @Date: 2019-05-18 11:49:00
 * @LastEditTime: 2019-05-18 15:58:37
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */

#define MAXSIZE 20 // 定义队列的最大值
typedef int ElemType;

#define QueueSize MAXSIZE

typedef struct QueueNode
{
    ElemType data;
    struct QueueNode *next;
} QueueNode, *LinkQueuePtr;

typedef struct LinkQueue
{
    LinkQueuePtr front; // 队首指针
    LinkQueuePtr rear;  // 队尾指针
} LinkQueue;

/**
 * @name: InitQueue
 * @brief: 初始化操作，建立一个空队列
 * @param {type} 
 * @return: 
 */
Status InitQueue(LinkQueue *Q)
{
    Q->front = Q->rear = (LinkQueuePtr)malloc(sizeof(QueueNode));
    if (!Q->front)
    {
        return ERROR;
    }
    Q->front->next = NULL;
    return OK;
}
/**
 * @name: DestroyQueue
 * @brief: 销毁队列Q
 * @param {type} 
 * @return: 
 */
Status DestroyQueue(LinkQueue *Q)
{
    while (Q->front)
    {
        Q->rear = Q->front->next; // 直接使用Q->rear指针，减少空间消耗
        free(Q->front);
        Q->front = Q->rear;
    }
    return OK;
}
/**
 * @name: ClearQueue
 * @brief: 若将队列清空
 * @param {type} 
 * @return: 
 */
Status ClearQueue(LinkQueue *Q)
{
    LinkQueuePtr p, q;
    Q->rear = Q->front; // 先把队首队尾指针处理了
    p = Q->front->next;
    Q->front->next = NULL;
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }

    return OK;
}
/**
 * @name: QueueEmpty
 * @brief: 若队列Q为空，返回true，否则返回false
 * @param {type} 
 * @return: 
 */
Status QueueEmpty(LinkQueue Q)
{
    if (Q.front == Q.rear)
    {
        return TRUE;
    }
    return FALSE;
}
/**
 * @name: GetHead
 * @brief: 若队列存在且非空，用e返回队列Q的队头元素
 * @param {type} 
 * @return: 
 */
Status GetHead(LinkQueue Q, ElemType *e)
{
    if (Q.front == Q.rear)
    {
        return ERROR;
    }
    *e = Q.front->next->data;
    return OK;
}
/**
 * @name: EnQueue
 * @brief: 若队列Q存在，插入新元素e到队列Q中并成为队尾元素
 * @param {type} 
 * @return: 
 */
Status EnQueue(LinkQueue *Q, ElemType e)
{
    LinkQueuePtr s = (LinkQueuePtr)malloc(sizeof(QueueNode));
    if (!s) // 存储分配失败
    {
        return ERROR;
    }
    s->data = e;       // 存储元素
    Q->rear->next = s; // 插入新的元素
    s->next = NULL;
    Q->rear = s; // 更新链表尾
    return OK;
}
/**
 * @name: DeQueue
 * @brief: 删除队列Q中队头元素，并用e返回其值
 * @param {type} 
 * @return: 
 */
Status DeQueue(LinkQueue *Q, ElemType *e)
{
    LinkQueuePtr p;
    if (Q->front == Q->rear) // 队列为空
    {
        return ERROR;
    }
    p = Q->front->next; // 队首结点暂存于p
    *e = p->data;
    Q->front->next = p->next; // 更新队首结点
    if (Q->rear == p)         // 若队头是队尾，则删除后将rear指向头结点
        Q->rear = Q->front;
    free(p); // 删除暂存结点
    return OK;
}
/**
 * @name: QueueLength
 * @brief: 返回队列Q的元素个数
 * @param {type} 
 * @return: 
 */
Status QueueLength(LinkQueue Q)
{
    LinkQueuePtr p;
    int i = 0;
    p = Q.front->next;
    while (p)
    {
        i++;
        p = p->next;
    }

    return i;
}
/**
 * @name: QueueToString
 * @brief: 打印整个队列
 * @param {type} 
 * @return: 
 */
Status QueueToString(LinkQueue Q)
{
    LinkQueuePtr p;
    p = Q.front->next;
    while (p)
    {
        printf("%d  ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}
//-------------------------------------------
int main(void)
{
    int i;
    ElemType d;
    LinkQueue q;
    i = InitQueue(&q);
    if (i)
        printf("成功地构造了一个空队列!\n");
    printf("是否空队列？%d(1:空 0:否)  ", QueueEmpty(q));
    printf("队列的长度为%d\n", QueueLength(q));

    EnQueue(&q, -5);
    EnQueue(&q, 5);
    EnQueue(&q, 10);
    printf("插入3个元素(-5,5,10)后,队列的长度为%d\n", QueueLength(q));
    printf("是否空队列？%d(1:空 0:否)  ", QueueEmpty(q));
    printf("队列的元素依次为：");
    QueueToString(q);
    i = GetHead(q, &d);
    if (i == OK)
        printf("队头元素是：%d\n", d);
    ClearQueue(&q);
    printf("清空队列后,q.front=%p q.rear=%p q.front->next=%p\n", q.front, q.rear, q.front->next);
    DestroyQueue(&q);
    printf("销毁队列后,q.front=%p q.rear=%p\n", q.front, q.rear);
    return 0;
}