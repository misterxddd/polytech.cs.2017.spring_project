#pragma once
#include "typedefs.h"
typedef struct pop
{
	byte symbol;
	struct pop * next;
}string;

string * CreateString(byte * _str); //Создание ячейки односвязного списка
string * CreateStringStruct(byte _symbol, string * _next); //Создание самого списка

int Lenght(string * _string); //Нахождение длины списка
void AddToTheEnd(string * _string, byte _symbol); //Добавление элемента в конец списка
void DeleteLast(string * _string); //Удаление последнего элемента 
void ClearString(string * str); //Очистка односвязного списка 
void CopyString(string * _str1, string * _str2); //Копирование элементов из первого во второй
char GetByIndex(string * _str, int _index); //Получение эллемента по i-ому индексу 
void DeleteString(string * str); //Удаление списка