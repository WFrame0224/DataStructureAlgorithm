#!/usr/bin/env python
# coding=UTF-8
'''
@Descripttion: 采用python实现Dijkstra算法的实例
@version: 
@Author: Frame
@LastEditors: Frame
@Date: 2019-04-12 10:44:25
@LastEditTime: 2019-04-12 15:35:18
------------------------------------------------
Dijkstra算法的步骤：
    1）找出起点权重值最低的节点，即消耗最小权重值可达的节点；
    2）对于该节点的邻居，检查是都有前往它们的权重值更小的路径，如果有，则更新其开销
    3）重复这个过程，直到对每个节点都这样做
    4）计算最终路径
    *注*：
        1）若权重值是相等的正数，其用途等效于广度优先搜索（BFS）
        2）若边的权重有负数，则该算法不适应，可采用 贝尔曼-福德算法
        3）该算法适合用于有向无环图
'''

# 给出有向图
graph = {
    'A': {'B': 3, 'C': 7},
    'B': {'C': 2, 'D': 4},
    'C': {'D': 1, 'E': 6},
    'D': {'E': 3},
    'E': {}
}
# 记录开销的字典,记录从起点到达当前节点的最少开销
costs = {
    'A': float('inf'),
    'B': float('inf'),
    'C': float('inf'),
    'D': float('inf'),
    'E': float('inf')
}
# 存储父节点的字典
parents = {
    'A': None,
    'B': None,
    'C': None,
    'D': None,
    'E': None
}
# 记录已经被处理过的节点,使用set是为了防止重复添加
processed = set()


def findLowestNode(costs, processed):
    '''
    @name: findLowestNode()
    @brief: 找出costs中未被标记且值最小的节点
    @param 
            costs : 开销表
            processed : 已经处理过的节点列表
    @return: 开销最低的节点列表
    '''
    lowestCost = float('inf')
    lowestCostNode = None
    # 遍历所有节点
    for node in costs:
        cost = costs[node]
        # 如果当前节点的开销更低，且从未处理过
        if cost < lowestCost and node not in processed:
            # 就将其视为开销最低的节点
            lowestCost = cost
            lowestCostNode = node
    return lowestCostNode


def dijkstra(graph, costs, parents, processed):
    '''
    @name: dijkstra()
    @brief: 狄克斯特拉算法主体函数，
            while循环中，根据当前节点与其邻居节点的距离，尝试到达邻居节点的最短距离
            若找到，更新costs字典中，邻居节点的最短距离，同时将邻居节点的父节点设置为当前节点
    @param 
            graph : 有向图 
            costs : 开销表
            parents : 父节点表,循环体结束后就是最终的路径
            processed : 已经处理过的节点列表
    @return: None 算法实现中，parents存储的便是到某个节点的最短路径
    '''
    # 在未处理的节点中找出开销最少（路径权值最小）节点
    currentNode = findLowestNode(costs, processed)
    while currentNode is not None:
        cost = costs[currentNode]
        neighbors = graph[currentNode]
        # 找出该节点的直接可达的节点
        for neighborNode in neighbors.keys():
            # 计算到该邻居节点的开销和
            newCost = cost + neighbors[neighborNode]
            if costs[neighborNode] > newCost:   # 如果当前节点前往该邻居节点更近，开销更小
                # 更新该邻居节点的开销
                costs[neighborNode] = newCost
                # 同时将该邻居节点的父节点设置为当前节点
                parents[neighborNode] = currentNode
        # 标记当前节点为处理过
        processed.add(currentNode)
        currentNode = findLowestNode(costs, processed)


def findShortestPath(graph,start,end):
    '''
    @name: findShortestPath()
    @brief: 寻找从低点到终点的最短路径
    @param {type} 
    @return: 
    '''
    if start in graph.keys() and end in graph.keys():
        # 起点从哪个节点开始，哪个节点的开销即为0
        if start in costs.keys():
            costs[start] = 0
    else:
        print('起点有误')
        return
    # 执行dijkstra算法，找出最短路径
    dijkstra(graph, costs, parents, processed)
    shortestPath = []
    decNode = end
    while decNode:
        shortestPath.append(decNode)
        decNode = parents.get(decNode)
    shortestPath.reverse()

    return shortestPath

if __name__ == "__main__":
    
    print(findShortestPath(graph,'A','E'))
    
