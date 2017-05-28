#include "unity.h"
#include "unity_fixture.h"
#include "dynamic_array.h"

TEST_GROUP(TestCopyString);

TEST_GROUP_RUNNER(TestCopyString)
{
    RUN_TEST_CASE(TestCopyString, FromStrToZero);
    RUN_TEST_CASE(TestCopyString, FromOneToString);
    RUN_TEST_CASE(TestCopyString, FromstringToString);
}

TEST_SETUP(TestCopyString)
{
}

TEST_TEAR_DOWN(TestCopyString)
{
}

/** \fn TEST(TestCopyString, FromStrToZero)
 Кладет все элементы из строчки с размером 30 в пустую строку. —равнивает длину строк и первый символ.
*/
TEST(TestCopyString, FromStrToZero)
{
	int index = 0;
	int size;
	char str[30] = "Big, Meaty CLAAAAAW!! PoPoVhj";
	size = 30;
	string * root = CreateStringStruct(str[0], NULL);
	string * Copyroot = root;
	index++;
	while(index != size)
	{
		root->next = CreateStringStruct(str[index], NULL);
		root = root->next;
		index++;

	}
	string * strTest;

	CopyString(Copyroot, strTest);

	int result1 = 0;
	result1 = Lenght(strTest);
	TEST_ASSERT_EQUAL_INT( 30, result1 );

    char result2;
    result2 = strTest->symbol;
    TEST_ASSERT_EQUAL_INT( 'B', result2 );
}

/** \fn TEST(TestCopyString, FromOneToString)
 Кладет элемент из единичной строки в строку с размером. —равнивает длину строк и первый символ.
*/
TEST(TestCopyString, FromOneToString)
{
	int index = 0;
	int size;
	char str[30] = "Big, Meaty CLAAAAAW!! PoPoVhj";
	size = 30;
	string * root = CreateStringStruct(str[0], NULL);
	string * Copyroot = root;
	index++;
	while(index != size)
	{
		root->next = CreateStringStruct(str[index], NULL);
		root = root->next;
		index++;

	}
	string * strTest = CreateStringStruct('A', NULL);

	CopyString(strTest, Copyroot);

    char result2;
    result2 = Copyroot->symbol;
    TEST_ASSERT_EQUAL_INT( 'A', result2 );
}

/** \fn TEST(TestCopyString, FromstringToString)
 Кладет все элементы из строчки в другую. —равнивает длину строк и первый символ.
*/
TEST(TestCopyString, FromstringToString)
{
	int index = 0;
	int size;
	char str[30] = "Big, Meaty CLAAAAAW!! PoPoVhj";
	size = 30;
	string * root = CreateStringStruct(str[0], NULL);
	string * Copyroot = root;
	index++;
	while(index != size)
	{
		root->next = CreateStringStruct(str[index], NULL);
		root = root->next;
		index++;

	}

	index = 0;
	char str1[15] = "Hello,darkness";
	size = 15;
	string * root1 = CreateStringStruct(str1[0], NULL);
	string * Copyroot1 = root1;
	index++;
	while(index != size)
	{
		root1->next = CreateStringStruct(str1[index], NULL);
		root1 = root1->next;
		index++;

	}

	CopyString(Copyroot, Copyroot1);

	int result1 = 0;
	result1 = Lenght(Copyroot1);
	TEST_ASSERT_EQUAL_INT( 30, result1 );

    char result2;
    result2 = Copyroot1->symbol;
    TEST_ASSERT_EQUAL_INT( 'B', result2 );
}


