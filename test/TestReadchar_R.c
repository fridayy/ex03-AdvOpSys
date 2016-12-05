//
// Created by bnjm on 12/5/16.
//
#include "unity/unity.h"
#include <unistd.h>
#include <fcntl.h>
#include "TestFileHelper.h"
#include "../src/count/readchar_R.h"

void test_ReadCharacterHappyPath(void) {
    char *fileName = createFileWithContent("test.txt", "this is a test!");
    int fd = open(fileName, O_RDONLY);

    TEST_ASSERT_EQUAL('a', ReadCharacter(fd, 8));
    TEST_ASSERT_EQUAL('t', ReadCharacter(fd, 10));

    remove(fileName);
    close(fd);
}

void test_ReadCharacterNonHappy(void) {
    char *fileName = createFileWithContent("test.txt", "this is a test!");
    int fd = open(fileName, O_RDONLY);

    TEST_ASSERT_EQUAL(-1, ReadCharacter(fd, 16));
    TEST_ASSERT_EQUAL(-1, ReadCharacter(fd, -1));

    remove(fileName);
    close(fd);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ReadCharacterHappyPath);
    RUN_TEST(test_ReadCharacterNonHappy);

    return UNITY_END();
}
