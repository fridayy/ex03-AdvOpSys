//
// Created by bnjm on 12/5/16.
//
#include "readchar_R.h"
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

char ReadCharacter(int fd, int position) {
    off_t eof = lseek(fd, 0, SEEK_END);

    if(position > eof || position < 0) {
        return -1;
    }

    char buffer[1] = {' '};
    pread(fd, buffer, 1, position);

    return buffer[0];
}