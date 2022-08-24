#include "mystring.h"

/*
 * @ Func:   字符串拷贝 
 * @ Para:   des：目的字符串
 *           src：要拷贝的字符串
 * @ Return: 拷贝过后的字符串
 */
char *mystrcpy(char *des, char *src)
{
    int i = 0;
    while (*(src + i) != '\0')
    {
        *(des + i) = *(src + i);
        i++;
    }
    *(des + i) = *(src + i);
    return des;
}

/*
 * @ Func:   比较字符串的大小
 * @ Para:   str1、str2为待比较的两个字符串
 * @ Return: -1：str1 < str2
 *           0: str1 = str2
 *           1: str1 > str2
 */
int mystrcmp(char *str1, char *str2)
{
    int i = 0;
    while (*(str1 + i) != '\0' && *(str2 + i) != '\0')
    {
        if (*(str1 + i) < *(str2 + i))
            return -1;
        else if(*(str1 + i) > *(str2 + i))
            return 1;
        else
            i++;
    }
    if (*(str1 + i) == '\0' && *(str2 + i) == '\0')
        return 0;
    else if (*(str1 + i) == '\0')
        return -1;
    else if (*(str2 + i) == '\0')
        return 1;
}

