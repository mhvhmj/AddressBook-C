#include "linklist.h"

int main(int argc, char const *argv[])
{
    char CMD;
    person *head = Init();
MENU:
    system("clear");
    Menu();
    scanf("%c", &CMD);
    switch (CMD)
    {
        case '1':
            AddPerson(head);
            goto MENU;
        case '2':
            ShowPerson(head);
            goto MENU;
        case '3':
            SearchUsr(head);
            goto MENU;
        case '4':
            DeleteSignalPerson(head);
            goto MENU;
        case '5':
            DeleteAllPerson(head);
            goto MENU;
        case '6':
            AdjustPerson(head);
            goto MENU;
        case '0':
            Exit();
            goto MENU;
        default:
            getchar();
            printf("输入有误，请重新输入！\n");
            sleep(1);
            goto MENU;
    }

    return 0;
}
