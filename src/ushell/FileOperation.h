//
// Created by bnjm on 12/5/16.
//

#ifndef LABEXERCISE3_FILEOPERATION_H
#define LABEXERCISE3_FILEOPERATION_H

#endif //LABEXERCISE3_FILEOPERATION_H

/*
 * Copies the contents of a source file to the
 * target file
 */
int mycp(char *source, char *target);

/*
 * Will delete (unlink) the file assed as parameter
 */
int myrm(char *fileName);

/*
 * Reads the content of fileName and returns them
 */
char *mycat(char *fileName);