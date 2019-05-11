/*
 * @Descripttion: 栈的C语言实现,包括顺序存储和链表存储
 * @version: 
 * @Author: Frame
 * @LastEditors: Frame
 * @Date: 2019-05-10 21:34:55
 * @LastEditTime: 2019-05-11 21:51:20
 */
#include <stdlib.h>
#include <stdio.h>


#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;   /* Status是函数的类型,其值是函数结果状态代码，如OK等 */

#define MAXSIZE 20 // 定义栈的最大值
typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int top; // 栈顶指针
} SqStack;

/**
 * @name: InitStack(...)
 * @brief: 初始化操作，建立一个空栈
 * @param {type} 
 * @return: 
 */
Status InitStack(SqStack *S)
{
    return OK;    
}
/**
 * @name: DestroyStack(...)
 * @brief: 若栈存在则销毁它
 * @param {type} 
 * @return: 
 */
Status DestroyStack(SqStack *S)
{
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
    return FALSE;
}
/**
 * @name: GetTop()
 * @brief: 若栈存在且非空，用e返回S的栈顶元素
 * @param {type} 
 * @return: 
 */
Status GetTop(SqStack S,ElemType *e)
{
    return OK;
}
/**
 * @name: Push(...)
 * @brief: 若栈S存在，插入新元素e到栈中并成为栈顶元素
 * @param {type} 
 * @return: 
 */
Status Push(SqStack *S,ElemType e)
{
    return OK;
}
/**
 * @name: Pop(...)
 * @brief: 删除栈S的栈顶元素，并用e返回其值
 * @param {type} 
 * @return: 
 */
Status Pop(SqStack *S,ElemType e)
{
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
    return 0;
}


//-------------------------------------------------
int main(void)
{
    return 0;
}
