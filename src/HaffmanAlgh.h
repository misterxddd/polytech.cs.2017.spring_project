#pragma once
#include "dynamic_array.h"
#include "typedefs.h"

/** @file HaffmanAlgh.h
*
@brief Заголовочный файл, в котором хранятся функции, связанный со структурой "vertexx" (Node).

@author Попов Дмитрий - gip840@mail.ru \n
@author Вачугова Екатерина - vachugova.katya@mail.ru
*
*/

/** \class vertexx
*
\brief Узлы Древа Хаффмана

Структура, представляющая из себя узел в древе Хаффмана. Для каждого символа из файла создается такой узел.

*
*/

/** \typedef Node
*

Запись структуры vertexx.

*
*/

typedef struct vertexx
{
	bool isChar; //!< Параметр, который сообщает о том, лежит ли в узле символ
	bool isNeed; //!< Значение параметра говорит нужел ли в данный момент этот узед
	struct vertexx * left; //!< Узел, лежащий слева от текущего
	struct vertexx * right; //!< Узел, находящийся после текущего
	struct vertexx * next; //!< Узел, лежащий справа от текущего
	byte symbol; //!< Символ, который лежит в узле
	int count; //!< Частота встречи данного символа в файле
}Node;

/** \fn Node * CreateNewNode(bool _isChar, bool _isNeed, Node * _left, Node * _right, Node * _next, byte _symbol, int _count);
*
 Создание нового узла.

\param[in] Все параметры функции совпадают с аргументами структуры vertexx (Node).

\return Новый узел.
*
*/
Node * CreateNewNode(bool _isChar, bool _isNeed, Node * _left, Node * _right, Node * _next, byte _symbol, int _count);

/** \fn Node * CreateTree(Node * _root, int _arraySize)
*
 Создание древа Хаффмана. \n Функция работает следующим образом: СРеди всех узлов выбираются два наименьших, объединяются в единый новый узел, а этот узел кладется в конец списка. Функция продолжает работать пока не найдет конечный узел.
\param[in] arraySize Размер исходного файла.
\param[in] root Начальный узел.

\return Дерево Хаффмана.
*
*/
Node * CreateTree(Node * _root, int _arraySize);

/** \fn string * CreateCodeOfSymbols(Node * _root, int _strLen)
*
 Присваение новой кодировки каждому символу.
\param[in] strLen Размер исходного файла.
\param[in] root Начальный узел.

\return Возвращает массив, в котором лежит новая кодировка каждого символа
*
*/
string * CreateCodeOfSymbols(Node * _root, int _strLen);

/** \fn byte * GetArchivedBytes(string * _table, byte * _bytes, int _length, int * _lengthOfArchivedBytes)
*
 Получение раархивированных элементов файла.

\param[in] table Массив, содержащий в себе новую кодировку каждого символа.
\param[in] bytes Элементы исходного файла.
\param[in] lenght Размер исходного файла.
\param[out] lengthOfArchivedBytes Размер заархивированного файла.

\return Заархивированные элементы файла.
*
*/
byte * GetArchivedBytes(string * _table, byte * _bytes, int _length, int * _lengthOfArchivedBytes);

/** \fn void BuildTable(Node * _root, string * _str, string * _buff)
*
 Рекурсивная функция, с помощью которой каждому символу приписыается новая кодировка. Создается массив указателей на структуру "pop"(string), массив состоит из 256 ячеек.
 Когда функция, проходясь по дереву, доходит до узла с символом, она записывает список, состоящий из 0 и 1, в i-ую ячейку массива (где i - кодировка данного символа в таблице ASCII).

\param[in] root Начальный узел.
\param[in] str Массив, который содержит в себе новые кодировки.
\param[in] buff Начальная ячейка односвязного списка.
*
*/
void BuildTable(Node * _root, string * _str, string * _buff);

/** \fn int CreateStartNodes(Node * _root, byte * _byteArray, int _size)
*
 Функция создает стартовые узлы по данным, полученным из файла.

\param[in] root Узел, с которого все начинается.
\param[in] byteArray  Элементы файла, из которых мы и создаем узлы.
\param[in] size Длина исходного файла.

\return Количество узлов древа.
*
*/
int CreateStartNodes(Node * _root, byte * _byteArray, int _size);
