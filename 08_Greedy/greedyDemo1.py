#!/usr/bin/env python
# coding=UTF-8
'''
@Descripttion: 采用贪婪算法实现NP问题，或是时间复杂度巨量的任务
@version: 解决集合覆盖问题
@Author: Frame
@LastEditors: Frame
@Date: 2019-04-13 11:22:33
@LastEditTime: 2019-04-13 17:11:21
----------------------------------------------------
贪婪算法描述：
    每一步都采取局部最优解，最终得到的就是全局最优解
----------------------------------------------------
问题描述：
    找出覆盖全美50个洲的最小广播台集合
贪婪算法解决思路：
    1）选出这样一个广播台，即它覆盖了 最多 的 未覆盖州。即便这个广播台覆盖了一些已覆盖的州，也没有关系；
    2）重复第一步，直到覆盖了所有的州
-----------------------------------------------------
NP问题的识别方法：
    1）元素较少是算法的运行速度非常快，但是随着元素数量的增加，速度会变的非常慢
    2）涉及“所有组合”的问题通常是NP完全问题
    3）不能将问题分成小问题，必须考虑各种可能的情况。这可能是NP完全问题
    4）如果问题涉及序列（如旅行商问题中的城市序列）且难以解决，它可能就是NP完全问题
    5）如果问题涉及集合（如广播台集合）且难以解决，它可能就是NP完全问题
    6）如果问题可转换为集合覆盖问题或旅行商问题，那它肯定是NP完全问题
'''

# 包含需要覆盖的州，转为集合，防止元素重复
statesNeeded = set(["mt", "wa", "or", "id", "nv", "ut", "ca", "az"])
# 广播台清单及其覆盖能力
stations = {
    "kone": set(["id", "nv", "ut"]),
    "ktwo": set(["wa", "id", "mt"]),
    "kthree": set(["or", "nv", "ca"]),
    "kfour": set(["nv", "ut"]),
    "kfive": set(["ca", "az"])
}
# 用来存储最终选择的广播台
finalStations = set()

def greedyDemo(statesNeeded,stations,finalStations):
    '''
    @name: greedyDemo(...)
    @brief: 寻找近似最优解
    @param 
            statesNeeded ：包含需要覆盖的州
            stations ： 广播台
            finalStations ： 用来存储最终选择的广播台
    @return: finalStations
    '''
    while statesNeeded:
        bestStation = None
        statesCovered = set()

        for station,statesForStation in stations.items():
            # 取交集，即包含当前广播台覆盖的一系列还未覆盖的州
            covered = statesNeeded & statesForStation
            # 检查广播台覆盖的州是否比bestStation还多
            if len(covered) > len(statesCovered):
                bestStation = station
                statesCovered = covered
        # 减去已经覆盖过的州
        statesNeeded -= statesCovered
        # 添加本次的最佳广播台
        finalStations.add(bestStation)
       
    return finalStations


if __name__ == "__main__":
    print(greedyDemo(statesNeeded,stations,finalStations))
