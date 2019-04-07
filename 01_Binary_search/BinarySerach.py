#!/usr/bin/env python
# coding=UTF-8
'''
@Descripttion: 
@version: 二分查找法python实现
@Author: Frame
@LastEditors: Frame
@Date: 2019-04-06 09:56:34
@LastEditTime: 2019-04-07 08:59:25
'''


def binarySearch(decList, item):
    '''
    @name: binarySearch
    @brief: 二分查找算法，输入待查找的元素，返回查找的结果
    @param: decList : 有序的列表   item : 查找的元素  
    @return: None：没有该元素  index ： 该元素在列表中的位置
    '''
    low = 0                            # 起点索引
    high = len(decList) - 1            # 终点索引
    mid = int((low + high) / 2)        # 中间元素的索引

    # 查找结束，必然起点索引大于终点索引
    while low <= high:
        if decList[mid] == item:       # 如果找到元素
            return mid
        elif decList[mid] > item:      # 如果元素大了
            high = mid - 1             # 更新查找上限
            mid = int((high + low)/2)
        else:                          # 如果元素小了
            low = mid + 1              # 更新元素下限
            mid = int((low + high)/2)
    return None                        # 没有查找到


if __name__ == "__main__":
    decList = [1,3,4,5,6,7,8,9,20,30]      # 目的的有序列表，必须为有序的
    item = 30
    print('在列表中找到的元素%4d    位置为%3s'%(item,binarySearch(decList,item)))
