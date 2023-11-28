#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
	pid_t pid = fork ();
	if ( pid < 0)
		return errno ;
	else if ( pid == 0)
		{
			/* child instructions */
			char * argv [] = {"prog" , NULL };
			execve ("/home/iustin/Desktop/lab4/prog" , argv , NULL );
			perror ( NULL );
		}
	else
		{
			
			printf("Parent pid: %d\n", (int)getpid());
			printf("Child pid: %d\n", (int)pid);
			wait(NULL);
		}
}