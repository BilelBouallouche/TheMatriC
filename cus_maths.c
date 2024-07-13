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