#pragma once
#include "typedefs.h"
/** @file dynamic_array.h
*
@brief Заголовочный файл, в котором хранятся определения функций, связанных со структурой "pop".

@author Попов Дмитрий - gip840@mail.ru \n
@author Вачугова Екатерина - vachugova.katya@mail.ru
*
*/

/** \class pop
*
\brief Односвязный список

Данный односвязный список создан для функции "CreateCodeOfSymbols", с помощью который мы присваиваем каждому символу из файла новую кодировку.
Каждому символу приписывается свой список, с лежащими внутри нулями и единицами.

*
*/

typedef struct pop
{
	byte symbol; //!< Символ, лежащий в ячейки односвязного списка
	struct pop * next; //!< Параметр, указывающий на следующий элемент в цепочке
}string;

/** \fn string * CreateString(byte * _str)
*
### На функцию подается строка, которая преобразуется в односвязный список, посредством создания для каждого символа ячейки.
*
*/
string * CreateString(byte * _str);

/** \fn string * CreateStringStruct(byte _symbol, string * _next)
*
### Функция, создающая ячейку односвязного списка.
*
*/
string * CreateStringStruct(byte _symbol, string * _next);

/** \fn int Lenght(string * _string)
*
### Функция, определяющая длину списка.

\return Возвращает значение длины списка.
*
*/
int Lenght(string * _string);

/** \fn void AddToTheEnd(string * _string, byte _symbol)
*
### Добавляет определенный элемент в конец списка.

\param[in] symbol Символ, который нужно добавить.
*
*/
void AddToTheEnd(string * _string, byte _symbol);

/** \fn void DeleteLast(string * _string)
*
### Удаляет последнюю ячейку односвязного списка.
*
*/
void DeleteLast(string * _string);

/** \fn void ClearString(string * str)
*
### Очищает строчку, удаляя все элементы списка кроме первого.
*
*/
void ClearString(string * str);

/** \fn void CopyString(string * _str1, string * _str2)
*
### Копирует элементы из первого списка во второй.
*
*/
void CopyString(string * _str1, string * _str2);

/** \fn char GetByIndex(string * _str, int _index)
*
### Получение элемента по i-ому индексу.

\return Возвращает нужный символ.
*
*/
char GetByIndex(string * _str, int _index);

/** \fn void DeleteString(string * str)
*
### Полностью удаляет все элементы списка.
*
*/
void DeleteString(string * str);
