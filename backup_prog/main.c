// #include "headers.h"
#include "functions.c"


int main(int argc, char *argv[], char *envp[])
{  	
    if (argc != 3) {
        perror("Wrong number of arguments");
        return 1;
    }

    printf("%s to %s\n", argv[1], argv[2]);
    mkdir(argv[2], 0777);
    scanDirectory(argv[1], argv[2]);
    return 0;
}
