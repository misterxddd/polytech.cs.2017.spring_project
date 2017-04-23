#include <stdio.h>
#include <stdlib.h>

#include "file.h"

void OtputArchivedFile(char * Str, char * Path, string * BinStr, Node * table, int numberOfNodes)
{
	int i = 0;
	FILE * file = fopen(Path, "wb");
	char signa[4] = { 0xAB,0xAD,0xBA,0xBE };
	fwrite(signa, 1, 4, file);
	byte * beVal = LitlleToBigEndian(&numberOfNodes);
	fwrite(beVal, 1, 4, file);
	free(beVal);
	for (i = 0; i < numberOfNodes; i++)
	{
		fwrite(&table->symbol, 1, 1, file);
		beVal = LitlleToBigEndian(&table->count);
		fwrite(beVal, 1, 4, file);
		free(beVal);
		table = table->next;
	}

	int count = 0;
	byte buff = 0;
	int index = 0;
	for (i = 0; i < Lenght(BinStr); i++)
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
		Str[index + 1] = buff;
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
}

byte * GetSignaHeaderByFile(FILE * file)
{
	byte signa[4];
	fread(signa, 1, 4, file);
	if (signa[0] != 0xAB && signa[1] != 0xAD && signa[2] != 0xBA && signa[3] != 0xBE)
		return 0;

}

byte * LitlleToBigEndian(byte * val)
{
	byte * beVal = (byte *)malloc(4);
	beVal[0] = val[3];
	beVal[1] = val[2];
	beVal[2] = val[1];
	beVal[3] = val[0];
	return beVal;
}
