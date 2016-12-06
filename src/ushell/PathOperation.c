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

void setPermissions(__mode_t mode, char* permissions) {
    //user
    (mode & S_IRUSR ) ? permissions[1] = 'r' : '-';
    ( mode & S_IWUSR ) ? permissions[2] = 'w' : '-';
    ( mode & S_IXUSR ) ? permissions[3] = 'x' : '-';
    // group
    ( mode & S_IRGRP ) ? permissions[4] = 'r' : '-';
    ( mode & S_IWGRP ) ? permissions[5] = 'w' : '-';
    ( mode & S_IXGRP ) ? permissions[6] = 'x' : '-';
    //other
    ( mode & S_IROTH ) ? permissions[7] = 'r' : '-';
    ( mode & S_IWOTH ) ? permissions[8] = 'w' : '-';
    ( mode & S_IXOTH ) ? permissions[9] = 'x' : '-';
    permissions[10] = '\0';
    permissions[0] = '-';
}

char *mypwd() {
    char *path;
    long size = pathconf(".", _PC_PATH_MAX);
    char *buffer = malloc(sizeof(char) * size);
    path = getcwd(buffer, (size_t) size);

    return path;
}

dirEntry** myls(char *directory) {
    DIR *dp = opendir(directory);

    if(dp == NULL) {
        dp = opendir(mypwd());
    }
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
        setPermissions(fileinfo.st_mode, dirEntries[counter]->permissions);

        counter++;
    }
    closedir(dp);

    return dirEntries;
}

int mycd(char *directory) {
    return chdir(directory);
}