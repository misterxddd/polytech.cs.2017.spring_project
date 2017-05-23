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
    FILE * file = fopen(argv[1], "rb"); //Открываем файл
    if (file == NULL)
        printf("This file isn't detected or his size equals zero");
    int fileSize = GetFileSize(file);
    byte * bytes;
  							                                 //256 Мб
    if ((GetSignaHeader(file) == false) && fileSize <= 268435456) //Проверка на наличие сигнатуры
    {
        bytes = (byte *)malloc(fileSize); //Выделение памяти под файл
        if (!bytes)
        {
            printf("Your computer is very bad!\n");
            return 0;
        }
        rewind(file);
        fread(bytes, 1, fileSize, file); //Запись всех элементов файла в память
        fclose(file);

        int numberOfNodes = 0; //Количество узлов дерева
        int lengthArchivedBytes = 0; //Размер заархивированного файла
        Node * root = CreateNewNode(true, true, NULL, NULL, NULL, 'R', INT_MAX); //Начальный узел
        assert(root != NULL);
        numberOfNodes = CreateStartNodes(root, bytes, fileSize); //Функция создает узлы и возвращает их кол-во

        Node * acc4 = CreateTree(root, fileSize); //Создание дерева
        assert(acc4 != NULL);
        string * codeTable = CreateCodeSymbols(acc4, fileSize); //Функция проходится по дереву и присваиает каждому символу новую кодировку
        assert(codeTable != NULL);
        byte * archivedBytes = GetArchivedBytes(codeTable, bytes, fileSize, &lengthArchivedBytes); //Получаем элементы исходного файла в заархивированном виде
        assert(archivedBytes != NULL);
        OtputArchivedFile(archivedBytes, argv[1], root->next, numberOfNodes, lengthArchivedBytes); //Запись заарвированных элементов в файл

        printf("Your file is archived\n");

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
        free(root);
        for (i = 0; i < 256; i++)
        {
            ClearString(codeTable + i);
        }
        free(codeTable);
    }
    else //При наличии сигнатуры начинается разархивация
    {
        FILE * file = fopen(argv[1], "rb");
        assert(file != NULL);
        int fileSize = GetFileSize(file);
        if (GetSignaHeader(file) == true)
            printf("This file is Archived\n");
        Node * root = CreateNewNode(true, true, false, NULL, NULL, 'R', INT_MAX); //Стартовый узел
        Node * copyRoot = root;
        Node * acc = NULL;
        assert(root != NULL);
        assert(copyRoot != NULL);
        int str = 0; //Длина заархивированного файла без сигнатуры и таблицы
        int strLength = CreateAchivedNodes(file,root,&str); //Воссоздание всех узлов дерева
        acc = CreateTree(copyRoot, strLength); //Создание древа
        byte * data = (byte *)malloc(str);
        assert(data != NULL);
        fseek(file, fileSize - str, SEEK_SET);
        fread(data, 1, str, file);
        byte * buff = (byte *)malloc(strLength); //Выделение памяти под блок с разаархированным файлом
        assert(buff != NULL);
        memset(buff, 0, strLength);
        Unarchive(acc, data, strLength, str, buff); //Процесс разархивации
        fclose(file);

        FILE * file1 = fopen(argv[1], "wb");
        assert(file1 != NULL);
        fwrite(buff, 1, strLength, file1); //Запись разархивированных элементов в файл
        fclose(file1);

        printf("Now this file is unachived\n");

        free(data);
        while (acc)
        {
            acc = root->next;
            free(root);
            root = acc;
        }
        free(root);
        free(buff);
    }
    return 0;
}