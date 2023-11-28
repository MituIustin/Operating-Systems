# Ex 1 + Ex 2

Ipoteza Collatz spune ca plecand de la orice numar natural daca aplicam
repetat urmatoarea operatie


f(n) = n / 2 , daca n este par

f(n) = n * 3 + 1, daca n este impar


sirul ce rezulta va atinge valoarea 1. Implementati un program care sa
testeze ipoteza Collatz pentru mai multe numere date folosind memorie
partajata.

Indicatii: Pornind de la un singur proces parinte, este creat cate un
copil care se ocupa de un singur numar si scrie sirul rezultant undeva
in memoria partajata. Parintele va crea obiectul de memorie partajata
folosind shm_open(3) si ftruncate(2) si pe urma va incarca in memorie
intreg spatiul pentru citirea rezultatelor cu mmap(2).
O conventie trebuie stabilita intre parinte si copii, astfel incat fiecare copil
sa aiba acces exclusiv la o parte din memoria partajata unde isi va scrie
datele (ex. impartim memoria in mod egal pentru fiecare copil). Astfel, fiecare copil va incarca doar zona dedicata lui pentru scriere folosind
dimensiunea cuvenita si un deplasament nenul in mmap(2). Parintele va
astepta ca fiecare copil sa termine executia, dupa care va scrie pe ecran
rezultatele obtinute de copiii sai.
Programul va demonstra acest comportament folosind functiile getpid(2)
si getppid(2).


In programul anterior folositi shm_unlink(3) si munmap(2) pentru a elibera resursele folosite.


```ssh-session
gcc ex1.c -o ex1
```


```ssh-session
./ex1 26 38 14 5 9
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

int main(int argc, char *argv[])
{
    char shm_name[] = "myshm";
    int shm_fd;
    shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd < 0)
    {
        perror(NULL);
        return errno;
    }

    size_t shm_size = (argc - 1) * 4096;

    if (ftruncate(shm_fd, shm_size) == -1)
    {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    pid_t pids[argc - 1];

    for (int i = 1; i < argc; i++)
    {
        pids[i - 1] = fork();
        if (pids[i - 1] < 0)
        {
            perror("fork");
            exit(errno);
        }
        else if (pids[i - 1] == 0)
        {
            printf("Child pid: %d\n", (int)getpid());

            char offset_str[16];
            sprintf(offset_str, "%d", (i - 1) * 4096);
            char *argvv[] = {"collatz", argv[i], offset_str, NULL};
            execve("/home/iustin/Desktop/lab5/collatz", argvv, NULL);

            // Aici este important să gestionați cazul în care execve() întoarce eroare
            perror("execve");
            exit(errno);
        }
    }

    for (int i = 0; i < argc - 1; i++)
    {
        waitpid(pids[i], NULL, 0);
    }

    void *shm_ptr = mmap(0, shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED)
    {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    int *data = (int *)shm_ptr;
    int count = shm_size / sizeof(int);

    for (int i = 0; i < count; i++)
    {
        if (data[i] == -1)
            printf("\n");
        else if (data[i] != 0)
            printf("%d ", data[i]);
    }
    printf("\n");
    printf("Parent pid: %d\n", (int)getpid());

    munmap(shm_ptr, shm_size);
    close(shm_fd);
    shm_unlink(shm_name);

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
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>

void collatz(int n, int* shared_memory) 
{
    

    int result[4096]; 
    int count = 0;
    while (n != 1) {
        result[count++] = n;
        if (n % 2 == 0)
            n = n / 2;
        else
            n = 3 * n + 1;
    }
    result[count] = 1;
    shared_memory[count + 1] = -1;
    memcpy(shared_memory, result, (count + 1) * sizeof(int));
}

int main(int argc, char* argv[])
{
    int shm_fd;
    char shm_name[] = "myshm";
    void* shm_ptr;

    shm_fd = shm_open(shm_name, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror(NULL);
        return errno;
    }


    shm_ptr = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, atoi(argv[2]));
    if (shm_ptr == MAP_FAILED) {
        perror(NULL);
        return errno;
    }

    collatz(atoi(argv[1]), shm_ptr);


    return 0;
}
```
