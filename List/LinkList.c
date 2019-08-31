#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "io.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20    /* 存储空间初始分配量 */
typedef int Status;   /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType; /* ElemType类型根据实际情况而定，这里假设为int */

typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;

typedef struct Node *LinkList; /* 定义LinkList */

Status visit(ElemType c)
{
    printf("%d ", c);
    return OK;
}
/* 初始化顺序线性表 */
Status InitList(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(Node)); /* 产生头结点,并使L指向此头结点 */
    if (!(*L))                           /* 存储分配失败 */
        return ERROR;
    (*L)->next = NULL; /* 指针域为空 */

    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
Status ListEmpty(LinkList L)
{
    if (L->next)
        return FALSE;
    else
        return TRUE;
}

/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(LinkList *L)
{
    LinkList p, q;
    p = (*L)->next; /*  p指向第一个结点 */
    while (p)       /*  没到表尾 */
    {
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL; /* 头结点指针域为空 */
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(LinkList L)
{
    int i = 0;
    LinkList p = L->next; /* p指向第一个结点 */
    while (p)
    {
        i++;
        p = p->next;
    }
    return i;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值 */
Status GetElem(LinkList L, int i, ElemType *e)
{
    int j;
    LinkList p;        /* 声明一结点p */
    p = L->next;       /* 让p指向链表L的第一个结点 */
    j = 1;             /*  j为计数器 */
    while (p && j < i) /* p不为空或者计数器j还没有等于i时，循环继续 */
    {
        p = p->next; /* 让p指向下一个结点 */
        ++j;
    }
    if (!p || j > i)
        return ERROR; /*  第i个元素不存在 */
    *e = p->data;     /*  取第i个元素的数据 */
    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
int LocateElem(LinkList L, ElemType e)
{
    int i = 0;
    LinkList p = L->next;
    while (p)
    {
        i++;
        if (p->data == e) /* 找到这样的数据元素 */
            return i;
        p = p->next;
    }

    return 0;
}

/* 初始条件：顺序线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListInsert(LinkList *L, int i, ElemType e)
{
    int j;
    LinkList p, s;
    p = *L;
    j = 1;
    while (p->next && j < i) /* 寻找第i个结点 */
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR;                   /* 第i个元素不存在 */
    s = (LinkList)malloc(sizeof(Node)); /*  生成新结点(C语言标准函数) */
    s->data = e;
    s->next = p->next; /* 将p的后继结点赋值给s的后继  */
    p->next = s;       /* 将s赋值给p的后继 */
    return OK;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
    int j;
    LinkList p, q;
    p = *L;
    j = 1;
    while (p->next && j < i) /* 遍历寻找第i个元素 */
    {
        p = p->next;
        ++j;
    }
    if (!(p->next) || j > i)
        return ERROR; /* 第i个元素不存在 */
    q = p->next;
    p->next = q->next; /* 将q的后继赋值给p的后继 */
    *e = q->data;      /* 将q结点中的数据给e */
    free(q);           /* 让系统回收此结点，释放内存 */
    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListToString(LinkList L)
{
    printf("This list is:\n");
    LinkList p = L->next;
    while (p)
    {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（头插法） */
void CreateListHead(LinkList *L, int n)
{
    LinkList p;
    int i;
    srand(time(0)); /* 初始化随机数种子 */
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL; /*  先建立一个带头结点的单链表 */
    for (i = 0; i < n; i++)
    {
        p = (Node *)malloc(sizeof(Node)); /*  生成新结点 */
        p->data = rand() % 100 + 1;       /*  随机生成100以内的数字 */
        p->next = (*L)->next;
        (*L)->next = p; /*  插入到表头 */
    }
}

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法） */
void CreateListTail(LinkList *L, int n)
{
    LinkList p, r;
    int i;
    srand(time(0));                      /* 初始化随机数种子 */
    *L = (LinkList)malloc(sizeof(Node)); /* L为整个线性表 */
    r = *L;                              /* r为指向尾部的结点 */
    for (i = 0; i < n; i++)
    {
        p = (Node *)malloc(sizeof(Node)); /*  生成新结点 */
        p->data = rand() % 100 + 1;       /*  随机生成100以内的数字 */
        r->next = p;                      /* 将表尾终端结点的指针指向新结点 */
        r = p;                            /* 将当前的新结点定义为表尾终端结点 */
    }
    r->next = NULL; /* 表示当前链表结束 */
}
/**
 * @name: LinkListReverse(...)
 * @brief: 反转链表
 * @param {type} 
 * @return: 
 */
LinkList ListReverse(LinkList *L)
{
    LinkList p = (*L)->next;
    if (p == NULL || p->next == NULL) // 链表为空，或者仅有一个数据
        return *L;

    LinkList LNew = (LinkList)malloc(sizeof(Node));
    LNew->next = NULL; // 先建立一个带头结点的空链

    while (p != NULL) // 一直遍历到链表尾部
    {
        (*L)->next = p->next; // 首先将首结点从原表中取下
        p->next = LNew->next;
        LNew->next = p; // 插入到表头
        p = (*L)->next; // 获取到下一个节点
    }
    free(*L);
    L = &LNew;
    return LNew;
}
LinkList ListReverse_1(LinkList *L)
{
    if ((*L) == NULL || (*L)->next == NULL)// 链表为空，或者仅有一个数据
        return *L;
    LinkList p = (*L)->next;
    LinkList LNew = (LinkList)malloc(sizeof(Node));
    LNew->next = NULL;
    while (p != NULL)
    {
        LinkList tmp = p->next;
        p->next = LNew->next;
        LNew->next = p;
        p = tmp;
    }
    return LNew;
}
/**
 * @name: ListReverse_recursive(...)
 * @brief: 采用递归方式进行反转
 * @param {type} 
 * @return: 
 */
LinkList ListReverse_recursive(LinkList L)
{
    if (L == NULL || L->next == NULL)// 链表为空，或者仅有一个数据
        return L;
    LinkList LNew = ListReverse_recursive(L->next);
    L->next->next = L;  //把当前节点的下一个结点反转
    L->next = NULL;     //断开原来的链
    return LNew;
}
char ListHasCircle(LinkList L)
{
    LinkList p1 = L->next;
    LinkList p2 = L->next;

    while (!p1->next|| !p2->next)
    {
        p1 = p1->next;
        p2 = p2->next->next;
        if(p1 == p2)
        {
            return 1;
        }
    }
    
    return 0;
}
