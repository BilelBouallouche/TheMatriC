#include <stdio.h>
#include "matrix.h"
#include "vector.h"

int main()
{
    /*
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
    //    printf("Rank of matrix %d = %d \n", i+1, rank(matrices[i]));
    }

    for(int i = 0; i < 5; i++)
    {
        deallocate_matrix(matrices[i]);
    }

    double marr[4][4] = {{1, 9, 5, 1}, {2, 0, 4, 6}, {0, 2, 2, 1}, {1, 3, 5, 6}};
    matrix mat = create_matrix(4, 4, marr);
    printf("avant reduction\n");
    matrix_pp(mat);
    printf("apres row echelon\n");
    row_echelon_form(&mat);
    matrix_pp(mat);
    printf("apres reduction \n");
    reduced_row_echelon_form(&mat);
    matrix_pp(mat);
    return 0;*/

   // Matrice 1: 2x3
    double m1[2][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};

    // Matrice 2: 3x2
    double m2[3][2] = {{7.0, 8.0}, {9.0, 10.0}, {11.0, 12.0}};

    // Matrice 3: 4x3
    double m3[4][3] = {{13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}, {19.0, 20.0, 21.0}, {22.0, 23.0, 24.0}};

    // Matrice 4: 2x4
    double m4[2][4] = {{25.0, 26.0, 27.0, 28.0}, {29.0, 30.0, 31.0, 32.0}};

    // Matrice 5: 3x3
    double m5[3][3] = {{33.0, 34.0, 35.0}, {36.0, 37.0, 38.0}, {39.0, 40.0, 41.0}};

    // Matrice 10: 4x4
    double m6[4][4] = {{92.0, 93.0, 94.0, 95.0}, {96.0, 97.0, 98.0, 99.0}, {100.0, 101.0, 102.0, 103.0}, {104.0, 105.0, 106.0, 107.0}};

    matrix matrices[] = {create_matrix(2, 3, m1), create_matrix(3, 2, m2), create_matrix(4, 3, m3), create_matrix(2, 4, m4), create_matrix(3, 3, m5), create_matrix(4, 4, m6)};

    for (int i = 0; i < 6; i++)
    {
        reduced_row_echelon_form(&matrices[i]);
        printf("Matrix %d reduced row echelon form:\n", i + 1);
        matrix_pp(matrices[i]);
    }
}
