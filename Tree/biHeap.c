/*
 * @Descripttion: 二叉堆的构建（最小堆为例），并依次为基础构建小优先队列
 * @version: 二叉堆采用顺序存储实现，不同与其他版本的书籍，我们此处，根节点存储在数组下标为1的位置，而非0，即空出一个空间不使用
 * @Author: Frame
 * @Date: 2019-08-26 21:09:06
 * @LastEditors: Frame
 * @LastEditTime: 2019-08-27 11:34:33
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void upAdjust(int arr[], int length);
void downAdjust(int arr[], int parentIndex, int length);
void buildHeap(int arr[], int length);

void resize();


#define QueueSize 32
//构建优先队列的数据结构
typedef struct
{
	int *array;
    int size;
}PriorityQueue;
PriorityQueue priQueue;

/**
 * @name: enQueue
 * @brief: 优先队列的入队操作
 * @param 
 *          int key :入队的值
 * @return: 
 */
void enQueue(int key)
{
    if(priQueue.size >= sizeof(priQueue.array)/sizeof(priQueue.array[0]))
    {
        resize();
    }
    priQueue.array[priQueue.size++] = key;
    upAdjust(priQueue.array,priQueue.size);
}
/**
 * @name: deQueue
 * @brief: 优先队列的出队操作
 * @param {type} 
 * @return: 
 */
int deQueue(void)
{
   if(priQueue.size <= 0)
   {
       return -1;
   }
   //获取堆顶元素
   int headData = priQueue.array[1];
   //替换最后一个元素的位置
   priQueue.array[1] = priQueue.array[--priQueue.size];
   //执行下沉操作
   downAdjust(priQueue.array,1,priQueue.size); 

   return headData;
}

void resize()
{
    int newsize = priQueue.size * 2;
    int * arry = (int *)malloc(sizeof(int)* newsize);
    for (int i = 0; i < newsize; i++)
    {
        if (i < priQueue.size)
        {
            arry[i] = priQueue.array[i];
        }
        
    }
    free(priQueue.array);
    priQueue.array = arry;
}

/**
 * @name: upAdjust
 * @brief: "上浮"操作
 * @param 
 *         int arr[]        ：待调整的堆 
 * @return: 
 */
void upAdjust(int arr[],int length)
{
    int childIndex = length - 1;
    int parentIndex = (int)(childIndex / 2);
    
    int temp = arr[childIndex];     //temp保存叶子节点的值，用于最后的赋值

    // 如果父节点大，则需要上浮
    while (childIndex > 0 && temp < arr[parentIndex])
    {
        arr[childIndex] = arr[parentIndex];
        childIndex = parentIndex;
        parentIndex = (int)(parentIndex / 2) ;
    }
    arr[childIndex] = temp;
}

/**
 * @name: downAdjust
 * @brief: "下沉"调整
 * @param 
 *           int arr[]      ：待调整的堆
 *           int parentIndex：要下沉的父节点
 *           int len        ：堆的有效大小
 * @return: 
 */
void downAdjust(int arr[], int parentIndex, int length)
{
    int childIndex = 2 * parentIndex; //左孩子结点的下标,不一定存在右孩子，因完全二叉树的特性
    int temp = arr[parentIndex];      //保存父节点的值，用于最后的赋值

    //不断下沉，直至最后到达末尾
    while (childIndex < length)
    {
        //如果存在右孩子，且右孩子的值小于左孩子，则更新孩子结点的下标为右孩子
        if (childIndex + 1 < length && arr[childIndex + 1] < arr[childIndex])
        {
            childIndex = childIndex + 1;
        }
        //如果父节点小于任何一个孩子的值，则直接跳出
        if (temp <= arr[childIndex] )
        {
            break;
        }
        //如果父节点大于两个孩子结点的最小值，则将孩子结点与父节点进行交换
        arr[parentIndex] = arr[childIndex];
        //更新此时父节点的下标
        parentIndex = childIndex;
        //更新(左孩子)孩子结点的下标
        childIndex = 2 * childIndex;    
    }
    //找到最后下沉的位置,进行赋值
    arr[parentIndex] = temp;

}

/**
 * @name: buildHeap
 * @brief: 构建二叉堆，本质上就是让所有的非叶子节点依次“下沉”
 * @param {type} 
 * @return: 
 */
void buildHeap(int arr[],int length)
{    
    for (int i = (length-1)/2; i >=1; i--)
    {
        downAdjust(arr,i,length);
    }
}

int main(void)
{
    int arr[] = {0,1,3,2,6,5,7,8,9,10,0};
    int arrLen = sizeof(arr)/sizeof(arr[0]);
    upAdjust(arr,arrLen);

    for (int i = 1; i < arrLen; i++)
    {
        printf("%d ",arr[i]);
    }
	printf("\n");
    int arr1[] = {0,7,1,3,10,5,2,8,9,6};
    int arr1Len = sizeof(arr1)/sizeof(arr1[0]);
    buildHeap(arr1,arr1Len);

    for (int i = 1; i < arr1Len; i++)
    {
        printf("%d ",arr1[i]);
    }
	printf("\n");
    //初始化最小优先序列
    priQueue.array = (int*)malloc(sizeof(int)*QueueSize);
    priQueue.size = 1;

    enQueue(3);
    enQueue(5);
    enQueue(10);
    enQueue(2);
    enQueue(7);
    enQueue(1);

	for (int i = 1; i < priQueue.size; i++)
	{
		printf("%d ", priQueue.array[i]);
	}
	printf("\n");
    printf("deQueue Data is:%d\n",deQueue());
    printf("deQueue Data is:%d\n",deQueue());

	return 0;
}