#include <stdio.h>
#include "matrix.h"
#include "vector.h"

int main()
{
    
    double m1_arr1[] = {1, 2, 3};
    double m1_arr2[] = {0, 4, 5};
    double m1_arr3[] = {0, 0, 6};
    matrix m1 = create_matrix_from_row_arrays(3, 3, m1_arr1, m1_arr2, m1_arr3);
    printf("det de m1 = %f\n", det(m1));

    double m2_arr1[] = {1, 0, 2};
    double m2_arr2[] = {2, 4, -1};
    double m2_arr3[] = {-2, 0, 2};
    matrix m2 = create_matrix_from_row_arrays(3, 3, m2_arr1, m2_arr2, m2_arr3);
    printf("det de m2 = %f\n", det(m2));

    double m3_arr1[] = {1, 4, 4};
    double m3_arr2[] = {2, 5, 6};
    double m3_arr3[] = {0, 8, 9};
    matrix m3 = create_matrix_from_row_arrays(3, 3, m3_arr1, m3_arr2, m3_arr3);
    printf("det de m3 = %f\n", det(m3));

    double m4_arr1[] = {0, 1, 1, 0};
    double m4_arr2[] = {1, 0, 0, 1};
    double m4_arr3[] = {1, 1, 0, 1};
    double m4_arr4[] = {1, 1, 1, 0};
    matrix m4 = create_matrix_from_row_arrays(4, 4, m4_arr1, m4_arr2, m4_arr3, m4_arr4);
    printf("det de m4 = %f\n", det(m4));
    
    deallocate_matrix(m1);
    deallocate_matrix(m2);
    deallocate_matrix(m3);
    deallocate_matrix(m4);
}