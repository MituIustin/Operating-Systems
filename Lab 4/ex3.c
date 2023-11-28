#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


int main(int argc, char *argv[])
{

	for(int i = 1; i <= argc; i++)
	{
        	pid_t pid = fork ();
        	if ( pid < 0)
                	return errno ;
        	else if ( pid == 0)
                	{

                        	char * argvv [] = {"collatz", argv[i] , NULL };
                        	execve ("/home/iustin/Desktop/lab4/collatz" , argvv , NULL);

                	}
       		else
               	 	{

                        	printf("Parent pid: %d\n", (int)getpid());
                        	printf("Child pid: %d\n", (int)pid);
                        	wait(NULL);
                	}
	}
        return 0;
}