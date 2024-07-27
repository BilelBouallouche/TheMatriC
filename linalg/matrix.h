#ifndef DEF_MATRIX
#define DEF_MATRIX

#include "vector.h"

typedef struct matrix { 
    unsigned int rows, cols;
    double **elements;
} matrix;

matrix allocate_matrix(unsigned int rows, unsigned int cols);
void deallocate_matrix(matrix mat);

matrix* matrix_deepcopy_ptr(matrix *mat);
void matrix_deepcopy(matrix*, matrix*);

void matrix_pp(matrix mat);

matrix null_matrix(unsigned int rows, unsigned int cols);
matrix eye(unsigned int n);

matrix create_matrix_from_row_arrays(unsigned int rows, unsigned int cols, ...);
matrix create_matrix(unsigned int rows, unsigned int cols, double elem[rows][cols]);
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

unsigned int row_echelon_form(matrix *mat);
int* reduced_row_echelon_form(matrix *mat);



double det(matrix mat);
double tr(matrix mat);


bool is_invertible(matrix mat);

matrix inverse(matrix mat);

unsigned int rank(matrix mat);;

matrix augmented_mat_vec(matrix A, vector b);
matrix augmented_mat_mat(matrix A, matrix B);

void split_mat_col(matrix aug, matrix *lp, matrix *rp, unsigned int split_col);
void split_mat_row(matrix aug, matrix *up, matrix *bp, unsigned int split_row);


vector rref_solve_linear_equations(matrix A, vector b);

void Doolittle_LU_decomposition(matrix A, matrix *L, matrix *U);

#endif