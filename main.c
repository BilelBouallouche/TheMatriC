#include <stdio.h>
#include "matrix.h"
#include "vector.h"

int main()
{
    matrix idmat = id(3);
    matrix_pp(idmat);
    printf("\n\n");
    double ar1[] = {1, 2, 3};
    double ar2[] = {3, 2, 1};
    double ar3[] = {1, 2, 3};
    matrix mat = create_matrix_from_row_arrays(3, 3, ar1, ar2, ar3);
    matrix_pp(mat);
    vector row1 = get_row(mat, 0);
    vector_pp(row1);
    printf("\n");
    vector mul = mat_mul_vec(mat, row1);
    vector_pp(mul);
    printf("\n mat_mul_mat \n");
    
    double arr1[] = {4, 5, 6};
    double arr2[] = {6, 5, 4};
    double arr3[] = {4, 6, 5};
    matrix mat2 = create_matrix_from_row_arrays(3, 3, arr1, arr2, arr3);
    matrix res = mat_mul_mat(mat, mat2);
    matrix_pp(res);

    printf("transpose \n");
    matrix_pp(transpose(res));
    deallocate_matrix(res);
    deallocate_matrix(mat2);
    deallocate_matrix(mat);
    deallocate_matrix(idmat);
}