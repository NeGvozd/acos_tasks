#ifndef DIR_SCANNING_H
#define DIR_SCANNING_H

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "backing_up.h"

// char* updatePath(char* path, char* name);
// void checkForDirExistence(char* path);
void scanDirectory(char* path, char* bpath);

#endif