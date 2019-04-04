#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
typedef struct arrays {
    double * sub1;
    double * sub2;
} arrays;

double * mainarray;
int size;

void *thread1(void *args) {
    arrays *temp = (arrays *)args;
    temp->sub1 = malloc((size/2) * sizeof(double));
}

void *thread2(void *args) {
    arrays *temp = (arrays *)args;
    temp->sub2 = malloc((size/2) * sizeof(double));
}

void *thread3(void *args) { 
    arrays *temp = (arrays *)args;
}
void sort(double array[],int arrsize) {
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

//fills
void fillarray() {
    mainarray = malloc(size *sizeof(double));
    time_t t;
    int i;
    srand((unsigned) time(&t));
    
    for(i=0; i < size; i++) mainarray[i] = rand() % 100 + 1;
    
    //printf("%d\n", size);
    //printf("%f\n", mainarray[542]);
}

int main(int argc, char *argv[]){
    
    if(argc != 2){
        fprintf(stderr, "Error: Usage ./assign4c.c N\n");
        exit(1);
    }
    
    arrays sortit;
    size = atoi(argv[1]);
    fillarray();
    sort(mainarray, size);
    int i;
    for(i=0; i<120; i++) printf("%f\n", mainarray[i]);

    pthread_t th1, th2, th3;
    
    //pthread_create(&th1, NULL, thread1, (void *)&mainarray);
    //pthread_create(&th2, NULL, thread2, (void *)&mainarray);
    
    return 0;
}
