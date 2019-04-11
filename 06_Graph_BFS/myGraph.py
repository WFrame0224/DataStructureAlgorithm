#!/usr/bin/env python
# coding=UTF-8
'''
@Descripttion: 利用字典实现图（Graph）,再用队列实现优先级
@version: 
@Author: Frame
@LastEditors: Frame
@Date: 2019-04-11 09:20:32
@LastEditTime: 2019-04-11 10:07:00
'''
from collections import deque


def creatGraph():
    '''
    @name: creatGraph
    @brief: 解决你人际关系中找到芒果销售商，并将芒果卖给他。需要解决：
            1：在你的人际关系网中，有芒果销售商么？（从节点A出发有前往B的路径么？）
            2：哪个芒果销售商与你的关系最近？（从节点A出发，前往节点B的哪条路径最短？）
            实际上构建的是一个有向图
    @param None
    @return: 字典构成的图graph
    '''
    graph = {}
    # 和你最近的第一层关系,直接的朋友
    graph['you'] = ['alice', 'bob', 'claire']
    # 和你的第二层关系，朋友的朋友
    graph['bob'] = ['anuj', 'peggy']
    graph['alice'] = ['peggy']
    graph['claire'] = ['thom', 'jonny']
    # 和你的第三层关系，朋友的朋友的朋友
    graph['anuj'] = []
    graph['peggy'] = []
    graph['thom'] = []
    graph['jonny'] = []

    return graph

def searchSeller(graph,name):
    '''
    @name: searchSeller()
    @brief: 采用了BFS(广度优先搜索算法进行)
        首先利用字典构建有向图，其次利用队列的FIFO结构区分查找的层级关系，并利用一个列表记录已经查找过的人
        利用循环结构不断的进行查找判断，直至队列为空且人员全部查找完毕
    @param {type} 
    @return: 
    '''
    
    # 创建一个队列
    search_queue = deque()
    # 将你的邻居都加入到这个搜索的队列中
    search_queue += graph[name]
    # 记录检查过的人
    searched = []

    # 只要队列不为空,
    while search_queue:
        # 就取出其中的第一个人
        person = search_queue.popleft()
        # 只有当这个人没有检查过时才检查
        if not person in searched:
            if personIsSeller(person):
                print(person + ' is a mango seller!')
                return True
            else:
                # 如果不是芒果销售商，将这个人的朋友都加入到搜索队列中
                search_queue += graph[person]
                # 将这个人进行标记已经检查过
                searched.append(person)
    return False
            
def personIsSeller(name):
    # 检查人的名字是否是以m结尾的，如果是，他就是芒果销售商
    return name[-1] == 'm'

if __name__ == "__main__":
    searchSeller(creatGraph(),'you')
