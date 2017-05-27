#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "files.h"

/** @file files.c
*
@brief Здесь содержатся все функции для работы с файлами.

@author Попов Дмитрий - gip840@mail.ru \n
@author Вачугова Екатерина - vachugova.katya@mail.ru
*
*/

void OtputArchivedFile(byte * ArchivedBytes, char * Path, Node * nodes, int numberOfNodes, int lengthArchivedBytes)
{
    FILE * file = fopen(Path, "ab"); //Открываем файл для записи
    assert(file != NULL);
    int i = 0;
    byte signa[4] = { 0xAB,0xAD,0xBA,0xBE }; //Вид нашей сигнатуры
    fwrite(signa, 1, 4, file);
    int offset = numberOfNodes * 5 + lengthArchivedBytes + 12;
    fwrite(&offset, 1, 4, file);
    fwrite(&numberOfNodes, 1, 4, file); //В файл кладется количество узлов для более простой разархивации
    for (i = 0; i < numberOfNodes; i++) //Записываем символ и его частоту для воссоздания узлов
    {
        fwrite(&nodes->symbol, 1, 1, file);
        fwrite(&nodes->count, 1, 4, file);
        nodes = nodes->next;
    }
    fwrite(ArchivedBytes, 1, lengthArchivedBytes, file); //Кладем заархивированные элементы
    fclose(file);
}

int GetFileSize(FILE * file) //Получение размера файла
{
    fseek(file, 0, SEEK_END);
    int fsize = ftell(file);
    rewind(file);
    return fsize;
}

bool GetSignaHeader(FILE * file) //Проверка на сигнатуру
{
    byte signa[4];
    fread(signa, 1, 4, file);
    if ((signa[0] == 0xAB) && (signa[1] == 0xAD) && (signa[2] == 0xBA) && (signa[3] == 0xBE))
        return true;
    else 
        return false;
}

int CreateAchivedNodes(FILE * file, Node * root, int * counter, int offset) //Воссоздание узлов
{
    int countOfNodes = 0;
    int strLength = 0;
    int i = 0;
    fread(&countOfNodes, 1, 4, file); //Считываем количество узлов

    byte buff[5]; //Строка, которая будет содержать в себе символ и его частоту

    for (i = 0; i < countOfNodes; i++)
    {
        fread(buff, 1, 5, file); //Считываем 5 байт (4 байта - частота, 1 - сам символ)
        root->next = CreateNewNode(true, true, NULL, NULL, NULL, buff[0], *(int *)(buff + 1)); //Создаем узлы друг за другом
        strLength += *(int *)(buff + 1); //Длина всех нодов
        root = root->next;
    }
    *counter = offset - (5 * countOfNodes) - 12; //MAGIIIC //Получаем файл без сигнатуры и узлов
    return strLength;
}

void Unarchive(Node * root, byte * archivedBlock,int sizeOfBlock, int sizeOfArchived, byte * str)
{
    Node * copyRoot = root;
    assert(copyRoot != NULL);
    int count = 0;
    int index1 = 0;
    int index2 = 0;
    int controlIndex = 0;
    byte buff = archivedBlock[index1]; //Заархивированный файл
    byte acc;

    while(true) //Проходимся по всему файлу
    {
        acc = buff & (1 << (7 - count)); //Побитовое сложение, выдаст нам единицу, либо ноль
        if (acc)
            root = root->right;
        else
            root = root->left;
        if (root->isChar == true) //Заносим соответсвующие элементы в строку, которая в будущем будет содержать в себе разазхивированные элементы файла
        {
            str[index2] = root->symbol;
            index2++;
            root = copyRoot;
            controlIndex++;
            if (controlIndex == sizeOfBlock)
                return;
        }
        count++;
        if (count == 8) // 1 байт = 8 битам, поэтому как только количество бит достигло 8, мы обнуляем count и переходим к следующему байту
        {
            count = 0;
            index1++;
            buff = archivedBlock[index1];
        }

    }
}