#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
	
	char shm_name [] = "myshm";
	int shm_fd ;
	shm_fd = shm_open ( shm_name , O_CREAT | O_RDWR , 0666 );
	if ( shm_fd < 0) {
		perror ( NULL );
		return errno ;
	}

	size_t shm_size = argc * 4096;
	
	if ( ftruncate ( shm_fd , shm_size ) == -1) {
		perror ( NULL );
		shm_unlink ( shm_name );
		return errno ;
	}
	
	


	
	for(int i = 1; i <= argc; i++)
	{
        	pid_t pid = fork ();
        	if ( pid < 0)
                	return errno ;
        	else if ( pid == 0)
                	{

                        	char offset_str[16];
				sprintf(offset_str, "%d", (i - 1) * 4096);

				char *argvv[] = {"collatz", argv[i], offset_str, NULL};
                        	
                        	execve ("/home/iustin/Desktop/lab5/collatz" , argvv , NULL);
                        	
                	}
                else{
                	printf("Child pid: %d\n", (int)pid);
			
                }
       			
	}
	for(int i = 1; i <= argc; i++)
	{
		wait(NULL);
	}
	printf("Parent pid: %d\n", (int)getpid());
	
	void *shm_ptr = mmap(0, shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (shm_ptr == MAP_FAILED) {
		perror(NULL);
		shm_unlink(shm_name);
		return errno;
	}

	int *data = (int *)shm_ptr;
	int count = shm_size / sizeof(int);

	for (int i = 0; i < count; i++) {
		if(data[i] == -1)
			printf("\n");
		else if(data[i]!=0)
			printf("%d ", data[i]);
		
	}
	printf("\n");
	
	munmap(shm_ptr, shm_size); 
        close(shm_fd); 
        shm_unlink(shm_name);
	
	
        return 0;
}