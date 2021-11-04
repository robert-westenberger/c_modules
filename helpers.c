#include <stdlib.h>
#include <limits.h>
#include <math.h>
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

int randIntInRange_Helpers(int min, int max)
{   
    if (min == INT_MIN && max == INT_MAX) {
        const int BITS_PER_RAND = (int)(log2(RAND_MAX / 2 + 1) + 1.0); /* Or log(RAND_MAX + 1) / log(2) with older language standards */
        int ret = 0;
        for (int i = 0; i < sizeof(int) * CHAR_BIT; i += BITS_PER_RAND)
        {
            ret <<= BITS_PER_RAND;
            ret |= rand();
        }
        return ret;
    }
    int test = (max - min + 1) + min;
    int num = (rand() % (max - min + 1)) + min;
    return num;
}
int *generateArrayOfRandomInts_Helpers(int length, int min, int max)
{
    int *arr = malloc(length * sizeof(int));
    for (int i = 0; i < length; i++)
    {
        *(arr + i) = randIntInRange_Helpers(min, max);
    }
    return arr;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}