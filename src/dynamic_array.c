#include <stdio.h>
#include "dynamic_array.h"
#include <string.h>
#include <stdlib.h>


string * CreateString(byte * str)
{
	int size = 0;
	int index = 0;
	size = strlen(str);
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

void PrintString(string * str)
{
	while (str)
	{
		printf("%c", str->symbol);
		str = str->next;
	}
	printf("\n");
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

void AddToTheEnd(string * str, byte symbol)
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
		for (int i = 0; i < len - 1; i++)
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

void Sex(string * str, string * str1)
{
	string * acc = NULL;
	while (str)
	{
		acc = str;
		str = str->next;
	}
	acc->next = str1;
}

char GetByIndex(string * str, int index)
{
	int count = 0;
	while (str)
	{
		if (count == index)
			return str->symbol;
		count++;
		str = str->next;
	}
}