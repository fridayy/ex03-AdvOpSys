//
// Created by bnjm on 12/6/16.
//
#include "DirectoryOperation.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int mymkdir(char *directoryName) {
    return mkdir(directoryName, 0755);
}

int myrmdir(char *directoryName) {
    return rmdir(directoryName);
}