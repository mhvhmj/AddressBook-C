#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "mystring.h"

typedef int PerNum;
typedef char CMD;
typedef struct person{
    char name[16];
    char sex[10];
    long phone;
    char addr[32];
    struct person *next;
}Person;



PerNum num;



//~~~FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Menu(void); // 显示用户交互界面
bool UsrDataAdd(Person **head); // 添加用户
void UsrDataShow(Person *head); // 无表头结点的遍历
void UsrSearch(Person *head); // 打印搜索的结点
void UsrDelete(Person **head); // 删除用户
void UsrUpdate(Person **head); // 修改用户

#endif