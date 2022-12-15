#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>


int process_counter = 0;


void error(char* msg)
{
    perror(msg);
    exit(1);
}


void signal_handler(int signum)
{
    process_counter--;
}


int create_process(char* command_name, pid_t pid_collection[])
{
    signal(SIGCHLD, signal_handler);
    pid_t pid = fork();
    if (pid == 0)
    {
        pid_collection[process_counter] = pid;
        return system(command_name);
    }
    else if (pid < 0)
    {
        error("Error while creating process");
    }

    process_counter++;
    return 0;
}


int main(int argc, char* argv[])
{
    if (argc != 2) error("Wrong number of arguments");

    int processes_max_number = atoi(argv[1]);
    if (processes_max_number <= 0) error("Wrong number");

    char command_name[1024];
    pid_t pid_collection[processes_max_number];
    while (fgets(command_name, sizeof(command_name), stdin) != NULL)
    {
        if (strcmp(command_name, "-1") == 0) break;

        if (process_counter < processes_max_number)
        {
            create_process(command_name, pid_collection);
        } else {
            printf("Waiting for processes to finish...\n");
        }
    }

    for (int i = 0; i < processes_max_number; i++)
    {
        kill(pid_collection[i], SIGKILL);
    }

    return 0;
}