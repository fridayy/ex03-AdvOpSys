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

#include "Commands.h"
#include "Colors.h"


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
    if(strcmp(command[0], PWD) == 0) {
        executePwd();
    }

    if(strcmp(command[0], LS) == 0) {
        executeLs(command[2], command[1]);
    }

    if(strcmp(command[0], CD) == 0) {
        mycd(command[1]);
    }

    if(strcmp(command[0], CAT) == 0) {
        printf("\n%s\n",mycat(command[1]));
    }

    if(strcmp(command[0], RM) == 0) {
        myrm(command[1]);
    }

    if(strcmp(command[0], CP) == 0) {
        mycp(command[1], command[2]);
    }

    if(strcmp(command[0], MKDIR) == 0) {
        mymkdir(command[1]);
    }

    if(strcmp(command[0], RMDIR) == 0) {
        myrmdir(command[1]);
    }

    if(strcmp(command[0], EXIT) == 0) {
        exitShell();
    }

    if(strcmp(command[0], HELP) == 0) {
        listCommands();
    }
}