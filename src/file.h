#pragma once
#include <stdio.h>

#include "dynamic_array.h"
#include "HaffmanAlgh.h"

void OtputArchivedFile(char * _Str, char * _Path, string * _BinStr, Node * _table, int _numberOfNodes);
byte * LitlleToBigEndian(byte * _val);
byte * GetSignaHeaderByFile(FILE * _file);