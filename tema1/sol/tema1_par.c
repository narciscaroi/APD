/*
 * APD - Tema 1
 * Octombrie 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

char *in_filename_julia;
char *in_filename_mandelbrot;
char *out_filename_julia;
char *out_filename_mandelbrot;
int NUM_THREADS; //numarul de threaduri

//dimensiunile folosite pentru matricea algoritmului Julia
int height_julia, width_julia;
//dimensiunile folosite pentru matricea algoritmului Mandelbrot
int height_mandelbrot, width_mandelbrot;

//Matricea rezultata al algoritmului Julia
int **result_julia;
//Matricea rezultata al algoritmului Mandelbrot
int **result_mandelbrot;

//declararea barierei
pthread_barrier_t barrier;

// structura pentru un numar complex
typedef struct _complex {
	double a;
	double b;
} complex;

// structura pentru parametrii unei rulari
typedef struct _params {
	int is_julia, iterations;
	double x_min, x_max, y_min, y_max, resolution;
	complex c_julia;
} params;

//declararea structurii pentru Julia
params *par_julia;
//declararea structurii pentru Mandelbrot
params *par_mandelbrot;

// citeste argumentele programului
void get_args(int argc, char **argv)
{
	if (argc < 6) {
		printf("Numar insuficient de parametri:\n\t"
				"./tema1 fisier_intrare_julia fisier_iesire_julia "
				"fisier_intrare_mandelbrot fisier_iesire_mandelbrot\n");
		exit(1);
	}

	in_filename_julia = argv[1];
	out_filename_julia = argv[2];
	in_filename_mandelbrot = argv[3];
	out_filename_mandelbrot = argv[4];
	//preiau din argumentele rularii programului numarul de threaduri
	NUM_THREADS = atoi(argv[5]);
}

// citeste fisierul de intrare
void read_input_file(char *in_filename, params* par)
{
	FILE *file = fopen(in_filename, "r");
	if (file == NULL) {
		printf("Eroare la deschiderea fisierului de intrare!\n");
		exit(1);
	}

	fscanf(file, "%d", &par->is_julia);
	fscanf(file, "%lf %lf %lf %lf",
			&par->x_min, &par->x_max, &par->y_min, &par->y_max);
	fscanf(file, "%lf", &par->resolution);
	fscanf(file, "%d", &par->iterations);

	if (par->is_julia) {
		fscanf(file, "%lf %lf", &par->c_julia.a, &par->c_julia.b);
	}

	fclose(file);
}

// scrie rezultatul in fisierul de iesire
void write_output_file(char *out_filename, int **result, int width, int height)
{
	int i, j;

	FILE *file = fopen(out_filename, "w");
	if (file == NULL) {
		printf("Eroare la deschiderea fisierului de iesire!\n");
		return;
	}

	fprintf(file, "P2\n%d %d\n255\n", width, height);
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			fprintf(file, "%d ", result[i][j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}


// aloca memorie pentru rezultat
int **allocate_memory(int width, int height)
{
	int **result;
	int i;
	printf("%d \n", height);
	result = malloc(height * sizeof(int*));
	if (result == NULL) {
		printf("Eroare la malloc!\n");
		exit(1);
	}

	for (i = 0; i < height; i++) {
		result[i] = malloc(width * sizeof(int));
		if (result[i] == NULL) {
			printf("Eroare la malloc!\n");
			exit(1);
		}
	}

	return result;
}

// elibereaza memoria alocata
void free_memory(int **result, int height)
{
	int i;

	for (i = 0; i < height; i++) {
		free(result[i]);
	}
	free(result);
}

void init_params() {
	//julia - initializare
	par_julia = (params*) malloc(sizeof(params));
	if(par_julia == NULL){
		printf("Eroare la malloc: par_julia\n");
		exit(1);
	}
	read_input_file(in_filename_julia, par_julia);
	width_julia = (par_julia->x_max - par_julia->x_min) / par_julia->resolution;
	height_julia = (par_julia->y_max - par_julia->y_min) / par_julia->resolution;
	result_julia = allocate_memory(width_julia, height_julia);

	//mandelbrot - initializare
	par_mandelbrot = (params*) malloc(sizeof(params));
	if(par_mandelbrot == NULL){
		printf("Eroare la malloc: par_mandelbrot\n");
		exit(1);
	}
	read_input_file(in_filename_mandelbrot, par_mandelbrot);
	width_mandelbrot = (par_mandelbrot->x_max - par_mandelbrot->x_min) / par_mandelbrot->resolution;
	height_mandelbrot = (par_mandelbrot->y_max - par_mandelbrot->y_min) / par_mandelbrot->resolution;
	result_mandelbrot = allocate_memory(width_mandelbrot, height_mandelbrot);
}

void compute_julia_result(int start_julia, int end_julia, int w, int h){

	//paralelizez pe coloane
	for (w = start_julia; w < end_julia; w++) {
		//algoritmul din schelet
		for (h = 0; h < height_julia; h++) {
			int step = 0;
			complex z = { .a = w * par_julia->resolution + par_julia->x_min,
							.b = h * par_julia->resolution + par_julia->y_min };

			while (sqrt(pow(z.a, 2.0) + pow(z.b, 2.0)) < 2.0 && step < par_julia->iterations) {
				complex z_aux = { .a = z.a, .b = z.b };

				z.a = pow(z_aux.a, 2) - pow(z_aux.b, 2) + par_julia->c_julia.a;
				z.b = 2 * z_aux.a * z_aux.b + par_julia->c_julia.b;

				step++;
			}
			/*am modificat pentru a trece direct din coordonate matematice
			in coordonate ecran, fara a mai fi nevoie de for-ul din schelet*/
			result_julia[height_julia - h - 1][w] = step % 256;
		}
	}

}

void compute_mandelbrot_result(int start_mandelbrot, int end_mandelbrot, int w, int h){
	for (w = start_mandelbrot; w < end_mandelbrot; w++) {
		for (h = 0; h < height_mandelbrot; h++) {
			complex c = { .a = w * par_mandelbrot->resolution + par_mandelbrot->x_min,
							.b = h * par_mandelbrot->resolution + par_mandelbrot->y_min };
			complex z = { .a = 0,.b = 0 };
			int step = 0;

			while (sqrt(pow(z.a, 2.0) + pow(z.b, 2.0)) < 2.0 && step < par_mandelbrot->iterations) {
				complex z_aux = { .a = z.a,.b = z.b };

				z.a = pow(z_aux.a, 2.0) - pow(z_aux.b, 2.0) + c.a;
				z.b = 2.0 * z_aux.a * z_aux.b + c.b;

				step++;
			}

			result_mandelbrot[height_mandelbrot - h - 1][w] = step % 256;
		}
	}

}

void* thread_function(void* arg) {

	int w = 0, h = 0;
	int thread_id = *(int *)arg;
	//initializez start si end cu formula din laboratoare si curs
	int start_julia = thread_id * width_julia / NUM_THREADS;
	int end_julia = min((thread_id + 1) * width_julia / NUM_THREADS, width_julia);

	compute_julia_result(start_julia, end_julia, w, h);

	//am pus bariera ca threadurile sa astepte rezultatul urmatoarelor thread-uri
	pthread_barrier_wait(&barrier);
	/*doar thread-ul "main" face scrierea in fisier
	cum am facut la exercitiul din laborator cu merge sort*/
	if(thread_id == 0){
		write_output_file(out_filename_julia, result_julia, width_julia, height_julia);
	}
	
	//aceeasi logica ca la algoritmul Julia
	int start_mandelbrot = thread_id * width_mandelbrot/ NUM_THREADS;
	int end_mandelbrot = min((thread_id + 1) * width_mandelbrot / NUM_THREADS, width_mandelbrot);

	compute_mandelbrot_result(start_mandelbrot, end_mandelbrot, w, h);

	pthread_barrier_wait(&barrier);

	if(thread_id == 0){
		write_output_file(out_filename_mandelbrot, result_mandelbrot, width_mandelbrot, height_mandelbrot);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	// se citesc argumentele programului
	get_args(argc, argv);

	/*initializez variabile pentru alg Julia si Mandelbrot ca in scheletul dat
	doar ca acum fiecare are variabilele sale*/
	init_params();

	//initializez bariera
	pthread_barrier_init(&barrier, NULL, NUM_THREADS);

	pthread_t threads[NUM_THREADS];
	int arguments[NUM_THREADS];
	void *status;
	int i, r;

	for (i = 0; i < NUM_THREADS; i++) {
		arguments[i] = i;
		r = pthread_create(&threads[i], NULL, thread_function, &arguments[i]);

		if (r) {
			printf("Eroare la crearea thread-ului %d\n", i);
			exit(-1);
		}
	}

	for (i = 0; i < NUM_THREADS; i++) {
		r = pthread_join(threads[i], &status);

		if (r) {
			printf("Eroare la asteptarea thread-ului %d\n", i);
			exit(-1);
		}

	}

	free_memory(result_julia, height_julia);
	free_memory(result_mandelbrot, height_mandelbrot);
	pthread_barrier_destroy(&barrier);

	return 0;
}
