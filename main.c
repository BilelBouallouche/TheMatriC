#include <stdio.h>
#include "matrix.h"
#include "vector.h"

int main()
{
    double m1[3][3] = {{1, 2, 3}, {0, 4, 5}, {0, 0, 6}};
    double m2[3][3] = {{1, 0, 2}, {2, 4, -1}, {-2, 0, 2}};
    double m3[4][4] = {{1, 0, 2, 3}, {2, 0, 4, 6}, {0, 2, 2, 0}, {1, 2, 4, 3}};
    double m4[3][2] = {{31, 32}, {33, 34}, {35, 36}};
    double m5[2][3] = {{1, 2, 3}, {4, 5, 6}};

    matrix matrices[] = {create_matrix(3, 3, m1), create_matrix(3, 3, m2), create_matrix(4, 4, m3), create_matrix(3, 2, m4), create_matrix(2, 3, m5)};


    for (int i = 0; i < 5; i++)
    {
        printf("Matrix %d before:\n", i + 1);
        matrix_pp(matrices[i]);
        row_echelon_form(&matrices[i]);
        printf("Matrix %d row echelon form:\n", i + 1);
        matrix_pp(matrices[i]);
    }

    for(int i = 0; i < 5; i++)
    {
        printf("Det of matrix %d = %f \n", i+1, det(matrices[i]));
    }

    for(int i = 0; i < 5; i++)
    {
        deallocate_matrix(matrices[i]);
    }
    
}