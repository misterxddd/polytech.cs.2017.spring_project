#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#include "HaffmanAlgh.h"
#include "dynamic_array.h"
#include "files.h"


int main(int argc, char * argv[])
{
    FILE * file = fopen(argv[1], "rb"); //Открываем файл
    int fileSize = GetFileSize(file);
	if (fileSize == NULL)
	{
		printf("This file isn't detected or his size equals zero");
		return 0;
	}
    byte * bytes;

    if ((GetSignaHeaderByFile(file) == false) && fileSize <= 268435456)
    {
        bytes = (byte *)malloc(fileSize);
        if (!bytes)
        {
            printf("bomzh!");
            return 0;
        }
        rewind(file);
        fread(bytes, 1, fileSize, file);
        fclose(file);

        int numberOfNodes = 0;
        int lengthOfArchivedBytes = 0;
        Node * root = CreateNewNode(true, true, NULL, NULL, NULL, 'R', INT_MAX);
        numberOfNodes = CreateStartNodes(root, bytes, fileSize);

        Node * acc4 = CreateTree(root, fileSize);
        string * codeTable = CreateCodeOfSymbols(acc4, fileSize);
        byte * archivedBytes = GetArchivedBytes(codeTable, bytes, fileSize, &lengthOfArchivedBytes);
        OtputArchivedFile(archivedBytes, argv[1], root->next, numberOfNodes, lengthOfArchivedBytes);

		//Следующий блок функций создан для очистки памяти
        free(bytes);					
        free(archivedBytes);
        int i = 0;
        while (acc4)
        {									
            acc4 = root->next;
            free(root);
            root = acc4;
        }
        for (i = 0; i < 256; i++)
        {
            ClearString(codeTable + i);
        }
        free(codeTable);
    }
    else
    {
        FILE * file = fopen(argv[1], "rb");
        int fileSize = GetFileSize(file);
        if (GetSignaHeaderByFile(file) ==  true)
            printf("Archived\n");
        Node * root = CreateNewNode(true, true, false, NULL, NULL, 'R', INT_MAX);
        Node * copyRoot = root;
        Node * acc = NULL;
        int siska = 0;
        int strLength = CreateStartNodesByArchived(file,root,&siska);
        acc = CreateTree(copyRoot, strLength);
        byte * data = (byte *)malloc(siska);
        fseek(file, fileSize - siska, SEEK_SET);
        fread(data, 1, siska, file);
        byte * buff = (byte *)malloc(strLength);
        buff = Unarchive(acc, data, strLength, siska);
        fclose(file);
        FILE * file1 = fopen(argv[1], "wb");
        fwrite(buff, 1, strLength, file1);
        fclose(file1);
    }
	return 0;
}
