//
// Created by bnjm on 12/4/16.
//
#include <fcntl.h>
#include <unistd.h>
#include "unity/unity.h"
#include "TestFileHelper.h"

void test_OverwriteSomeBytesInAFile(void) {
    char *fileName = createTestFileWithContent(5, "overrideme.txt");
    int fd = open(fileName, O_RDWR);
    char buffer[5] = { 'b', 'b', 'b', 'b', 'b' };
    ssize_t bytesWritten = write(fd, buffer, 5);
    close(fd);
    TEST_ASSERT_EQUAL(5, bytesWritten);

    FILE *fp;
    fp = fopen(fileName,"r");
    char readBuffer[100];
    fread(readBuffer, 5, 1, fp);
    fclose(fp);
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT_EQUAL('b', readBuffer[i]);
    }

    remove(fileName);
}
/*
 * File gets correctly overwritten by file contest after the 2 written bytes
 * are garbage.
 */
void test_OverwriteMoreBytesThanThereAreInAFile(void) {
    char *fileName = createTestFileWithContent(1, "override!.txt");
    int fd = open(fileName, O_RDWR);
    char buffer[3] = { 'b', 'b', '\0' };
    ssize_t bytesWritten = write(fd, buffer, 3);
    close(fd);
    TEST_ASSERT_EQUAL(3, bytesWritten);
    remove(fileName);
}

void test_writeInAFileWHenPositionedAtItsEnd(void) {
    char *fileName = createTestFileWithContent(5, "append.txt");
    int fd = open(fileName, O_APPEND|O_RDWR);
    char buffer[1] = { 'b' };
    ssize_t bytesWritten = write(fd, buffer, 1);
    close(fd);

    TEST_ASSERT_EQUAL(1, bytesWritten);

    FILE *fp;
    fp = fopen(fileName,"r");
    char readBuffer[100];
    fread(readBuffer, 6, 1, fp);
    fclose(fp);

    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT_EQUAL('a', readBuffer[i]);
    }

    TEST_ASSERT_EQUAL(readBuffer[5], 'b');

    remove(fileName);
}

/*
 * Since there is no append 2 fds still means overwrite
 */
void writeInAFileUsingTwoDifferentDescriptors(void) {
    char *fileName = createTestFileWithContent(10, "twooverrides.txt");
    int fd1 = open(fileName, O_RDWR);
    int fd2 = open(fileName, O_RDWR);
    char buffer[5] = { 'b', 'b', 'b', 'b', 'b' };
    ssize_t bytesWritten1 = write(fd1, buffer, 5);
    ssize_t bytesWritten2 = write(fd2, buffer, 5);
    close(fd1);
    close(fd2);

    TEST_ASSERT_EQUAL(5, bytesWritten1);
    TEST_ASSERT_EQUAL(5, bytesWritten2);

    FILE *fp;
    fp = fopen(fileName,"r");
    char readBuffer[100];
    fread(readBuffer, 10, 1, fp);
    fclose(fp);

    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT_EQUAL('b', readBuffer[i]);
    }

    for (int i = 5; i < 10; ++i) {
        TEST_ASSERT_EQUAL('a', readBuffer[i]);
    }
    remove(fileName);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_OverwriteSomeBytesInAFile);
    RUN_TEST(test_OverwriteMoreBytesThanThereAreInAFile);
    RUN_TEST(test_writeInAFileWHenPositionedAtItsEnd);
    RUN_TEST(writeInAFileUsingTwoDifferentDescriptors);

    return UNITY_END();
}