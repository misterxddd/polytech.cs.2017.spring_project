#include "unity.h"
#include "unity_fixture.h"
#include "dynamic_array.h"

TEST_GROUP(TestDeleteLast);

TEST_GROUP_RUNNER(TestDeleteLast)
{
    RUN_TEST_CASE(TestDeleteLast, LenghtOfStr);
    RUN_TEST_CASE(TestDeleteLast, LastSymbol);
}

TEST_SETUP(TestDeleteLast)
{
}

TEST_TEAR_DOWN(TestDeleteLast)
{
}

/** \fn TEST(TestDeleteLast, LenghtOfStr)
 Удаляет последний элемент и проверяет длину списка.
*/
TEST(TestDeleteLast, LenghtOfStr)
{
   int index = 0;
   char str[30] = "When I Was Young!vredckeow pe";
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

   DeleteLast(Copyroot);

   int result1 = 0;
   result1 = Lenght(Copyroot);
   TEST_ASSERT_EQUAL_INT( StartSize - 1, result1 );
}

/** \fn TEST(TestDeleteLast, LastSymbol)
 Удаляет последний элемент и проверяет последний символ.
*/
TEST(TestDeleteLast, LastSymbol)
{
   int index = 0;
   char str[30] = "When I Was Young!vredckeow pe";
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
   DeleteLast(Copyroot);

   string * acc;
   while(Copyroot)
   {
      acc = Copyroot;
      Copyroot = Copyroot->next;
   }

   char result2;
   result2 = acc->symbol;
   TEST_ASSERT_EQUAL_INT( 'e', result2 );
}





