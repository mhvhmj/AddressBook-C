#include "mystring.h"

/* Func:    比较两个字符串的大小
 * Para:    str1: 待比较字符串
 *          str2: 待比较字符串
 * Return:  0:  字符串相等
 *          1:  str1>str2
 *          -1: str1<str2
 * */
int mystrcmp(char *str1, char *str2)
{
    char *p1, *p2;
    p1 = str1;
    p2 = str2;
    while (*p1 != '\0' && *p2 != '\0')
    {
        if (*p1 < *p2)
            return -1;
        else if (*p1 > *p2)
            return 1;
        p1++;
        p2++;
    }
    if (*p1 == '\0' && *p2 == '\0')
        return 0;
    else if (*p1 == '\0')
        return 1; 
    else if (*p2 == '\0')
        return -1;
}
