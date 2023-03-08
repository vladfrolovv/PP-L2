#ifndef FUNCTION_UTILITIES_H
#define FUNCTIONS_UTILITIES_H

#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

struct Parameters {
    double a, b;
    int n;
};

typedef struct Parameters Parameters;

double getXI(int i, double a, double b, int n);
double h(double a, double b, int n);

#endif