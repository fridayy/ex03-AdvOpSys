//
// Created by bnjm on 12/5/16.
//
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "count_M.h"

int CountCharacters(int fd, char character) {
    off_t len = lseek(fd, 0, SEEK_END);
    char *map = mmap(0, len, PROT_READ, MAP_SHARED, fd, 0);
    int counter = 0;
    if(map == MAP_FAILED) {
        return -1;
    }

    for (int i = 0; i < len; ++i) {
        if(map[i] == character) {
            counter++;
        }
    }

    return counter;
}