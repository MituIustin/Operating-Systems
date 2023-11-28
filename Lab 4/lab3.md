# Ex 1

Creati un proces nou folosind fork(2) si afisati fisierele din directorul
curent cu ajutorul execve(2). Din procesul initial afisati pid-ul propriu
si pid-ul copilului. 

```ssh-session
gcc ex1.c -o ex1
```

```ssh-session
./ex1
```


ex1.c

```c
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
```

prog.c

```c
#include <dirent.h>
#include <stdio.h>
 
int main(void)
{
    DIR *d;
    struct dirent *dir;
    d = opendir("/home/iustin/Desktop/lab4");
    
    while ((dir = readdir(d)) != NULL)
    {
         printf("%s\n", dir->d_name);
    }
    closedir(d);
    
    return(0);
}
```


# Ex 2

Ipoteza Collatz spune ca plecand de la orice numar natural daca aplicam
repetat urmatoarea operatie


f(n) = n / 2 daca n este par
f(n) = n * 3 + 1 daca n este impar


sirul ce rezulta va atinge valoarea 1. Implementati un program care
foloseste fork(2) si testeaza ipoteza generand sirul asociat unui numar
dat in procesul copil.

```ssh-session
gcc ex2.c -o ex2
```

```ssh-session
./ex2 24
```

ex2.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


int main(int argc, char *argv[])
{
        pid_t pid = fork ();
        if ( pid < 0)
                return errno ;
        else if ( pid == 0)
                {
                 
                        char * argvv [] = {"collatz", argv[1] , NULL };
                        execve ("/home/iustin/Desktop/lab4/collatz" , argvv , NULL);
                   
                }
        else
		{

                        printf("Parent pid: %d\n", (int)getpid());
                        printf("Child pid: %d\n", (int)pid);
                        wait(NULL);
                }
	return 0;
}
```

collatz.c

```c
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
        {
                printf("\n");
                return;
        }
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
```


# Ex 3

Implementati un program care sa testeze ipoteza Collatz pentru mai multe
numere date. Pornind de la un singur proces parinte, este creat cate un
copil care se ocupa de un singur numar. Parintele va astepta sa termine
executia fiecare copil. Programul va demonstra acest comportament folosind functiile getpid(2) si getppid(2).


```ssh-session
gcc ex3.c -o ex3
```

```ssh-session
./ex3 24 12 3 4 7 8
```

ex3.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    pid_t pids[argc - 1]; // Aici am corectat dimensiunea array-ului pids

    for (int i = 1; i < argc; i++) // Aici am schimbat condiția din <= în <
    {
        pids[i - 1] = fork();
        if (pids[i - 1] < 0)
        {
            perror("fork");
            exit(errno);
        }

        if (pids[i - 1] == 0)
        {
            printf("Child pid: %d\n", (int)getpid());
            char *argvv[] = {"collatz", argv[i], NULL};
            execve("/home/iustin/Desktop/lab4/collatz", argvv, NULL);
            
        }
    }

    for (int i = 0; i < argc - 1; i++) 
    {
        waitpid(pids[i], NULL, 0);
    }

    printf("Parent pid: %d\n", (int)getpid());
    return 0;
}

```

