#pragma region 

#define _POSIX_C_SOURCE 200112L

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "FunctionUtilities.h"

#pragma endregion


pthread_barrier_t main_barrier;


double F1_value;
double F2_value;
double F3_value;


void* F1(void* parameters) {
    struct Parameters* p = (struct Parameters*) parameters;
    
    for (int i = 0; i < p->n; i++) {
        double x = getXI(i, p->a, p->b, p->n);
        F1_value = pow(sin(x), 2) * cos(x);

        pthread_barrier_wait(&main_barrier);
        usleep(50);
    }

    return NULL;
}


void* F2(void* parameters) {
    struct Parameters* p = (struct Parameters*) parameters;
    
    for (int i = 0; i < p->n; i++) {
        double x = getXI(i, p->a, p->b, p->n);
        F2_value = pow(cos(x), 2) * sin(x);

        pthread_barrier_wait(&main_barrier);
        usleep(50);
    }

    return NULL;
}


void* F3(void* parameters) {
    struct Parameters* p = (struct Parameters*) parameters;
    
    for (int i = 0; i < p->n; i++) {
        double x = getXI(i, p->a, p->b, p->n);
        F3_value = (1 - pow(cos(x), 2)) * sin(x);

        pthread_barrier_wait(&main_barrier);
        usleep(50);
    }

    return NULL;
}


void main() {
    printf("--------------------------------------------------------------------------\n");
    printf("|                    Vlad Frolov, KV-14 PP-L2, V-18                      |\n");
    printf("--------------------------------------------------------------------------\n");
    printf("|    x    | sin^2(x) * cos(x)  | sin(x) * cos^2(x)  | sin(x)*(1-cos^2(x) |\n");
    printf("--------------------------------------------------------------------------\n");

    pthread_t F1_thread;
    pthread_t F2_thread;
    pthread_t F3_thread;


    struct Parameters F_parameters;

    F_parameters.a = -2 * M_PI;
    F_parameters.b = 0;
    F_parameters.n = 12;


    pthread_barrier_init(&main_barrier, NULL, 4);


    pthread_create(&F1_thread, NULL, &F1, &F_parameters);
    pthread_create(&F2_thread, NULL, &F2, &F_parameters);
    pthread_create(&F3_thread, NULL, &F3, &F_parameters);


    for (int i = 0; i < F_parameters.n; i++) {
        pthread_barrier_wait(&main_barrier);

        printf("| %7d | %18.4lf | %18.4lf | %18.4lf |\n", i, F1_value, F2_value, F3_value);
    }


    printf("--------------------------------------------------------------------------\n");

    pthread_join(F1_thread, NULL);
	pthread_join(F1_thread, NULL);
	pthread_join(F1_thread, NULL);
	pthread_barrier_destroy(&main_barrier);

}
