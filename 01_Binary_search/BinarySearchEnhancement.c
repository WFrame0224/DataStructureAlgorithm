/*
 * @Descripttion: 二分查找法的变形版本
 * @version: 
 * @Author: Frame
 * @Date: 2019-07-22 09:24:45
 * @LastEditors: Frame
 * @LastEditTime: 2019-07-22 15:34:22
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef enum
{
    find_first,   //查找第一个值 等于 给定值的元素
    find_last,    //查找最后一个值 等于 给定值的元素
    find_greater, //查找第一个 大于等于 给定值的元素
    find_under    //查找最后一个 小于等于 给定值的元素
} Model;

/**
 * @name: BinarySearchFirst
 * @brief: 二分查找，变形版本，查找第一个值等于给定值的元素
 * @param   
 *          int arr[]   :待查找数组
 *          int n       :待查找数组大小
 *          int value   :待查找的值
 * @return: 若查找成功，返回待查找值的下标，若查找失败，则返回-1
 */
int BinarySearchEnhancement(int arr[], int n, int value, Model model)
{
    int low = 0, high = n - 1;
    int mid = low + (int)((high - low) >> 1);

    //数据检查
    if (arr == NULL || n == 0)
    {
        return -2;
    }
    //注意循环退出条件，如果没有首尾查找的话为“<=”，如果有判断的话为<即可
    while (low <= high)
    {
        mid = low + (int)((high - low) >> 1);
        if (value == arr[mid])
        {
            switch ((int)model)
            {
            case find_first:
                if (mid == 0 || arr[mid - 1] != value)
                {
                    return mid;
                }
                else
                {
                    high = mid - 1;
                }
                break;
            case find_last:
                if (mid == n - 1 || arr[mid + 1] != value)
                {
                    return mid;
                }
                else
                {
                    low = mid + 1;
                }
                break;
            default:
                break;
            }
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

int BinarySearchEnhancement1(int arr[], int n, int value, Model model)
{
    int low = 0, high = n - 1;
    int mid = low + (int)((high - low) >> 1);

    //数据检查
    if (arr == NULL || n == 0)
    {
        return -2;
    }
    while (low <= high)
    {
        mid = low + (int)((high - low) >> 1);
        if (arr[mid] >= value)
        {
            if (model == find_greater && (mid == 0 || arr[mid - 1] < value))
            {
                return mid;
            }
            else
            {
                high = mid - 1;
            }
        }
        else
        {
            if (model == find_under && (mid == n-1 || arr[mid + 1] > value))
            {
                return mid;
            }
            else
            {
                low = mid + 1;
            }
        }
    }
}
int main(void)
{
    int arr[10] = {1, 3, 4, 5, 6, 8, 8, 8, 11, 18};
    int index = -2;
    int value = 8;
    Model model = find_last;
    index = BinarySearchEnhancement(arr, 10, value, model);
    printf("在arr中的%s等于数值 %d 的位置是 %d \n", model == find_first ? "第一个" : "最后一个", value, index);

    value = 8;
    model = find_under;
    index = BinarySearchEnhancement1(arr, 10, value, model);
    printf("在arr中%s数值 %d 的位置是 %d \n", model == find_greater ? "第一个大于等于" : "最后一个小于", value, index);

    return 1;
}
