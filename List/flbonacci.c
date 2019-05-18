/*
 * @Descripttion: 递归实现裴波那契数列
 * @version: 
 * @Author: Frame
 * @LastEditors: Frame
 * @Date: 2019-05-13 15:25:15
 * @LastEditTime: 2019-05-18 09:48:55
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack_L.c"
static int flboncaaiList[100];

int flbonacci(int n)
{
    if (n < 2)
    {
        flboncaaiList[n] = n;
        return n == 0 ? 0 : 1;
    }
    flboncaaiList[n] = flbonacci(n - 1) + flbonacci(n - 2);
    return flbonacci(n - 1) + flbonacci(n - 2);
}

int main(void)
{
    int flbonacciNumberLength = 12;
    flbonacci(flbonacciNumberLength);
    
    for (int i = 0; i < flbonacciNumberLength; i++)
    {
        printf("%d ", flboncaaiList[i]);
    }

    return 0;
}