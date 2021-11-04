#ifndef _HELPERS_H_
#define _HELPERS_H_

extern double randDoubleInRange_Helpers(double min, double max);
extern double* generateArrayOfRandomDoubles_Helpers(int length, double min, double max);

extern int randIntInRange_Helpers(int min, int max);
extern int *generateArrayOfRandomInts_Helpers(int length, int min, int max);

extern int max(int a, int b);
#endif