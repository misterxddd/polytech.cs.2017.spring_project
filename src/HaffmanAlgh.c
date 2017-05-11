#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "HaffmanAlgh.h"
#include "dynamic_array.h"

Node * CreateNewNode(bool _isChar,bool _isNeed, Node * _left, Node * _rigth,Node * _next,byte _symbol,int _count)
{
	Node * newNode = malloc(sizeof(Node));
	newNode->count = _count;
	newNode->isChar = _isChar;
	newNode->isNeed = _isNeed;
	newNode->left = _left;
	newNode->rigth = _rigth;
	newNode->symbol = _symbol;
	newNode->next = _next;
	return newNode;
}

int CreateStartNodes(Node * root, byte * byteArray, int size)
{
    Node * acc = root;
	int i, j;
	int numberOfNodes = 0;
    int entropyOfSymbols[256];
    memset(entropyOfSymbols, 0, 256 * 4);
    for (j = 0; j < size; j++)
    {
        entropyOfSymbols[byteArray[j]]++;
    }
    for (i = 0; i < 256; i++)
    {
        if (entropyOfSymbols[i] != 0)
        {
            acc->next = CreateNewNode(true, true, NULL, NULL, NULL, i, entropyOfSymbols[i]);
            numberOfNodes++;
            acc = acc->next;
        }
    }
    return numberOfNodes;
}


Node * CreateTree(Node * root, int arraySize)
{
	Node * acc1;
	Node * acc2;
	Node * acc3;
	Node * acc4 = NULL;

    acc3 = root->next;

    while (acc3)
    {
        acc4 = acc3;
        acc3 = acc3->next;
    }

	gt:
	acc1 = root;
	acc2 = root;
	acc3 = root->next;

	while (acc3)
	{
		if ((acc1->count > acc3->count) && (acc3->isNeed == true))
			acc1 = acc3;
		acc3 = acc3->next;
	}

	acc3 = root->next;
	while (acc3)
	{
		if ((acc2->count > acc3->count) && (acc3 != acc1) && (acc3->isNeed == true))
			acc2 = acc3;
		acc3 = acc3->next;
	}
	acc1->isNeed = false;
	acc2->isNeed = false;
	acc3 = root->next;


	acc4->next = CreateNewNode(false, true, acc1, acc2, NULL, 0, acc1->count + acc2->count);
    acc4 = acc4->next;
	if ((acc1->count + acc2->count) == arraySize)
		return acc4;
	goto gt;
}

string * GetCodeOfSymbol(string * table, byte symbol)
{
	return table + symbol;
}

byte * GetArchivedBytes(string * table, byte * bytes, int length, int * lengthOfArchivedBytes)
{
    int k = 0;
	byte * archivedBytes = (byte *)malloc(length);
    int * lengthsOfCodesOfSymbols = (int *)malloc(4 * 256);
    memset(archivedBytes, 0, length);
    string * buff;
    
    for (k = 0; k <= 0xff; k++)
    {
        buff = table + k;
        *(lengthsOfCodesOfSymbols + k) = Lenght(buff);
    }

    int i = 0;
    int index = 0;
    int count = 0;
    while (i < length)
    {
        buff = table + bytes[i];
		int j;
        for (j = 0; j < *(lengthsOfCodesOfSymbols + bytes[i]); j++)
        {
            archivedBytes[index] = archivedBytes[index] | GetByIndex(buff,j) << (7 - count);
            count++;
            if (count == 8)
            {
                count = 0;
                index++;
            }
        }
        i++;
    }
    if((length % 8) != 0)
        *lengthOfArchivedBytes = index + 1;
    else
        *lengthOfArchivedBytes = index;
    free(lengthsOfCodesOfSymbols);
    return archivedBytes;
}

string * CreateCodeOfSymbols(Node * root, int strLen)
{
    string * code = CreateStringStruct(0, 0);
    string * str = (string *)malloc(sizeof(string) * 256);
    memset(str, 0, sizeof(string) * 256);
    BuildTable(root, str, code);
    return str;
}

void BuildTable(Node * root, string * str, string * code)
{
    if (root->left != NULL)
    {
        AddToTheEnd(code, 0);
        BuildTable(root->left, str, code);
    }
    if (root->rigth != NULL)
    {
        AddToTheEnd(code, 1);
        BuildTable(root->rigth, str, code);
    }
    if (root->isChar)
    {
        CopyString(code->next, str + *(byte *)(&root->symbol));
    }
        DeleteLast(code);
}
