#include <stdio.h>
#include <limits.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#include "HaffmanAlgh.h"
#include "dynamic_array.h"
#include "files.h"


int main()
{
    const char path[] = "C:/Anime/1.txt";

    int c = 0;
    scanf("%i", &c);
    if (c == 0)
    {
        FILE * file = fopen(path, "rb");
        int fileSize = GetFileSize(file);
        byte * bytes;
        if (GetSignaHeaderByFile(file) == false && fileSize < 67108864)
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
            Node * root = CreateNewNode(true, true, false, NULL, NULL, 'R', INT_MAX);
            numberOfNodes = CreateStartNodes(root, bytes, fileSize);

            Node * acc4 = CreateTree(root, fileSize);
            printf("Tree created");
            string * codeTable = CreateCodeOfSymbols2(acc4, fileSize);
            //GetAllCodes(codeTable);
            byte * archivedBytes = GetArchivedBytes(codeTable, bytes, fileSize,&lengthOfArchivedBytes);
           // PrintString(binTExt);
            OtputArchivedFile(archivedBytes, path, root->next, numberOfNodes, lengthOfArchivedBytes);
        }
    }
    if (c == 1)
    { 
        FILE * file = fopen(path, "rb");
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
       // printf("%s",Unarchive(acc, data , strLength,siska));
        byte * buff = (byte *)malloc(strLength);
        buff = Unarchive(acc, data, strLength, siska);
        fclose(file);
        FILE * file1 = fopen(path, "wb");
        fwrite(buff, 1, strLength, file1);
        fclose(file1);
    }
	//_getch();
	return 0;
}