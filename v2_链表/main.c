#include "linklist.h"

int main(int argc, char const *argv[])
{
    CMD cmd;
    Person *head = NULL;
    while (1)
    {
        system("clear");
        Menu();
        scanf("%c", &cmd);
        switch(cmd)
        {
            case '1':                             
                while (UsrDataAdd(&head));        // 添加新用户
                break;
            case '2':
                UsrDataShow(head);                // 查看所有用户信息
                break;
            case '3':
                UsrSearch(head);                  // 打印搜索的结点
                break;
            case '4':
                UsrDelete(&head);                 // 删除用户
                break;
            case '5':
                UsrUpdate(&head);                 // 修改用户信息
                break;
            case '6':
                printf("\n~~~Bye~~~\n");
                exit(0);
                break;
            default:
                printf("输入指令有误！\n");
                sleep(1);
                system("clear");
                getchar();
                break;
        }
    }
    return 0;
}
