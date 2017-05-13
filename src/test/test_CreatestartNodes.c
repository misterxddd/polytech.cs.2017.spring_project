#include "unity.h"
#include "unity_fixture.h"
#include "HaffmanAlgh.h"

TEST_GROUP(TestCreateStartNodes);

TEST_GROUP_RUNNER(TestCreateStartNodes)
{
    RUN_TEST_CASE(TestCreateStartNodes, StartNodes);
}

TEST_SETUP(TestCreateStartNodes)
{
}

TEST_TEAR_DOWN(TestCreateStartNodes)
{
}

TEST(TestCreateStartNodes, StartNodes)
{
	Node * root = CreateNewNode(true, true, NULL, NULL, NULL, 'R', INT_MAX);	
	char byteArray[10] = "AAABBBBSS";
	char byteArray1[50] = "AAABBBBSSQWERTYUIOP{}ASDFGHJKL:fZXCVBNM<>?qwertyu";
	int size = 10;
	int size1 = 50;

	int result = CreateStartNodes(root, byteArray, size);
	TEST_ASSERT_EQUAL_INT( 4, result );

	int result1 = CreateStartNodes(root, byteArray1, size1);
	TEST_ASSERT_EQUAL_INT( 41, result1 );	
}
