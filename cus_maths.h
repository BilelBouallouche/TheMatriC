#ifndef DEF_CUS_MATHS
#define DEF_CUS_MATHS

#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define EPSILON 0.000001

double sum_on_double(double *to_sum, unsigned int size);


void max_abs_array(double* array, unsigned int size, double *max, unsigned int *max_index);

#endif