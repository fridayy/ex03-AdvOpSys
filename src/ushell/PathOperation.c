//
// Created by bnjm on 12/6/16.
//
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include "PathOperation.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//#include "dirEntry.h"

char identifyFileType(__mode_t mode) {
    if(S_ISSOCK(mode))
        return 's';
    if(S_ISLNK(mode))
        return 'l';
    if(S_ISREG(mode))
        return 'f';
    if(S_ISBLK(mode))
        return 'b';
    if(S_ISDIR(mode))
        return 'd';
    if(S_ISCHR(mode))
        return 'c';
    if(S_ISFIFO(mode))
        return 'f';
    return '?';
}

void setPermissions(__mode_t mode, dirEntry *entry) {
    char str[10] = { '-', '-','-','-','-','-','-','-','-'};
    //user
    if ( mode & S_IRUSR ) str[1] = 'r';
    if ( mode & S_IWUSR ) str[2] = 'w';
    if ( mode & S_IXUSR ) str[3] = 'x';
    // group
    if ( mode & S_IRGRP ) str[4] = 'r';
    if ( mode & S_IWGRP ) str[5] = 'w';
    if ( mode & S_IXGRP ) str[6] = 'x';
    //other
    if ( mode & S_IROTH ) str[7] = 'r';
    if ( mode & S_IWOTH ) str[8] = 'w';
    if ( mode & S_IXOTH ) str[9] = 'x';
    str[10] = '\0';
    entry->permissions = str;
}

char *mypwd() {
    char *path;
    long size = pathconf(".", _PC_PATH_MAX);
    char *buffer = malloc(sizeof(char) * size);
    path = getcwd(buffer, (size_t) size);

    return path;
}

dirEntry** myls(char *directory, char *arguments) {
    DIR *dp = opendir(directory);
    struct dirent *entry;
    dirEntry** dirEntries = malloc(sizeof(*dirEntries) * USHRT_MAX);

    struct stat fileinfo = {0};

    int counter = 0;
    while((entry = readdir(dp)) != NULL) {
        dirEntries[counter] = malloc(sizeof(**dirEntries));
        dirEntries[counter]->name = entry->d_name;

        //get infos about file
        stat(entry->d_name, &fileinfo);
        dirEntries[counter]->uid = fileinfo.st_uid;
        dirEntries[counter]->gid = fileinfo.st_gid;
        dirEntries[counter]->size = fileinfo.st_size;
        dirEntries[counter]->lastModified = fileinfo.st_mtim.tv_sec;
        dirEntries[counter]->type = identifyFileType(fileinfo.st_mode);
        setPermissions(fileinfo.st_mode, dirEntries[counter]);

        counter++;
    }
    closedir(dp);

    return dirEntries;
}

int mycd(char *directory) {
    return chdir(directory);
}