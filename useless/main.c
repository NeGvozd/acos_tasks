#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[])
{    
	FILE *f;
	f = fopen(argv[1], "r");
    
	// if (fopen == failed)
	// {

	// }

	char str[FILENAME_MAX];
	int t = 0;
	int input = 0;
	
	while(!feof(f))
	{
		fscanf(f, "%d %s", &t, str);

		// if (t < 0)
        	// {

        	// }

        	printf("Command \"%s\" will be executed with %dsec delay\n", str, t);
	    
        	pid_t pid = fork();
        	switch(pid)
        	{
        	case -1:
            		perror("fork");
            		return -1;
        	case 0:
			sleep(t);
            		printf("%s is executed\n", str);
			execlp(str, str, NULL);

			printf("\"%s\" failed!\n", str);
			exit(EXIT_FAILURE);
        	}
	}

   	while (wait(NULL) != -1) {};

    	fclose(f);
	return EXIT_SUCCESS;
}