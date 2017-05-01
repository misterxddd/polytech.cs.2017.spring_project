#pragma once
#include "dynamic_array.h"
#include "HaffmanAlgh.h"

void OtputArchivedFile(byte * _ArchivedBytes, char * _Path, Node * _table, int _numberOfNodes, int _countOfArchivedBytes);
int CreateStartNodesByArchived(FILE * _file, Node * _root, int * _counter);
bool GetSignaHeaderByFile(FILE * _file);
byte * Unarchive(Node * _root, byte * _archivedBlock, int _sizeOfBlock, int _sizeOfArchived);
int GetFileSize(FILE * _file);
