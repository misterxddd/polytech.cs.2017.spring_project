#ifndef FILES_H
#define FILES_H

#include "dynamic_array.h"
#include "HaffmanAlgh.h"

/** @file files.h
*
@brief Заголовочный файл, с функциями, работающими непосредственно с файлом.

@author Попов Дмитрий - gip840@mail.ru \n
@author Вачугова Екатерина - vachugova.katya@mail.ru
*
*/

/** \fn void OtputArchivedFile(byte * _ArchivedBytes, char * _Path, Node * _table, int _numberOfNodes, int _countOfArchivedBytes)
*
Функция кладет заархивированные элементы в файл.

\param[in] ArchivedBytes Заархивированные элементы.
\param[in] Path Путь к файлу.
\param[in] table Узлы Дерева Хаффмана.
\param[in] numberOfNodes Количество узлов.
\param[in] countOfArchivedBytes Размер заархивированного блока.
*
*/
void OtputArchivedFile(byte * _ArchivedBytes, char * _Path, Node * _table, int _numberOfNodes, int _countOfArchivedBytes);

/** \fn CreateAchivedNodes(FILE * _file, Node * _root, int * _counter)
*
Воссоздает узлы дерева, при помощи таблицы, лежащей в начале файла. Таблица лежит сразу после сигнатуры.

\param[in] file Исходный файл.
\param[in] root Начальный узел.
\param[in] offset Длина одного блока.
\param[out] counter Длина заархивированного файла без сигнатуры и таблицы.

\return Длину незаархивированного файла.
*
*/
int CreateAchivedNodes(FILE * _file, Node * _root, int * _counter, int _offset);

/** \fn GetSignaHeader(FILE * _file)
*
Проверяет файл на наличие специальной сигнатуры.

\param[in] file Исходный файл.

\return Возвращает информацию о том, заархивирован ли файл.
*
*/
bool GetSignaHeader(FILE * _file);

/** \fn byte * Unarchive(Node * _root, byte * _archivedBlock, int _sizeOfBlock, int _sizeOfArchived)
*
Процесс разархивации файла.

\param[in] root Цепочка из всех узлов.
\param[in] archivedBlock Заархивированный блок элементов части файла.
\param[in] sizeOfBlock Размер разархивированного блока файла.
\param[in] sizeOfArchived Длина заархивированного блока файла.
\param[in] str Блок с разархивированными файлами.

\return Разархивированные элементы файла.
*
*/
void Unarchive(Node * _root, byte * _archivedBlock, int _sizeOfBlock, int _sizeOfArchived, byte * _str);

/** \fn int GetFileSize(FILE * _file)
*
Функция вычисляет размер файла.

\param[in] file Файл.

\return Длину файла.
*
*/
int GetFileSize(FILE * _file);

#endif