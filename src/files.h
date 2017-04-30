#pragma once
#include "dynamic_array.h"
#include "HaffmanAlgh.h"

void OtputArchivedFile(byte * _Str, char * _Path, string * _BinStr, Node * _table, int _numberOfNodes);
int CreateStartNodesByArchived(FILE * _file, Node * _root, int * _counter);
bool GetSignaHeaderByFile(FILE * _file);
byte * Unarchive(Node * _root, byte * _archivedBlock, int _sizeOfBlock, int _sizeOfArchived);
int GetFileSize(FILE * _file);
void OtputArchivedFile2(byte * Str, char * Path, string * BinStr, Node * table, int numberOfNodes);