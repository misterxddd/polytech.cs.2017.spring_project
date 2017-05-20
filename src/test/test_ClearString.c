#include "unity.h"
#include "unity_fixture.h"
#include "dynamic_array.h"

TEST_GROUP(TestClearString);

TEST_GROUP_RUNNER(TestClearString)
{
    RUN_TEST_CASE(TestClearString, NullString);
}

TEST_SETUP(TestClearString)
{
}

TEST_TEAR_DOWN(TestClearString)
{
}


/** \fn TEST(TestClearString, NullString)
 Функция очищает список. Сравнивается длина строки и проверяется наличие первой ячейки с символом.
*/
TEST(TestClearString, NullString)
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

	ClearString(Copyroot);

	int result = 0;
    result = Lenght(Copyroot);
    TEST_ASSERT_EQUAL_INT( 1, result );

    char result2;
    result2 = Copyroot->symbol;
    TEST_ASSERT_EQUAL_INT( 'B', result2 );

}
