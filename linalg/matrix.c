#include "matrix.h"

matrix allocate_matrix(unsigned int rows, unsigned int cols)
{
    matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.elements = malloc(sizeof(double*)*rows);
    for(int i = 0; i < rows; i++)
    {
        mat.elements[i] = malloc(sizeof(double) * cols);
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

matrix* matrix_deepcopy(matrix *mat)
{
    matrix *res = malloc(sizeof(matrix));
    res->rows = mat->rows;
    res->cols = mat->cols;
    res->elements = malloc(mat->rows*sizeof(double *));
    for(int i = 0; i < res->rows; i++)
    {
        res->elements[i] = malloc(sizeof(double) * res->cols);
        for(int j = 0; j < res->cols; j++)
        {
            res->elements[i][j] = mat->elements[i][j];
        }
    }
    return res;
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

matrix eye(unsigned int n)
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


matrix create_matrix(unsigned int rows, unsigned int cols, double elem[rows][cols])
{
    matrix mat = allocate_matrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat.elements[i][j] = elem[i][j];
        }
    }
    return mat;
}

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
    for(int i = 0; i < mat->cols; i++)
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

unsigned int row_echelon_form(matrix *mat)
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
        }
        for(int i = k+1; i < mat->rows; i++)
        {
            if(mat->elements[k][k] != 0)
            {
                double factor = -(mat->elements[i][k]/mat->elements[k][k]);
                add_row_to_row(mat, i, k, factor);
            }
        }
    }
    return swap_counter;
}


int* reduced_row_echelon_form(matrix *mat)
{
    row_echelon_form(mat);

    unsigned int num_pivots = 0;
    for(int i = mat->rows-1; i > -1; i--)
    {
       if(!is_null_vec(get_row(*mat, i)))
       {
            num_pivots++;
       }
    }
    int *pivots_cols = malloc(num_pivots*sizeof(int));
    for(int i = mat->rows-1; i > -1; i--)
    {
        if(!is_null_vec(get_row(*mat, i)))
        {   
            int first_non_zero_col = -1;
            int j = 0;
            while(mat->elements[i][j] == 0 && j < mat->cols)
            {
                j++;
            }
            first_non_zero_col = j;
            pivots_cols[i] = j;
            double factor = 1/mat->elements[i][first_non_zero_col];
            scalar_mul_row(mat, i, factor);
        }
    }

    for(int i = mat->rows-1; i > 0; i--)
    {
        if(!is_null_vec(get_row(*mat, i)))
        {
            int pivot_row = i;
            int pivot_col = pivots_cols[i];
            double pivot = mat->elements[pivot_row][pivot_col];
            
            if(pivot !=0)
            {
                for(int u = pivot_row-1; u > -1; u--)
                {
                    double factor = -(mat->elements[u][pivot_col]);
                    add_row_to_row(mat, u, pivot_row, factor);
                }
            }
        }
    }
    return pivots_cols;
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
    matrix *tmp = matrix_deepcopy(&mat);
    int swaps = row_echelon_form(tmp);
    double res = 1;
    for(int i = 0; i < tmp->rows; i++)
    {
        res *= tmp->elements[i][i];
    }
    deallocate_matrix(*tmp);
    free(tmp);

    return pow(-1, swaps)*res;
}


double tr(matrix mat)
{
    if(mat.rows != mat.cols)
    {
        printf("pour calculer la trace faut une matrice carrée\n");
    }
    double res = 0;
    for(int i = 0; i < mat.rows; i++)
    {
        res += mat.elements[i][i];
    }
    return res;
}

unsigned int rank(matrix mat)
{
    unsigned int r = 0;
    matrix *tmp = matrix_deepcopy(&mat);
    row_echelon_form(tmp);
    for(int i = 0; i < tmp->rows; i++)
    {
        vector row_i = get_row(*tmp, i);
        if(!is_null_vec(row_i))
        {
            r++;
        }
    }
    deallocate_matrix(*tmp);
    free(tmp);
    return r;
}

bool is_invertible(matrix mat)
{
    return (det(mat) != 0);
}

matrix augmented_mat_vec(matrix A, vector b)
{
    matrix A_aug = allocate_matrix(A.rows, A.cols +1);
    for(int i = 0; i < A.rows; i++)
    {
        for(int j = 0; j < A.cols; j++)
        {
            A_aug.elements[i][j] = A.elements[i][j];
        }
    }
    for(int i = 0; i < A.rows; i++)
    {
        A_aug.elements[i][A.cols] = b.coords[i];
    }
    return A_aug;
}


matrix augmented_matrix_matrix(matrix A, matrix B)
{
    matrix aug = allocate_matrix(A.rows, A.cols + B.cols);
    for(int i = 0; i < A.rows; i++)
    {
        for(int j = 0; j < A.cols; j++)
        {
            aug.elements[i][j] = A.elements[i][j];
        }
    }
    for(int i = 0; i < A.rows; i++)
    {
        for(int j = A.cols; j < A.rows+B.rows; j++)
        {
            aug.elements[i][j] = B.elements[i][j-A.rows];
        }
    }
    return aug;
}


void split_mat_col(matrix aug, matrix *lp, matrix *rp, unsigned int split_col)
{
    *lp = allocate_matrix(aug.rows, split_col);
    *rp = allocate_matrix(aug.rows, aug.cols-split_col);
    for(int i = 0; i < aug.rows; i++)
    {
        for(int j = 0; j < split_col; j++)
        {
            lp->elements[i][j] = aug.elements[i][j];
        }
        for(int j = split_col; j < aug.cols; j++)
        {
            rp->elements[i][j-split_col] = aug.elements[i][j];
        }
    }
}


void split_mat_row(matrix aug, matrix *up, matrix *bp, unsigned int split_row)
{
    *up = allocate_matrix(split_row, aug.cols);
    *bp = allocate_matrix(aug.rows-split_row, aug.cols); 
    for(int j = 0; j < aug.cols; j++)
    {
        for(int i = 0; i < split_row; i++)
        {
            up->elements[i][j] = aug.elements[i][j];
        }
        for(int i = split_row; i < aug.rows; i++)
        {
            bp->elements[i-split_row][j] = aug.elements[i][j];
        }
    }
}


matrix inverse(matrix mat)
{
    if(!is_invertible(mat))
    {
        printf("the matrix is not invertible. Returning null matrix\n");
        return null_matrix(mat.rows, mat.cols);
    }
    matrix id = eye(mat.rows);
    matrix aug_id = augmented_matrix_matrix(mat, id);
    
    
    reduced_row_echelon_form(&aug_id);
    matrix lp, rp;
    split_mat_col(aug_id, &lp, &rp, id.cols);
    deallocate_matrix(lp);
    deallocate_matrix(id);
    return rp;

}


vector rref_solve_linear_equations(matrix A, vector b)
{
    if(A.cols != b.dim)
    {
        printf("Dimension error \n");
        return null_vector(b.dim);
    }
    matrix A_aug_b = augmented_mat_vec(A, b);
    unsigned int rank_A = rank(A);
    reduced_row_echelon_form(&A);
    reduced_row_echelon_form(&A_aug_b);
    unsigned int rank_aug = rank(A_aug_b);
    if(rank_aug != rank_A)
    {
        printf("No solution for the system\n");
        return null_vector(b.dim);
    }
    vector res = null_vector(b.dim);
    if(rank_aug == A.cols)
    {
        for(int i = 0; i < rank_aug; i++)
        {
            res.coords[i] = A_aug_b.elements[i][A.cols];
        }
        return res;
    }
    /*
    Buggy part, i'll think about it later
    else if (rank_aug < A.cols)
    {
        printf("infinite number of solutions\n");
        
        int num_free_variables = A.cols - rank_aug;
        int first_free_variable = 0;
        printf("number of num_free_variables = %d\n", num_free_variables);
        while(!is_null_vec(get_row(A, first_free_variable)))
        {
            first_free_variable++;
        }
        
        for(int i = 0; i < first_free_variable; i++)
        {
            printf("x_%d = %f", i+1, b.coords[i]);
            for(int j = 0; j < num_free_variables; j++)
            {
                int free_var = first_free_variable+j+1;
                double coeff = -
                printf(" + %f*x_%d", coeff, free_var);
            }
            printf("\n");
        }
    }*/
    deallocate_matrix(A_aug_b);
    return res;
}


void LU_decomposition(matrix A, matrix *L, matrix *U)
{
    if(A.cols != A.rows)
    {
        printf("Error mat is supposed to be squared for a LU decomposition\n");
        return;
    }
    unsigned int n = A.rows;
    *L = allocate_matrix(n, n);
    *U = allocate_matrix(n, n);
    
}