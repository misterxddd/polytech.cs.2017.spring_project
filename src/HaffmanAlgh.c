#include <Windows.h>
#include <limits.h>
#include <stdio.h>

#include "HaffmanAlgh.h"
#include "dynamic_array.h"

Node * CreateNewNode(bool _isChar, bool _isNeed, Node * _left, Node * _rigth, Node * _next, char _symbol, int _count)
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

int CreateStartNodes(Node * root, const char * byteArray)
{
	Node * acc = root;
	int numberOfNodes = 0;
	for (int i = 0; i < MAX_SYMBOL_COUNT; i++)
	{
		int counter = 0;
		for (int j = 0; j < strlen(byteArray) + 1; j++)
		{
			if (byteArray[j] == i)
				counter++;
		}
		if (counter != 0)
		{
			acc = root;
			for (int i = 0; i < numberOfNodes; i++)
			{
				acc = acc->next;
			}
			numberOfNodes++;
			acc->next = CreateNewNode(true, true, NULL, NULL, NULL, i, counter);
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
										  //static string str[256];
	string * buf = CreateStringStruct(0, NULL);
	Node * stackNodes[1000]; //WARNING!!! Buffer overflow!
	Node * copyRoot = root;
	int index = 0;
	stackNodes[index] = root;
	direction direct = LEFT;
	while (true)
	{
	gt:
		if (root->left == NULL && root->rigth == NULL && root == copyRoot)
			return str;
		if (root->left == NULL && root->rigth == NULL && root->isChar == false)
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
			//printf("%c\n", root->symbol);
			CopyString(buf->next, str + *(char *)(&root->symbol));
			ClearString(buf);
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
			//printf("1");
			AddToTheEnd(buf, '1');
			if (root->rigth != NULL)
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

string * GetBinaryText(string * table, char * bytes, int length)
{
	string * binstr = CreateStringStruct(0, NULL);
	for (int i = 0; i < length; i++)
	{
		string * temp = CreateStringStruct(0, 0);
		CopyString(GetCodeOfSymbol(table, bytes[i]), temp);
		Sex(binstr, temp);
	}

	return binstr->next;
}


//BEGIN FOR DEBUG
void GetAllCodes(string * table)
{
	byte i = 0;
	for (i = 0; i < MAX_SYMBOL_COUNT; i++)
	{
		if (*(int *)GetCodeOfSymbol(table, i))
		{
			printf("%c : ", i);
			PrintString((GetCodeOfSymbol(table, i)));
		}
		else if (i == (MAX_SYMBOL_COUNT - 1))
			break;
	}
}
//END FOR DEBUG