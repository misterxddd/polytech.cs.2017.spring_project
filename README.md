# Компрессор файлов
Программа представляет из себя компрессор файлов (архиватор), основанный на Алгоритме Хаффмана.
Считывается файл, и с помощью алгоритма Хаффмана создается дерево, проходясь по которому программа создает новую кодировку для каждого символа. В итоге, при записи элементов файла с новой кодировкой, мы получаем файл с размером на 20-50% меньше изначального.

## Информация
Проект написан на языке C. Unit-тесты были написаны с истользованием фреймворка Unity.

### Интерфейс
Командная строка, где сначала пишется путь к программе, а следом путь кфайлу.
![Image alt](https://github.com/misterxddd/polytech.cs.2017.spring_project/raw/master/doc/res/imagine.png)

### Запуск
Запуск компрессора осуществляется при помощи командной строки. Сначала нужно написать путь к программе, а затем путь к файлу, который необходимо заархивировать. 
Для разархивации необходимо провести те же действия, так как при архивировании в исходный файл кладется сигнатура, с помощью которой программа поймет заархивирован ли файл.

### Важные примечания
1. Некоторые файлы после проведения процесса архивации могут сохранить свой объем, а некоторых случаях и увеличиться. Всему виной плохая энтропия данных файлов: количество различных символов максимально (256) и частота их встречи примерно одинакова. Это не связано с тем, что программа работает некорректно, это проблема самого алгоритма Хаффмана.

2. Следующее важное замечание: сейчас программа архивирует файлы не всех размеров (к 27 мая это будет исправлено). Установленный максимум - 256 Мб. Вы можете увеличить это значение, если ваш ОЗУ вам позволяет.

### Структура директории
Файлы в директории лежат следующим образом:

  Каталог    |   Описание
-------------|--------------------------
src/         | файлы исходного кода 
src/tests    | unit-тесты
doc/         | документация
doc/res/     | ресурсы для документации

### Сборка
Для того, чтобы собрать проект напишите следующее:
````
make
````
Чтобы восстановить все с нуля, выполните следующее действие:
````
make clean
````
Для запуска тестов необходимо ввести следующую команду:
````
make D_UNITY=../Unity check
````
Для сборки документации:
````
make doxygen
````
Для сборки документации в формате PDF:
````
make pdf
````
Для сборки документации в формате HTML:
````
make html
````

## Авторы
* **Dmitriy Popov** - gip840@mail.ru
* **Katya Vachugova** - vachugova.katya@mail.ru

## Лицензия
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
