#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "files.h"

void OtputArchivedFile(byte * ArchivedBytes, char * Path, Node * nodes, int numberOfNodes, int countOfArchivedBytes)
{
    FILE * file = fopen(Path, "wb");
    byte signa[4] = { 0xAB,0xAD,0xBA,0xBE };
    fwrite(signa, 1, 4, file);
    fwrite(&numberOfNodes, 1, 4, file);
    for (int i = 0; i < numberOfNodes; i++)
    {
        fwrite(&nodes->symbol, 1, 1, file);
        fwrite(&nodes->count, 1, 4, file);
        nodes = nodes->next;
    }   
    fwrite(ArchivedBytes, 1, countOfArchivedBytes, file);
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
        root->next = CreateNewNode(true, true, NULL, NULL, NULL, buff[0], *(int *)(buff + 1));
        strLength += *(int *)(buff + 1);
        root = root->next;
    }
    *counter = GetFileSize(file) - (5 * countOfNodes) - 8; //MAGIIIC
    return strLength;
}

byte * Unarchive(Node * root, byte * archivedBlock,int sizeOfBlock, int sizeOfArchived)
{
    byte * str = (byte *)malloc(sizeOfBlock);
    Node * copyRoot = root;
    int count = 0;
    int index1 = 0;
    int index2 = 0;
    byte buff = archivedBlock[index1];
    byte acc;
 
    while(index1 != sizeOfArchived)
    {
        acc = buff & (1 << (7 - count));
        if (acc) 
            root = root->rigth;
        else
            root = root->left;        
        if (root->isChar == true)
        {
            str[index2] = root->symbol; 
            index2++;
            root = copyRoot;
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