#include "function.h"

static int CheckRepetition(People **, People *);//检查是否重复
static int AddPeople(People **);//创建新用户
static void ShowMsg(People *, int);//查看用户
static void Show(People **);//遍历用户
static People **SortbyName(People **);//以姓名为升序输出
static People **SortbyID(People **);//以id为升序输出
static People *FindbyID(People **);//通过id查找用户信息
static People *FindbyName(People **);//通过姓名查找用户信息
static int FindbyWay(void);//选择查找/删除的关键词
static void DeleteMsg(People **, People *);//删除用户信息
static void EditMsg(People **, People *);//修改用户信息

int num = 0;



/* Func:   检查是否重复
 * Para:   无
 * Return: 1：重复
           0：不重复
 * */
static int CheckRepetition(People **people, People *target)
{
    int i = 0;
    unsigned char flag = 0;
    if (num >= 1)
    {
        for (i = 0; i < num; i++)
        {
            if (people[i]->id == target->id)
                continue;
            if (mystrcmp(people[i]->name, target->name) != 0 ||
                people[i]->sex != target->sex ||
                people[i]->phone != target->phone ||
                mystrcmp(people[i]->address, target->address) != 0)
                flag = 0;
            else
            {
                flag = 1;
                break;
            }
        }
        if (flag)
            return 1;
        else
            return 0;   
    }
}

/* Func:    创建新用户
 * Para:    存放各用户的结构体地址的指针数组
 * Return:  0:不重复添加
 *          1:重复添加
 * */
static int AddPeople(People **people)
{
    char cmd;
    int ret = 0;
    People *new = (People *)malloc(sizeof(People));
    if (new == NULL)
    {
        printf("添加用户失败!\n");
        Exit();
    }
    system("clear");
    printf("请输入用户信息(姓名|性别|电话|地址):\n");
    printf("输入姓名: ");
    scanf("%s", new->name);
    getchar();
    printf("输入性别: ");
    scanf("%c", &new->sex);
    printf("输入电话: ");
    scanf("%ld", &new->phone);
    printf("输入地址: ");
    scanf("%s", new->address);
    ret = CheckRepetition(people, new);
    if (ret == 0)
    {
        people[num++] = new;
        new->id = num;
        printf("录入信息成功!现在共有%d人\n\n", num);
        sleep(1);
        system("clear");
        
        while(1)
        {
            printf("是否继续添加(y or n)\ncmd: ");
            getchar();
            scanf("%c", &cmd);
            if(cmd == 'y' || cmd == '\n')
                return 1;
            else if (cmd == 'n')
            {
                return 0;
            }
            else
                ErrDebug(0);
        }
    }
    else if (ret == 1)
    {
        free(new);
        ErrDebug(2);
    }
}

/* Func:    查看用户
 * Para:    显示一个用户的信息
            on = 1：显示表头
            on = 0：不显示表头
 * Return:  无
 * */
static void ShowMsg(People *people, int on)
{
    if(on == 1)
        printf("| id |  name  | sex |    phone    |      address     |\n");
    printf("---------------------------------------------------------------\n");
    printf("|%4d|%8s|%5c|%13ld|%18s|\n", people->id,
                                         people->name,
                                         people->sex,
                                         people->phone,
                                         people->address);
}   

/* Func:    遍历用户
 * Para:    people: 存放各用户的结构体地址的指针数组
 * Return:  无
 * */
static void Show(People **people)
{
    int i;
    system("clear");
    printf("显示所有用户如下:\n\n");
    printf("| id |  name  | sex |    phone    |      address     |\n");
    for (i = 0; i < num; i++)
        ShowMsg(people[i], 0);
    printf("\n");
    getchar();
}

/* Func:    以姓名为升序输出
 * Para:    存放各用户的结构体地址的指针数组
 * Return:  排序后的指针数组
*/
static People **SortbyName(People **people)
{
    People **res = people;
    People *tmp = NULL;
    int i, j;
    for (i = 0; i < num - 1; i++)
    {
        for (j = i + 1; j < num; j++)
        {
            if (mystrcmp(res[i]->name, res[j]->name) == 1)
            {
                tmp = res[i];
                res[i] = res[j];
                res[j] = tmp;
            }
        }
    }
    return res;
}

/* Func:    以id为升序输出
 * Para:    存放各用户的结构体地址的指针数组
 * Return:  排序后的指针数组
*/
static People **SortbyID(People **people)
{
    People **res = people;
    People *tmp = NULL;
    int i, j;
    for (i = 0; i < num - 1; i++)
    {
        for (j = i + 1; j < num; j++)
        {
            if (res[i]->name > res[j]->name)
            {
                tmp = res[i];
                res[i] = res[j];
                res[j] = tmp;
            }
        }
    }
    return res;
}

/* Func:    通过id查找用户信息
 * Para:    people: 存放各用户的结构体地址的指针数组
 * Return:  用户信息的地址
 * */
static People *FindbyID(People **people)
{
    People *res;
    int i, id;
    system("clear");
    printf("请输入想要查找的id名:\n");
    scanf("%d", &id);
    getchar();
    for (i = 0; i < num; i++)
    {
        if (people[i]->id == id)
            return people[i];
    }
    return NULL;
}

/* Func:    通过姓名查找用户信息
 * Para:    people: 存放各用户的结构体地址的指针数组
 * Return:  用户信息的地址
 * */
static People *FindbyName(People **people)
{
    int i;
    char name[64];
    printf("请输入想要查找的姓名:\n");
    scanf("%s", name);
    getchar();
    for (i = 0; i < num; i++)
    {
        if (mystrcmp(people[i]->name, name) == 0)
            return people[i];
    }
    return NULL;
}

/* Func:    选择查找/删除的关键词
 * Para:    无
 * Return： 0:通过id搜索
            1:通过姓名搜索
            -1:关键词输入错误
*/
static int FindbyWay()
{
    People *res = NULL;
    char cmd[5] = {0};
    printf("通过何种方式查找(id or name):\n");
    scanf("%s", cmd);
    if (mystrcmp(cmd, "id") == 0)
        return 0;
    else if (mystrcmp(cmd, "name") == 0)
        return 1;
    else
    {
        ErrDebug(0);
        return -1;
    }
}

/* Func:    删除用户信息
 * Para:    删除用户信息
 * Return:  无
 * */
static void DeleteMsg(People **people, People *target)
{
    int i = 0;
    while(people[i] != target)
        i++;
    while (people[i + 1] != NULL)
    {
        people[i] = people[i + 1];
        people[i]->id--;
        i++;
    }
    free(people[i + 1]);
    num--;
    printf("删除信息成功!\n");
    sleep(1);
    system("clear");    
}

/* Func:    修改用户信息
 * Para:    用户结构体地址
 * Return: 无
 * */
static void EditMsg(People **people, People *target)
{
    char cmd;
    int ret = 0;
    People *tmp = (People *)malloc(sizeof(People));
    system("clear");
    while (1)
    {
        printf("是否为此条信息(y or n):\n");
        ShowMsg(target, 1);
        printf("\n");
        scanf("%c", &cmd);

        if (cmd == 'y' || cmd == '\n')
        {
            if (cmd == 'y')
                getchar();
            printf("请输入修改后的内容:\n");
            printf("输入姓名: ");
            scanf("%s", tmp->name);
            getchar();
            printf("输入性别: ");
            scanf("%c", &tmp->sex);
            printf("输入电话: ");
            scanf("%ld", &tmp->phone);
            printf("输入地址: ");
            scanf("%s", tmp->address);
            getchar();
            system("clear");
            ret = CheckRepetition(people, tmp);
            if (ret == 0)
            {
                target = tmp;
                printf("修改后的值为:\n");
                    ShowMsg(target, 1);
                sleep(2);
                system("clear");
                break;
            }
            else
            {
                ErrDebug(2);
                break;
            }
            free(tmp);
        }
        else if (cmd == 'n')
        {
            system("clear");
            break;
        }
        else
            ErrDebug(0);
    }
}



/* Func:   显示菜单
 * Para:   无
 * Return: 无
 * */
void Menu(void)
{
    printf("  通讯录          共%4d人  \n", num);
    printf("----------------------------\n");
    printf("1.添加用户   2.查看用户\n");
    printf("3.搜索用户   4.删除用户\n");
    printf("5.修改用户   6.退出\n");
    printf("----------------------------\n");
}

/* Func:   退出程序
 * Para:   无
 * Return: 无
 * */
void Exit(void)
{
    printf("\nBy~~\n");
    exit(0);
}

/* Func:   输入错误时进行提示
 * Para:   0: 命令输入错误
 * Return: 无
 * */
void ErrDebug(int err_code)
{
    if (err_code == 0)
        printf("Code:%d 请重新输入命令!\n", err_code);
    else if (err_code == 1)
        printf("Code:%d 查无此人!\n", err_code);
    else if (err_code == 2)
        printf("Code:%d 数据重复!\n", err_code);
    sleep(1);
    system("clear");
}

/* Func:    循环添加用户
 * Para:    存放各用户的结构体地址的指针数组
 * Return:  无
*/
void Add(People **people)
{
    int ret = 1;
    while(ret)
        ret = AddPeople(people);
    system("clear");
    getchar();
}

/* Func:    以某种方式遍历所有用户信息
 * Para:    people: 存放各用户的结构体地址的指针数组
 * Return:  无
 * */
void ShowAll(People **people)
{
    char cmd;
    int ret ;
    while((ret = FindbyWay())== -1);
    system("clear");
    while (1)
    {
        if (ret == 0)
            Show(SortbyID(people));
        else if (ret == 1)
            Show(SortbyName(people));
        printf("0: exit\n");
        scanf("%c", &cmd);
        if (cmd == '0')
        {
            getchar();
            system("clear");
            break;
        }
        else if (cmd == '\n')
        {
            system("clear");
            break;
        }
        else
            ErrDebug(0);
    }

}

/* Func:    以某种方式搜索用户信息
 * Para:    people: 存放各用户的结构体地址的指针数组
 * Return:  无
 * */
void Search(People **people)
{
    int ret;
    People *res = NULL;
    char cmd;
    // system("clear");
    while ((ret = FindbyWay()) == -1);
    if (ret == 0)
    {
        res = FindbyID(people);
        if (res == NULL)
            ErrDebug(1);
        else
        {
            system("clear");
            while (1)
            {   
                printf("查找结果如下:\n");
                ShowMsg(res, 1);
                printf("\n0: exit\n");
                scanf("%c", &cmd);
                if (cmd == '0')
                {
                    getchar();
                    system("clear");
                    break;
                }
                else if(cmd == '\n')
                {
                    system("clear");
                    break;
                }
                else
                {
                    getchar();
                    ErrDebug(0);
                }
            }
        }
    }
    else if (ret == 1)
    {
        res = FindbyName(people);
        if (res == NULL)
            ErrDebug(1);
        else
        {
            system("clear");
            while (1)
            {   
                printf("查找结果如下:\n");
                ShowMsg(res, 1);
                printf("\n0: exit\n");
                scanf("%c", &cmd);
                if (cmd == 0)
                {
                    getchar();
                    system("clear");
                    break;
                }
                else if(cmd == '\n')
                {
                    system("clear");
                    break;
                }
                else
                {
                    getchar();
                    ErrDebug(0);
                }
            }
        }
    }
}

/* Func:    以某种方式删除用户信息
 * Para:    people: 存放各用户的结构体地址的指针数组
 * Return:  无
 * */
void Delete(People **people)
{
    int ret;
    while ((ret = FindbyWay()) == -1);
    People *res = NULL;
    if (ret == 0)
    {
        res = FindbyID(people);
        if (res == NULL)
            ErrDebug(1);
        else
            DeleteMsg(people, res);
        getchar();
    }
    else if (ret == 1)
    {
        res = FindbyName(people);
        if (res == NULL)
            ErrDebug(1);
        else
            DeleteMsg(people, res);
    }
    
}

/* Func:    修改用户信息
 * Para:    用户结构体地址
 * Return: 无
 * */
void Edit(People **people)
{
    int ret;
    while ((ret = FindbyWay()) == -1);
    People *res = NULL;
    system("clear");
    if (ret == 0)
    {
        res = FindbyID(people);
        if(res == NULL)
            ErrDebug(1);
        else
            EditMsg(people, res);
        // getchar();
    }
    else if (ret == 1)
    {
        res = FindbyName(people);
        if(res == NULL)
            ErrDebug(1);
        else
            EditMsg(people, res);
    }
}






