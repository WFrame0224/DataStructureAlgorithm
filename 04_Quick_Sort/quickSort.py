#!/usr/bin/env python
# coding=UTF-8
'''
@Descripttion: 快速排序的python实现
@version: 
@Author: Frame
@LastEditTime: 2019-08-28 13:57:51
@Date: 2019-04-08 10:45:52
@LastEditTime: 2019-08-28 14:00:24
'''


def quickSort(decList, pattern=1):
    '''
@LastEditors: Frame
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


'''
@name: partition
@brief: 寻找分区点，返回其下标,使用的是原地分区算法，类似插入排序
@param {type} 
@return: 
'''
def partition(arr, start, end):

    i = start
    j = start
    pivot = arr[end]

    while j <= end-1:
        if arr[j] < pivot:
            temp = arr[i]
            arr[i] = arr[j]
            arr[j] = temp
            i += 1
        j = j+1
    
    arr[end] = arr[i]
    arr[i] = pivot
    return i

'''
@name: _quick_sort
@brief: 
 *      快速排序递归调用函数
 *      递推公式：
 *          quick_sort(start..end) = quick_sort(start..q_1) + quick_sort(q+1,end)
 *      终止条件
 *          start >= end
@param 
*          int arr[]:需要排序的数组
*          int start，int end:下标从p到r进行排序
@return: 
'''
def _quick_sort(arr, start, end):
    partitionValue = 0
    while start >= end:
        return
    partitionValue = partition(arr, start, end)
    _quick_sort(arr, start, partitionValue-1)
    _quick_sort(arr, partitionValue+1, end)

'''
@name: quick_sort
@brief: 快速排序
 *      思想：
 *          如果要排序数组中下标从 p 到 r 之间的一组数据，我们选择 p 到 r 之间任意一个数据作为分区点 pivot
 *          我们遍历 p 到 r 之间的数据，将小于pivot放到左边，将大于pivot放到右边，将pivot放到中间，经过这一步，
 *      数据被分为三个部分，前面 p 到q-1 之间都是小于pivot，后面q+1到r之间的是大于pivot的，中间的是pivot，
 *      根据分治的思想，我们可以递归排序从（p~q-1）和（q+1,r）之间的数据，直至区间为1
 *      特点：
 *          时间复杂度：O(nlogn)，最好情况O(nlogn),最坏情况O(n^2)，平均情况O(nlogn) 
 *          空间复杂度是O(1)，属于原地排序算法
 *          是 不稳定 的排序算法
@param 
 *          int arr[]   :待排序数组 
 *          int n       :数组长度 
@return: 
'''
def quick_sort(arr):
    _quick_sort(arr, 0, len(arr)-1)


if __name__ == "__main__":
    decList = [10, 5, 2, 3]
    print(decList)
    print(quickSort(decList, 1))
