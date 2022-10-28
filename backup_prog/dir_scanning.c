#include "dir_scanning.h"
#include "backing_up.h"

char* updatePath(char* path, char* name)
{
    char* new_path = malloc(strlen(path) + strlen(name) + 2);
    sprintf(new_path, "%s/%s", path, name);
    return new_path;
}


void checkForDirExistence(char* path)
{
    DIR* dir = opendir(path);
    if (dir) { closedir(dir); return; }
    if (errno == ENOENT) { mkdir(path, 0777); return; }
    perror("Error opening directory");
}


void scanDirectory(char* path, char* bpath)
{
    DIR* dir;
    if ((dir = opendir(path)) == NULL) {
        printf("Can't open directory\n");
        return;
    } 

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || 
                strcmp(entry->d_name, "..") == 0)
            continue;

        char* file_path = updatePath(path, entry->d_name);
        char* backup_path = updatePath(bpath, entry->d_name);
        int status;

        if (entry->d_type != DT_DIR) {
            pid_t pid = fork();
            pid_t wpid;
            if (pid == 0) {
                backupController(file_path, backup_path);
                break;
            }
            if (pid == -1) {
                printf("Error with fork\n");
                exit(1);
            }
            
            wpid = wait(&status);
            if (wpid == -1) {
                printf("Error with wait\n");
                exit(1);
            }
            // backupController(file_path, backup_path);
            continue;
        }
        checkForDirExistence(backup_path);
        scanDirectory(file_path, backup_path);
    }
    closedir(dir);
}