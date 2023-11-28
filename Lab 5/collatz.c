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
