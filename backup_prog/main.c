#include "dir_scanning.h"
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char *argv[], char *envp[])
{  	
    if (argc != 3) {
        perror("Wrong number of arguments");
        return 1;
    }

    mkdir(argv[2], 0777);
    scanDirectory(argv[1], argv[2]);
    return 0;
}
