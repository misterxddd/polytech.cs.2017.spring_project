#include "unity.h"
#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(TestAddToTheEnd);
    RUN_TEST_GROUP(TestCreateString);
    RUN_TEST_GROUP(TestLenght);
    RUN_TEST_GROUP(TestDeleteLast);
    RUN_TEST_GROUP(TestClearString);
    RUN_TEST_GROUP(TestCopyString);
    RUN_TEST_GROUP(TestCreateStartNodes);
    RUN_TEST_GROUP(TestCreateTree);
}

int main(int argc, const char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
