#include "cus_maths.h"

double sum_on_double(double *to_sum, unsigned int size)
{
    double res = 0;
    for(int i = 0; i < size; i++)
    {
        res += to_sum[i];
    }
    return res;
}


void max_abs_array(double* array, unsigned int size, double *max, unsigned int *max_index)
{
    double current_max = abs(array[0]);
    unsigned int current_max_index = 0;
    for(int i = 1; i < size; i++)
    {
        if(current_max < abs(array[i]))
        {
            current_max = abs(array[i]);
            current_max_index = i;
        }
    }
    *max_index = current_max_index;
    *max = current_max;
}