#pragma once
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
### Функция кладет заархивированные элементы в файл.
\param[in] ArchivedBytes Заархивированные элементы.
\param[in] Path Путь к файлу.
\param[in] table Узлы Дерева Хаффмана.
\param[in] numberOfNodes Количество узлов.
\param[in] countOfArchivedBytes Размер заархивированного файла.
*
*/
void OtputArchivedFile(byte * _ArchivedBytes, char * _Path, Node * _table, int _numberOfNodes, int _countOfArchivedBytes); //Функция кладет заархивированные элементы в файл

/** \fn CreateStartNodesByArchived(FILE * _file, Node * _root, int * _counter)
*
### Воссоздает узлы дерева, при помощи таблицы, лежащей в начале файла. Таблица лежит сразу после сигнатуры.
\param[in] file Исходный файл.
\param[in] root Начальный узел.
\param[out] counter Длина заархивированного файла без сигнатуры и таблицы.
*
*/
int CreateStartNodesByArchived(FILE * _file, Node * _root, int * _counter); //Воссоздание узлов

/** \fn GetSignaHeaderByFile(FILE * _file)
*
### Проверяет файл на наличие специальной сигнатуры.
\return Возвращает информацию о том, заархивирован ли файл.
*
*/
bool GetSignaHeaderByFile(FILE * _file); //Проверка на наличие сигнатуры

/** \fn byte * Unarchive(Node * _root, byte * _archivedBlock, int _sizeOfBlock, int _sizeOfArchived)
*
### Процесс разархивации файла.
\param[in] root Цепочка из всех узлов.
\param[in] archivedBlock Заархивированный блок элементов файла.
\param[in] sizeOfBlock Размер разархивированного файла.
\param[in] sizeOfArchived Длина заархивированного файла.
*
*/
byte * Unarchive(Node * _root, byte * _archivedBlock, int _sizeOfBlock, int _sizeOfArchived); //Процесс разархивации

/** \fn int GetFileSize(FILE * _file)
*
### Функция вычисляет размер файла.
*
*/
int GetFileSize(FILE * _file); //Вычисление размера файла
