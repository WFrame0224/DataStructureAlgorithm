/*
 * @Descripttion: 二分查找C语言版本
 * @version: 
 * @Author: Frame
 * @Date: 2019-07-21 13:43:50
 * @LastEditors: Frame
 * @LastEditTime: 2019-07-21 14:40:15
 * ----------------------------------
 * 注意点：
 *      1）非递归版本的循环条件是low<=high,而不是low<high,放置上边界的遗漏
 *      2）mid = low+((high-low)>>1),可放置溢出且性能极致
 *      3）low和high的更新，low = mid+1,high = mid-1
 * 应用场景的局限性：
 *      1）二分查找依赖额是顺序结构，因二分查找算法需要按照下标随机访问元素，链表存储采用二分查找时间福在读会大大增加
 *      2）二分查找针对的是有序数组，且插入，删除操作不频繁一次排序多次查找的场景中
 *      3）数据量很小，完全没有必要使用二分查找，数据太大，内存有限制的场合，二分查找也不适合
 */
#include <stdio.h>
#include <stdlib.h>

int BSearchInternally(int arr[], int low, int high, int value);

/**
 * @name: BinarySearchRecursion
 * @brief: 二分查找的递归版本
 * @param   int arr[]   :待查找数组
 *          int n       :待查找数组大小
 *          int value   :待查找的值 
 * @return: 若查找成功，返回待查找值的下标，若查找失败，则返回-1
 */
int BinarySearchRecursion(int arr[], int n, int value)
{
    return BSearchInternally(arr, 0, n - 1, value);
}
int BSearchInternally(int arr[], int low, int high, int value)
{
    int mid = mid = low + (int)((high - low) >> 1);
    if (low > high)
    {
        return -1;
    }
    if (value == arr[mid])
    {
        return mid;
    }
    else if (value > arr[mid])
    {
        return BSearchInternally(arr, mid + 1, high, value);
    }
    else
    {
        return BSearchInternally(arr, low, mid - 1, value);
    }
}

/**
 * @name: BinarySearchBase
 * @brief: 二分查找，基础版本
 * @param   
 *          int arr[]   :待查找数组
 *          int n       :待查找数组大小
 *          int value   :待查找的值
 * @return: 若查找成功，返回待查找值的下标，若查找失败，则返回-1
 */
int BinarySearchBase(int arr[], int n, int value)
{
    int low = 0, high = n - 1;
    int mid = low + (int)((high - low) >> 1);

    //数据检查
    if (arr == NULL || n == 0)
    {
        return -2;
    }
    /**
    //判断待查找的数据是否在首尾
    if (value == arr[0])
    {
        return 0;
    }
    else if (value == arr[n - 1])
    {
        return n - 1;
    }
*/
    //注意循环退出条件，如果没有首尾查找的话为“<=”，如果有判断的话为<即可
    while (low <= high)
    {
        mid = low + (int)((high - low) >> 1);
        if (value == arr[mid])
        {
            return mid;
        }
        else if (value > arr[mid])
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

int main(void)
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int index = -2;
    int value = 4;
    index = BinarySearchRecursion(arr, 10, value);

    printf("数值 %d 在arr中的位置是 %d \n", value, index);
    return 1;
}