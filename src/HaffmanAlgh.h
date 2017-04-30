#pragma once
#include "dynamic_array.h"
#include "typedefs.h"

typedef struct vertexx
{
	bool isChar;
	bool isNeed;
	struct vertexx * left;
	struct vertexx * rigth;
	struct vertexx * next;
	byte symbol;
	int count;
}Node;

Node * CreateNewNode(bool _isChar, bool _isNeed, Node * _left, Node * _rigth, Node * _next, byte _symbol, int _count); //Создание нового узла (нода)
int CreateStartNodes(Node * _root, byte * _byteArray, int _size);
Node * CreateTree(Node * _root, int _arraySize); //Создание древа
string * CreateCodeOfSymbols2(Node * root, int strLen);
string * CreateCodeOfSymbols(Node * root, int strLen);
string * GetCodeOfSymbol(string * _table, byte _symbol);
string * GetBinaryText(string * table, byte * bytes, int length);
void GetAllCodes(string * table); //debug
void BuildTable(Node * root, string * str, string * code);


/*Node * Sort(Node * root, int numberOfNodes);
Node * CreateTree2(Node * root, int arraysize, int numberOfNodes);*/