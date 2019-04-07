#!/usr/bin/env python
# coding=UTF-8
'''
@Descripttion: 选择排序的Python代码实现
@version: 
@Author: Frame
@LastEditors: Frame
@Date: 2019-04-07 10:28:56
@LastEditTime: 2019-04-07 11:36:17
'''


def selectSort(decList, pattern=1):
    '''
    @name: selectSort(...)
    @brief: 选择排序
    @param decList：待排序的数组，列表 pattern：是升序还是降序,默认升序
    @return: 一个有序的列表
    '''
    resultList = decList.copy()
    # 需要执行的次数
    for i in range(0, len(resultList)):
        tempIndex = i
        # 和本元素后面的进行比较
        for j in range(i + 1, len(resultList)):
            if pattern == 1:              # 如果是升序
                if resultList[j] > resultList[tempIndex]:
                    tempIndex = j
                else:
                    continue
            elif pattern == 0:            # 如果是降序
                if resultList[j] < resultList[tempIndex]:
                    tempIndex = j
                else:
                    continue
            else:
                print('仅能选择升序(pattern=1),降序(pattern=0)')
                return
        # 交换这个
        resultList[i],resultList[tempIndex] = resultList[tempIndex],resultList[i]
        

    return resultList


if __name__ == "__main__":
    dec = [9,1,4,2,3,7,8,5,6,0]
    print('没有排序的列表为：')
    print(dec)
    print('升序排序后的列表为：')
    print(selectSort(dec,1))
    print('降序排序后的列表为：')
    print(selectSort(dec,0))
