#pragma once
#include "dynamic_array.h"
typedef unsigned char byte;
typedef int bool;
typedef int direction;
#define true 1
#define false 0
#define RIGTH 1
#define LEFT 0
#define MAX_SYMBOL_COUNT 256




typedef struct vertexx
{
	bool isChar;
	bool isNeed;
	struct vertexx * left;
	struct vertexx * rigth;
	struct vertexx * next;
	char symbol;
	int count;
}Node;

Node * CreateNewNode(bool _isChar, bool _isNeed, Node * _left, Node * _rigth, Node * _next, char _symbol, int _count); //Создание нового узла (нода)
int CreateStartNodes(Node * _root,const char * _byteArray);
Node * CreateTree(Node * _root, int _arraySize); //Создание древа
string * CreateCodeOfSymbols(Node * root, int strLen);
string * GetCodeOfSymbol(string * _table, byte _symbol);
string * GetBinaryText(string * table, char * bytes, int length);
void GetAllCodes(string * table); //debug