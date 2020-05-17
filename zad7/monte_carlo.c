#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_plain.h>
#include <gsl/gsl_monte_miser.h>
#include <gsl/gsl_monte_vegas.h>

double calculateIntegralValue(int sampleCount)
{
    int correctSamples = 0;

    srand(time(NULL));
    FILE* file = fopen("sqrt.txt", "w");

    for (int i = 0; i < sampleCount; ++i){
        double x = (double)rand() / RAND_MAX; // double [0, 1]
        double y = (double)rand() / RAND_MAX; // double [0, 1000]

        if (y <= 1.0/sqrt(x)){
            fprintf (file,"%g %g\n", x, y); //Save correct samples to file
            correctSamples++;
        }
    }
    return (double)correctSamples / (double)sampleCount; // (b-a) is (1.0-0.0) so we can ignore this multiply
}

void calculateIntegralError(int maxSamples)
{
    srand(time(NULL));
    FILE* file = fopen("sqrt_err.txt", "w");

    for (int sampleCount = 1; sampleCount < maxSamples; ++sampleCount){
        int correctSamples = 0;
        for (int i = 0; i < sampleCount; ++i){
            double x = (double)rand() / RAND_MAX; // double [0, 1]
            double y = (double)rand() / RAND_MAX; // double [0, 1]

            if (y <= x * x){
                correctSamples++;
            }
        }

        double sum = (double)correctSamples / (double)sampleCount; // (b-a) is (1.0-0.0) so we can ignore this multiply
        double sumError = sum - 1.0/3.0;
        fprintf(file, "%d %g\n", sampleCount, sqrt(sumError * sumError));
    }
}

void monteCarloPLAIN()
{
    double res, err;
    double xl[3] = {0,0,0};
    double xu[3] = {M_PI, M_PI, M_PI};

    const gsl_rng_type *T;
    gsl_rng *r;

    gsl_monte_function G;
    
}

int main(void)
{
    // printf("Sum: %g\n", sum);

    return 0;
}