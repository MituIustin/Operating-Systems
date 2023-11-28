# Ex 1

Rescrieti programul HelloWorld de data trecuta folosind numai functii sistem.

```sh-session
gcc ex1.c  -o ex1
./ex1
```

ex1.c 

```c
#include <unistd.h>

int main() {

    char message[] = "Hello world!\n";
    write(1, message, sizeof(message) - 1);

    -- 1 inseama output in consola

    return 0;
}
```

# Ex 2

Scrieti un program care sa primeasca la intrare in primul argument
un fisier sursa pe care sa-l copieze intr-un alt fisier cu numele primit in al
doilea argument.

```sh-session
gcc ex2.c  -o ex2
./ex2 fisier1.txt fisier2.txt
```


```c
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
  

    int sourceFile = open(argv[1], O_RDONLY);
    if (sourceFile == -1) {
        perror("Error opening source file");
        return errno;
    }

    
    int destinationFile = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (destinationFile == -1) {
        perror("Error opening destination file");
        return errno;
    }


    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while ((bytesRead = read(sourceFile, buffer, sizeof(buffer))) > 0) 
    {
        write(destinationFile, buffer, bytesRead);
    }

    close(sourceFile);
    close(destinationFile);

    printf("File copy successful: %s -> %s\n", argv[1], argv[2]);

    return 0;
}
```

