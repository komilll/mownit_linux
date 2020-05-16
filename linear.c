#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_linalg.h>

double* generateVector(int size)
{
    double* vec = calloc(sizeof(double), size);
    for (int i = 0; i < size; ++i){
        double val = (double)rand() / RAND_MAX; // double [0, 1]
        vec[i] = val;
    }
    return vec;
}

void calculate(int n)
{
    double* a_data = generateVector(n * n);
    double* b_data = generateVector(n);

    gsl_matrix_view m = gsl_matrix_view_array(a_data, n, n);
    gsl_vector_view b = gsl_vector_view_array(b_data, n);

    gsl_vector *x = gsl_vector_alloc(n);
    int s;
    
    gsl_permutation *p = gsl_permutation_alloc(n);

    gsl_linalg_LU_decomp(&m.matrix, p, &s);
    gsl_linalg_LU_solve(&m.matrix, p, &b.vector, x);

    gsl_permutation_free(p);
    gsl_vector_free(x);
}

int main(int argc, char* argv[])
{
    if (argc != 2){
        return -1;
    }
    char *pEnd;
    int n = strtol(argv[1], &pEnd, 0);

    srange(time(NULL));

    if (n == 0){
        return -1;
    } else if (n < 0){
        //Iterate
    } else {
        calculate(n);
    }

    return 0;
}