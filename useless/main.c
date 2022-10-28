#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[])
{    
	if (argc != 2){
		perror("Wrong number of arguments");
		return -1;
	}

	FILE *f;
	f = fopen(argv[1], "r");    
	if (f == NULL) {
		perror("File not found");
		return -1;
	}

	char str[FILENAME_MAX];
	int t = 0;
	int input = 0;
	
	while(!feof(f))
	{
		int rs = fscanf(f, "%d %s", &t, str);
		if (rs != 2) {
			printf("Wrong format of file\n");
			return -1;
		}
		if (t < 0) {
			printf("Wrong time format\n");
			return -1;
		}

		printf("Command \"%s\" will be executed with %dsec delay\n", str, t);
	
		pid_t pid = fork();
		if (pid == -1) perror("Fork error");

		switch(pid)
		{
			case -1:
					perror("Fork error");
					return -1;
			case 0:
				sleep(t);
				printf("Child process %s started\n", str);
				execlp(str, str, NULL);

				printf("\"%s\" failed!\n", str);
				exit(EXIT_FAILURE);
		}
	}

   	while (wait(NULL) != -1) {};

	fclose(f);
	return 0;
}