#include "FunctionUtilities.h"

double getXI(int i, double a, double b, int n) {
    return(a + i * h(a, b, n));
}


double h(double a, double b, int n) {
    return (a - b) / n;
}