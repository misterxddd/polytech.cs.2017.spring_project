#include <stdio.h>
#include <Windows.h>
#include <limits.h>


#include "HaffmanAlgh.h"


int main()
{
	//AAAAABBBBCCCCCCCDDDDDD
	const char sampleText[] = "AAAAABBBBCCCCCCCDDDDDD";//сюда подается строчка, далее будет реализация работы с файлом
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
	CreateCodeOfSymbols(acc4);

	return 0;
}
