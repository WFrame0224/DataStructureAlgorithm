#!/usr/bin/env python
# coding=UTF-8
'''
@Descripttion: 采用递归方式实现列表求和
@version: 
@Author: Frame
@LastEditors: Frame
@Date: 2019-04-08 10:07:30
@LastEditTime: 2019-04-08 10:40:17
'''

def sum(decList):
    '''
    @name: sum(...)
    @brief: 使用递归方法实现求和运算
    @param {type} 
    @return: 
    '''
    if decList == []:          # 基线条件，列表个数只剩1个
        return 0
    else:
        # 缩小问题的规模，使其符合基线条件
        return decList[0] + sum(decList[1:]) # 递归条件

def listLen(decList):
    '''
    @name: listLen
    @brief: 使用递归方法实现求列表个数
    @param {type} 
    @return: 
    '''
    if decList == []:
        return 0
    else:
        return 1 + listLen(decList[1:])

def findMax(decList):
    '''
    @name: findMax
    @brief: 采用递归的方法寻找最大值
    @param {type} 
    @return: 
    '''
    if len(decList) == 2:           # 基线条件，当列表长度为2时
        return decList[0] if decList[0] > decList[1] else decList[1]
    sub_max = findMax(decList[1:])  # 保存得到的最大值，并缩小规模
    return decList[0] if decList[0] > sub_max else sub_max  # 当列表长度为1时，执行最后一次比较

if __name__ == "__main__":
    decList = [1,2,3,4,5,6,7,8,9]
    print(sum(decList))
    print(listLen(decList))
    print(findMax(decList))