#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>



void collatz(int n) 
{
	printf("%d ",n);
        if (n == 1)
                return;
        else
        {
                if(n % 2 == 0)
                        collatz(n/2);
                else
                        collatz(3*n+1);
        }
}

int main(int argc, char*argv[])
{
	
	collatz(atoi(argv[1]));
	return 0;
}