#include <stdio.h>
#include "dynamic_array.h"
#include <string.h>
#include <stdlib.h>

/** @file dynamic_array.c
*
@brief Функции для работы с односвязным списком.

@author Попов Дмитрий - gip840@mail.ru \n
@author Вачугова Екатерина - vachugova.katya@mail.ru
*
*/

string * CreateString(byte * str)
{
	int size = 0;
	int index = 0;
	size = strlen((const char *)str);
	if (size == 0)
		return CreateStringStruct(0, NULL);
	string * root = CreateStringStruct(str[0], NULL);
	string * copyRoot = root;
	index++;
	while (index != size)
	{
		root->next = CreateStringStruct(str[index], NULL);
		root = root->next;
		index++;
	}
	return copyRoot;
}

string * CreateStringStruct(byte symbol, string * next)
{
	string * root = (string *)malloc(sizeof(string));
	root->symbol = symbol;
	root->next = NULL;
	return root;
}

int Lenght(string * str)
{
	int count = 0;
	while (str)
	{
		count++;
		str = str->next;
	}
	return count;
}

void AddToEnd(string * str, byte symbol)
{
	string * acc = NULL;
	while (str)
	{
		acc = str;
		str = str->next;
	}
	acc->next = CreateStringStruct(symbol, NULL);
}

void DeleteLast(string * str)
{
	string * acc = NULL;
	string * acc1 = str;
	while (str)
	{
		acc = str;
		str = str->next;
	}
	while (acc1)
	{
		if (acc1->next == acc)
		{
			acc1->next = NULL;
			break;
		}
		else {};
		acc1 = acc1->next;
	}
	free(acc);
}

void ClearString(string * str)
{
	int len = Lenght(str);
	string * acc;
	string * acc1 = NULL;
	acc = str;
	int i = 0;
	while (len != 1)
	{
		acc = str;
		for (i = 0; i < len - 1; i++)
		{
			acc1 = acc;
			acc = acc->next;
		}
		acc1->next = NULL;
		free(acc);
		len--;
	}
	str->next = NULL;
}

void CopyString(string * str1, string * str2)
{
	int count = Lenght(str1);
	int i = 0;
	for (i = 0; i < count; i++)
	{
		*(byte *)str2 = *(byte *)str1;
		if (i != count - 1)
			str2->next = CreateStringStruct(0, NULL);
		str1 = str1->next;
		str2 = str2->next;
	}
}

char GetByIndex(string * str, int index)
{
    int count = 0;
    while (str)
    {
        if (count == index)
            return str->symbol;
		else {};
        count++;
        str = str->next;
    }
	return 0;
}

void DeleteString(string * str)
{
    int len = Lenght(str);
    string * acc;
    string * acc1 = NULL;
    acc = str;
    int i = 0;
    while (len != 1)
    {
        acc = str;
        for (i = 0; i < len - 1; i++)
        {
            acc1 = acc;
            acc = acc->next;
        }
        acc1->next = NULL;
        free(acc);
        len--;
    }
    str->next = NULL;
    free(str);
}