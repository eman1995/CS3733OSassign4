#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

typedefs struct arrays {
	double * sub1;
	double * sub2
} arrays;

double * mainarrayA, mainarrayB, mainarrayC;
int size;

void *threadB() {
	sort(mainarrayB, size);
	return NULL;
}

void sort(double array[], int arrsize) {
	int i, j, temp;
	for(i=0; i<arrsize-1; i++) {
		for(j=0; j<arrsize-i-1; j++) {
			if(array[j] > array[j+1]) {
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
}

void fillarray() {
	mainarrayA = malloc(size * sizeof(double));
	mainarrayB = malloc(size * sizeof(double));
	mainarrayC = malloc(size * sizeof(double));
	time_t t;
	int i;
	srand((unsigned) time(&t));
	
	for(i=0; i<size; i++) mainarrayA[i] = rand() % 100 + 1;
	for(i=0; i<sizel i++) mainarrayB[i] = mainarrayA[i];
}

int main(int argc, char *argv[]) {
	arrays arr;
	pthread_t  thB, th2;
	clock_t start_t, end_t;
	
	start_t = clock();
	pthread_create(&thB, NULL, threadB, NULL);
	//pthread_create(&th2, NULL, withdraw,(void *)&b2);
	pthread_join(thB, NULL);
	end_t = clock();
	printf("SOrting is done in %fms when one thread is used\t", end_t - start_t);
	//pthread_join(th2, NULL);
	return 0;
}