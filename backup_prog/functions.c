#include "headers.h"


bool isBackedUp(char *orig_file, char *backuped_file)
{
    struct stat original, backup;
    stat(orig_file, &original);
    stat(backuped_file, &backup);

    if (errno == ENOENT) return false; //Backup file doesn't exist

    return original.st_mtime <= backup.st_mtime;
}


void backupController(char* orig_path, char* backup_path) {
    if (isBackedUp(orig_path, backup_path)) {
        printf("File %s is already backed up\n", orig_path);
    } else {
        printf("File %s is not backed up\n", orig_path);
        backupFile(orig_path, backup_path);
    }
}


int backupFile(char* orig_file, char* backup_file)
{
    printf("Backing up %s to %s\n", orig_file, backup_file);

    int f_in = open(orig_file, O_RDONLY);
    int f_out = open(backup_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (f_in == -1 || f_out == -1) {
        perror("Error opening file");
        return -1;
    }

    int read_data = 0, write_data = 0;
    char buffer[1024];
    while ((read_data = read(f_in, buffer, sizeof(buffer))) > 0)
    {
        write_data = write(f_out, buffer, read_data);
        if (write_data != read_data)
        {
            printf("Error writing to file %s\n", backup_file);
            return -1;
        }        
    }
    close(f_in);
    close(f_out);

    printf("Backed up from %s to %s\n", orig_file, backup_file);
    return 0;
}


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
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char* file_path = updatePath(path, entry->d_name);
        char* backup_path = updatePath(bpath, entry->d_name);

        if (entry->d_type != DT_DIR) {
            printf("File: %s\nBackup: %s\n\n", file_path, backup_path);
            backupController(file_path, backup_path);
            continue;
        }
        checkForDirExistence(backup_path);
        scanDirectory(file_path, backup_path);
    }
    closedir(dir);
}