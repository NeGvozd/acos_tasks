#ifndef BACKING_UP_H
#define BACKING_UP_H

#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool isBackedUp(char *orig_file, char *backuped_file);
void backupController(char* orig_path, char* backup_path);
void gzip(char* file_path);
int backupFile(char* orig_file, char* backup_file);

#endif