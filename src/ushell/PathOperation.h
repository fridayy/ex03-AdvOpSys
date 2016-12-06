//
// Created by bnjm on 12/5/16.
//

#ifndef LABEXERCISE3_PATHOPERATION_H
#define LABEXERCISE3_PATHOPERATION_H

#endif //LABEXERCISE3_PATHOPERATION_H

#include "dirEntry.h"
/*
 * Shows the full path and name of the current directory
 */
char * mypwd();

/*
 * Lists the entries of a directory with optional arguments like -l
 */
dirEntry** myls(char *directory, char* arguments);


/*
 * Changes the directory to the directory passed as argument.
 * If no argument is specified (null) the shell will change in the directory
 * it was initially launched from
 */
int mycd(char *directory);