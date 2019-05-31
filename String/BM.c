/*
 * @Descripttion: BM算法实现
 * @version: 
 * @Author: Frame
 * @Date: 2019-05-31 09:53:39
 * @LastEditors: Frame
 * @LastEditTime: 2019-05-31 11:32:32
 * -----------------------------------
 * BM算法：
 *   包含两个部分：坏字符原则+好后缀原则
 *      1）坏字符原则：（最好情况下，时间复杂度为O(n/m)）
 *          1.倒着匹配（从后往前匹配），当发现某个字符没法匹配的时候，我们把这个没有匹配的字符叫做坏字符（主串中的字符）
 *          2.拿着坏字符c在模式串（子串）中查找，
 *              坏字符在模式串中的字符下标是Si,假如坏字符在模式串中存在，下标记为Xi(不存在记作Xi=-1)
 *          3.找到坏字符之后，模式串应该向后移动的位置为Si-Xi
 *          4.为了提高查找效率，采用散列表存储模式串中所有字符的位置        
 *      2）好后缀原则：（避免因坏字符原则导致的倒退（向前滑动））
 */
#include "string.h"

#define MAX_SIZE 255

typedef char String[MAX_SIZE];

void generate_Bc(String T, int m, int TC[]);

/**
 * @name: generate_Bc
 * @brief: 模式串生成的简单散列表，存储模式串和模式串对应的下标
 * @param 
 *       String T：模式串（子串）
 *          int m：模式串的长度
 *      char TC[]：模式串存储散列表
 *                  TC 下标 存储的是模式串的ASCII码值
 *                     下标对应的数组，存储的是字符对应于模式串中的位置
 * @return: 
 */
void generate_Bc(String T, int m, int TC[])
{
    int i, assicNum;
    // 初始化bc
    for (i = 0; i < MAX_SIZE; i++)
    {
        TC[i] = -1;
    }
    // 生成对应的散列表
    for (i = 0; i < m; i++)
    {
        assicNum = (int)T[i]; // 计算b[i]的ASCII码值
        TC[assicNum] = i;
    }
}
/**
 * @name: Index_BM
 * @brief: BM算法
 * @param  
 *          String S：主串
 *          String T：模式串
 *        int *index：获取最后的索引
 * @return: 
 */
void Index_BM(String S, String T, int *index)
{
    //求取主串和模式串的长度
    int n = strlen(S);
    int m = strlen(T);
    int i, j;
    int TC[255];
    i = 0;//表示主串与模式串对齐的第一个字符
    //生成坏字符的散列表
    generate_Bc(T, m, TC);
    while (i < n - m)
    {
        for (j = m - 1; i > 0; j--)
        {
            if (S[i + j] != T[j]) //存在坏字符
            {
                break;
            }
        }
        if (j < 0)
        {
            *index = i;
            return; // 匹配成功
        }
        //坏字符(主串中的字符)在模式串中的位置,模式串向后移动(Si-Xi)
        i = i + (j - TC[(int)S[i + j]]);
    }
    *index = -1;
    return;
}

int main(void)
{
    return 0;
}