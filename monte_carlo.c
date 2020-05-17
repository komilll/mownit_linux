#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int correctSamples = 0;
    const int sampleCount = 100000;

    srand(time(NULL));

    FILE* file = fopen("sqr.txt", "w");

    for (int i = 0; i < sampleCount; ++i){
        double x = (double)rand() / RAND_MAX; // double [0, 1]
        double y = (double)rand() / RAND_MAX; // double [0, 1]

        if (y <= x * x){
            fprintf (file,"%g %g\n", x, y);
            correctSamples++;
        }
    }

    double sum = (double)correctSamples / (double)sampleCount; // (b-a) is (1.0-0.0) so we can ignore this multiply
    printf("Sum: %g\n", sum);

    return 0;
}