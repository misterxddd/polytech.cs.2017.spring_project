#pragma once


typedef struct pop
{
	char symbol;
	struct pop * next;
}string;

string * CreateString(char * str);
string * CreateStringStruct(char _symbol, string * _next);
void PrintString(string * _string);

int Lenght(string * _string);
void AddToTheEnd(string * _string, char _symbol);
void DeleteLast(string * _string);
void DeleteAll(string * _string, int _lenght);
void ClearString(string * str);
void CopyString(string * _str1, string * _str2);
void Sex(string * _str, string * _str1);
char GetByIndex(string * _str, int _index);
