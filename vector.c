#include "vector.h"
#include <math.h>
#include <stdio.h>


vector allocate_vector(unsigned int dim)
{
    vector vec;
    vec.dim = dim;
    vec.coords = malloc(sizeof(double)* dim);
    return vec;
}


void deallocate_vector(vector vec)
{
    free(vec.coords);
    vec.coords = NULL;
    vec.dim = 0;
}


vector null_vector(unsigned int dim)
{
    vector vec_null = allocate_vector(dim);
    for(int i = 0; i < dim; i++)
    {
        vec_null.coords[i] = 0;
    }
    return vec_null;
}


vector create_vector(unsigned int dim, ...)
{
    vector vec = allocate_vector(dim);
    va_list args;
    va_start(args, dim);
    for(int i = 0; i < dim; i++)
    {
        vec.coords[i] = va_arg(args, double);
    }
    va_end(args);
    return vec;
}

vector array_to_vector(double *array, unsigned int size)
{
    vector vec = allocate_vector(size);
    for(int i = 0; i < size; i++)
    {
        vec.coords[i] = array[i];
    }
    return vec;
}


void add_vector_to(vector* vec, vector vec2)
{
    if(vec == NULL || vec->coords == NULL || vec->dim != vec2.dim)
    {
        return;
    }
    for(int i = 0; i < vec2.dim; i++)
    {
        vec->coords[i] += vec2.coords[i];
    }
}

vector add_vectors(vector vec1, vector vec2)
{
    if(vec1.dim != vec2.dim)
    {
        return null_vector(vec1.dim);
    }
    unsigned int dim = vec1.dim;
    
    vector vec = allocate_vector(dim);
    for(int i = 0; i < dim; i++)
    {
        vec.coords[i] = vec1.coords[i] + vec2.coords[i];
    }
    return vec;
}

void scalar_mul_to(double scalar, vector* vec)
{
    if(vec == NULL || vec->coords == NULL)
    {
        return;
    }
    for(int i = 0; i < vec->dim; i++)
    {
        vec->coords[i] *= scalar;
    }
}

vector scalar_mul(double scalar, vector vec)
{
    unsigned int dim = vec.dim;
    vector res = allocate_vector(dim);
    for(int i = 0; i < dim; i++)
    {
        res.coords[i] = vec.coords[i] * scalar;
    }
    return res;
}

vector sub_vectors(vector vec1, vector vec2)
{
    oppose_coord(&vec2);
    return add_vectors(vec1, vec2);
}

void oppose_coord(vector *vec)
{
    scalar_mul_to(-1, vec);
}


bool are_vector_same_dim(vector u, vector v)
{
    return u.dim == v.dim;
}

bool are_vectors_equals(vector u, vector v)
{
    if(are_vector_same_dim(u, v))
    {
        for(int i = 0; i < u.dim; i++)
        {
            if(u.coords[i] != v.coords[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

double dot(vector u, vector v)
{
    if(are_vector_same_dim(u, v))
    {
        double* to_sum = malloc(sizeof(double)*u.dim);
        for(int i = 0; i < u.dim; i++)
        {
            to_sum[i] = u.coords[i]*v.coords[i];
        }
        return sum_on_double(to_sum, u.dim);
    }
    else
    {
        printf("erreur dimension, on retourne 0 arbitrairement pour l'instant");
        return 0;
    }
}



vector cross_product(vector u, vector v)
{
    if (u.dim != 3 && v.dim != 3)
    {
        vector res = allocate_vector(3);

        res.coords[0] = u.coords[1]*v.coords[2] - u.coords[2]*v.coords[1];
        res.coords[1] = u.coords[2]*v.coords[0] - u.coords[0]*v.coords[2];
        res.coords[2] = u.coords[0]*v.coords[1] - u.coords[1]*v.coords[0];
        return res;
    }
    return null_vector(u.dim);
}

double norm(vector u)
{
    return sqrt(dot(u, u));
}

bool are_vectors_orthogonal(vector u, vector v)
{
    return (dot(u, v) == 0);
}

void vector_pp(vector vec)
{
    for(int i = 0; i < vec.dim; i++)
    {
        printf("| %f |\n",  vec.coords[i]);
    }
}