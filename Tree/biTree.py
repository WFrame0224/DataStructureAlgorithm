'''
@Descripttion: 二叉树python构建
@version: 
@Author: Frame
@Date: 2019-08-24 10:54:12
@LastEditors: Frame
@LastEditTime: 2019-08-24 14:23:51
'''
# -*- coding: utf-8 -*-
import sys
from collections import deque



class BiTreeNode(object):
    """二叉树的节点"""

    def __init__(self, data=None, leftChild=None, rightChild=None):
        self.data = data
        self.leftChild = leftChild
        self.rightChild = rightChild


class BiTree(BiTreeNode):
    """二叉树的类"""

    def __init__(self, dataList):
        # 初始化即将传入的列表的迭代器
        self.it = iter(dataList)

    def createBinaryTree(self, node=None):
        """递归创建二叉树"""
        next_data = next(self.it)
        # 如果当前列表的元素为 None ，则认为其为None
        if not next_data:
            node = None
        else:
            node = BiTreeNode(next_data)
            node.leftChild = self.createBinaryTree(node.leftChild)
            node.rightChild = self.createBinaryTree(node.rightChild)
        
        return node

    def preOrderTraveral(self,biTree):
        """ 递归前序遍历 """
        if biTree == None:
            return
        print(biTree.data, end=" ")
        self.preOrderTraveral(biTree.leftChild)
        self.preOrderTraveral(biTree.rightChild)

    def inOrderTraveral(self,biTree):
        """ 递归中序遍历 """
        if biTree == None:
            return
        self.inOrderTraveral(biTree.leftChild)
        print(biTree.data, end=" ")
        self.inOrderTraveral(biTree.rightChild)

    def postOrderTraveral(self,biTree):
        """ 递归后续遍历 """
        if biTree == None:
            return
        self.postOrderTraveral(biTree.leftChild)
        self.postOrderTraveral(biTree.rightChild)
        print(biTree.data, end=" ")

    def perOrderTraveralWithStack(self,root):
        """ 采用非递归方式（利用栈）进行前序遍历 """
        stack = deque()
        bT = root
        while  (bT is not None) or len(stack) !=0:
            # 迭代访问结点的左孩子，并入栈
            while (bT is not None):
                print(bT.data,end=" ")
                stack.append(bT)
                bT = bT.leftChild
            # 如果结点没有左孩子，则弹出栈结点，访问结点右孩子
            if len(stack) != 0:
                bT = stack.pop()
                bT = bT.rightChild



    def printTrave(self, biTree):
        print("先序遍历: ", end="")
        self.preOrderTraveral(biTree)
        print('\n')
        print("中序遍历: ", end="")
        self.inOrderTraveral(biTree)
        print('\n')
        print("后序遍历: ", end="")
        self.postOrderTraveral(biTree)
        print('\n')



if __name__ == "__main__":
    biTree = BiTree(list([1,2,4,None,None,5,None,None,3,6,None,None,7,None,None]))
    root = biTree.createBinaryTree()
    # biTree.printTrave(root)
    biTree.perOrderTraveralWithStack(root)
    pass
