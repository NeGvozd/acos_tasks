#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>


void scandr(DIR *pDir)
{
    struct dirent *dir = readdir(pDir);
    if (dir == NULL)
        return;
    printf("%s\n", dir->d_name);
    scandr(pDir);
}

int main(int argc, char *argv[], char *envp[])
{  	
    DIR *pDir;
    struct dirent *dir;
    printf("%s to %s\n", argv[1], argv[2]);

    pDir = opendir(argv[1]);
    if (pDir)
    {
        dir = readdir(pDir);
        scandr(pDir);
        // printf("done\n");
        
    }
    else
    {

    }
    closedir(pDir);
    // char cwd[FILENAME_MAX];
    // if (getcwd(cwd, sizeof(cwd)) != NULL)   
    //     printf("%s\n", cwd);    
    // else
    //     perror("getcwd() error");
    //     return 1;
    return 0;
}
