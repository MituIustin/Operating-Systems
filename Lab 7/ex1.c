#include <stdio.h>
#include <pthread.h>
#include <errno.h>


#define MAX_RESOURCES 5

int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx;

int decrease_count(int count) {
    pthread_mutex_lock(&mtx);

    if (available_resources < count) {
        pthread_mutex_unlock(&mtx);
        return -1;
    } else {
        available_resources -= count;
        pthread_mutex_unlock(&mtx);
        return 0;
    }
}

int increase_count(int count) {
    pthread_mutex_lock(&mtx);

    available_resources += count;

    pthread_mutex_unlock(&mtx);

    return 0;
}

void* thread_function(void* arg) {
    int requested_resources = *((int*)arg);

    if (decrease_count(requested_resources) == 0) {
        printf("Got %d resources %d remaining\n", requested_resources, available_resources);

       
        int i, j;
        for (i = 0; i < 1000000; i++) {
            for (j = 0; j < 100; j++) {
                /////////////////
            }
        }

        increase_count(requested_resources);
        printf("Released %d resources %d remaining\n", requested_resources, available_resources);
    } else {
        printf("Not enough resources for %d\n", requested_resources);
    }

    return NULL;
}

int main() {
    if (pthread_mutex_init(&mtx, NULL)) {
        perror(NULL);
        return errno;
    }

    pthread_t threads[3];
    int thread1_resources = 1;
    int thread2_resources = 2;
    int thread3_resources = 3;

    printf("MAX_RESOURCES = %d\n", MAX_RESOURCES);

    pthread_create(&threads[0], NULL, thread_function, (void*)&thread1_resources);
    pthread_create(&threads[1], NULL, thread_function, (void*)&thread2_resources);
    pthread_create(&threads[2], NULL, thread_function, (void*)&thread3_resources);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);

    pthread_mutex_destroy(&mtx);

    return 0;
}
