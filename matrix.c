#include "matrix.h"

matrix allocate_matrix(unsigned int rows, unsigned int cols)
{
    matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.elements = malloc(sizeof(double*)*cols);
    for(int i = 0; i < cols; i++)
    {
        mat.elements[i] = malloc(sizeof(double) * rows);
    }
    return mat;
}

void deallocate_matrix(matrix mat)
{
    for(int i = 0; i < mat.rows; i++)
    {
        free(mat.elements[i]);
    }
    free(mat.elements);
    mat.cols = 0;
    mat.rows = 0;
}

void matrix_pp(matrix mat)
{
    for(int i = 0; i < mat.rows; i++)
    {
        printf("( ");
        for(int j = 0; j < mat.cols; j++)
        {
            printf("%f ", mat.elements[i][j]);
        }
        printf(")\n");
    }
    printf("\n");
}

matrix null_matrix(unsigned int rows, unsigned int cols)
{
    matrix null = allocate_matrix(rows, cols);
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j  < cols; j++)
        {
            null.elements[i][j] = 0;
        }
    }
    return null;
}

matrix id(unsigned int n)
{
    matrix identity = null_matrix(n, n);
    for(int i = 0; i  < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j)
            {
                identity.elements[i][j] = 1;
            }
        }
    }
    return identity;
}


matrix create_matrix_from_row_arrays(unsigned int rows, unsigned int cols, ...)
{
    matrix mat = allocate_matrix(rows, cols);
    va_list args;
    va_start(args, cols);
    for(int i = 0; i < rows; i++)
    {
        double * row_i = va_arg(args, double*);
        mat.elements[i] = row_i;
    }
    va_end(args);
    return mat;
}

/*
matrix create_matrix_from_col_arrays(unsigned int rows, unsigned int cols, ...)
{
    matrix mat = allocate_matrix(rows, cols);
    va_list args;
    va_start(args, rows);
    for(int i = 0; i < cols; i++)
    {
        double * cols_i = va_arg(args, double*);
        mat.elements[row] = cols_i;
    }
    va_end(args);
    return mat;
}*/

bool are_mats_equals(matrix mat1, matrix mat2)
{
    if(mat1.rows != mat2.rows || mat1.cols != mat2.cols)
    {
        return false;
    }
    else
    {
        for(int i = 0; i < mat1.rows; i++)
        {
            for(int j = 0; j  < mat1.cols; j++)
            {
                if(mat1.elements[i][j] != mat2.elements[i][j])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

matrix transpose(matrix mat)
{
    matrix transposed = allocate_matrix(mat.cols, mat.rows);
    for(int i = 0; i < transposed.rows; i++)
    {
        for(int j =0; j < transposed.cols; j++)
        {
            transposed.elements[i][j] = mat.elements[j][i];
        }
    }
    return transposed;
}


vector get_col(matrix mat, unsigned int c)
{
    if(c > mat.cols)
    {
        printf("pb get_row c > mat.cols\n");
        return null_vector(mat.rows);
    }
    vector col = allocate_vector(mat.rows);
    for(int i = 0; i < mat.rows; i++)
    {
        col.coords[i] = mat.elements[i][c];
    }
    return col;
}


vector get_row(matrix mat, unsigned int r)
{
    if(r > mat.rows)
    {
        printf("pb get_row r > mat.rows\n");
        return null_vector(mat.cols);
    }
    vector row = allocate_vector(mat.cols);
    for(int i = 0; i < mat.cols; i++)
    {
        row.coords[i] = mat.elements[r][i];
    }
    return row;
}

vector mat_mul_vec(matrix mat, vector vec)
{
    if(mat.rows != vec.dim)
    {
        printf("pb dimension mat_mul_vec, on retourne un vecteur nul\n");
        return null_vector(mat.rows);
    }
    vector res = allocate_vector(mat.rows);
    for(int i = 0; i < mat.rows; i++)
    {
        vector row = get_row(mat, i);
        res.coords[i] = dot(row, vec);
    }
    return res;
}


matrix mat_mul_mat(matrix m1, matrix m2)
{
    if(m1.rows != m2.cols)
    {
        printf("pb dimension mat_mul_mat, on retourne une matrice nulle\n");
        return null_matrix(m1.rows, m2.cols);
    }
    unsigned int rows, cols;
    rows = m1.rows;
    cols = m2.cols;
    matrix res = allocate_matrix(rows, cols);
    for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            res.elements[j][i] = dot(get_row(m1, j), get_col(m2, i));
        }
    }
    return res;
}


/*
void swap_row(matrix *mat, unsigned int r1, unsigned int r2)
{
    unsigned int rows = mat->rows;
    if(r1 > rows || r2 > rows)
    {
        printf("pb de parametre sur swap_row\n");
        return;
    }
    vector row1 = get_row(*mat, r1);
    vector row2 = get_row(*mat, r2);
    for(int i = 0; i < mat->cols; i++)
    {
        mat->elements[r1][i] = row2.coords[i];
        mat->elements[r2][i] = row1.coords[i];
    }
    deallocate_vector(row1);
    deallocate_vector(row2);
}
*/

void swap_row(matrix *mat, unsigned int r1, unsigned int r2)
{
    unsigned int rows = mat->rows;
    if(r1 > rows || r2 > rows)
    {
        printf("pb de parametre sur swap_row\n");
        return;
    }
    for(int i = 0; i < mat->cols; i++)
    {
        double r1_i = mat->elements[r1][i];
        mat->elements[r1][i] = mat->elements[r2][i];
        mat->elements[r2][i] = r1_i;
    }
}

void scalar_mul_row(matrix *mat, unsigned int r, double s)
{
    unsigned int rows = mat->rows;
    if(r > rows)
    {
        printf("pb de parametre sur swap_row\n");
        return;
    }
    for(int i = 0; i < mat->rows; i++)
    {
        mat->elements[r][i] *= s;
    }
}

void add_row_to_row(matrix *mat, unsigned int dest_row, unsigned int src_row, double s)
{
    unsigned int rows = mat->rows;
    if(dest_row > rows || src_row > rows)
    {
        printf("pb de parametre sur swap_row\n");
        return;
    }
    for(int i = 0; i < mat->cols; i++)
    {
        mat->elements[dest_row][i] += s*mat->elements[src_row][i];
    }
}

/*
void row_echelon_form(matrix *mat, bool verbose)
{
    unsigned int pivot_row = 0;
    for(int j = 0; j < mat->cols; j++)
    {
        double max;
        unsigned int max_index;
        double *arr = malloc(sizeof(double)*(mat->rows - pivot_row));
        for(int k = pivot_row+1; k < mat->rows; k++)
        {
            arr[k-pivot_row-1] = mat->elements[k][j];
        }
        max_abs_array(arr, mat->rows - pivot_row, &max, &max_index);
        if(mat->elements[max_index][j] != 0)
        {
            pivot_row++;
            double factor = 1/mat->elements[max_index][j];
            scalar_mul_row(mat, max_index, factor);
            if(max_index != pivot_row)
            {
                swap_row(mat, max_index, pivot_row);
            }
            for(int i = 0; i < mat->rows; i++)
            {
                if(i != pivot_row)
                {
                    factor *= -1.0;
                    scalar_mul_row(mat, i, factor);
                    add_row_to_row(mat, i, pivot_row);
                }
            }
        }
    }
}
*/


unsigned int row_echelon_form(matrix *mat, bool verbose)
{
    int swap_counter = 0;
    for(int k = 0; k < mat->cols; k++)
    {
        int pivot = k;
        for(int i = k+1; i < mat->rows; i++)
        {
            if(abs(mat->elements[i][k]) > abs(mat->elements[pivot][k]))
            {
                pivot = i;
            }
        }
        if(pivot != k)
        {
            swap_row(mat, k, pivot);
            swap_counter++;
            if(verbose)
            {
                printf("swapping row %u with row %u : ", k, pivot);
                matrix_pp(*mat);
            }
        }
        for(int i = k+1; i < mat->rows; i++)
        {
            double factor = -(mat->elements[i][k]/mat->elements[k][k]);
            add_row_to_row(mat, i, k, factor);
            if(verbose)
            {
                matrix_pp(*mat);
            }
        }
    }
    return swap_counter;
}


double det(matrix mat)
{
    if(mat.rows != mat.cols)
    {
        printf("pour calculer le determinant faut une matrice carrée\n");
        return 0;
    }

    if(mat.rows == 2)
    {
        return mat.elements[0][0]*mat.elements[1][1] - mat.elements[0][1]*mat.elements[1][0];
    }
    matrix tmp = mat;
    int swaps = row_echelon_form(&tmp, false);
    double res = 1;
    for(int i = 0; i < tmp.rows; i++)
    {
        res *= tmp.elements[i][i];
    }
    return pow(-1, swaps)*res;
}


double tr(matrix mat)
{
    if(mat.rows != mat.cols)
    {
        printf("pour calculer la trace faut une matrice carrée\n");
    }
    double res;
    for(int i = 0; i < mat.rows; i++)
    {
        res += mat.elements[i][i];
    }
    return res;
}



bool is_invertible(matrix mat)
{
    return (det(mat) != 0);
}