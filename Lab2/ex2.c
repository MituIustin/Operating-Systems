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
    ssize_t bytesRead, bytesWritten;

    while ((bytesRead = read(sourceFile, buffer, sizeof(buffer))) > 0) 
    {
        bytesWritten = write(destinationFile, buffer, bytesRead);
    }

    close(sourceFile);
    close(destinationFile);

    printf("File copy successful: %s -> %s\n", argv[1], argv[2]);

    return 0;
}
