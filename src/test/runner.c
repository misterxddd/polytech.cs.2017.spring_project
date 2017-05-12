#include "unity.h"
#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(TestAddToTheEnd);
    RUN_TEST_GROUP(TestCreateString);
    RUN_TEST_GROUP(TestLenght);
    RUN_TEST_GROUP(TestDeleteLast);
}

int main(int argc, const char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
