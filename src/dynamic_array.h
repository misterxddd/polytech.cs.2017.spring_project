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
@brief Односвязный список

Данный односвязный список создан для функции "CreateCodeOfSymbols", с помощью который мы присваиваем каждому символу из файла новую кодировку.
Каждому символу приписывается свой список, с лежащими внутри нулями и единицами.
*
*/

/** \typedef string
*
Имя структуры "pop".
*
*/
typedef struct pop
{
	byte symbol; //!< Символ, лежащий в ячейки односвязного списка
	struct pop * next; //!< Параметр, указывающий на следующий элемент в цепочке
}string;

/** \fn string * CreateString(byte * _str)
*
На функцию подается строка, которая преобразуется в односвязный список, посредством создания для каждого символа ячейки.

\param[in] str Строка, которую нужно превратить в односвязный список.

\return Односвязный список
*
*/
string * CreateString(byte * _str);

/** \fn string * CreateStringStruct(byte _symbol, string * _next)
*
Функция, создающая ячейку односвязного списка.

\param[in] symbol Символ нового элемента списка.
\param[in] next Следующий за текущим элемент.

\return Обновленный список
*
*/
string * CreateStringStruct(byte _symbol, string * _next);

/** \fn int Lenght(string * _string)
*
Функция, определяющая длину списка.

\param[in] Список, длину которого нужно посчитать

\return Возвращает значение длины списка.
*
*/
int Lenght(string * _string);

/** \fn void AddToEnd(string * _string, byte _symbol)
*
Добавляет определенный элемент в конец списка.

\param[in] symbol Символ, который нужно добавить.
\param[in] string Список типа "pop" (string).

*
*/
void AddToEnd(string * _string, byte _symbol);

/** \fn void DeleteLast(string * _string)
*
Удаляет последнюю ячейку односвязного списка.

\param[in] string Односвязный список
*
*/
void DeleteLast(string * _string);

/** \fn void ClearString(string * str)
*
Очищает строчку, удаляя все элементы списка кроме первого.

\param[in] str Односвязный список
*
*/
void ClearString(string * str);

/** \fn void CopyString(string * _str1, string * _str2)
*
Копирует элементы из первого списка во второй.

\param[in] str1 Список, из которого копируем
\param[in] str2 Куда копируем
*
*/
void CopyString(string * _str1, string * _str2);

/** \fn char GetByIndex(string * _str, int _index)
*
Получение элемента по i-ому индексу.

\param[in] str Односвязный список
\param[in] index i-ый индекс

\return Возвращает нужный символ.
*
*/
char GetByIndex(string * _str, int _index);

/** \fn void DeleteString(string * str)
*
Полностью удаляет все элементы списка.

\param[in] str Список, который нужно удалить
*
*/
void DeleteString(string * str);