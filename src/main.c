#include <stdio.h>
#include <conio.h>
#include <string.h>

#include "HaffmanAlgh.h"
#include "dynamic_array.h"

#define INT_MAX 2147483647


int main()
{
	//AAAAABBBBCCCCCCCDDDDDD
	const char sampleText[] = "AAAAABBBBCCCCCCCDDDDDD";
	unsigned int numberOfNodes = 0;
	int srtLength = strlen(sampleText) + 1; //debug

	Node * root = CreateNewNode(true, true, false, NULL, NULL, 'R', INT_MAX);
	numberOfNodes = CreateStartNodes(root, sampleText);


	Node * acc3 = root->next;
	/*for (int i = 0; i < numberOfNodes + 1; i++)
	{
	printf("%c - %i\n", acc3->symbol, acc3->count);
	acc3 = acc3->next;
	}*/

	while (acc3)
	{
	printf("%c - %i\n", acc3->symbol, acc3->count);
	acc3 = acc3->next;
	}
	Node * acc4 = CreateTree(root, srtLength);
	string * codeTable = CreateCodeOfSymbols(acc4, srtLength);
	GetAllCodes(codeTable);
	string * binTExt = GetBinaryText(codeTable, sampleText, srtLength);
	PrintString(binTExt);
	OtputArchivedFile(sampleText, "C:/Anime/test.bin", binTExt, root->next, numberOfNodes);
	_getch();
	return 0;
}