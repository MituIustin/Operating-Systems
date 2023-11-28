#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>
#include <string.h>

char* reverseString(char str[]) 
{
    int length = strlen(str);
    int start = 0;
    int end = length - 1;

    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

    return str;
}

void * hello ( void * v )
{
	char * who = ( char *) v ;
	char * str = reverseString(who);
	return str ;
}



int main(int argc, char *argv[])
{
	pthread_t thr ;
	if ( pthread_create (& thr , NULL , hello , argv[1])) {
		perror ( NULL );
		return errno ;
	}
	
	
	
	char * result;
	if ( pthread_join ( thr , (void **)&result)) {
		perror ( NULL );
		return errno ;
	}
	printf ("%s \n" , result);
	
	
	return 0;
}