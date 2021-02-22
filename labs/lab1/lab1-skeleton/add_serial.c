#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
    schelet pentru exercitiul 5
*/
#define NUM_THREADS 12
#define min(a,b) ((a) < (b) ? (a) : (b))

int* arr;
int array_size;

void *f(void *arg) {
    long id = *(long*) arg;
    int start = id * array_size / NUM_THREADS;
    int end = min((id + 1) * array_size / NUM_THREADS, array_size);

    for(int i = start; i < end; i++){
        arr[i] +=100;
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("Specificati dimensiunea array-ului\n");
        exit(-1);
    }

    array_size = atoi(argv[1]);

    arr = malloc(array_size * sizeof(int));
    for (int i = 0; i < array_size; i++) {
        arr[i] = i;
    }

   /* for (int i = 0; i < array_size; i++) {
        printf("%d", arr[i]);
        if (i != array_size - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }*/

    // TODO: aceasta operatie va fi paralelizata
    printf("task5\n");
    pthread_t threads [NUM_THREADS];
    long arguments [NUM_THREADS];
    int r;
    long id;
    void *status;

  	for (id = 0; id < NUM_THREADS; id++) {
        arguments[id] = id;
        r = pthread_create(&threads[id], NULL, f, &arguments[id]);

        if (r) {
            printf("Eroare la crearea thread-ului %ld\n", id);
            exit(-1);
        }
    }

    for (id = 0; id < NUM_THREADS; id++) {
        r = pthread_join(threads[id], &status);

        if (r) {
            printf("Eroare la asteptarea thread-ului %ld\n", id);
            exit(-1);
        }
    }

    /*for (int i = 0; i < array_size; i++) {
        printf("%d", arr[i]);
        if (i != array_size - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }*/

  	pthread_exit(NULL);
}
