//
// Created by bnjm on 12/5/16.
//
#include "TestFileHelper.h"
#include "unity/unity.h"
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * Positon cursor at the end of the file and write data.
 */
void test_JumpToEOFAndWriteSomeData(void) {
    char *fileName = createTestFileWithContent(10, "lseek.txt");
    int fd = open(fileName, O_RDWR);
    // Position pointer at the end
    off_t eof = lseek(fd, 0, SEEK_END);
    char buffer[3] = {'b', 'b', '\0'};
    pwrite(fd, buffer, 3, eof);
    close(fd);

    TEST_ASSERT_EQUAL(10, eof);

    FILE *fp;
    fp = fopen(fileName, "r");
    char readBuffer[100];
    fread(readBuffer, 13, 1, fp);
    fclose(fp);
    for (int i = 10; i < 12; ++i) {
        TEST_ASSERT_EQUAL('b', readBuffer[i]);
    }

    remove(fileName);
}

/*
 * Positon cursor at the beginning of the file and read this data.
 */
void test_JumpToBeginningOfTheFileAndReadSomeData(void) {
    char *fileName = createTestFileWithContent(10, "lseekread.txt");
    int fd = open(fileName, O_RDWR);

    // Position at beginning of the file
    off_t bof = lseek(fd, 0, SEEK_SET);
    char buffer[100];
    pread(fd, buffer, 1, bof);
    close(fd);
    remove(fileName);

    TEST_ASSERT_EQUAL(buffer[0], 'a');
}

/*
 * The cursor gets positioned beyond EOF. The offset of
 * old EOF and cursor pos gets filled with zeros.
 *
 * EOF:
 *      aaaa
 *         |
 * +5:
 *      aaaa00000
 *              |
 * add b:
 *      aaaa00000bb
 *                |
 */
void test_JumpBeyondTheEndOFTheFileANdWriteSomeData(void) {
    char *fileName = createTestFileWithContent(5, "lseekbyond.txt");
    int fd = open(fileName, O_RDWR);

    off_t eofAndOffset = lseek(fd, 5, SEEK_END);
    char buffer[3] = {'b', 'b', '\0'};
    pwrite(fd, buffer, 3, eofAndOffset);

    close(fd);

    FILE *fp;
    fp = fopen(fileName, "r");
    char readBuffer[100];
    fread(readBuffer, 13, 1, fp);
    fclose(fp);

    remove(fileName);

    TEST_ASSERT_EQUAL(0, readBuffer[9]);
    TEST_ASSERT_EQUAL('b', readBuffer[10]);
    TEST_ASSERT_EQUAL('b', readBuffer[11]);
}

/*
 * SEEK_CUR returns the current position of the cursor. In this test the cursor
 * gets positioned BOF + 20bytes so SEEK_CUR should return 20.
 */
void test_FindCurrentCursorPosition(void) {
    char *fileName = createTestFileWithContent(100, "lseekpos.txt");
    int fd = open(fileName, O_RDWR);

    // initial position
    lseek(fd, 20, SEEK_SET);

    off_t seekPos = lseek(fd, 0, SEEK_CUR);
    close(fd);
    remove(fileName);

    TEST_ASSERT_EQUAL(20, seekPos);
}

/**
 * The size of a file is equal to the SEEK_END position of the cursor which is EOF.
 */
void test_FindSizeOfAFile(void) {
    char *fileName = createTestFileWithContent(1000, "bigfile.txt");
    int fd = open(fileName, O_RDWR);

    off_t size = lseek(fd, 0, SEEK_END);
    close(fd);
    remove(fileName);

    TEST_ASSERT_EQUAL(1000, size);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_JumpToEOFAndWriteSomeData);
    RUN_TEST(test_JumpToBeginningOfTheFileAndReadSomeData);
    RUN_TEST(test_JumpBeyondTheEndOFTheFileANdWriteSomeData);
    RUN_TEST(test_FindCurrentCursorPosition);
    RUN_TEST(test_FindSizeOfAFile);

    return UNITY_END();
}

