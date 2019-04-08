#!/usr/bin/env python
# coding=UTF-8
'''
@Descripttion: 快速排序的python实现
@version: 
@Author: Frame
@LastEditors: Frame
@Date: 2019-04-08 10:45:52
@LastEditTime: 2019-04-08 11:38:22
'''


def quickSort(decList, pattern=1):
    '''
    @name: quickSort(...)
    @brief: 快速排序的实现
    @param decList：待排序的数组，列表 pattern：是升序还是降序,默认升序 
    @return: 一个有序的列表
    '''
    if len(decList) < 2:    # 基线条件，如果长度为1,或者空，则无需排序
        return decList
    else:
        if pattern == 1:    # 如果是升序排序
            # 进行分区：1-取基准值；2-分出小于基准值的区；3-分出大于基准值的区
            pivot = decList[0]  # 递归条件，选取基准值
            less = [i for i in decList[1:] if i <= pivot]       # 由所有小于基准值的元素组成的子数组
            greater = [i for i in decList[1:] if i > pivot]     # 由所有大于基准值的元素组成的子数组

            return quickSort(less, 1) + [pivot] + quickSort(greater, 1)  # 进行递归
        elif pattern == 0:  # 如果进行降序排序
            # 进行分区：1-取基准值；2-分出小于基准值的区；3-分出大于基准值的区
            pivot = decList[0]  # 递归条件，选取基准值
            less = [i for i in decList[1:] if i < pivot]        # 由所有小于基准值的元素组成的子数组
            greater = [i for i in decList[1:] if i >= pivot]    # 由所有大于基准值的元素组成的子数组

            return quickSort(greater, 0) + [pivot] + quickSort(less, 0)  # 进行递归
        else:
            print('仅能选择升序(pattern=1),降序(pattern=0)')
            return


if __name__ == "__main__":
    decList = [10, 5, 2, 3]
    print(decList)
    print(quickSort(decList, 1))
