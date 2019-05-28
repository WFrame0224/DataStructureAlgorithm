/*
 * @Descripttion: 实现普通字符串的 朴素的模式匹配算法 KMP模式匹配算法
 * @version: 采用基本的数组实现
 * @Author: Frame
 * @Date: 2019-05-28 21:19:26
 * @LastEditors: Frame
 * @LastEditTime: 2019-05-28 22:05:01
 */
#include "stdlib.h"
#include "stdio.h"
#include "myString.c"

/**朴素的模式匹配算法 算法时间复杂度O(n+m)
 * @name: findStr,同myString.c 中的index方法相同，重新提炼巩固一下
 * @brief: 返回子串T在主串S中第pos个字符之后的位置，若不存在，则函数返回值为0
 * @param 
 *          S：主串 S[0]存放串的长度
 *          T：子串 T[0]存放串的长度
 *          pos：位置,[1,StrLength(S)]
 * @return: 
 */
int findStr(String S, String T, int pos)
{
    int i = pos; //从主串第pos位开始寻找
    int j = 1;
    int SLen = S[0];
    int TLen = T[0];

    while (i <= SLen && j <= TLen) // 若i小于S长度，且j小于T长度则未寻找结束，继续寻找
    {
        if (S[i] == T[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 2;// 返回到已经匹配过的下一位
            j = 1;
        }
    }
    if (j > TLen)
        return i-TLen;
    else
        return 0;
}

int main(void)
{
    char *s = "123456789";
    char *t = "567";
    String S,T;
    StrAssign(S,s);
    StrAssign(T,t);  
    printf("找到的位置为第%d",findStr(S,T,6));
    return 0;
}
