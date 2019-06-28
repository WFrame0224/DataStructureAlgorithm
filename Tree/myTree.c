/*
 * @Descripttion: 树结构的基本展示,采用三种方式进行树结构的存储
 *          - 双亲表示法
 *          - 孩子表示法
 *          - 孩子兄弟表示法
 * @version: 
 * @Author: Frame
 * @Date: 2019-06-11 21:18:34
 * @LastEditors: Frame
 * @LastEditTime: 2019-06-11 21:27:46
 */

#include "stdio.h"
#include "stdlib.h"

#define MAX_TREE_SIZE       100

typedef int TElemType;      /* 树结点的数据类型，目前暂定为整型 */

/**************************双亲表示法*******************************/
// 结点结构
typedef struct PTNode
{
    TElemType data;         //数据域，存储结点信息
    int parent;             //指针域，存储该结点的双亲在数组中的下标
}PTNode;
//树结构
typedef struct
{
    PTNode nodes[MAX_TREE_SIZE];//结点数组
    int r;                      //根的位置
    int n;                      //结点数
}PTree;
/******************************************************************/
