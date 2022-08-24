#include "linklist.h"

/* @ Func:   创建结点
 * @ Para:   用户信息数据
 * @ Return: 新节点的地址
 */
static Person *LinklistCreateNode(Person *person)
{
    Person *newperson = (Person *)malloc(sizeof(Person));
    if (newperson == NULL)
    {
        printf("创建结点失败!\n");
        exit(-1);
    }
    newperson->next = NULL;
    mystrcpy(newperson->name, person->name);
    mystrcpy(newperson->sex, person->sex);
    newperson->phone = person->phone;
    mystrcpy(newperson->addr, person->addr);
    return newperson;
}

/* @ Func:      按顺序插入
 * @ Para:      头指针的地址
 *              要添加的用户的地址
 * @ Return:    无
 */
static void LinklistInsertByName(Person **head, Person *newpersondata)
{
    Person *newperson = LinklistCreateNode(newpersondata);
    if (*head == NULL)
    {
        newperson->next = NULL;
        *head = newperson;
    }
    else if (mystrcmp(newperson->name, (*head)->name) <= 0)
    {
        newperson->next = *head;
        *head = newperson;
    }
    else
    {
        Person *p = (*head)->next, *q = *head;
        while (p != NULL)
        {
            if (mystrcmp(newperson->name, p->name) <= 0)
            {
                newperson->next = p;
                q->next = newperson;
                break;
            }
            q = p;
            p = p->next;
        }
        if (p == NULL)
        {
            newperson->next = NULL;
            q->next = newperson;
        }
    }
}

/* @ Func:     按姓名搜索用户
 * @ Para:     头指针
 *             要搜索的姓名
 * @ Return:   返回指向结点的指针
 */
static Person *SerachNodeByName(Person *head, char *name)
{
    Person *p = head;
    while (p != NULL)
    {
        if (mystrcmp(p->name, name) == 0)
            return p;
        p = p->next;
    }
    if (p == NULL)
    {
        printf("查无此人!\n");
        return NULL;
    }
}

/* @ Func:      按电话搜索用户
 * @ Para:      头指针
                搜索的电话
 * @ Return:    返回指向结点的指针
 */
static Person *SerachNodeByPhone(Person *head, long phone)
{
    Person *p = head;
    while (p != NULL)
    {
        if (phone == p->phone)
            return p;
        p = p->next;
    }
    if (p == NULL)
    {
        printf("查无此人!\n");
        return NULL;
    }
}

/* @ Func:      删除结点
 * @ Para:      头指针的地址
 *              待删除的结点
 * @ Return:    无
 */
static void LinklistDeleteNode(Person **head, Person *node)
{
    if (*head == NULL)
    {
        printf("通讯录为空！\n");
        return;
    }
    else if (*head == node)
    {
        *head = (*head)->next;
        free(node);
    }
    else
    {
        Person *p = *head, *q = p->next;
        while (q != NULL)
        {
            if (q == node)
            {
                p->next = q->next;
                free(node);
                break;
            }
            p = q;
            q = q->next;
        }
    }
}

/* @ Func:      修改结点
 * @ Para:      头指针的地址
 *              待修改后的结点的地址
 * @ Return:    无
 */
static void LinklistNodeUpdate(Person **head, Person *oldnode, Person *newdata)
{

    LinklistDeleteNode(head, oldnode);
    LinklistInsertByName(head, newdata);
}

/* @ Func:   显示交互界面
 * @ Para:   无
 * @ Return: 无
 */
void Menu(void)
{
    printf("  通讯录          共%4d人  \n", num);
    printf("----------------------------\n");
    printf("1.添加用户   2.查看用户\n");
    printf("3.搜索用户   4.删除用户\n");
    printf("5.修改用户   6.退出\n");
    printf("----------------------------\n");
    printf(">>> ");
}

/* @ Func:   添加用户数据
 * @ Para:   链表头指针
 * @ Return: 1:继续添加
 *           0：不再添加
 */
bool UsrDataAdd(Person **head)
{
    Person tmp;
    char cmd;
    printf("请输入姓名： ");
    scanf("%s", tmp.name);
    printf("请输入性别： ");
    scanf("%s", tmp.sex);
    printf("请输入电话： ");
    scanf("%ld", &tmp.phone);
    if (tmp.phone / 1e10 >= 10)
    {
        printf("电话超过了11位!\n");
        printf("请重新输入:\n");
        getchar();
        sleep(1);
        system("clear");
        return 1;
    }
    else
    {
        printf("请输入地址： ");
        scanf("%s", tmp.addr);
        LinklistInsertByName(head, &tmp);
        printf("用户数据添加成功!\n");
        sleep(1);
        system("clear");
        num++;
        while (1)
        {
            printf("是否继续添加?(y or n): ");
            getchar();
            scanf("%c", &cmd);
            if (cmd == 'y' || cmd == 'Y' || cmd == 10)
            {
                system("clear");
                return 1;
            }
            else if (cmd == 'n' || cmd == 'N')
            {
                system("clear");
                getchar();
                return 0;
            }
            else
                printf("指令输入错误!\n");
        }
    }
}

/* @ Func:   无表头结点的单链表的遍历
 * @ Para:   head:头指针
 * @ Return: 0：数据为空
 *           1：数据不为空
 */
void UsrDataShow(Person *head)
{
    if (head == NULL)
    {
        printf("用户数据为空!\n");
        sleep(1);
        system("clear");
        getchar();
        return;
    }
    else
    {
        CMD cmd;
        Person *p = head;
        while (1)
        {
            printf("显示结果如下：\n");
            printf("          |name      |sex   |phone      |address                 |\n");
            printf("          --------------------------------------------------------\n");
            while (p != NULL)
            {
                printf("          |%-10s|%-6s|%-11ld|%-24s|\n", p->name, p->sex, p->phone, p->addr);
                printf("          --------------------------------------------------------\n");
                p = p->next;
            }
            printf("\n                                                         --q--\n");
            getchar();
            scanf("%c", &cmd);
            if (cmd == 'q')
            {
                getchar();
                system("clear");
                return;
            }
            else if (cmd == 10)
            {
                system("clear");
                return;
            }
            else
            {
                printf("指令错误\n, 请重新输入！\n");
                system("clear");
                getchar();
            }
        }
    }
}

/* @ Func:     打印搜索的结点
 * @ Para:     头指针
 * @ Return:   无
 */
void UsrSearch(Person *head)
{
    CMD cmd[10];
    Person *ret;
    while (1)
    {
        system("clear");
        printf("按姓名或按电话查找(name or phone)? ");
        scanf("%s", cmd);
        if (mystrcmp(cmd, "name") == 0)
        {
            char name[16] = {0};
            printf("请输入搜索的用户的姓名： ");
            scanf("%s", name);
            getchar();
            ret = SerachNodeByName(head, name);
        }
        else if (mystrcmp(cmd, "phone") == 0)
        {
            long phone = 0;
            printf("请输入要搜索的电话： ");
            scanf("%ld", &phone);
            getchar();
            ret = SerachNodeByPhone(head, phone);
        }
        else
        {
            printf("指令错误！请重新输入。\n");
            sleep(1);
            system("clear");
            return;
        }
        while (1)
        {
            if (ret != NULL)
            {
                printf("搜索结果如下:\n");
                printf("          |name      |sex   |phone      |address                 |\n");
                printf("          --------------------------------------------------------\n");
                printf("          |%-10s|%-6s|%-11ld|%-24s|\n", ret->name, ret->sex, ret->phone, ret->addr);
                printf("          --------------------------------------------------------\n");
                printf("\n                                                         --q--\n");
                CMD cmd;
                scanf("%c", &cmd);
                getchar();
                if (cmd == 'q')
                {
                    system("clear");
                    return;
                }
                else if (cmd == 10)
                {
                    getchar();
                    system("clear");
                    return;
                }
                else
                {
                    printf("指令错误\n, 请重新输入！\n");
                    system("clear");
                    getchar();
                }
            }
            else
            {
                sleep(1);
                system("clear");
                break;
            }
        }

        break;
    }
}

/* @ Func:      删除用户
 * @ Para:      头指针的地址
 * @ Return:    无
 */
void UsrDelete(Person **head)
{
    CMD cmd[10];
    Person *ret;
    while (1)
    {
        system("clear");
        UsrDataShow(*head);
        printf("按姓名或按电话删除(name or phone or q)? ");
        scanf("%s", cmd);
        if (mystrcmp(cmd, "name") == 0)
        {
            char name[16] = {0};
            printf("请输入删除的用户的姓名： ");
            scanf("%s", name);
            ret = SerachNodeByName(*head, name);
        }
        else if (mystrcmp(cmd, "phone") == 0)
        {
            long phone = 0;
            printf("请输入要删除的电话： ");
            scanf("%ld", &phone);
            getchar();
            ret = SerachNodeByPhone(*head, phone);
        }
        else if (mystrcmp(cmd, "q") == 0 || mystrcmp(cmd, "quit") == 0 || mystrcmp(cmd, "\n") == 0)
        {
            getchar();
            break;
        }
        else
            printf("指令错误！请重新输入。\n");
        if (ret != NULL)
        {
            LinklistDeleteNode(head, ret);
            num--;
            getchar();
            printf("删除成功！\n");
            sleep(1);
            system("clear");
        }
        break;
    }
}

/* @ Func:      修改用户信息
 * @ Para:      头指针的地址
 * @ Return:    无
 */
void UsrUpdate(Person **head)
{
    CMD cmd[10];
    CMD ch;
    Person *ret;
    while (1)
    {
        system("clear");
        UsrDataShow(*head);
        printf("按姓名或按电话修改(name or phone)? ");
        scanf("%s", cmd);
        if (mystrcmp(cmd, "name") == 0)
        {
            char name[16] = {0};
            printf("请输入修改的用户的姓名： ");
            scanf("%s", name);
            getchar();
            ret = SerachNodeByName(*head, name);
        }
        else if (mystrcmp(cmd, "phone") == 0)
        {
            long phone = 0;
            printf("请输入要修改的电话： ");
            scanf("%ld", &phone);
            getchar();
            ret = SerachNodeByPhone(*head, phone);
        }
        else if (mystrcmp(cmd, "q") == 0 || mystrcmp(cmd, "quit") == 0 || mystrcmp(cmd, "\n") == 0)
        {
            getchar();
            break;
        }
        else
            printf("指令错误！请重新输入。\n");
        if (ret != NULL)
        {
            printf("          |name      |sex   |phone      |address                 |\n");
            printf("          --------------------------------------------------------\n");
            printf("          |%-10s|%-6s|%-11ld|%-24s|\n", ret->name, ret->sex, ret->phone, ret->addr);
            printf("          --------------------------------------------------------\n");
            Person tmp;
            printf("请输入修改后的值：\n");
            printf("请输入姓名： ");
            scanf("%s", tmp.name);
            printf("请输入性别： ");
            scanf("%s", tmp.sex);
            while (1)
            {
                printf("请输入电话： ");
                scanf("%ld", &tmp.phone);
                if (tmp.phone / 1e10 >= 10)
                {
                    printf("电话超过了11位!\n");
                    printf("请重新输入:\n");
                }
                else
                    break;
            }
            printf("请输入地址： ");
            scanf("%s", tmp.addr);
            LinklistNodeUpdate(head, ret, &tmp);
            sleep(1);
            system("clear");
            printf("修改信息成功\n");
            break;
        }
        else
        {
            sleep(1);
            system("clear");
        }
    }
    getchar();
}