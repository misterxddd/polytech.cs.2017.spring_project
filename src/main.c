#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "HaffmanAlgh.h"
#include "dynamic_array.h"
#include "files.h"

/** @file main.c
*
@brief Основной файл.

@author Попов Дмитрий - gip840@mail.ru \n
@author Вачугова Екатерина - vachugova.katya@mail.ru
*
*/

/**
*
Это основной цикл нашей программы.
Программа считывает файл, проверяет файн на наличие специальной сигнатуры.
Если таковая имеется программа начинает процесс разархивации, то если нет, то процесс архивации.
*
*/

int main(int argc, char * argv[])
{
    char * path = argv[1];
   
    FILE * file = fopen(path, "rb"); //Открываем файл
    if (file == NULL)
        printf("This file isn't detected or his size equals zero");

    unsigned long long fileSize = GetFileSize(file);
    
    byte * bytes;
  							                                 
    if (GetSignaHeader(file) == false)
    {
        int countOfParts;
        int sizeOfBlock;
        int i;
        if (fileSize <= SIZE_OF_BLOCK)
        {
            countOfParts = 1;
            sizeOfBlock = (int)fileSize;
        }
        else
        {
            countOfParts = fileSize / SIZE_OF_BLOCK;
            if (fileSize % SIZE_OF_BLOCK != 0)
                countOfParts++;
            sizeOfBlock = SIZE_OF_BLOCK;
        }
        rewind(file);
        int sizeOfWay = strlen(path);
        char * path1 = (char *)malloc(sizeOfWay + 5);
        strcpy(path1, path);
        strcat(path1, ".huff");

        for (i = 1; i <= countOfParts; i++)
        {
            bytes = (byte *)malloc(sizeOfBlock); //Выделение памяти под файл
            if (bytes == NULL)
            {
                printf("Your computer is very bad!\n");
                return 0;
            }
            fread(bytes, 1, sizeOfBlock, file); //Запись всех элементов файла в память

            int numberOfNodes = 0; //Количество узлов дерева
            int lengthArchivedBytes = 0; //Размер заархивированного файла
            Node * root = CreateNewNode(true, true, NULL, NULL, NULL, 'R', INT_MAX); //Начальный узел
            assert(root != NULL);
            numberOfNodes = CreateStartNodes(root, bytes, sizeOfBlock); //Функция создает узлы и возвращает их кол-во
            
            Node * acc4 = CreateTree(root, sizeOfBlock); //Создание дерева
            assert(acc4 != NULL);
            string * codeTable = CreateCodeSymbols(acc4, sizeOfBlock); //Функция проходится по дереву и присваиает каждому символу новую кодировку
            assert(codeTable != NULL);
            byte * archivedBytes = GetArchivedBytes(codeTable, bytes, sizeOfBlock, &lengthArchivedBytes); //Получаем элементы исходного файла в заархивированном виде
            assert(archivedBytes != NULL); 
            OtputArchivedFile(archivedBytes, path1, root->next, numberOfNodes, lengthArchivedBytes); //Запись заарвированных элементов в файл

            printf("A part of your file is archived\n");

            //Следующий блок функций создан для очистки памяти
            free(bytes);
            free(archivedBytes);
            int k = 0;
            while (acc4)
            {
                acc4 = root->next;
                free(root);
                root = acc4;
            }
            free(root);
            for (k = 0; k < 256; k++)
            {
                ClearString(codeTable + k);
            }
            free(codeTable);

            if (i == (countOfParts - 1))
                sizeOfBlock = fileSize - (countOfParts - 1) * SIZE_OF_BLOCK;
        }
        printf("Now your file is archived");
        fclose(file);
        return 0;
    }
    else //При наличии сигнатуры начинается разархивация
    {
        FILE * file = fopen(argv[1], "rb");
        char * path = argv[1];

        int offset;
        int fuckOffset = 0;
        int sizeOfBlock = 0; //Длина заархивированного файла без сигнатуры и таблицы
        printf("Archived!\n");

        int waySize = strlen(path);
        path[waySize - 5] = 0x00;

        while (true)
        {
            if (GetSignaHeader(file) == true);

            Node * root = CreateNewNode(true, true, false, NULL, NULL, 'R', INT_MAX); //Стартовый узел
            Node * copyRoot = root;
            Node * acc = NULL;
            assert(root != NULL);
            assert(copyRoot != NULL);

            fread(&offset, 1, 4, file);

            if (fuckOffset >= fileSize)
            {
                printf("Now all parts of your file are unachived!!!");
                fclose(file);
                return 0;
            }

            int strLength = CreateAchivedNodes(file, root, &sizeOfBlock, offset); //Воссоздание всех узлов дерева
            acc = CreateTree(copyRoot, strLength); //Создание древа
            byte * data = (byte *)malloc(sizeOfBlock);
            assert(data != NULL);
            fseek(file, offset - sizeOfBlock + fuckOffset, SEEK_SET);
            fread(data, 1, sizeOfBlock, file);
            byte * buff = (byte *)malloc(strLength); //Выделение памяти под блок с разаархированным файлом
            assert(buff != NULL);
            Unarchive(acc, data, strLength, sizeOfBlock, buff); //Процесс разархивации

            FILE * file1 = fopen(path, "ab");
            assert(file1 != NULL);
            fwrite(buff, 1, strLength, file1); //Запись разархивированных элементов в файл
            fclose(file1);

            printf("Now a part of you file is unachived\n");

            free(data);
            while (acc)
            {
                acc = root->next;
                free(root);
                root = acc;
            }
            free(root);
            free(buff);
            fuckOffset += offset;
        }
    }
}