#include "unity.h"
#include "unity_fixture.h"
#include "dynamic_array.h"

TEST_GROUP(TestCreateString);

TEST_GROUP_RUNNER(TestCreateString)
{
    RUN_TEST_CASE(TestCreateString, FunctionStringOfFour);
}

TEST_SETUP(TestCreateString)
{
}

TEST_TEAR_DOWN(TestCreateString)
{
}

/** \fn TEST(TestCreateString, FunctionStringOfFour)
 Проверка на работоспособность разбиени¤ строки на ¤чейки структуры.
*/
TEST(TestCreateString, FunctionStringOfFour)
{
   byte str[4] = "lol";

   string * sas = CreateString(str);
   char result, result1, result2;
   result = sas->symbol;
   TEST_ASSERT_EQUAL_INT( 'l', result );

   sas = sas->next;
   result1 = sas->symbol;
   TEST_ASSERT_EQUAL_INT( 'o', result1 );

   sas = sas->next;
   result2 = sas->symbol;
   TEST_ASSERT_EQUAL_INT( 'l', result2 );
}


