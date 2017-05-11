#pragma once
#include "typedefs.h"
typedef struct pop
{
	byte symbol;
	struct pop * next;
}string;

string * CreateString(byte * _str); //�������� ������ ������������ ������
string * CreateStringStruct(byte _symbol, string * _next); //�������� ������ ������

int Lenght(string * _string); //���������� ����� ������
void AddToTheEnd(string * _string, byte _symbol); //���������� �������� � ����� ������
void DeleteLast(string * _string); //�������� ���������� �������� 
void ClearString(string * str); //������� ������������ ������ 
void CopyString(string * _str1, string * _str2); //����������� ��������� �� ������� �� ������
char GetByIndex(string * _str, int _index); //��������� ��������� �� i-��� ������� 
void DeleteString(string * str); //�������� ������