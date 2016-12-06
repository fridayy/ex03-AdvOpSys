//
// Created by bnjm on 12/5/16.
//

#ifndef LABEXERCISE3_PATHOPERATION_H
#define LABEXERCISE3_PATHOPERATION_H

#endif //LABEXERCISE3_PATHOPERATION_H

/*
 * Shows the full path and name of the current directory
 */
char * mypwd();

/*
 * Lists the entries of a directory
 */
char * myls();


/*
 * Changes the directory to the directory passed as argument.
 * If no argument is specified (null) the shell will change in the directory
 * it was initially launched from
 */
void mycd(char *directory);