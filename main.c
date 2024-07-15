#include <stdio.h>
#include "matrix.h"
#include "vector.h"

int main()
{
    
    double arr1[] = {4, 5, 6};
    double arr2[] = {6, 5, 4};
    double arr3[] = {4, 6, 5};
    matrix mat = create_matrix_from_row_arrays(3, 3, arr1, arr2, arr3);
    printf("originale\n");
    matrix_pp(mat);
    printf("\n swap 1 et 2 \n");
    swap_row(&mat, 1, 2);
    matrix_pp(mat);
    deallocate_matrix(mat);
}