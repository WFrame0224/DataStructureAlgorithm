/*
 * @Descripttion: BM算法实现
 * @version: 
 * @Author: Frame
 * @Date: 2019-05-31 09:53:39
 * @LastEditors: Frame
 * @LastEditTime: 2019-05-31 16:44:39
 * -----------------------------------
 * BM算法：
 *   包含两个部分：坏字符原则+好后缀原则
 *      1）坏字符原则：（最好情况下，时间复杂度为O(n/m)）
 *          1.倒着匹配（从后往前匹配），当发现某个字符没法匹配的时候，我们把这个没有匹配的字符叫做坏字符（主串中的字符）
 *          2.拿着坏字符 c 在模式串（子串）中查找，
 *              坏字符在模式串中的字符下标是Si,假如另外的坏字符在模式串中存在，下标记为Xi(不存在记作Xi=-1)
 *          3.找到坏字符之后，模式串应该向后移动的位置为Si-Xi
 *          4.为了提高查找效率，采用散列表存储模式串中所有字符的位置        
 *      2）好后缀原则：（避免因坏字符原则导致的倒退（向前滑动））
 *          1.模式串中最后一部分同主串中有匹配的串{u}，成为好后缀
 *          2.如果找到了好后缀，那么我们我们在模式串中找到另一个跟{u}想匹配的子串{u*}
 *              就将模式串滑到子串{u*}与主串中{u}对齐的位置
 *          3.如果没有找到{u*}(模式串中另一个同{u}匹配的)，我们要将模式串向后移动
 *          4.向后移动不可过渡滑动（直接滑到好后缀后面）
 *          5.除了寻找{u*},还应该考虑 好后缀 的后缀子串，是否存在跟模式串的 前缀子串 匹配的，
 *              我们从好后缀的后缀子串中，找一个最长的并且能跟模式串的前缀子串匹配的，假设为{v}
 *              然后将模式串滑动到{v}同好后缀中{v}的位置
 *          
 *          - 好后缀处理规则中最核心的内容
 *              - 在模式串中，查找跟好后缀匹配的另一个子串  ----->利用suffix数组
 *              - 在好后缀的 后缀子串 中，查找最长的，能跟模式串 前缀子串 匹配的 后缀子串----->利用prefix数组
 *              
 *              具体应用步骤：
 *                1）假设好后缀长度是k,我们先拿好后缀在suffix数组中查找其匹配的子串
 *                2）如果存在子串（suffix[k]!=-1），那么我们就将模式串往后移动 j-suffix[k]+1 位（j表示坏字符对应的模式串中的下标）
 *                3）如果不存在子串（suffix[k] == -1），我们需要好后缀处理规则的第二条核心内容
 *                4）好后缀的后缀子串b[r,m-1](其中 r 取值从 j+2 到 m-1 )的长度为k=m-r，
 *                      如果 prefix[k]==True,表示长度为 k 的后缀子串，有可匹配的前缀子串，这样我们可以把模式串后移 r 位
 *                      如果 prefix[k]==False，表示长度为 k 的后缀子串中，无可匹配的前缀子串，我们把模式串直接后移 m 位
 *  -------------------------------------------
 * 当模式串和主串中的某个字符不匹配的时候，如何选择用好后缀规则还是坏字符规则？
 *      - 分别计算好后缀和坏字符往后滑动的位数
 *      - 然后取两个数中最大的，作为模式串往后滑动的位数，可以避免坏字符规则，计算得到的往后滑动位数为负数的情况
 * 
 */
#include "string.h"

#define MAX_SIZE 255

typedef char String[MAX_SIZE];
typedef enum
{
    FALSE,
    TRUE
} Boolen;

void generate_Bc(String T, int m, int TC[]);
void generate_GS(String T, int m, int suffix[], Boolen prefix[]);
int moveByGS(int j, int m, int suffix[], Boolen prefix[]);
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
 * @name: generate_GS
 * @brief: 我们拿下标从 0 到 i 的子串（i 可以是 0 到 m-2）与整个模式串，求公共后缀子串。如果公共后
 *         缀子串的长度是k，那我们就记录suffix[k]=j(j表示公共后缀子串的起始下标)。如果j==0也就是说
 *         公共后缀子串也是模式串的前缀子串，那么我们就记录prefix[k]=true 
 * @param 
 *        String T：模式串（子串）
 *           int m：模式串长度
 *    int suffix[]：后缀子串数组
 *                下标：             表示后缀子串的长度
 *                下标对应的数组内容：  在模式串中跟好后缀{u}相匹配的子串{u*}的起始下标值
 *    int prefix[]：用来记录模式串的后缀子串是能否匹配模式串的前缀子串
 *                下标：             表示后缀子串的长度    
 *                下标对应的数组内容： 后缀子串匹配模式串前缀子串的结果 false/true     
 * @return: 
 */
void generate_GS(String T, int m, int suffix[], Boolen prefix[])
{
    int i, j;
    int k;
    i = 0;
    //suffix,prefix初始化
    for (i = 0; i < m; i++)
    {
        suffix[i] = -1;
        prefix[i] = FALSE;
    }
    for (i = 0; i < m - 1; i++) //T[0,i]
    {
        j = i;
        k = 0;                                 //公共后缀子串长度
        while (j >= 0 && T[j] == T[m - 1 - k]) //与 T[0,m-1] 求公共后缀子串
        {
            ++k;           //找到一公共子串，公共后缀子串长度加1
            suffix[k] = j; //j表示公共后缀子串在b[0,i]中的起始下标
            --j;           //找到一个与后缀子串匹配的字符，继续倒着移动
        }
        if (j == -1) //如果公共后缀子串也是模式串的前缀子串，因为程序实现的原因“多减一次”
        {
            prefix[k] = TRUE;
        }
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
    int suffix[m], prefix[m];
    int x, y; //分别记录坏字符原则，和好后缀原则对应的移动位置，取最大的那个

    i = 0; //表示主串与模式串对齐的第一个字符
    //生成坏字符的散列表
    generate_Bc(T, m, TC);
    //生成公共后缀子串数组suffix和对应的前缀子串prefix
    generate_GS(T, m, suffix, prefix);

    while (i <= n - m)
    {
        for (j = m - 1; j >= 0; j--) // 模式串从后往前匹配
        {
            if (S[i + j] != T[j]) //存在坏字符，坏字符对应模式串中的下标为j
            {
                break;
            }
        }
        if (j < 0)
        {
            *index = i;
            return; // 匹配成功返回主串与模式串第一个匹配的字符的位置
        }

        //开始利用坏字符和好后缀原则进行滑动

        //坏字符(主串中的字符)在模式串中的位置,模式串向后移动（ Si-Xi：j-TC[(int)S[i + j]] ）位
        x = j - TC[(int)S[i + j]];
        //好后缀原则，得到需要移动的位置
        if (j < m - 1)
        {
            y = moveByGS(j, m, suffix, prefix);
        }
        // 两种原则中取最大值，得到最终的移动位置
        i = i + (y > x ? y : x);
    }
    *index = -1;// 没有符合的子串
    return;
}
/**
 * @name: moveByGS
 * @brief: 根据好后缀原则需要移动的位置
 *          1）假设好后缀长度是k,我们先拿好后缀在suffix数组中查找其匹配的子串
 *          2）如果存在子串（suffix[k]!=-1），那么我们就将模式串往后移动 j-suffix[k]+1 位（j表示坏字符对应的模式串中的下标）
 *          3）如果不存在子串（suffix[k] == -1），我们需要好后缀处理规则的第二条核心内容
 *          4）好后缀的后缀子串b[r,m-1](其中 r 取值从 j+2 到 m-1 )的长度为 k=m-r，
 *                如果 prefix[k]==True,表示长度为 k 的后缀子串，有可匹配的前缀子串，这样我们可以把模式串后移 r 位
 *                如果 prefix[k]==False，表示长度为 k 的后缀子串中，无可匹配的前缀子串，我们把模式串直接后移 m 位
 * @param 
 *           int j：坏字符对应的模式串中的位置
 *           int m：模式串的长度
 *    int suffix[]：公共后缀子串数组
 * Boolen prefix[]：与公共后缀子串对应的前缀数组
 * 
 * @return: 好后缀原则需要移动的位置
 */
int moveByGS(int j, int m, int suffix[], Boolen prefix[])
{
    int r;
    int k = m - 1 - j; //好后缀的长度
    int y = 0;
    if (suffix[k] != -1)
    {
        return (j - suffix[k] + 1);
    }
    for (r = j + 2; r <= m - 1; r++) //遍历后缀子串
    {
        k = m - r;             // 后缀子串的长度
        if (prefix[k] == TRUE) // 表示模式串中存在有可匹配的前缀子串
        {
            return r; //模式串后移 r 位
        }
        return m; // 模式串中不存在有可匹配的前缀子串，模式串后移 m 位
    }
}

int main(void)
{
    return 0;
}