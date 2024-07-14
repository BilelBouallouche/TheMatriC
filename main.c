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
    printf("\n add row 2 to row 1 \n");
    add_row_to_row(&mat, 2, 1);
    matrix_pp(mat);
    deallocate_matrix(mat);
}