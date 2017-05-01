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

int CreateStartNodes(Node * root, byte * byteArray,int size)
{
	int i, j;
	byte k;
	Node * acc = root;
	int numberOfNodes = 0;
	for (k = 0; k < MAX_SYMBOL_COUNT; k++)
	{
		int counter = 0;
		for (j = 0; j < size; j++)
		{
			if (byteArray[j] == k)
				counter++;
		}
		if (counter != 0)
		{
			acc = root;
			for (i = 0; i < numberOfNodes; i++)
			{
				acc = acc->next;
			}
			numberOfNodes++;
			acc->next = CreateNewNode(true, true, NULL, NULL, NULL, k, counter);
		}
        if(k == 0xff)
            return numberOfNodes;
	}
}

Node * CreateTree(Node * root, int arraySize)
{	
	Node * acc1;
	Node * acc2;
	Node * acc3;
	Node * acc4 = NULL;
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
	
		while (acc3)
		{
			acc4 = acc3;
			acc3 = acc3->next;
		}
		acc4->next = CreateNewNode(false, true, acc1, acc2, NULL, 0, acc1->count + acc2->count);
		if ((acc1->count + acc2->count) == arraySize)
			return acc4->next;
		goto gt;	
}

string * CreateCodeOfSymbols(Node * root, int strLen)
{
	string * str = (string *)malloc(sizeof(string) * 256);
	memset(str, 0, sizeof(string) * 256); // debug
	string * buf = CreateStringStruct(0,NULL);
	Node * stackNodes[100]; //WARNING!!! Buffer overflow!
	Node * copyRoot = root;
	int index = 0;
	stackNodes[index] = root;
	direction direct = LEFT;
	while (true)
	{
	gt:
		if (root->left == NULL && root->rigth == NULL && root == copyRoot)
			return str;
		if(root->left == NULL && root->rigth == NULL && root->isChar == false)
		{
			root = stackNodes[index - 1];
			if (direct == LEFT)
				root->left = NULL;
			else
				root->rigth = NULL;
			root = stackNodes[0];
			index = 0;
			ClearString(buf);
			goto gt;
		}
		
		if (root->left == NULL && root->rigth != NULL)
		{
			direct = !direct;
		}
		if (root->left != NULL && root->rigth == NULL)
		{
			direct = !direct;
		}
		if (root->isChar == true)
		{
			CopyString(buf->next, str + *(byte *)(&root->symbol));
			ClearString(buf);

            if (stackNodes[index - 1] == copyRoot)
            {
                if (direct == LEFT)
                    copyRoot->left = NULL;
                else
                    copyRoot->rigth = NULL;

                if (root->left == NULL && root->rigth == NULL && root == copyRoot)
                    return str;

                index = 0;
                root = stackNodes[index];
                goto gt;
            }

			index--;
			root = stackNodes[index];
			if (direct == LEFT)
				root->left = NULL;
			else
				root->rigth = NULL;

			if (root->left == NULL && root->rigth == NULL && root == copyRoot)
				return str;
				
			index = 0;
			root = stackNodes[index];
			goto gt;
		}
		if (direct == LEFT)
		{
			AddToTheEnd(buf, '0');
			if (root->left != NULL)
				root = root->left;
			else
			{
				index = 0;
				root = stackNodes[index];
				direct = !direct;
				ClearString(buf);
			}
			index++;
			stackNodes[index] = root;			
		}
		if (direct == RIGTH)
		{
			AddToTheEnd(buf, '1');
			if(root->rigth != NULL)
			root = root->rigth;
			else
			{
				index = 0;
				root = stackNodes[index];
				direct = !direct;
				ClearString(buf);
			}
			index++;
			stackNodes[index] = root;			
		}
	}

}

string * GetCodeOfSymbol(string * table, byte symbol)
{
	return table + symbol;
}


byte * GetArchivedBytes(string * table, byte * bytes, int length, int * lengthOfArchivedBytes)
{
	/*string * binstr = CreateStringStruct(0, NULL);
	for (int i = 0; i < length; i++)
	{
	string * temp = CreateStringStruct(0, 0);
	CopyString(GetCodeOfSymbol(table, bytes[i]),temp);
	Sex(binstr, temp);
	}
	return binstr->next;*/

	byte * archivedBytes = (byte *)malloc(length);
	memset(archivedBytes, 0, length);
	string * buff = CreateStringStruct(0, 0);
	int i = 0;
	int index = 0;
	int count = 0;
	while (i < length)
	{
		CopyString(GetCodeOfSymbol(table, bytes[i]), buff);
		//PrintString(buff);f
		int j = 0;
		for (j = 0; j < Lenght(buff); j++)
		{
			archivedBytes[index] = archivedBytes[index] | (GetByIndex(buff, j) - 48) << (7 - count);
			count++;
			if (count == 8)
			{
				count = 0;
				index++;
			}
		}
		ClearString(buff);
		i++;
	}
	if ((length % 8) != 0)
		*lengthOfArchivedBytes = index + 1;
	else
		*lengthOfArchivedBytes = index;
	return archivedBytes;
}


//BEGIN FOR DEBUG
void GetAllCodes(string * table)
{
	byte i = 0;
	for (i = 0; i < MAX_SYMBOL_COUNT; i++)
	{
		if (*(int *)GetCodeOfSymbol(table, i))
		{
			printf("%x : ", i);
			PrintString((GetCodeOfSymbol(table, i)));
		}
        if (i == 0xff)
            return;
	}
}
//END FOR DEBUG

string * CreateCodeOfSymbols2(Node * root, int strLen)
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
        printf("0");
        AddToTheEnd(code, '0');
        BuildTable(root->left, str, code);
    }
    if (root->rigth != NULL)
    {
        printf("1");
        AddToTheEnd(code, '1');
        BuildTable(root->rigth, str, code);
    }
    if (root->isChar)
    {
        printf("%c\n", root->symbol);
        CopyString(code->next, str + *(byte *)(&root->symbol));
        //ClearString(code);
    }
    //DeleteLast(code);

    //if (Lenght(code) > 1)
    //{
        //printf("|");
        DeleteLast(code);
    //}
}