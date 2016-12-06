//
// Created by bnjm on 12/6/16.
//

#ifndef LABEXERCISE3_DIRENTRY_H
#define LABEXERCISE3_DIRENTRY_H

#endif //LABEXERCISE3_DIRENTRY_H

#include <limits.h>

/*
 *  Struct to hold informations about a file or directory.
 *
 *  Type declaration to identify the type:
 *       S_IFSOCK   0140000   socket              = s
 *       S_IFLNK    0120000   symbolic link       = l
 *       S_IFREG    0100000   regular file        = f
 *       S_IFBLK    0060000   block device        = b
 *       S_IFDIR    0040000   directory           = d
 *       S_IFCHR    0020000   character device    = c
 *       S_IFIFO    0010000   FIFO                = f
 */
typedef struct dirEntry {
    char * name;         // file / directory name
    int uid;            // user id
    int gid;            // group id
    int size;           // hold the size in bytes
    long lastModified; // Last modfied date in unix time
    char type;         // holds as specified above
    char permissions[10]; // permissions in format -rwx-rwx-rwx
} dirEntry;