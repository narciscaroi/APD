#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 2

void *f(void *arg) {
  	long id = *(long*) arg;
  	//printf("TASK3\n");
  	//for(int i = 0; i < 100; i++){
  		printf("Hello World din thread-ul %ld!\n", id);
  	//}
  	pthread_exit(NULL);
}

void *fth1(void *arg){
	long id = *(long*) arg;
	printf("Functia pentru thread-ul %ld\n\n",id);
	pthread_exit(NULL);
}

void *fth2(void *arg){
	long id = *(long*) arg;
	printf("Functia pentru thread-ul %ld\n\n",id);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
  	int r;
  	long id;
  	void *status;
  	long arguments[NUM_THREADS];

  	printf("task1\n");
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

  	printf("task2\n");
  	long cores = sysconf(_SC_NPROCESSORS_CONF);
  	long arguments2[cores];
  	pthread_t threads2[cores];

  	for (id = 0; id < cores; id++) {
  		arguments2[id] = id;
		r = pthread_create(&threads2[id], NULL, f, &arguments2[id]);

		if (r) {
	  		printf("Eroare la crearea thread-ului %ld\n", id);
	  		exit(-1);
		}
  	}

  	for (id = 0; id < cores; id++) {
		r = pthread_join(threads2[id], &status);

		if (r) {
	  		printf("Eroare la asteptarea thread-ului %ld\n", id);
	  		exit(-1);
		}
  	}

  	printf("task4\n");
  	r = pthread_create(&threads[0],NULL,fth1,&arguments[0]);
  	if (r) {
	  		printf("Eroare la crearea thread-ului %ld\n", id);
	  		exit(-1);
		}

	r = pthread_create(&threads[1],NULL,fth2,&arguments[1]);
  	if (r) {
	  		printf("Eroare la crearea thread-ului %ld\n", id);
	  		exit(-1);
		}
		
	r = pthread_join(threads[0], &status);

		if (r) {
	  		printf("Eroare la asteptarea thread-ului %ld\n", id);
	  		exit(-1);
		}
	r = pthread_join(threads[0], &status);

		if (r) {
	  		printf("Eroare la asteptarea thread-ului %ld\n", id);
	  		exit(-1);
		}
  	pthread_exit(NULL);
}
