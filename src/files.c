#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "files.h"



void OtputArchivedFile(byte * Str, char * Path, string * BinStr, Node * table, int numberOfNodes)
{
	FILE * file = fopen(Path, "wb");
	byte signa[4] = { 0xAB,0xAD,0xBA,0xBE };
	fwrite(signa, 1, 4, file);
	fwrite(&numberOfNodes, 1, 4, file);
	for (int i = 0; i < numberOfNodes; i++)
	{
		fwrite(&table->symbol, 1, 1, file);
		fwrite(&table->count, 1, 4, file);
		table = table->next;
	}

	int count = 0;
	byte buff = 0;
	int index = 0;
	for (int i = 0; i < Lenght(BinStr); i++)
	{
		buff = buff | (GetByIndex(BinStr, i) - 48) << (7 - count);
		count++;
		if (count == 8)
		{
			count = 0;
			Str[index] = buff;
			buff = 0;
			index++;
		}
	}
	if ((Lenght(BinStr) % 8) != 0)
	{
		Str[index] = buff;
		fwrite(Str, 1, index + 1, file);
	}
	else
	{
		fwrite(Str, 1, index, file);
	}
	fclose(file);
}

int GetFileSize(FILE * file)
{
	fseek(file, 0, SEEK_END);
	int fsize = ftell(file);
	rewind(file);
	return fsize;
}

bool GetSignaHeaderByFile(FILE * file)
{
	byte signa[4];
	fread(signa, 1, 4, file);
	if ((signa[0] == 0xAB) && (signa[1] == 0xAD) && (signa[2] == 0xBA) && (signa[3] == 0xBE))
		return true;
	return false;
}

int CreateStartNodesByArchived(FILE * file, Node * root, int * counter)
{
	int countOfNodes = 0;
	int strLength = 0;
	fread(&countOfNodes, 1, 4, file);
	byte buff[5];

	for (int i = 0; i < countOfNodes; i++)
	{
		fread(buff, 1, 5, file);
		root->next = CreateNewNode(true, true, NULL, NULL, NULL, buff[0], *(buff + 1));
		strLength += *(buff + 1);
		root = root->next;
	}
	*counter = GetFileSize(file) - (5 * countOfNodes) - 8; //MAGIIIC
	return strLength;
}

byte * Unarchive(Node * root, byte * archivedBlock, int sizeOfBlock, int sizeOfArchived)
{
	byte * str = (byte *)malloc(sizeOfBlock);
	Node * copyRoot = root;
	int count = 0;
	int count2 = 0;
	int index1 = 0;
	int index2 = 0;
	byte buff = archivedBlock[index1];
	byte acc;

	while (1)
	{
		acc = buff & (1 << (7 - count));
		if (acc) root = root->rigth;
		else
			root = root->left;
		if (root->left == NULL && root->rigth == NULL)
		{
			str[index2] = root->symbol;
			index2++;
			root = copyRoot;
			count2++;
			if (count2 == sizeOfBlock)
				return str;
		}
		count++;
		if (count == 8)
		{
			count = 0;
			index1++;
			buff = archivedBlock[index1];
		}
	}
	return str;
}