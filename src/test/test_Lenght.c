#include "unity.h"
#include "unity_fixture.h"
#include "dynamic_array.h"

TEST_GROUP(TestLenght);

TEST_GROUP_RUNNER(TestLenght)
{
    RUN_TEST_CASE(TestLenght, LenghtOfTwo);
    RUN_TEST_CASE(TestLenght, LenghtOfString);
}

TEST_SETUP(TestLenght)
{
}

TEST_TEAR_DOWN(TestLenght)
{
}

TEST(TestLenght, LenghtOfTwo)
{
   string * str1 = CreateStringStruct('A', NULL);

   str1->next = CreateStringStruct('B', NULL);
   
   int result = 0;
   result = Lenght(str1);
   TEST_ASSERT_EQUAL_INT( 2, result );
}

TEST(TestLenght, LenghtOfString)
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
        int result = 0;
        result = Lenght(Copyroot);
        TEST_ASSERT_EQUAL_INT( 30, result );
}


