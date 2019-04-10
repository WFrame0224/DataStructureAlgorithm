/*
 * @Descripttion: 散列表测试文件
 * @version: 
 * @Author: Frame
 * @LastEditors: Frame
 * @Date: 2019-04-10 11:08:28
 * @LastEditTime: 2019-04-10 11:24:27
 */

#include <stdio.h>
#include <stdlib.h>

#include "HashTable.h"

// 要放入哈希表中的结构体
typedef struct
{
    int age;
    float score;
    char name[32];
    char data[1024 * 1024 * 10];
} Student;

// 结构体内存释放函数
static void free_student(void *stu)
{
    free(stu);
}
// 显示学生信息的函数
static void show_student(Student *p)
{
    printf("姓名:%s, 年龄:%d, 学分:%.2f\n", p->name, p->age, p->score);
}

int main()
{
    // 新建一个HashTable实例
    HashTable *ht = hashTableNew();
    if (ht == NULL)
    {
        return -1;
    }
    // 向哈希表中加入多个学生结构体
    for (int i = 0; i < 10; i++)
    {
        Student *stu = (Student *)malloc(sizeof(Student));
        stu->age = 18 + rand() % 5;
        stu->score = 50.0f + rand() % 100;
        sprintf(stu->name,"同学%d",i);
        hashTableInsert(ht,stu->name,stu,free_student);
    }
    
    // 根据学生姓名查找学生结构
    for(int i = 0; i < 10; i++)
    {
        char name[32];
        sprintf(name, "同学%d", i);
        Student* stu = (Student*)hashTableGet(ht,name);
        show_student(stu);
    }
    // 销毁哈希表实例
    hashTableDelete(ht);
    return 0;
    
}