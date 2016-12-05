//
// Created by bnjm on 12/5/16.
//
#include "TestFileHelper.h"
#include "unity/unity.h"
#include <unistd.h>
#include <fcntl.h>

void test_closeANonExistingFileDescriptor(void) {
    TEST_ASSERT_EQUAL(-1, close(9999));
}

void test_ReadOrWriteDataAfterClosing(void) {
    char *fileName = createTestFileWithContent(100, "sadf.txt");
    int fd = open(fileName, O_RDWR);
    char buffer[100];
    //Close before reading!
    close(fd);
    TEST_ASSERT_EQUAL(-1, read(fd, buffer, 100));
    TEST_ASSERT_EQUAL(-1, write(fd, buffer, 100));
    remove(fileName);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_closeANonExistingFileDescriptor);
    RUN_TEST(test_ReadOrWriteDataAfterClosing);

    return UNITY_END();
}

