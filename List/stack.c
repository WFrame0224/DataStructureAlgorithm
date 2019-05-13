/*
 * @Descripttion: 栈的C语言实现,包括顺序存储和链表存储
 * @version: 
 * @Author: Frame
 * @LastEditors: Frame
 * @Date: 2019-05-10 21:34:55
 * @LastEditTime: 2019-05-13 11:26:29
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */

#define MAXSIZE 20 // 定义栈的最大值
typedef int ElemType;

typedef struct sqstack
{
    ElemType data[MAXSIZE];
    int top; // 栈顶指针
    
    // 采用函数指针模拟面向对象
    Status (*init)(struct sqstack *);
    Status (*clear)(struct sqstack *);
    int (*isEmpty)(struct sqstack);
    Status (*getTop)(struct sqstack, ElemType *);
    Status (*push)(struct sqstack *, ElemType);
    Status (*pop)(struct sqstack *, ElemType *);
    int (*getLength)(struct sqstack);
    Status (*toString)(struct sqstack);
} SqStack;

//---------------函数声明-------------------
Status ClearStack(SqStack *S);
int StackEmpty(SqStack S);
Status GetTop(SqStack S, ElemType *e);
Status GetTop(SqStack S, ElemType *e);
Status Push(SqStack *S, ElemType e);
Status Pop(SqStack *S, ElemType *e);
int StackLength(SqStack S);
Status StackTraverse(SqStack S);
//-----------------------------------------
/**
 * @name: InitStack(...)
 * @brief: 初始化操作，建立一个空栈
 * @param {type} 
 * @return: 
 */
Status InitStack(SqStack *S)
{
    memset(S->data, 0, MAXSIZE);
    S->top = -1;
    
    S->clear = ClearStack;
    S->getLength = StackLength;
    S->pop = Pop;
    S->push = Push;
    S->toString = StackTraverse;
    S->isEmpty = StackEmpty;
    S->getTop = GetTop;

    return OK;
}
/**
 * @name: ClearStack(...)
 * @brief: 将栈清空，恢复至初始化状态
 * @param {type} 
 * @return: 
 */
Status ClearStack(SqStack *S)
{
    for (int i = 0; i < S->top + 1; i++)
    {
        S->data[i] = 0;
    }
    S->top = -1;
    return OK;
}
/**
 * @name: StackEmpty(...)
 * @brief: 若栈为空，返回true,否则返回false
 * @param {type} 
 * @return: 
 */
int StackEmpty(SqStack S)
{
    if (S.top == -1)
    {
        return TRUE;
    }

    return FALSE;
}
/**
 * @name: GetTop()
 * @brief: 若栈存在且非空，用e返回S的栈顶元素
 * @param {type} 
 * @return: 
 */
Status GetTop(SqStack S, ElemType *e)
{
    if (S.top == -1)
    {
        return ERROR;
    }
    *e = S.data[S.top];

    return OK;
}
/**
 * @name: Push(...)
 * @brief: 若栈S存在，插入新元素e到栈中并成为栈顶元素
 * @param {type} 
 * @return: 
 */
Status Push(SqStack *S, ElemType e)
{
    // 如果栈满
    if (S->top == MAXSIZE - 1)
    {
        return ERROR;
    }
    S->top++;            // 栈顶指针加1
    S->data[S->top] = e; // 将元素压栈，赋值给栈顶空间

    return OK;
}
/**
 * @name: Pop(...)
 * @brief: 删除栈S的栈顶元素，并用e返回其值
 * @param {type} 
 * @return: 
 */
Status Pop(SqStack *S, ElemType *e)
{
    if (S->top == -1) // 本身就是空栈
    {
        return ERROR;
    }
    *e = S->data[S->top]; // 取出栈顶元素
    S->top--;             // 指针减
    return OK;
}
/**
 * @name: StackLength(...)
 * @brief: 返回栈S的元素个数
 * @param {type} 
 * @return: 
 */
int StackLength(SqStack S)
{
    return (S.top + 1);
}

/**
 * @name: StackTraverse()
 * @brief: 打印所有的元素
 * @param {type} 
 * @return: 
 */
Status StackTraverse(SqStack S)
{
    int i;
    i = 0;
    while (i <= S.top)
    {
        printf("%d ", S.data[i++]);
    }
    printf("\n");
    return OK;
}

//-------------------------------------------------
int main(void)
{
    SqStack S;
    ElemType e;
    InitStack(&S);
    S.toString(S);
    for (int i = 0; i < MAXSIZE / 2; i++)
    {
        S.push(&S, i);
    }
    S.toString(S);
    S.getTop(S, &e);
    printf("栈顶元素：%d", e);
    return 0;
}
