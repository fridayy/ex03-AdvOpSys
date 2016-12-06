//
// Created by bnjm on 12/5/16.
//
#include "../../src/ushell/FileOperation.h"
#include "../unity/unity.h"
#include "../TestFileHelper.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_myrmReturnsCorrectValueOnFailure(void) {
    char *fileName = "Idontexists.txt";

    //myrm() should return -1 in case of an error
    TEST_ASSERT_EQUAL(-1, myrm(fileName));
}

void test_myrmRemovesFileAndReturnsCorrectValue(void) {
    char *fileName = createFileWithContent("deleteme.txt", "TEST FILE PLEASE IGNORE!");

    // Test for correct return value and execute myrm().
    TEST_ASSERT_EQUAL(0, myrm(fileName));

    // Check if the file is deleted correctly.
    FILE *fp = fopen(fileName, "r");
    TEST_ASSERT_EQUAL(NULL, fp);

    if(fp) {
        fclose(fp);
    }
}

void test_mycpCopiesContentAndReturnsCorrectValueWithNonExistingTargetfile(void) {
    char *content = "COPY ME PLEASE!";
    char *fileName = createFileWithContent("copyme.txt", content);

    char *targetFile = "copied.txt";
    TEST_ASSERT_EQUAL(0,mycp(fileName, targetFile));

    FILE *fp = fopen(targetFile, "r");
    // target file must exist
    TEST_ASSERT_NOT_EQUAL(NULL, fp);

    char readBuffer[1024] = { '0' };
    fread(readBuffer, strlen(content) + 1, 1, fp);
    TEST_ASSERT_EQUAL(0,strcmp(content, readBuffer));

    remove(fileName);
    remove(targetFile);
}

void test_mycpOveridesAlreadyExistingFile(void) {
    char *expectedContent = "aaaa";
    char *source = createFileWithContent("copyme.txt", expectedContent);
    char *target = createFileWithContent("copyme2.txt", "bbbb");

    TEST_ASSERT_EQUAL(0, mycp(source, target));

    FILE *fp = fopen(target, "r");
    // target file must exist
    TEST_ASSERT_NOT_EQUAL(NULL, fp);

    char readBuffer[1024] = { '0' };
    fread(readBuffer, strlen(expectedContent) + 1, 1, fp);

    TEST_ASSERT_EQUAL(0,strcmp(expectedContent, readBuffer));

    remove(source);
    remove(target);
}


void test_mycatShowsFileContents(void) {
    char *content = "hey, please read me :)";
    char *fileName = createFileWithContent("readme.txt", content);

    char *mycatReturnValue = mycat(fileName);
    TEST_ASSERT_EQUAL(0, strcmp(content, mycatReturnValue));
}

void test_mycatThrowsError(void) {
    mycat("saihdasidasd");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_myrmReturnsCorrectValueOnFailure);
    RUN_TEST(test_myrmRemovesFileAndReturnsCorrectValue);
    RUN_TEST(test_mycpCopiesContentAndReturnsCorrectValueWithNonExistingTargetfile);
    RUN_TEST(test_mycpOveridesAlreadyExistingFile);
    RUN_TEST(test_mycatShowsFileContents);
    RUN_TEST(test_mycatThrowsError);

    return UNITY_END();
}
