//
// Created by bnjm on 12/5/16.
//
#include "../../src/ushell/PathOperation.h"
#include "../unity/unity.h"
#include "../TestFileHelper.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

char *testDir = "./bin/test";

void test_mymkdirCreatesDirectoryCorrectly(void) {
    char *path;
    long size = pathconf(".", _PC_PATH_MAX);
    char *buf = malloc(sizeof(char) * size);

    path = getcwd(buf, (size_t)size);

    TEST_ASSERT_EQUAL(0, strcmp(path, mypwd()));
}

void test_mylsReturnsFiles(void) {
    mkdir(testDir, 0755);
    creat("./bin/test/test0.txt", 0755);
    dirEntry **entries = myls(testDir);

    TEST_ASSERT_EQUAL(0, strcmp(entries[0]->name, ".."));
    TEST_ASSERT_EQUAL(0, strcmp(entries[1]->name, "test0.txt"));
    TEST_ASSERT_EQUAL(0, strcmp(entries[2]->name, "."));
    rmdir(testDir);
}

void test_mycdReturns0WhenChangingIntoDirectory(void) {
    mkdir(testDir, 0755);
    TEST_ASSERT_EQUAL(0, mycd(testDir));
    rmdir(testDir);
}

void test_mycdReturnsErrorWhenCDIntoNonExistantDirectory(void) {
    TEST_ASSERT_EQUAL(-1, mycd(testDir));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_mymkdirCreatesDirectoryCorrectly);
    RUN_TEST(test_mylsReturnsFiles);
    RUN_TEST(test_mycdReturns0WhenChangingIntoDirectory);
    RUN_TEST(test_mycdReturnsErrorWhenCDIntoNonExistantDirectory);

    return UNITY_END();
}
