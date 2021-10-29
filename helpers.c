#include <stdlib.h>
#include "helpers.h"

double randDoubleInRange_Helpers(double min, double max) {
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}
double *generateArrayOfRandomDoubles_Helpers(int length, double min, double max) {
    double *arr = malloc(length * sizeof(double));
    for (int i = 0; i < length; i++)
    {
        *(arr + i) = randDoubleInRange_Helpers(min, max);
    }
    return arr;
}