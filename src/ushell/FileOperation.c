//
// Created by bnjm on 12/5/16.
//
#include "FileOperation.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

int getFilesize(int fd) {
    struct stat fileinfo = {0};

    if(fstat(fd, &fileinfo) == -1) {
        return -1;
    }

    return fileinfo.st_size;
}


int mycp(char *source, char *target) {
    int fdSource = open(source, O_RDONLY);
    char *readBuffer = malloc(sizeof(char) * 1024);

    int fileSize = getFilesize(fdSource);
    ssize_t byesRead = read(fdSource, readBuffer, fileSize);

    int fdTarget = open(target, O_RDWR|O_CREAT, 0644);
    char *writeBuffer = malloc(sizeof(char) * 1024);
    writeBuffer = strcpy(writeBuffer, readBuffer);
    ssize_t bytesWritten = write(fdTarget, writeBuffer, fileSize);

    free(readBuffer);
    free(writeBuffer);
    if(byesRead == -1 || bytesWritten == -1) {
        //error occurred
        return -1;
    }

    return 0;
}

int myrm(char *fileName) {
    return unlink(fileName);
}

char *mycat(char *fileName) {
    int fd = open(fileName, O_RDONLY);

    if(fd == -1) {
        perror("File not found");
        exit(EXIT_FAILURE);
    }

    int fileSize = getFilesize(fd);
    char *map = mmap(0, fileSize, PROT_READ, MAP_SHARED, fd, 0);

    if(map == MAP_FAILED) {
        perror("Could not read file");
        exit(EXIT_FAILURE);
    }

    char *returnValue = malloc(fileSize * sizeof(char));
    strcpy(returnValue, map);

    return returnValue;
}
