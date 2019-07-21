/*
 * @Descripttion: 二分查找C语言版本
 * @version: 
 * @Author: Frame
 * @Date: 2019-07-21 13:43:50
 * @LastEditors: Frame
 * @LastEditTime: 2019-07-21 14:14:29
 */
#include <stdio.h>
#include <stdlib.h>

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
    int mid = low + (int)((high - low)>>1);

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
        mid = low + (int)((high - low)>>1);
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
    int arr[10] = {1,2,3,4,4,6,7,8,9,10};
    int index = -2;
    int value = 10;
    index = BinarySearchBase(arr,10,value);

    printf("数值 %d 在arr中的位置是 %d \n",value,index);
    return 1;
}