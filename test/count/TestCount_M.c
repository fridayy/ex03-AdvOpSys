//
// Created by bnjm on 12/5/16.
//
#include "../TestFileHelper.h"
#include "../unity/unity.h"
#include <unistd.h>
#include <fcntl.h>
#include "../../src/count/count_M.h"

void test_CountCharactersHappyPath(void) {
    char *fileName = createFileWithContent("test.txt", "this is a test!");
    int fd = open(fileName, O_RDONLY);

    TEST_ASSERT_EQUAL(3, CountCharacters(fd, 't'));
    TEST_ASSERT_EQUAL(2, CountCharacters(fd, 'i'));
    TEST_ASSERT_EQUAL(0, CountCharacters(fd, 'x'));
    TEST_ASSERT_EQUAL(3, CountCharacters(fd, ' '));
    TEST_ASSERT_EQUAL(1, CountCharacters(fd, '!'));

    remove(fileName);
    close(fd);
}

void test_CountCharactersNonHappy(void) {
    char *fileName = createFileWithContent("test.txt", "this is a test!");
    int fd = open(fileName, O_RDONLY);


    remove(fileName);
    close(fd);
}

void test_CountCharactersInvalidFd(void) {
    int fd = -1;

    TEST_ASSERT_EQUAL(-1, CountCharacters(fd, 'a'));
}
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_CountCharactersHappyPath);
    RUN_TEST(test_CountCharactersNonHappy);
    RUN_TEST(test_CountCharactersInvalidFd);

    return UNITY_END();
}