#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double f1(double x)
{
    return x*x;
}

double f2(double x)
{
    return 1 / sqrt(x);
}

void calculateIntegralVoid(double a, double b, int maxInterval, double expected)
{
    FILE* output = fopen("integral_first.txt", "w");
    int n = 1;
    while (n < maxInterval)
    {
        double dx = (b - a) / (double)n;
        double sum = 0;

        for (int i = 1; i < n; ++i)
        {
            sum += f1(a + i * dx);
        }
        sum *= dx;
        fprintf (output,"%d %f\n", n, expected - sum);

        n++;
    }
}

int calculateIntegral(double a, double b, int n, double expected, double error)
{
    double dx = (b - a) / (double)n;
    double sum = 0;

    for (int i = 1; i < n; ++i)
    {
        sum += f1(a + i * dx);
    }
    sum *= dx;
    if (fabs(sum - expected) < error)
    {
        printf("Sum with error %.1e error for %d samples: %f\n", error, n, sum);
        return 1;
    }
    return 0;
}

void tryFindIntergral(double a, double b, double error, int step)
{
    int interval = 1;
    while (!calculateIntegral(a, b, interval, 1.0/3.0, error))
    {
        interval += step;
    }
}

int main (int argc, char* argv[])
{
    // tryFindIntergral(0, 1.0, 1e-3, 1);
    // tryFindIntergral(0, 1.0, 1e-4, 1);
    // tryFindIntergral(0, 1.0, 1e-5, 1);
    // tryFindIntergral(0, 1.0, 1e-6, 100);

    calculateIntegralVoid(0.0, 1.0, 10000, 1.0/3.0);
    return 0;
}