#include "unity.h"
#include "unity_fixture.h"
#include "HaffmanAlgh.h"

TEST_GROUP(TestCreateTree);

TEST_GROUP_RUNNER(TestCreateTree)
{
    RUN_TEST_CASE(TestCreateTree, LittleTree);
}

TEST_SETUP(TestCreateTree)
{
}

TEST_TEAR_DOWN(TestCreateTree)
{
}

TEST(TestCreateTree, LittleTree)
{
	Node * root = CreateNewNode(true, true, NULL, NULL, NULL, 'R', INT_MAX);
	char byteArray[10] = "AAABBBBSS";
	int size = 10;

	int NumberOfNodes = CreateStartNodes(root, byteArray, size);

	Node * Tree = CreateTree(root, size);

	int result;
	result = Tree->count;
	TEST_ASSERT_EQUAL_INT( 10, result );

	int result1, result11;
	Node * acc1 = Tree->left;
	result1 = acc1->count;
	result11 = acc1->symbol;
	TEST_ASSERT_EQUAL_INT( 4, result1 );
	TEST_ASSERT_EQUAL_INT( 'B', result11 );

	int result2, result22;
	Node * acc2 = Tree->rigth;
	result2 = acc2->count;
	result22 = acc2->symbol;
	TEST_ASSERT_EQUAL_INT( 6, result2 );
	TEST_ASSERT_EQUAL_INT( 0, result22 );
}
