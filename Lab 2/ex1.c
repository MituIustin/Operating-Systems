#include <unistd.h>

int main() {

    char message[] = "Hello world!\n";
    write(1, message, sizeof(message) - 1);

    return 0;
}