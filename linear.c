#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_linalg.h>

int DEBUG = 1;
int DEBUG_SOLUTION = 1;
int STORE_TIMING = 0;

double* generateVector(int size)
{
    double* vec = calloc(sizeof(double), size);
    for (int i = 0; i < size; ++i){
        double val = (double)rand() / RAND_MAX; // double [0, 1]
        vec[i] = val;
    }
    return vec;
}

void printMatrix(double* m, int size)
{
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            printf("%g    ", m[j + i * size]);
        }
        printf("\n");
    }
    printf("\n");
}

void printVector(double* v, int size)
{
    for (int i = 0; i < size; ++i){
        printf("%g", v[i]);
        printf("\n");
    }
    printf("\n");
}

double* copyVector(double* src, int size)
{
    double* vec = calloc(sizeof(double), size);
    for (int i = 0; i < size; ++i){
        vec[i] = src[i];
    }
    return vec;
}

void checkSolution(double* m, double* b, gsl_vector x, int size)
{
    const double epsilon = 0.0001;
    int failures = 0;

    for (int i = 0; i < size; ++i){
        double sum = 0;
        for (int j = 0; j < size; ++j){
            sum += m[j + i * size] * x.data[j];
            // printf("%g * %g = %g\n", m[j + i * size], x.data[j], m[j + i * size] * x.data[j]);
        }
        if (abs(sum - b[i]) > epsilon){
            failures++;
            if (DEBUG_SOLUTION){
                printf("Wrong solution was calculated: %g --- %g\n", sum, b[i]);
                printf("\n");
            }
        }
    }
    if (DEBUG_SOLUTION){
        if (failures == 0){
            printf("All calculated values were correct");
        } else {
            printf("Total %n errors in calculated value", failures);
        }
        printf("\n");
    }
}

void decomp()
{

}

void solve()
{
    
}

void calculate(int n)
{
    double* a_data = generateVector(n * n);
    double* b_data = generateVector(n);

    double* originalMatrix = copyVector(a_data, n * n);

    gsl_matrix_view m = gsl_matrix_view_array(a_data, n, n);
    gsl_vector_view b = gsl_vector_view_array(b_data, n);

    if (DEBUG){
        printf("Matrix M:\n");
        printMatrix(a_data, n);

        printf("Vector B:\n");
        printVector(b_data, n);
    }
    gsl_vector *x = gsl_vector_alloc(n);
    int s;
    
    gsl_permutation *p = gsl_permutation_alloc(n);

    gsl_linalg_LU_decomp(&m.matrix, p, &s);
    gsl_linalg_LU_solve(&m.matrix, p, &b.vector, x);

    if (DEBUG){
        printf("Solution X:\n");
        gsl_vector_fprintf(stdout, x, "%g");
        printf("\n");
    }
    checkSolution(originalMatrix, b_data, *x, n);

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

    srand(time(NULL));

    if (n == 0){
        return -1;
    } else if (n < 0){
        DEBUG = 0;
        DEBUG_SOLUTION = 0;
        STORE_TIMING = 1;
        for (int i = 10; i < 1000; i+=10){
            calculate(i);
        }
    } else {
        calculate(n);
    }

    return 0;
}