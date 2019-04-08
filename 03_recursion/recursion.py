#!/usr/bin/env python
# coding=UTF-8
'''
@Descripttion: 
@version: 
@Author: Frame
@LastEditors: Frame
@Date: 2019-04-08 09:14:02
@LastEditTime: 2019-04-08 09:36:05
'''

'''
    递归指的是调用自己的函数
    每个递归函数都有两个条件：基线条件和递归条件
    栈有两种操作：压入和弹出
    所有函数调用都进入调用栈
    调用栈可能很长，这将占用大量的内存
'''

def countDown(i):
    '''
    @name: 
    @brief: 递归函数的示例，必须包含基线条件和递归条件
    @param 参数 
    @return: 
    '''

    print(i)
    if i <= 1:          # 基线条件
        return
    else:
        countDown(i-1)  # 递归条件


def factorial(x):
    if x == 1:
        return 1
    else:
        return x * factorial(x - 1)


if __name__ == "__main__":
    # countDown(10)
    print(factorial(3))
