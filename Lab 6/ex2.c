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

int firstMatrix[2][3] = {{1, 4, 3}, {3, 2, 1}};
int secondMatrix[3][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
int resultMatrix[2][3];

void * hello ( void * v )
{
	int *args = (int *)v;
	int i = args[0];
        int j = args[1];
        int colsFirst = args[2];
	int *s = malloc(sizeof(int));
	*s = 0;
	for (int k = 0; k < colsFirst; ++k) 
	{
		*s += firstMatrix[i][k] * secondMatrix[k][j];
	}
	return s;
}

void displayMatrix(int rows, int cols) 
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", resultMatrix[i][j]);
        }
        printf("\n");
    }
}


int main(int argc, char *argv[])
{
	int rowsFirst = 2;
	int colsFirst = 3;
	int rowsSecond = 3;
	int colsSecond = 3;
	
	int argumente[rowsFirst*colsSecond][3];
	pthread_t thr[rowsFirst][colsSecond];

	for (int i = 0; i < rowsFirst; ++i) 
	{
		for (int j = 0; j < colsSecond; ++j) 
		{	
		
			argumente[3*i+j][0] = i;
			argumente[3*i+j][1] = j;
			argumente[3*i+j][2] = colsFirst;

			if ( pthread_create (& thr[i][j] , NULL , hello , argumente[3*i+j])) 
			{
				perror ( NULL );
				return errno ;
			}
			
			
        	}
    	}
	
	for (int i = 0; i < rowsFirst; ++i) 
	{
		for (int j = 0; j < colsSecond; ++j) 
		{	
		
			int *x;
			if ( pthread_join ( thr[i][j] , (void**)&x) )
			{
				perror ( NULL );
				return errno ;
			}
			resultMatrix[i][j] = *x;
        	}
    	}	
	
	displayMatrix(rowsFirst, colsSecond);
	
	
	return 0;
}