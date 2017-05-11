#pragma once
#include "dynamic_array.h"
#include "HaffmanAlgh.h"

void OtputArchivedFile(byte * _ArchivedBytes, char * _Path, Node * _table, int _numberOfNodes, int _countOfArchivedBytes); //Функция кладет заархивированные элементы в файл
int CreateStartNodesByArchived(FILE * _file, Node * _root, int * _counter); //Воссоздание узлов
bool GetSignaHeaderByFile(FILE * _file); //Проверка на наличие сигнатуры
byte * Unarchive(Node * _root, byte * _archivedBlock, int _sizeOfBlock, int _sizeOfArchived); //Процесс разархивации
int GetFileSize(FILE * _file); //Вычисление размера файла
