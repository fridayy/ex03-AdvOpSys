//
// Created by bnjm on 12/6/16.
//
#include "PathOperation.h"
#include "FileOperation.h"
#include "DirectoryOperation.h"
#include "InternalOperation.h"
#include <stdio.h>
#include <string.h>
#include <stdio.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
// Thank you: http://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix#3586005

void executePwd() {
    printf("%s\n", mypwd());
}

void printLsSimple(dirEntry *entry) {
    if(entry->type == 'd') {
        printf(BLU "%s\n", entry->name);
    } else if(entry->type == 'f') {
        printf(GRN "%s\n", entry->name);
    } else {
        printf(RESET "%s\n", entry->name);
    }
}

void printLsExtended(dirEntry *entry) {
    if(entry->type == 'd')
        printf(RESET "%10s  %1c  %5d  %5d  %5d  %5ld" BLU  " %2s\n", entry->permissions, entry->type, entry->uid, entry->gid, entry->size, entry->lastModified, entry->name);
    else if (entry->type == 'f')
        printf(RESET "%10s  %1c  %5d  %5d  %5d  %5ld" GRN  " %2s\n", entry->permissions, entry->type, entry->uid, entry->gid, entry->size, entry->lastModified, entry->name);
    else
        printf(RESET "%10s  %1c  %5d  %5d  %5d  %5ld  %s\n", entry->permissions, entry->type, entry->uid, entry->gid, entry->size, entry->lastModified, entry->name);
}

void renderLsCommand(dirEntry **entries, char *arguments) {
    int counter = 0;
    while(entries[counter] != NULL) {
        if(arguments == NULL) {
            printLsSimple(entries[counter]);
        } else if(strcmp("-l", arguments) == 0) {
            printLsExtended(entries[counter]);
        } else {
            printf("Unknown argument.");
            break;
        }
        counter++;
    }
    printf(RESET "\nTotal: %d\n", counter);
}

void renderLsLong(dirEntry **entries) {
    int counter = 0;
    while(entries[counter] != NULL) {
        printLsSimple(entries[counter]);
        counter++;
    }
    printf(RESET "\n");
}


void executeLs(char *directory, char* arguments) {
    if(directory == NULL) {
        renderLsCommand(myls("."), arguments);
    } else {
        renderLsCommand(myls(directory), arguments);
    }
}



void executeCommand(char **command) {
    if(strcmp(command[0], "pwd") == 0) {
        executePwd();
    }

    if(strcmp(command[0], "ls") == 0) {
        executeLs(command[2], command[1]);
    }

    if(strcmp(command[0], "cd") == 0) {
        mycd(command[1]);
    }

    if(strcmp(command[0], "cat") == 0) {
        printf("\n%s\n",mycat(command[1]));
    }

    if(strcmp(command[0], "rm") == 0) {
        myrm(command[1]);
    }

    if(strcmp(command[0], "cp") == 0) {
        mycp(command[1], command[2]);
    }

    if(strcmp(command[0], "mkdir") == 0) {
        mymkdir(command[1]);
    }

    if(strcmp(command[0], "rmdir") == 0) {
        myrmdir(command[1]);
    }

    if(strcmp(command[0], "exit") == 0) {
        exitShell();
    }
}