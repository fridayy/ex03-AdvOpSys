//
// Created by bnjm on 12/4/16.
//
#include "unity/unity.h"
#include <unistd.h>
#include <fcntl.h>
#include "TestFileHelper.h"

void test_ReadBytesFromFile(void) {
    char *fileName = createTestFileWithContent(500, "500bytes.txt");
    int fd = open(fileName, O_RDWR);
    char buffer[500];
    ssize_t bytesRead = read(fd, buffer, 500);
    close(fd);
    remove(fileName);

    TEST_ASSERT_EQUAL(500, bytesRead);
}

void test_TryToReadTooManyBytes(void) {
    char *fileName = createTestFileWithContent(50, "50Bytes.txt");
    int fd = open(fileName, O_RDWR);
    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, 100);
    close(fd);

    remove(fileName);

    TEST_ASSERT(bytesRead != 100);
    TEST_ASSERT_EQUAL(50, bytesRead);
}

void test_ReadEmptyFile(void) {
    char *fileName = "emptyfile.txt";
    int fd = open(fileName, O_CREAT, S_IRUSR);
    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, 100);
    close(fd);

    remove(fileName);

    TEST_ASSERT_EQUAL(0, bytesRead);
}

/**
 * Reading from the same file descriptor leads to unexpected behavior!
 */
void test_ReadFromSameFileDescriptor(void) {
    char *fileName = createTestFileWithContent(16, "smallfile.txt");
    int fd = open(fileName, O_RDONLY);
    char buffer1[100];
    char buffer2[100];
    ssize_t bytesRead1 = read(fd, buffer1, 10);
    ssize_t bytesRead2 = read(fd, buffer2, 5);
    close(fd);
    remove(fileName);

    printf("RESULTS IN UNEXPECTED BEHAVIOR!");
    TEST_ASSERT_EQUAL(10, bytesRead1);
    TEST_ASSERT_EQUAL(5, bytesRead2);
}

void test_ReadUsingTwoDifferentDescriptors(void) {
    char *fileName = createTestFileWithContent(100, "2fd.txt");
    int fd1 = open(fileName, O_RDONLY);
    int fd2 = open(fileName, O_RDONLY);
    char buffer[100];
    ssize_t bytesRead1 = read(fd1, buffer, 50);
    ssize_t bytesRead2 = read(fd2, buffer, 50);
    close(fd1);
    close(fd2);
    remove(fileName);

    TEST_ASSERT_EQUAL(50, bytesRead1);
    TEST_ASSERT_EQUAL(50, bytesRead2);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ReadBytesFromFile);
    RUN_TEST(test_TryToReadTooManyBytes);
    RUN_TEST(test_ReadEmptyFile);
    RUN_TEST(test_ReadFromSameFileDescriptor);
    RUN_TEST(test_ReadUsingTwoDifferentDescriptors);

    return UNITY_END();
}

