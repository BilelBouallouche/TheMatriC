#ifndef DEF_MATRIX
#define DEF_MATRIX

#include "vector.h"

typedef struct matrix {
    unsigned int rows, cols;
    double **elements;
} matrix;

matrix allocate_matrix(unsigned int rows, unsigned int cols);
void deallocate_matrix(matrix mat);

void matrix_pp(matrix mat);

matrix null_matrix(unsigned int rows, unsigned int cols);
matrix id(unsigned int n);

matrix create_matrix_from_row_arrays(unsigned int rows, unsigned int cols, ...);
//matrix create_matrix_from_col_arrays(unsigned int rows, unsigned int cols, ...);

bool are_mats_equals(matrix mat1, matrix mat2);

matrix transpose(matrix mat);

vector get_col(matrix mat, unsigned int col);
vector get_row(matrix mat, unsigned int row);

vector mat_mul_vec(matrix mat, vector vec);
matrix mat_mul_mat(matrix m1, matrix m2);

void swap_row(matrix *mat, unsigned int r1, unsigned int r2);
void scalar_mul_row(matrix *mat, unsigned int r, double s);
void add_row_to_row(matrix *mat, unsigned int dest_row, unsigned int src_row, double s);

unsigned int row_echelon_form(matrix *mat, bool verbose);

double det(matrix mat);
double tr(matrix mat);

bool is_invertible(matrix mat);

#endif