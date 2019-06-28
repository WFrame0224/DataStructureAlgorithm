/*
 * @Descripttion: 本文件实现常见的几种排序算法：冒泡，选择、插入、快速、归并等
 * @version: 
 * @Author: Frame
 * @Date: 2019-06-28 15:48:27
 * @LastEditors: Frame
 * @LastEditTime: 2019-06-28 20:58:35
 */
#include "stdio.h"
#include "stdlib.h"

/**
 * @name: SelectSort
 * @brief: 选择排序
 *      特点：
 *          时间复杂度：O(n^2)，最好情况O(n),最坏情况O(n^2)，平均情况O(n^2) 
 *          基于比较的排序
 *          空间复杂度是O(1)，属于原地排序算法
 *          是稳定的排序算法，对于值相同的元素，我么可以选择将后面出现的元素，插入到前面出现元素的后面
 * @param 
 *          int arr[]   :待排序数组 
 *          int n       :数组长度
 * @return: 
 */
void SelectSort(int arr[], int n)
{
    
}

/**
 * @name: InsertSort
 * @brief: 插入排序
 *      特点：
 *          时间复杂度：O(n^2)，最好情况O(n),最坏情况O(n^2)，平均情况O(n^2) 
 *          基于比较的排序
 *          空间复杂度是O(1)，属于原地排序算法
 *          是稳定的排序算法，对于值相同的元素，我么可以选择将后面出现的元素，插入到前面出现元素的后面
 * @param 
 *          int arr[]   :待排序数组 
 *          int n       :数组长度
 * @return: 
 */
void InsertSort(int arr[], int n)
{
    //i为有序数组的上限下标，j表示从有序数组中寻找插入位置的游标
    int i, j;
    //从无序数组分区中取出待插入有序数组中的元素
    int insertTemp;
    int insertIndex;
    
    for (i = 1; i < n; i++)
    {
        //i为有序数组的上限，i+1为无序数组的第一个元素
        insertTemp = arr[i];
        //初始化插入位置，它的前一位
        j = i-1;
        //从有序数组(0~i)中寻找位置,倒着来寻找，
        //如果比较一次，不是可插入的位置，则元素向后移动一次，时间消耗更少
        for (; j >= 0; j--)
        {
            //升序，小的往前插
            if (arr[j] > insertTemp)
            {
                //后移元素
                arr[j + 1] = arr[j];
            }
            else//找到插入位置,跳出循环
            {
                break;
            }
        }
        //将空出的位置，填充要插入的元素
        arr[j+1] = insertTemp;
    }
}

/**
 * @name: BubbleSort
 * @brief: 冒泡排序
 *      特点：
 *          时间复杂度：O(n^2)，最好情况O(n),最坏情况O(n^2)，平均情况O(n^2) (平均情况需要交换n*(n-1)/4)
 *          基于比较的排序
 *          空间复杂度是O(1)，属于原地排序算法
 *          是稳定的排序算法，相等元素不交换位置即可
 * @param 
 *          int arr[]   :待排序数组 
 *          int n       :数组长度
 * @return: 
 */
void BubbleSort(int arr[], int n)
{
    //i是冒泡次数=逆序度（加标志），j是每次冒泡的游标
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
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
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
    int arr[] = {4, 5, 6, 1, 3, 2};
    int arrLen = (int)sizeof(arr) / sizeof(arr[0]);
    printf("未排序的数组为：\r\n");
    ArrayToString(arr, arrLen);

    // printf("冒泡排序之后的数组为：\r\n");
    // BubbleSort(arr, arrLen);
    // ArrayToString(arr, arrLen);

    printf("插入排序之后的数组为：\r\n");
    InsertSort(arr, arrLen);
    ArrayToString(arr, arrLen);

    return 0;
}