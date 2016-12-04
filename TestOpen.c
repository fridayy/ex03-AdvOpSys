//
// Created by bnjm on 12/4/16.
//
#include "unity/unity.h"
#include <fcntl.h>

void test_PlainOpenWithInvalidPath(void) {
    TEST_ASSERT_EQUAL(-1, open("invalid Path!", O_RDONLY));
}

void test_PlainOpenWithValidPath(void) {
    TEST_ASSERT(open("open.c", O_RDONLY) > 0);
}

void test_PlainOpenWithPrivileges(void) {
    TEST_ASSERT(open("test.txt", O_CREAT, S_IRUSR) > 0);
    TEST_ASSERT_EQUAL(-1, open("test.txt", O_RDWR));
    // Remove the created file again.
    remove("test.txt");
}

void removeMultipleTestFiles(int numberOfFiles) {
    for (int i = 0; i < numberOfFiles; ++i) {
        char buffer[50];
        sprintf(buffer, "test%d.txt", i);
        remove(buffer);
    }
}

void createMultipleTestFiles(int numberOfFiles) {
    for(int i = 0; i < numberOfFiles; i++) {
        char buffer[50];
        sprintf(buffer, "test%d.txt", i);
        FILE *fp = fopen(buffer, "w");
        fprintf(fp, "test");
        fclose(fp);
    }
}

/*
 * Test 3a:
 *  When opening multiple files we can assert that the file descriptor
 *  is growing steadily.
 */
void test_ConsecutiveCallsToOpenForDifferentFiles(void) {
    createMultipleTestFiles(3);
    int fileDescriptorFile0 = open("test0.txt", O_RDONLY);
    int fileDescriptorFile1 = open("test1.txt", O_RDONLY);
    int fileDescriptorFile2 = open("test2.txt", O_RDONLY);

    TEST_ASSERT(fileDescriptorFile0 < fileDescriptorFile1);
    TEST_ASSERT(fileDescriptorFile1 < fileDescriptorFile2);

    printf("File Descriptor first File: \t%d\n", fileDescriptorFile0);
    printf("File Descriptor second File: \t%d\n", fileDescriptorFile1);
    printf("File Descriptor third File: \t%d\n", fileDescriptorFile2);

    removeMultipleTestFiles(3);
}

void createTestFile() {
    if(fopen("test.txt", "r") == NULL) {
        FILE *fp = fopen("test.txt", "w");
        fprintf(fp, "test");
        fclose(fp);
    }
}

/*
 * Test 3b:
 *  Consecutive calls to the same file with the same open mode.
 */
void test_ConsecutiveCallsToOpenForSameFile(void) {
    createTestFile();
    int fileDescriptorFirstAccess = open("test.txt", O_RDONLY);
    int fileDescriptorSecondAccess = open("test.txt", O_RDONLY);
    int fileDescriptorThirdAccess = open("test.txt", O_RDONLY);

    TEST_ASSERT(fileDescriptorFirstAccess < fileDescriptorSecondAccess);
    TEST_ASSERT(fileDescriptorSecondAccess < fileDescriptorThirdAccess);

    printf("File Descriptor first access \t%d\n", fileDescriptorFirstAccess);
    printf("File Descriptor second access: \t%d\n", fileDescriptorSecondAccess);
    printf("File Descriptor third access: \t%d\n", fileDescriptorThirdAccess);
    remove("test.txt");
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_PlainOpenWithInvalidPath);
    RUN_TEST(test_PlainOpenWithValidPath);
    RUN_TEST(test_PlainOpenWithPrivileges);
    RUN_TEST(test_ConsecutiveCallsToOpenForDifferentFiles);
    RUN_TEST(test_ConsecutiveCallsToOpenForSameFile);

    return UNITY_END();
}