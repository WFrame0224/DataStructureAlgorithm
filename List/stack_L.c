/*
 * @Descripttion: 栈的C语言实现,链式存储（链表实现）
 * @version: 
 * @Author: Frame
 * @LastEditors: Frame
 * @Date: 2019-05-13 21:34:55
 * @LastEditTime: 2019-05-13 15:05:14
 * ------------------------------
 * 注：链栈来讲，不需要头结点
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

// 定义一个结点
typedef struct StackNode
{
    ElemType data;
    struct StackNode *next;
} StackNode, *LinkStackPtr;

// 定义链栈的结构
typedef struct LinkStack
{
    LinkStackPtr top;
    int count;
} LinkStack;

//-------------------------------
/**
 * @name: InitStack
 * @brief: 构造一个空栈S
 * @param {type} 
 * @return: 
 */
Status InitStack(LinkStack *S)
{
    S->top = (LinkStackPtr)malloc(sizeof(StackNode));
    if (!S->top)
    {
        return ERROR;
    }
    S->top = NULL;
    S->count = 0;

    return OK;
}
/**
 * @name: ClearStack
 * @brief: 清空链栈
 * @param {type} 
 * @return: 
 */
Status ClearStack(LinkStack *S)
{
    LinkStackPtr p, q;
    p = S->top;
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    S->count = 0;
    return OK;
}
/**
 * @name: StackEmpty
 * @brief: 检查是否是空栈
 * @param {type} 
 * @return: 
 */
Status StackEmpty(LinkStack S)
{
    if (S.count == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
/**
 * @name: StackLength
 * @brief: 返回当前栈的元素个数
 * @param {type} 
 * @return: 
 */
int StackLength(LinkStack S)
{
    return S.count;
}
/**
 * @name: GetTop
 * @brief: 得到栈顶元素
 * @param {type} 
 * @return: 
 */
Status GetTop(LinkStack S, ElemType *e)
{
    if (S.top == NULL)
    {
        return ERROR;
    }
    *e = S.top->data;
    return OK;
}
/**
 * @name: Push
 * @brief: 插入元素e为新的栈顶元素
 * @param {type} 
 * @return: 
 */
Status Push(LinkStack *S, ElemType e)
{
    LinkStackPtr p;
    p = (LinkStackPtr)malloc(sizeof(StackNode));
    p->data = e;
    p->next = S->top; // 把当前的栈顶元素赋值给新结点的后继
    S->top = p;       // top指针指向新的栈顶
    S->count++;       // 栈元素个数增1

    return OK;
}
/**
 * @name: Pop(...)
 * @brief: 将栈顶元素出栈，并赋值给元素e
 * @param {type} 
 * @return: 
 */
Status Pop(LinkStack *S, ElemType *e)
{
    LinkStackPtr p;
    if (S->count == 0)
    {
        return ERROR;
    }
    *e = S->top->data;     // 取出要出栈的元素
    p = S->top;            // 保存出栈的地址
    S->top = S->top->next; // 出站后，更新栈顶指针
    S->count--;            // 栈内元素个数减1
    free(p);               // 释放内存
    return OK;
}
Status StackTraverse(LinkStack S)
{
    LinkStackPtr p;
    p = S.top;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

//---------------------------------------------
int main(void)
{
    LinkStack S;
    ElemType e;
    InitStack(&S);
    for (int i = 0; i < MAXSIZE; i++)
    {
        Push(&S, i);
    }
    StackTraverse(S);
    Pop(&S, &e);
    StackTraverse(S);
    GetTop(S,&e);
    printf("栈顶元素 e=%d 栈的长度为%d\n",e,StackLength(S));
    ClearStack(&S);
    printf("清空栈后，栈空否：%d(1:空 0:否)\n",StackEmpty(S));
    return 0;
}