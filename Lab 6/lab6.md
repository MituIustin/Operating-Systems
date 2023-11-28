# Ex 1

Scrieti un program care primeste un sir de caractere la intrare, ale carui
caractere le copiaza in ordine inversa si le salveaza intr-un sir separat.
Operatia de inversare va avea loc intr-un thread separat. Rezultatul va fi
obtinut cu ajutorul functiei pthread_join.

```ssh_session
gcc ex1.c -o ex1
```

```ssh-session
./ex1 hello
```

ex1.c

```c
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
```

# Ex 2 

Scrieti un program care sa calculeze produsul a doua matrice date (de
dimensiuni compatibile) unde fiecare element al matricei rezultate este
calculat de catre un thread distinct.

```ssh-session
gcc ex2.c -o ex2
```

```ssh-session
./ex2
```

ex2.c

```c
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
```

