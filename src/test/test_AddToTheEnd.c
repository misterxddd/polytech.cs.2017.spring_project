#include "unity.h"
#include "unity_fixture.h"
#include "dynamic_array.h"

TEST_GROUP(TestAddToTheEnd);

TEST_GROUP_RUNNER(TestAddToTheEnd)
{
    RUN_TEST_CASE(TestAddToTheEnd, FunctionLastSymbol);
}

TEST_SETUP(TestAddToTheEnd)
{
}

TEST_TEAR_DOWN(TestAddToTheEnd)
{
}

TEST(TestAddToTheEnd, FunctionLastSymbol)
{
   int index = 0;
   char str[30] = "Big, Meaty CLAAAAAW!! PoPoVhj";
   int size = 30;
   string * root = CreateStringStruct(str[0], NULL);
   string * Copyroot = root;
   index++;
   while(index != size)
   {
      root->next = CreateStringStruct(str[index], NULL);
      root = root->next;
      index++;

   }
   
   int StartSize = Lenght(Copyroot);

   AddToTheEnd(Copyroot, 'A');
   
   int result1 = 0;
   result1 = Lenght(Copyroot);
   TEST_ASSERT_EQUAL_INT( StartSize + 1, result1 );

   char result2 = 0;
   root = root->next;
   result2 = root->symbol;
   TEST_ASSERT_EQUAL_INT( 'A', result2 );
}

