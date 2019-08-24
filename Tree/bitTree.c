/*
 * @Descripttion: 二叉树的实现
 * @version:
 * @Author: Frame
 * @Date: 2019-08-23 16:17:19
 * @LastEditors: Frame
 * @LastEditTime: 2019-08-24 14:26:06
 */
#include <stdio.h>
#include <stdlib.h>


#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef char ElemType;
typedef char Status;

//定义一个二叉树结点的数据类型
typedef struct BiTreeNode
{
	ElemType data;  //结点数据
	struct BiTreeNode* leftChild, * rightChild;   //左右孩子结点
}BiTreeNode;
//定义二叉树数据类型
typedef struct BiTreeNode* BiTree;

/**
 * @name: InitBiTree
 * @brief: 初始化二叉树，递归实现构造
 * @param {type}
 * @return: Status
 */
void CreateBiTree(BiTree* biTree)
{
	ElemType ch;
	scanf_s("%c", &ch);
	if (ch == '#')
	{
		*biTree = NULL;
	}
	else
	{
		*biTree = (BiTree)malloc(sizeof(BiTreeNode));
		if (!(*biTree))
		{
			exit(0);//存储空间分配失败
		}

		(*biTree)->data = ch;//生成根节点
		CreateBiTree(&(*biTree)->leftChild);    //构造左子树
		CreateBiTree(&(*biTree)->rightChild);   //构造右子树
	}
}

/**
 * @name: preOrderTraveral
 * @brief: 前序遍历
 * @param {type} 
 * @return: 
 */
void preOrderTraveral(BiTree biTree)
{
    if (biTree == NULL)
    {
        return;
    }
    printf("%c",biTree->data);//根节点输出
    preOrderTraveral(biTree->leftChild);//左子树遍历
    preOrderTraveral(biTree->rightChild);//右子树遍历
}
/**
 * @name: inOrderTraveral
 * @brief: 中序遍历
 * @param {type} 
 * @return: 
 */
void inOrderTraveral(BiTree biTree)
{
    if (biTree == NULL)
    {
        return;
    }
	inOrderTraveral(biTree->leftChild);//左子树遍历
    printf("%c",biTree->data);//根节点输出
	inOrderTraveral(biTree->rightChild);//右子树遍历 
}
/**
 * @name: postOrderTraveral
 * @brief: 后序遍历
 * @param {type} 
 * @return: 
 */
void postOrderTraveral(BiTree biTree)
{
    if (biTree == NULL)
    {
        return;
    }
	postOrderTraveral(biTree->leftChild);//左子树遍历
	postOrderTraveral(biTree->rightChild);//右子树遍历
    printf("%c",biTree->data);//根节点输出 
}

int main(void)
{
	BiTree biTree;
	CreateBiTree(&biTree);
    printf("\n前序遍历输出：\n");
    preOrderTraveral(biTree);
    printf("\n中序遍历输出：\n");
    inOrderTraveral(biTree);
    printf("\n后序遍历输出：\n");
    postOrderTraveral(biTree);
}
