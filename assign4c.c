#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

typedef struct arrays {
	double * sub1;
	double * sub2;
} arrays;

double * mainarrayA;
double * mainarrayB;
double * mainarrayC;
int size;

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

void *threadB(void *args) {
    sort(mainarrayB, size);
    return NULL;
}

void *threadA1(void *args) {
    arrays *temp = (arrays *)args;
    sort(temp->sub1, size/2 + 1);
    return NULL;
}

void *threadA2(void *args) {
    arrays *temp = (arrays *)args;
    sort(temp->sub2, size/2 +1);
    return NULL;
}

void *mergeThread(void *args) { 
    arrays *temp = (arrays *)args;
    int i, j=0, k=0;
    for(i=0; i<size; i++) {
        if(temp->sub1[j] < temp->sub2[k]) { 
            mainarrayC[i] = temp->sub1[j++];
        }
        else if(temp->sub1[j] > temp->sub2[k]) { 
            mainarrayC[i] = temp->sub2[k++];
        }
        else {
            mainarrayC[i] = temp->sub1[j++];
        }    
    }
    return NULL;
}

void fillarray() {
	mainarrayA = malloc(size * sizeof(double));
	mainarrayB = malloc(size * sizeof(double));
	mainarrayC = malloc(size * sizeof(double));
	time_t t;
	int i;
	srand((unsigned) time(&t));
	
	for(i=0; i<size; i++) mainarrayA[i] = rand() % 100 + 1;
	for(i=0; i<size; i++) mainarrayB[i] = mainarrayA[i];
}

void copyarray(arrays *array) {
    //array.sub1 = malloc(((size/2) + 1) * sizeof(double));
    //array.sub2 = malloc(((size/2) + 1) * sizeof(double));
    int i;
    for(i=0; i<size/2; i++) { 
        array->sub1[i] = mainarrayA[i];
        //printf("%.1f\n", array.sub1[i]);
    }
    for(i=size/2; i<size; i++) {
        array->sub2[i] = mainarrayA[i];
       //printf("%.1f\n", array.sub2[i]);
    }
    //printf("%d\n", size/2);
}

int main(int argc, char *argv[]) {
	size = atoi(argv[1]);
    arrays arr;
	pthread_t  thB, thA1, thA2, thM;
	clock_t start_t, end_t;
    double duration;
    
    arr.sub1 = malloc((size/2 + 1) * sizeof(double));
    arr.sub2 = malloc((size/2 + 1) * sizeof(double));

    fillarray();
	//fine
	start_t = clock();
	pthread_create(&thB, NULL, threadB, (void *)&arr);
	pthread_join(thB, NULL);
	end_t = clock();
    
    duration = (double)(end_t - start_t);
	printf("Sorting is done in %.1fms when one thread is used\n", duration); 
    
    copyarray(&arr);
    
    start_t = clock();
    pthread_create(&thA1, NULL, threadA1, (void *)&arr);
    pthread_create(&thA2, NULL, threadA2, (void *)&arr);
    pthread_join(thA1, NULL);
    pthread_join(thA2, NULL);
    pthread_create(&thM, NULL, mergeThread, (void *)&arr);
    pthread_join(thM, NULL);
    end_t = clock();

    duration = (double)(end_t - start_t);
    printf("Sorting is done in %.1fms when two threads are used\n", duration);
    
	return 0;
}
