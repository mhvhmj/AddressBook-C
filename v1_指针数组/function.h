#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include "mystring.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct Perple{
    int id;
    char name[64];
    char sex;
    long phone;
    char address[64];
}People;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Menu(void);// 菜单
void Exit(void);// 退出程序
void ErrDebug(int);// 用户输入错误显示

void Add(People **);// 添加用户
void ShowAll(People **);// 以某种方式遍历所有用户信息
void Search(People **);// 以某种方式搜索用户信息
void Delete(People **);// 以某种方式删除用户信息
void Edit(People **);// 以某种方式修改用户信息



#endif

