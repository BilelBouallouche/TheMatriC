#ifndef DEF_VECTOR
#define DEF_VECTOR

#include "cus_maths.h"

typedef struct vector
{
    unsigned int dim;
    double *coords;
} vector;

vector allocate_vector(unsigned int dim);
void deallocate_vector(vector vec);

vector null_vector(unsigned int dim);
vector create_vector(unsigned int dim, ...);
vector array_to_vector(double *array, unsigned int size);

void add_vector_to(vector* vec, vector vec2);
vector add_vectors(vector vec1, vector vec2);

void scalar_mul_to(double scalar, vector *vec);
vector scalar_mul(double scalar, vector vec);
void oppose_coord(vector *vec);

void sub_vector_to(vector *vec, vector vec2);
vector sub_vectors(vector vec1, vector vec2);

void oppose_coord(vector *vec);

bool are_vectors_same_dim(vector u, vector v);
bool are_vectors_equals(vector u, vector v);

double dot(vector u, vector v);

vector cross_product(vector u, vector v);
double norm(vector u);
bool are_vectors_orthogonal(vector u, vector v);

void vector_pp(vector vec);

void vector_to_array(vector vec, double* arr);

#endif