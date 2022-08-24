#include "linklist.h"

/* @ brief:     保存信息至文件
 * @ Para:      head：头指针
 * @ Return:    void
 */
static void SaveToFile(person *head)
{
    FILE *fp;
    fp = fopen(SAVE_PATH, "w");
    if (fp == NULL)
    {
        perror("fopen");
        exit(-1);
    }
    int ret;
    person *tmp = head->next;
    while (tmp != NULL)
    {
        ret = fwrite(tmp, sizeof(person), 1, fp);
        if (ret != 1)
        {
            perror("fwrite");
            exit(-1);
        }
        tmp = tmp->next;
    }
    fclose(fp);
}

/* @ brief:     创建表头结点
 * @ Para:      void
 * @ Return:    指向表头结点的指针
 */
static person *LinklistCreateHead(void)
{
    person *head = (person *)malloc(sizeof(person));
    if (head == NULL)
    {
        printf("创建表头结点失败!\n");
        exit(-1);
    }
    head->next = NULL;
    return head;
}

/* @ brief:     创建数据节点
 * @ Para:      指向存放数据的结构体的指针
 * @ Return:    指向数据结点的指针
 */
static person *LinklistCreateNewNode(person *datdanode)
{
    person *newnode = (person *)malloc(sizeof(person));
    if (newnode == NULL)
    {
        printf("创建数据结点失败\n");
        exit(-1);
    }
    newnode->next = NULL;
    mystrcpy(newnode->name, datdanode->name);
    mystrcpy(newnode->sex, datdanode->sex);
    mystrcpy(newnode->phone, datdanode->phone);
    mystrcpy(newnode->address, datdanode->address);
    return newnode;
}

/* @ brief:     按照数据升序插入结点
 * @ Para:      head:结点的地址
 *              data:传入数据的结构体的地址
 * @ Return:    void
 */
static void LinklistSortInsert(person *head, person *data)
{
    person *tmp = head;
    person *newnode = LinklistCreateNewNode(data);
    while (tmp->next != NULL && mystrcmp(newnode->name, tmp->next->name) > 0)
        tmp = tmp->next;
    newnode->next = tmp->next;
    tmp->next = newnode;
}

/* @ brief:     打印单个结点信息
 * @ Para:      头结点的地址
 *              单个用户结点的地址
 * @ Return:    void
 */
static void LinklistPrintSingle(person *head, person *usr)
{
    person *tmp = head->next;
    while (tmp != usr && tmp != NULL)
        tmp = tmp->next;
    if (tmp == NULL)
        printf("查无此人！\n");
    else
    {
        printf("          |name      |sex   |phone      |address                 |\n");
        printf("          --------------------------------------------------------\n");
        printf("          |%-10s|%-6s|%-12s|%-24s|\n", tmp->name, tmp->sex, tmp->phone, tmp->address);
        printf("          --------------------------------------------------------\n");
    }
}

/* @ brief:     遍历单链表
 * @ Para:      头节点的地址
 * @ Return:    void
 */
static void LinklistPrintAll(person *head)
{
    person *tmp = head->next;
    if (head->next == NULL)
    {
        printf("通讯录为空!\n");
        return;
    }
    printf("显示结果如下：\n");
    printf("          |name      |sex   |phone      |address                 |\n");
    printf("          --------------------------------------------------------\n");
    while (tmp != NULL)
    {
        printf("          |%-10s|%-6s|%-12s|%-24s|\n", tmp->name, tmp->sex, tmp->phone, tmp->address);
        printf("          --------------------------------------------------------\n");
        tmp = tmp->next;
    }
    
}

/* @ brief:     按照姓名查找
 * @ Para:      head:头结点地址
 *              name:要查找吗姓名
 * @ Return:    NULL：查无此人
 *              否则返回查到的节点的地址
 */
static person *LinklistSearchByName(person *head, char *name)
{
    person *tmp = head->next;
    while (tmp != NULL)
    {
        if (mystrcmp(tmp->name, name) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return tmp;
}

/* @ brief:     按照手机号查找
 * @ Para:      head：头节点地址
 *              phone：手机号
 * @ Return:    NULL:查无此人
 *              否则返回查到的节点的地址
 */
static person *LinklistSearchByPhone(person *head, char *phone)
{
    person *tmp = head->next;
    while (tmp != NULL)
    {
        if (mystrcmp(tmp->name, phone) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return tmp;
}

/* @ brief:     删除链表单个结点
 * @ Para:      head：头指针
 *              deletenode:待删除的结点的地址
 * @ Return:    void
 */
static void LinklistDeleteNode(person *head, person *deletenode)
{
    person *tmp = head;
    while (tmp != NULL)
    {
        if (tmp->next == deletenode)
        {
            tmp->next = tmp->next->next;
            free(deletenode);
            return;
        }
        tmp = tmp->next;
    }
}

/* @ brief:     删除全部整表
 * @ Para:      head：头指针
 * @ Return:    void
 */
static void LinklistDeleteAll(person *head)
{
    person *tmp;
    while (head->next != NULL)
    {
        tmp = head->next;
        head->next = tmp->next;
        free(tmp);
    }
}

/* @ brief:     读取保存在文件中的信息
 * @ Para:      head头指针
 * @ Return:    void
 */
void LoadFromFile(person *head)
{
    FILE *fp;
    fp = fopen(SAVE_PATH, "r");
    if (fp == NULL)
    {
        fopen(SAVE_PATH, "w");
        system("clear");
        printf("创建AddressBook文件成功，用于存储用户信息\n");
        sleep(1);
        return ;
    }
    person *tmp = (person *)malloc(sizeof(person));
    int ret;
    while ((ret = fread(tmp, sizeof(person), 1, fp)) != 0)
        LinklistSortInsert(head, tmp);

    if (feof(fp) == 0)
    {
        perror("feof");
        exit(-1);
    }
    else
        printf("通讯录加载成功！\n");
    fclose(fp);
}

/* @ brief:     交互界面
 * @ Para:      void
 * @ Return:    void
 */
void Menu(void)
{
    printf("  通讯录                     \n");
    printf("----------------------------\n");
    printf("1.添加用户   2.查看用户\n");
    printf("3.搜索用户   4.删除用户\n");
    printf("5.清除全部   6.修改用户\n");
    printf("        0.退出\n");
    printf("----------------------------\n");
    printf("CMD>>> ");
}

/* @ brief:     初始化通讯录
 * @ Para:      void
 * @ Return:    头指针
 */
person *Init(void)
{
    person *head = LinklistCreateHead();
    LoadFromFile(head);
    return head;
}

/* @ brief:     添加用户数据
 * @ Para:      头节点的地址
 * @ Return:    void
 */
void AddPerson(person *head)
{
    person node;
ADD:
    printf("请输入姓名：");
    scanf("%s", node.name);
    printf("请输入性别：");
    scanf("%s", node.sex);
    printf("请输入电话：");
    scanf("%s", node.phone);
    printf("请输入住址：");
    scanf("%s", node.address);

    LinklistSortInsert(head, &node);
    SaveToFile(head);
    printf("插入成功! \n文件成功保存至./AddressBook.txt中\n");
    sleep(1);
    system("clear");
    char cmd;
INPUT_ERR:
    system("clear");
    printf("是否继续插入?(y/n)\nCMD>>> ");
    getchar();
    scanf("%c", &cmd);
    if (cmd == 'Y' || cmd == 'y' || cmd == 10)
        goto ADD;
    else if (cmd == 'N' || cmd == 'n')
    {
        getchar();
        system("clear");
    }
    else
    {
        printf("输入有误，请重新输入！\n");
        sleep(1);
        goto INPUT_ERR;
    }
}

/* @ brief:     遍历所有用户
 * @ Para:      头节点的地址
 * @ Return:    void
 */
void ShowPerson(person *head)
{
    LinklistPrintAll(head);
    printf("                             --q--\n");
    while (getchar() != 'q');
    getchar();
}

/* @ brief:     搜索用户
 * @ Para:      头节点地址
 * @ Return:    void
 */
void SearchUsr(person *head)
{
    char CMD[10];
    char check[32];
    person *res = NULL;
INPUT_ERR:
    system("clear");
    printf("按照何种方式查找?(1.name 2.phone)\nCMD>>> ");
    scanf("%s", CMD);
    if (mystrcmp(CMD, "1") == 0 || mystrcmp(CMD, "name") == 0)
        printf("请输入要搜索的姓名： ");
    else if (mystrcmp(CMD, "2") == 0 || mystrcmp(CMD, "phone") == 0)
        printf("请输入要搜索的电话： ");
    else
    {
        printf("输入有误，请重新输入！\n");
        sleep(1);
        goto INPUT_ERR;
    }
    scanf("%s", check);
    res = LinklistSearchByPhone(head, check);
    if (res == NULL)
    {
        printf("查无此人!\n");
        getchar();
        sleep(1);
        return;
    }
    LinklistPrintSingle(head, res);
    printf("                             --q--\n");
    while (getchar() != 'q')
        ;
    getchar();
}

/* @ brief:     删除单个用户
 * @ Para:      head：右指针
 * @ Return:    void
 */
void DeleteSignalPerson(person *head)
{
    char CMD[10];
    char check[32];
    person *res = NULL;
INPUT_ERR:
    system("clear");
    printf("按照何种方式查找删除?(1.name 2.phone)\nCMD>>> ");
    scanf("%s", CMD);
    if (mystrcmp(CMD, "1") == 0 || mystrcmp(CMD, "name") == 0)
        printf("请输入要删除的用户的姓名： ");
    else if (mystrcmp(CMD, "2") == 0 || mystrcmp(CMD, "phone") == 0)
        printf("请输入要搜索的用户的电话： ");
    else
    {
        printf("输入有误，请重新输入！\n");
        sleep(1);
        goto INPUT_ERR;
    }
    scanf("%s", check);
    res = LinklistSearchByPhone(head, check);
    if (res == NULL)
    {
        printf("查无此人!\n");
        getchar();
        sleep(1);
        return;
    }
    LinklistDeleteNode(head, res);
    SaveToFile(head);
    printf("删除用户成功!\n");
    sleep(1);
    getchar();
}

/* @ brief:     删除全部用户
 * @ Para:      head：头节点
 * @ Return:    void
 */
void DeleteAllPerson(person *head)
{
    LinklistDeleteAll(head);
    SaveToFile(head);
    printf("删除全部用户成功!\n");
    sleep(1);
    getchar();
}

/* @ brief:     修改用户
 * @ Para:      head：头指针
 * @ Return:    void
 */
void AdjustPerson(person *head)
{
    char CMD[10];
    char check[32];
    person *res = NULL;
INPUT_ERR:
    system("clear");
    printf("按照何种方式查找?(1.name 2.phone)\nCMD>>> ");
    scanf("%s", CMD);
    if (mystrcmp(CMD, "1") == 0 || mystrcmp(CMD, "name") == 0)
        printf("请输入要搜索的姓名： ");
    else if (mystrcmp(CMD, "2") == 0 || mystrcmp(CMD, "phone") == 0)
        printf("请输入要搜索的电话： ");
    else
    {
        printf("输入有误，请重新输入！\n");
        sleep(1);
        goto INPUT_ERR;
    }
    scanf("%s", check);
    res = LinklistSearchByPhone(head, check);
    if (res == NULL)
    {
        printf("查无此人!\n");
        getchar();
        sleep(1);
        return;
    }
    LinklistDeleteNode(head, res);
    person after;
    printf("请输入修改后的姓名：");
    scanf("%s", after.name);
    printf("请输入修改后的性别：");
    scanf("%s", after.sex);
    printf("请输入修改后的电话：");
    scanf("%s", after.phone);
    printf("请输入修改后的住址：");
    scanf("%s", after.address);
    LinklistSortInsert(head, &after);
    SaveToFile(head);
    printf("修改成功!\n");
    sleep(1);
    getchar();
}

/* @ brief:     退出程序
 * @ Para:      void
 * @ Return:    void
 */
void Exit(void)
{
    printf("BYE~~~\n");
    exit(0);
}
