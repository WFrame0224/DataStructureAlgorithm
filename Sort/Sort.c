/*
 * @Descripttion: 本文件实现常见的几种排序算法：冒泡，选择、插入、快速、归并等
 * @version: 
 * @Author: Frame
 * @Date: 2019-06-28 15:48:27
 * @LastEditors: Frame
 * @LastEditTime: 2019-07-06 21:07:54
 */
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <math.h>

void ArrayToString(int arr[], int n);

void QuickSort(int arr[], int n);
void QuickSort_C(int arr[], int p, int r);
int Partition(int arr[], int p, int r);

void MergeSort_C(int arr[], int p, int r);
void Merge(int arr[], int p, int q, int r);

/**
 * @name: BucketSort
 * @brief: 桶排序
 *      思想：
 *          核心思想是将要排序的数据分到几个有序的桶里，每个桶里的数据再单独进行排序，
 *      桶内排序完成后，再把每个桶里数据按照顺序依次取出，组成的序列就是有序的了。
 *      
 *      比较关键的一点是映射函数的确定，即将元素放入桶中的映射，为了使得桶排序更加高效，我们需要做到下面两点：
 *      （1）在额外空间充足的情况下，尽量增加桶的数量
 *      （2）使用的映射函数能够将输入的N个数据均分的分配到K个桶中
 *      特点：
 *          时间复杂度：O(n) ，
 *          最好情况，输入的数据被均匀的分配到每一个桶中O(n)
 *          最坏的情况，输入的数据被分配到了同一个桶中o(nlogn)
 * 
 *          是 稳定 的排序算法，必须从数组后面插入临时数组，才能保证
 *      限制条件:
 *          堆排序比较适合用在外部排序中（数据存储在外部磁盘中，数据量比较大，内存有限，无法将数据全部加载到内存中）
 *          数据范围不能太大
 * @param 
 *          int arr[]   :待排序数组 
 *          int n       :数组长度
 * @return: 
 */
void BucketSort(int arr[], int n)
{
    int MAX = arr[0];
    int MIN = arr[0];
    int i = 0, j = 0;
    //桶的数量
    int bucketNum = 0;
    //每个桶的元素个数
    int bucketSize = 10;
    //创建桶数组，二维数组，行表示一不同的桶，列表示桶内不同的元素
    int **bucketArr;
    //每个元素存储的是存放入桶中元素的数量
    int buckIndex[10] = {0};
    int index = 0;

    //查找需要排序的数组的范围
    for (i = 0; i < n; i++)
    {
        if (MAX < arr[i])
        {
            MAX = arr[i];
        }
        if (MIN > arr[i])
        {
            MIN = arr[i];
        }
    }
    //得到桶的数量
    bucketNum = (int)floor((MAX - MIN) / bucketSize) + 1;
    //动态申请桶的数量
    bucketArr = (int **)malloc(sizeof(int *) * bucketNum);
    for (i = 0; i < bucketNum; i++)
    {
        bucketArr[i] = (int *)malloc(sizeof(int) * bucketSize);
    }
    //将全部元素放入桶中
    for (i = 0; i < n; i++)
    {
        //得到应该存放的桶
        index = (int)floor((arr[i] - MIN) / bucketSize);
        //放入桶中
        bucketArr[index][buckIndex[index]++] = arr[i];
    }
    //将桶中的元素进行排序
    for (i = 0; i < bucketNum; i++)
    {
        QuickSort(bucketArr[i], buckIndex[i]);
        //将桶中的元素依次取出
        for (j = 0; j < buckIndex[i]; j++)
        {
            arr[i+j] = bucketArr[i][j];
        }
    }
    //释放缓存区
    for ( i = 0; i < bucketNum; i++)
    {
        free(bucketArr[i]);
    }
    free(bucketArr); 
}

/**
 * @name: CountingSort
 * @brief: 计数排序
 *      思想：
 *          计数排序是桶排序的特殊情况，当要排序的n个数据，所处的范围并不大的时候，比如最大值是k,我们就把数据
 *  划分为K个桶，每个桶内的数据值都是相同的，省掉了桶内的排序的时间
 *      步骤：
 *      （1）找出待排序的数组中最大和最小的元素，计数数组长度 = MAX-MIN+1
 *      （2）统计数组中每个值为i的元素出现的次数，存入数组C的第i项
 *      （3）对所有的计数累加（从C中的第一个元素开始，每一项和前一项相加）
 *      （4）反向填充目标数组：将每个元素i放在新数组的第C(i)项，每放一个元素就将C(i)减去1
 *      特点：
 *          时间复杂度：O(n) 
 *          是 稳定 的排序算法,必须从数组后面插入临时数组，才能保证
 *      限制条件:
 *          计数排序只能用在数据范围不大的场景中，如果数据范围k要比排序的数据n大很多，就不合适用计数排序了
 *          计数排序只能给非负整数排序，如果要排序的数据是其他类型的，要将其在不改变相对大小的情况下，转化为非负整数
 * @param 
 *          int arr[]   :待排序数组 
 *          int n       :数组长度
 * @return: 
 */
void CountingSort(int arr[], int n)
{
    int MAX = arr[0];
    int MIN = arr[0];
    int i = 0;
    int *countArr;
    int countArr_Len = 0;
    int *decArr;
    int index = 0;
    //查找需要排序的数组的范围
    for (i = 0; i < n; i++)
    {
        if (MAX < arr[i])
        {
            MAX = arr[i];
        }
        if (MIN > arr[i])
        {
            MIN = arr[i];
        }
    }
    countArr_Len = MAX - MIN + 1;
    //创建计数数组，分成MAX个大小的区域,并初始化
    countArr = (int *)malloc(sizeof(int) * countArr_Len);
    memset(countArr, 0, sizeof(int) * countArr_Len);
    //填充计数数组,当前存储的是数量
    for (i = 0; i < n; i++)
    {
        countArr[arr[i]] += 1;
    }
    //填充计数数组，最后存储的是计数和
    for (i = 1; i < countArr_Len; i++)
    {
        countArr[i] += countArr[i - 1];
    }
    //开始存放一个数组
    decArr = (int *)malloc(sizeof(int) * n);

    //存放至目标数组
    for (i = n - 1; i >= 0; i--)
    {
        //从计数数组中得到存放的位置
        index = countArr[arr[i]] - 1;

        decArr[index] = arr[i];
        //更新计数数组
        countArr[arr[i]] -= 1;
    }
    //取出存放入原数组中
    for (i = 0; i < n; i++)
    {
        arr[i] = decArr[i];
    }
    //释放之前申请的内存
    free(countArr);
    free(decArr);
}

/**
 * @name: QuickSort
 * @brief: 快速排序
 *      思想：
 *          如果要排序数组中下标从 p 到 r 之间的一组数据，我们选择 p 到 r 之间任意一个数据作为分区点 pivot
 *          我们遍历 p 到 r 之间的数据，将小于pivot放到左边，将大于pivot放到右边，将pivot放到中间，经过这一步，
 *      数据被分为三个部分，前面 p 到q-1 之间都是小于pivot，后面q+1到r之间的是大于pivot的，中间的是pivot，
 *      根据分治的思想，我们可以递归排序从（p~q-1）和（q+1,r）之间的数据，直至区间为1
 *      特点：
 *          时间复杂度：O(nlogn)，最好情况O(nlogn),最坏情况O(n^2)，平均情况O(n^2) 
 *          空间复杂度是O(1)，属于原地排序算法
 *          是 不稳定 的排序算法
 * @param 
 *          int arr[]   :待排序数组 
 *          int n       :数组长度
 * @return: 
 */
void QuickSort(int arr[], int n)
{
    QuickSort_C(arr, 0, n - 1);
}
/**
 * @name: MergeSort_C
 * @brief: 快速排序递归调用函数
 *      递推公式：
 *          quick_sort(p..r) = quick_sort(p..q_1) + quick_sort(q+1,r)
 *      终止条件
 *          p >= r
 * @param 
 *          int arr[]:需要排序的数组
 *          int p，int r:下标从p到r进行排序
 * @return: 
 */
void QuickSort_C(int arr[], int p, int r)
{
    //终止条件
    if (p >= r)
        return;
    //获取分区点
    int pivot = Partition(arr, p, r);
    QuickSort_C(arr, p, pivot - 1);
    QuickSort_C(arr, pivot + 1, r);
}
/**
 * 寻找分区点，返回其下标
 * 使用的是原地分区算法，类似插入排序
 */
int Partition(int arr[], int p, int r)
{
    int i = p, j = p;
    int pivot = arr[r];
    int temp;
    //arr[p,i-1]都是小于pivot的，成为已处理区间，arr[i,r-1]是未处理区间，每次从未处理区间取一个数加入已处理区间尾部
    for (; j <= r - 1; j++)
    {
        if (arr[j] < pivot)
        {
            //交换arr[i]和arr[j]
            temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;

            //已排序数组加1
            i++;
        }
    }
    //将pivot最后插入到i的位置
    arr[r] = arr[i];
    arr[i] = pivot;
    return i;
}
/**
 * @name: MergeSort
 * @brief: 归并排序--分治思想
 *      要排序一个数组，我们先把数组从中间分成前后两个部分，然后后对前后两个部分分别排序，
 * 再将排序好的两个部分合并在一起，这样整个数组就有序了
 *      特点：
 *          时间复杂度：O(nlogn)，最好情况O(nlogn),最坏情况O(nlogn)，平均情况O(nlogn) ，任何情况下都是O(nlogn)
 *          需要临时temp空间，不属于原地排序算法
 *          是 稳定 的排序算法
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
 * @brief: 归并排序递归调用函数
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
    int start1 = p, start2 = q + 1, end1 = q, end2 = r;
    int k = 0;
    //创建一个大小为r-q的临时数组
    int *temp = (int *)malloc((r - p) * sizeof(int));

    //借助临时数组，小的就先往临时数组中放，已经放入之后，自增
    while (start1 <= end1 && start2 <= end2)
    {
        temp[k++] = arr[start1] <= arr[start2] ? arr[start1++] : arr[start2++];
    }
    //把子数组中剩余的数给加上去
    while (start1 <= end1)
    {
        temp[k++] = arr[start1++];
    }
    while (start2 <= end2)
    {
        temp[k++] = arr[start2++];
    }
    for (k = 0; k <= r - p; k++)
    {
        arr[p + k] = temp[k];
    }
    free(temp);
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
    int arr[] = {2, 5, 3, 0, 2, 3, 0, 3};
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

    // printf("归并排序之后的数组为：\r\n");
    // MergeSort(arr, arrLen);
    // ArrayToString(arr, arrLen);

    // printf("选择排序之后的数组为：\r\n");
    // QuickSort(arr, arrLen);
    // ArrayToString(arr, arrLen);

    // printf("计数排序之后的数组为：\r\n");
    // CountingSort(arr, arrLen);
    // ArrayToString(arr, arrLen);

    printf("桶排序之后的数组为：\r\n");
    BucketSort(arr, arrLen);
    ArrayToString(arr, arrLen);

    return 0;
}