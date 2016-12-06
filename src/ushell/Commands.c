//
// Created by bnjm on 12/6/16.
//
#include "Commands.h"
#include <stdio.h>

void listCommands() {
    const char* commands[10] = { PWD, LS, CD, CAT, RM, CP, MKDIR, RMDIR, EXIT, HELP };
    printf("Available commands:\n");
    for (int i = 0; i < 10; ++i) {
        printf("\t%s\n", commands[i]);
    }
}