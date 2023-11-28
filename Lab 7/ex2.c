#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int count;           
    int total_threads;    
    pthread_mutex_t mutex;
    sem_t sem;
} Barrier;

Barrier barrier; 


void init_barrier(Barrier *barrier, int total_threads) {
    barrier->count = 0;
    barrier->total_threads = total_threads;
    pthread_mutex_init(&barrier->mutex, NULL);
    sem_init(&barrier->sem, 0, 0);
}


void barrier_point(Barrier *barrier) {
    pthread_mutex_lock(&barrier->mutex);

    barrier->count++;

    if (barrier->count < barrier->total_threads) {
        pthread_mutex_unlock(&barrier->mutex);
        sem_wait(&barrier->sem);
    } else {

        barrier->count = 0;
        sem_post(&barrier->sem);

        for (int i = 1; i < barrier->total_threads; i++) {
            sem_post(&barrier->sem);
        }

        pthread_mutex_unlock(&barrier->mutex);
    }
}


void *tfun(void *v) {
    int *tid = (int *)v;
    printf("%d reached the barrier\n", *tid);
    barrier_point(&barrier);
    printf("%d passed the barrier\n", *tid);
    free(tid);
    return NULL;
}



int main() {
    int number_of_threads = 5;
    pthread_t threads[number_of_threads];

    printf("Number of threads = %d\n", number_of_threads);

    init_barrier(&barrier, number_of_threads);

    for (int i = 0; i < number_of_threads; i++) {
        int *tid = malloc(sizeof(int));
        *tid = i;
        pthread_create(&threads[i], NULL, tfun, tid);
    }

    for (int i = 0; i < number_of_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&barrier.mutex);
    sem_destroy(&barrier.sem);

    return 0;
}
