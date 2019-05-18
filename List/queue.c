/*
 * @Descripttion: 实现顺序存储的循环队列
 * @version: 
 * @Author: Frame
 * @LastEditors: Frame
 * @Date: 2019-05-18 09:49:12
 * @LastEditTime: 2019-05-18 11:26:15
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
typedef struct
{
    ElemType data[QueueSize];
    int front; // 队首指针
    int rear;  // 队尾指针，若队列不空，指向队列尾元素的下一个位置
} SqQueue;

/**
 * @name: InitQueue
 * @brief: 初始化操作，建立一个空队列
 * @param {type} 
 * @return: 
 */
Status InitQueue(SqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}
/**
 * @name: ClearQueue
 * @brief: 若将队列情况
 * @param {type} 
 * @return: 
 */
Status ClearQueue(SqQueue *Q)
{
    memset(Q->data, 0, QueueSize);
    Q->front = 0;
    Q->rear = 0;
    return OK;
}
/**
 * @name: QueueEmpty
 * @brief: 若队列Q为空，返回true，否则返回false
 * @param {type} 
 * @return: 
 */
Status QueueEmpty(SqQueue Q)
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
Status GetHead(SqQueue Q, ElemType *e)
{
    if (!QueueEmpty(Q)) // 如果队列非空
    {
        *e = Q.data[Q.front];
        return OK;
    }

    return ERROR;
}
/**
 * @name: EnQueue
 * @brief: 若队列Q存在，插入新元素e到队列Q中并成为队尾元素
 * @param {type} 
 * @return: 
 */
Status EnQueue(SqQueue *Q, ElemType e)
{
    if (((Q->rear + 1) % QueueSize == Q->front)) // 判断队列是否已满
    {
        // 如果已满
        return ERROR;
    }
    Q->data[Q->rear] = e;                // 插入元素
    Q->rear = (Q->rear + 1) % QueueSize; // 更新队列尾指针，循环队列的方式
    return OK;
}
/**
 * @name: DeQueue
 * @brief: 删除队列Q中队头元素，并用e返回其值
 * @param {type} 
 * @return: 
 */
Status DeQueue(SqQueue *Q, ElemType *e)
{
    if (QueueEmpty(*Q)) // 若队列为空
    {
        return ERROR;
    }
    *e = Q->data[Q->front];                // 取出要删除的元素
    Q->front = (Q->front + 1) % QueueSize; // 更新队首指针
    return OK;
}
/**
 * @name: QueueLength
 * @brief: 返回队列Q的元素个数
 * @param {type} 
 * @return: 
 */
Status QueueLength(SqQueue Q)
{
    return ((QueueSize + Q.rear - Q.front) % QueueSize);
}
/**
 * @name: QueueToString
 * @brief: 打印整个队列
 * @param {type} 
 * @return: 
 */
Status QueueToString(SqQueue Q)
{
    int i;
    i = Q.front;
    while ((i + Q.front) != Q.rear)
    {
        printf("%d  ", Q.data[i]);
        i = (i + 1) % MAXSIZE;
    }
    printf("\n");
    return OK;
}
//---------------------------------------------------
int main(void)
{
    Status j;
    int i = 0, l;
    ElemType d;
    SqQueue Q;
    InitQueue(&Q);
    printf("初始化队列后，队列空否？%u(1:空 0:否)\n", QueueEmpty(Q));

    do
    {
        /* scanf("%d",&d); */
        d = i + 100;
        if (d == -1)
            break;
        i++;
        EnQueue(&Q, d);
    } while (i < MAXSIZE - 1);
    QueueToString(Q);

    printf("队列长度为: %d\n", QueueLength(Q));
    printf("现在队列空否？%u(1:空 0:否)\n", QueueEmpty(Q));
    printf("连续%d次由队头删除元素,队尾插入元素:\n", MAXSIZE);
    for (l = 1; l <= MAXSIZE; l++)
    {
        DeQueue(&Q, &d);
        printf("删除的元素是%d,插入的元素:%d \n", d, l + 1000);
        /* scanf("%d",&d); */
        d = l + 1000;
        EnQueue(&Q, d);
    }
    l = QueueLength(Q);

    printf("现在队列中的元素为: \n");
    QueueToString(Q);
    printf("共向队尾插入了%d个元素\n", i + MAXSIZE);
    if (l - 2 > 0)
        printf("现在由队头删除%d个元素:\n", l - 2);
    while (QueueLength(Q) > 2)
    {
        DeQueue(&Q, &d);
        printf("删除的元素值为%d\n", d);
    }

    j = GetHead(Q, &d);
    if (j)
        printf("现在队头元素为: %d\n", d);
    ClearQueue(&Q);
    printf("清空队列后, 队列空否？%u(1:空 0:否)\n", QueueEmpty(Q));
    return 0;
}
