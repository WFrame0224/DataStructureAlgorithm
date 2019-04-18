#!/usr/bin/env python
# coding=UTF-8
'''
@Descripttion:
@version: 
@Author: Frame
@LastEditors: Frame
@Date: 2019-04-18 11:14:41
@LastEditTime: 2019-04-18 16:52:23
-------------------------------------------------------------
假设你要去野营。你有一个容量为6磅的背包，需要决定该携带下面的哪些东西。其中
每样东西都有相应的价值，价值越大意味着越重要：
     水（重3磅，价值10）；
     书（重1磅，价值3）
     食物（重2磅，价值9）；
     夹克（重2磅，价值5）；
     相机（重1磅，价值6）。
问：携带哪些东西时价值最高？
'''


# 最终问题的最终限制条件
MAXLimit = 6
# 可携带的物品集
FoodsSet = {
    # Name:(subLimit,value)
    'W': (3, 10),
    'B': (1, 3),
    'F': (2, 9),
    'J': (2, 5),
    'C': (1, 6)
}


def getResultDynamic(FoodsSet, MAXLimit):
    '''
    @name: getResultDynamic(...)
    @brief: 动态规划，解决典型的背包问题
            ceil[i][j] = max(
                    ceil[i-1][j],# 上一个单元格的值
                    thisValue + ceil[i-1][j-thisLimit] # 当前商品的价值 + 剩余空间的价值（ceil[i-1][j-当前商品的重量]）
            )
    @param {type} 
    @return: 最大的价值，对应的方案
    '''
    MINLimit = MAXLimit
    # 找到最小分辨率
    for key, value in FoodsSet.items():
        if MINLimit > value[0]:
            MINLimit = value[0]
        else:
            continue

    # 得出最终的列的范围
    j_MAX = int(MAXLimit / MINLimit)
    i_MAX = len(FoodsSet)

    # 初始化表格，三维数组
    dynamicMap = [[[0,[]] for col in range(j_MAX)] for row in range(i_MAX)]
    
    # 获取事物列表
    foodsList = list(FoodsSet.keys())

    # 动态规划，更新表格
    for i in range(0, i_MAX):
        for j in range(0, j_MAX):
            
            # 如果是首行
            if i == 0:
                # 如果没有剩余空间的价值
                if j < FoodsSet[foodsList[i]][0] - 1:
                    dynamicMap[i][j][0] = 0
                    continue
                else:
                    dynamicMap[i][j][0] = FoodsSet[foodsList[i]][1]
                    dynamicMap[i][j][1].clear()
                    dynamicMap[i][j][1].append(foodsList[i])
            # 如果不是首行
            else:
                # 如果当前重量放不下本行对应的物体
                if j+1 < FoodsSet[foodsList[i]][0]:
                    dynamicMap[i][j] = dynamicMap[i-1][j]
                    continue
                # 如果当前重量放得下本行的物体,且没有剩余价值
                elif j +1 == FoodsSet[foodsList[i]][0]:
                    # 如果当前商品的价值大于上以上相同列，怎更新为本行的对应的商品
                    if FoodsSet[foodsList[i]][1] > dynamicMap[i-1][j][0]:
                        dynamicMap[i][j][0] = FoodsSet[foodsList[i]][1]
                        dynamicMap[i][j][1].clear()
                        dynamicMap[i][j][1].append(foodsList[i])
                    else:
                        dynamicMap[i][j] = dynamicMap[i-1][j]
                        continue
                # 如果当前重量放得下本行对应的物体，且有多余空间
                else:
                    # 如果上一个单元格的值 > 当前商品的价值 + 剩余空间的价值
                    if dynamicMap[i-1][j][0] >= FoodsSet[foodsList[i]][1] + dynamicMap[i-1][j-FoodsSet[foodsList[i]][0]][0]:
                        dynamicMap[i][j] = dynamicMap[i-1][j]
                        continue
                    # 如果上一个单元格的值 < 当前商品的价值 + 剩余空间的价值
                    else:
                        # 更新价值
                        dynamicMap[i][j][0] = FoodsSet[foodsList[i]][1] + dynamicMap[i-1][j-FoodsSet[foodsList[i]][0]][0]
                        # 更新选项
                        dynamicMap[i][j][1].clear()
                        dynamicMap[i][j][1] = (dynamicMap[i-1][j-FoodsSet[foodsList[i]][0]][1]).copy()
                        dynamicMap[i][j][1].append(foodsList[i])

    # for row in dynamicMap:
    #     print(row)
                        
    return  dynamicMap[i_MAX-1][j_MAX-1][0],dynamicMap[i_MAX-1][j_MAX-1][1]            
            



if __name__ == "__main__":
    maxValue,result = getResultDynamic(FoodsSet, MAXLimit)
    print("最大的价值为:%3d, 对应的方案为:%s" % (maxValue,result))
