#include "backing_up.h"


bool isBackedUp(char* orig_file, char* backup_file)
{
    struct stat original, backup;
    if (stat(orig_file, &original) == -1) {
        perror(orig_file);
        return false;
    }

    char* archived_path = strcpy(malloc(strlen(backup_file) + 4), backup_file);
    if (stat(strcat(archived_path, ".gz"), &backup) == -1) {
        return false; // file is not archived
    }

    return original.st_mtime <= backup.st_mtime;
}


void backupController(char* orig_path, char* backup_path)
{
    if (isBackedUp(orig_path, backup_path)) {
        printf("File %s is already backed up\n", orig_path);
    } else {
        printf("File %s is not backed up\n", orig_path);
        backupFile(orig_path, backup_path);
    }
}


void gzip(char* file_path)
{    
    execlp("gzip", "gzip", "-f", file_path, NULL);
    if (errno == ENOENT) {
        printf("Error with gzip\n");
        return;
    }
}


int backupFile(char* orig_file, char* backup_file)
{
    printf("Backing up %s\n", orig_file);

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

    gzip(backup_file);
    printf("Backed up successfully\n");
    return 0;
}