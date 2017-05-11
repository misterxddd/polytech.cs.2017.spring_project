#pragma once
#include "dynamic_array.h"
#include "typedefs.h"

typedef struct vertexx //Структура узла
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
Node * CreateTree(Node * _root, int _arraySize); //Создание дерева
string * CreateCodeOfSymbols(Node * _root, int _strLen); //Получение кодировки для каждого символа
byte * GetArchivedBytes(string * _table, byte * _bytes, int _length, int * _lengthOfArchivedBytes); //Получение заархивированных элементов файла
void BuildTable(Node * _root, string * _str, string * _buff); //Создание кодировки для каждого символа
int CreateStartNodes(Node * _root, byte * _byteArray, int _size); //Создание стартовых узлов
