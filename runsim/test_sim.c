#include <stdio.h>

int main(int argc, char* argv[])
{
    int sec;

    sscanf(argv[1], "%d", &sec);

    sleep(sec);

    printf("Process ID = %d \n", getpid());
    return 0;
}