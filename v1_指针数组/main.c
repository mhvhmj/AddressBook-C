#include "function.h"

int main()
{
    system("clear");
    char cmd;
    People *people[1024] = {0};
    while (1)
    {
        Menu();
        scanf("%c", &cmd);
        system("clear");
        switch(cmd)
        {
            case '1':
                Add(people);// 添加用户
                break;
            case '2':
                ShowAll(people);// 查看用户
                break;
            case '3':
                Search(people);// 搜索用户
                break;
            case '4':
                Delete(people);// 删除用户
                break;
            case '5':
                Edit(people);// 修改用户信息
                break;
            case '6':
                Exit();// 退出
                break;
            default:
                ErrDebug(0);
                break;
        }
    }
    return 0;
}
