//
// Created by bnjm on 12/4/16.
//

#include <stdio.h>

char * createTestFile(char *fileName) {
    if(fopen(fileName, "r") == NULL) {
        FILE *fp = fopen(fileName, "w");
        fclose(fp);
    }
    return fileName;
}

char * createTestFileWithContent(int numberOfByes, char *fileName) {
    char input[numberOfByes];
    if(fopen(fileName, "r") == NULL) {
        FILE *fp = fopen(fileName, "w");

        for (int i = 0; i < numberOfByes; ++i) {
            input[i] = 'a';
        }
        input[numberOfByes] = '\0';
        fprintf(fp, input);
        fclose(fp);
    }
    return fileName;
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
