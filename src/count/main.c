//
// Created by bnjm on 12/5/16.
//
#include "count_M.h"
#include "readchar_R.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int getFileDescriptor(char *file) {
    int fd = open(file, O_RDONLY);

    if(fd == -1) {
        printf("Could not open file.\n");
        exit(-1);
    }
    return fd;
}

int getCountWithReadCharacter(int fd, char character) {
    off_t size = lseek(fd, 0, SEEK_END);
    int counter = 0;
    for (int i = 0; i <size; ++i) {
        if(character == ReadCharacter(fd, i)) {
            counter++;
        }
    }
    return counter;
}

int main(int argc, char *argv[]) {
    if(argc != 4) {
        printf("Wrong number of arguments!\n");
        exit(-1);
    }


    int fd = getFileDescriptor(argv[2]);
    if(fd == -1) {
        printf("Could not open file.\n");
        exit(-1);
    }


    if(argv[1][0] == 'M') {
        printf("The character %c has %d ocurrences.\n", argv[1][0],CountCharacters(fd, argv[3][0]));
    }

    if(argv[1][0] == 'R') {
        printf("The character %c has %d ocurrences.\n", argv[1][0],getCountWithReadCharacter(fd, argv[3][0]));
    }
}