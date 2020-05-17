#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(void)
{
    int correctSamples = 0;
    // const int sampleCount = 100;

    srand(time(NULL));

    FILE* file = fopen("sqr.txt", "w");

    for (int sampleCount = 1; sampleCount < 10000; ++sampleCount){
        int correctSamples = 0;
        for (int i = 0; i < sampleCount; ++i){
            double x = (double)rand() / RAND_MAX; // double [0, 1]
            double y = (double)rand() / RAND_MAX; // double [0, 1]

            if (y <= x * x){
                // fprintf (file,"%g %g\n", x, y);
                correctSamples++;
            }
        }

        double sum = (double)correctSamples / (double)sampleCount; // (b-a) is (1.0-0.0) so we can ignore this multiply
        double sumError = sum - 1.0/3.0;
        // printf("Sum: %d --- %g --- %g\n", sampleCount, sum, sqrt(sumError * sumError));
        fprintf(file, "%d %g\n", sampleCount, sqrt(sumError * sumError));
    }
    return 0;
}