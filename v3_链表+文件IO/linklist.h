#ifndef _LINKLIST_H__
#define _LINKLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "mystring.h"

typedef struct Person{
    char name[32];
    char sex[10];
    char phone[12];
    char address[32];
    struct Person *next;
}person;

#define SAVE_PATH "./AddressBook.txt"

/* @ brief:     交互界面
 * @ Para:      void
 * @ Return:    void
 */
void Menu(void);
/* @ brief:     初始化通讯录
 * @ Para:      void
 * @ Return:    头指针
 */
person *Init(void);
/* @ brief:     添加用户数据
 * @ Para:      头节点的地址
 * @ Return:    void
 */
void AddPerson(person *head);
/* @ brief:     遍历所有用户
 * @ Para:      头节点的地址
 * @ Return:    void 
 */
void ShowPerson(person *head);
/* @ brief:     搜索用户
 * @ Para:      头节点地址
 * @ Return:    void
 */
void SearchUsr(person *head);
/* @ brief:     删除单个用户
 * @ Para:      head：右指针
 * @ Return:    void
 */
void DeleteSignalPerson(person *head);
/* @ brief:     删除全部用户
 * @ Para:      head：头节点
 * @ Return:    void
 */
void DeleteAllPerson(person *head);
/* @ brief:     修改用户
 * @ Para:      head：头指针
 * @ Return:    void
 */
void AdjustPerson(person *head);
/* @ brief:     退出程序
 * @ Para:      void
 * @ Return:    void
 */
void Exit(void);


#endif