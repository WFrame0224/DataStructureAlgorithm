/*
 * @Descripttion: 本文件实现常见的几种排序算法：冒泡，选择、插入、快速、归并等
 * @version: 
 * @Author: Frame
 * @Date: 2019-06-28 15:48:27
 * @LastEditors: Frame
 * @LastEditTime: 2019-07-01 14:46:37
 */
#include "stdio.h"
#include "stdlib.h"

void MergeSort_C(int arr[], int p, int r);
void Merge(int arr[], int p, int q, int r);

/**
 * @name: MergeSort
 * @brief: 归并排序--分治思想
 *      要排序一个数组，我们先把数组从中间分成前后两个部分，然后后对前后两个部分分别排序，
 * 再将排序好的两个部分合并在一起，这样整个数组就有序了
 *      特点：
 *          时间复杂度：O(nlogn)，最好情况O(nlogn),最坏情况O(n^2)，平均情况O(n^2) 
 *          基于比较的排序
 *          空间复杂度是O(1)，属于原地排序算法
 *          是 不稳定 的排序算法，因为不是相邻元素交换位置
 * @param 
 *          int arr[]   :待排序数组 
 *          int n       :数组长度
 * @return: 
 */
void MergeSort(int arr[], int n)
{
    MergeSort_C(arr, 0, n - 1);
}
/**
 * @name: MergeSort_C
 * @brief: 递归调用函数
 *      递推公式：
 *              Merge_Sort(p...r) = Merge( Merge_Sort(p..q),Merge_Sort(q..r))
 *      终止条件：
 *              p >= r
 * @param 
 *          int arr[]:需要排序的数组
 *          int p，int r:下标从p到r进行排序
 * @return: 
 */
void MergeSort_C(int arr[], int p, int r)
{
    //判断是否达到终止条件
    if (p >= r)
        return;
    //取 p 到 r 之间的中间位置 q
    int q = (p + r) / 2;
    //分治递归
    MergeSort_C(arr, p, q);
    MergeSort_C(arr, q + 1, r);
    //将A[p..q]和A[q+1...r]合并为A[p...r]
    Merge(arr, p, q, r);
}
/**
 * 合并函数，将两个有序的数组合并成一个大的数组
 */
void Merge(int arr[], int p, int q, int r)
{
    int i = p, j = q + 1;
    int k = 0;
    //创建一个大小为r-q的临时数组
    int* temp = (int*)malloc((r-p)*sizeof(int));
    while (i <= q && j <= r)
    {
        if (arr[i]<=arr[j])
        {
            temp[k++] = arr[j++];
        }
        else
        {
            temp[k++] = arr[i++];
        }
    }
    //判断哪个子数组中有剩余的数据
    int start = i, end = q;
    if (j <= r)
    {
        start = j;
        end = r;
    }
    while (start <= end)
    {
        temp[k++] = arr[start++];
    }
    for ( i = 0; i <= r-p; i++)
    {
        arr[p+i] = temp[i]; 
    }
    
}

/**
 * @name: QuickSort
 * @brief: 快速排序
 *      特点：
 *          时间复杂度：O(nlogn)，最好情况O(nlogn),最坏情况O(n^2)，平均情况O(n^2) 
 *          基于比较的排序
 *          空间复杂度是O(1)，属于原地排序算法
 *          是 不稳定 的排序算法，因为不是相邻元素交换位置
 * @param 
 *          int arr[]   :待排序数组 
 *          int n       :数组长度
 * @return: 
 */
void QuickSort(int arr[], int n)
{
}

/**
 * @name: SelectSort
 * @brief: 选择排序
 *      特点：
 *          时间复杂度：O(n^2)，最好情况O(n^2),最坏情况O(n^2)，平均情况O(n^2) 
 *          基于比较的排序
 *          空间复杂度是O(1)，属于原地排序算法
 *          是 不稳定 的排序算法，因为不是相邻元素交换位置
 * @param 
 *          int arr[]   :待排序数组 
 *          int n       :数组长度
 * @return: 
 */
void SelectSort(int arr[], int n)
{
    //i表示从每一次寻找最小的元素，j表示从未排序数组中寻找最小元素的游标
    int i, j;
    //存储最小的元素
    int min;
    int minIndex;

    // 总共要经过 N-1 轮比较，最后一次未排序的区间就剩一个元素了，还比较个屁，所以是N-1
    for (i = 0; i < n - 1; i++)
    {
        minIndex = i;
        //从未排序数组中寻找最小值
        for (j = i + 1; j < n; j++)
        {
            if (min > arr[j])
            {
                min = arr[j];
                minIndex = j;
            }
        }
        //将最小值放置到已排序数组末尾，并原本的元素放置在取出的元素位置
        arr[minIndex] = arr[i];
        arr[i] = min;
    }
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
        j = i - 1;
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
            else //找到插入位置,跳出循环
            {
                break;
            }
        }
        //将空出的位置，填充要插入的元素
        arr[j + 1] = insertTemp;
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

    // printf("插入排序之后的数组为：\r\n");
    // InsertSort(arr, arrLen);
    // ArrayToString(arr, arrLen);

    // printf("选择排序之后的数组为：\r\n");
    // SelectSort(arr, arrLen);
    // ArrayToString(arr, arrLen);

    printf("归并排序之后的数组为：\r\n");
    MergeSort(arr, arrLen);
    ArrayToString(arr, arrLen);
    return 0;
}