/*
 * @Descripttion: 本文件实现常见的几种排序算法：冒泡，选择、插入、快速、归并等
 * @version: 
 * @Author: Frame
 * @Date: 2019-06-28 15:48:27
 * @LastEditors: Frame
 * @LastEditTime: 2019-06-28 16:27:09
 */
#include "stdio.h"
#include "stdlib.h"

/**
 * @name: BubbleSort
 * @brief: 冒泡排序
 *      特点：
 *          时间复杂度：O(n^2)
 *          基于比较的排序
 *          空间复杂度是O(1)，属于原地排序算法
 *          是稳定的排序算法，相等元素不交换位置即可
 * @param {type} 
 * @return: 
 */
void BubbleSort(int arr[], int n)
{
    int i, j;
    int temp;
    //记录某次冒泡是否需要进行数据交换
    char swapFlag = 0;
    for (i = 0; i < n; i++)
    {
        swapFlag = 0;
        for (j = 0; j < n - 1 - i; j++)
        {
            //判断是否需要交换
            if (arr[j] > arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                //表示有数据交换
                swapFlag = 1;
            }
        }
        //本次冒泡已不需要数据交换了，说明数组已经完全有序，无需继续排序
        if (0 == swapFlag)
        {
            break;
        }
        
    }
}

void ArrayToString(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\r\n");
}

int main(void)
{
    int arr[] = {4, 5, 3, 1, 6, 2, 7};
    int arrLen = (int)sizeof(arr) / sizeof(arr[0]);
    printf("未排序的数组为：\r\n");
    ArrayToString(arr, arrLen);

    printf("冒泡排序之后的数组为：\r\n");
    BubbleSort(arr, arrLen);
    ArrayToString(arr, arrLen);

    return 0;
}