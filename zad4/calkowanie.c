#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

double f1(double x, void* params)
{
    return x*x;
}

double f2(double x, void* params)
{
    return 1 / sqrt(x);
}

void calculateIntegralVoid(double (*f)(double x), double a, double b, int maxInterval, double expected)
{
    FILE* output = fopen("integral.txt", "w");
    int n = 1;
    while (n < maxInterval)
    {
        double dx = (b - a) / (double)n;
        double sum = 0;

        for (int i = 1; i < n; ++i)
        {
            sum += f(a + i * dx);
        }
        sum *= dx;
        fprintf (output,"%d %f\n", n, expected - sum);

        n++;
    }
}

int calculateIntegral(double (*f)(double x), double a, double b, int n, double expected, double error)
{
    double dx = (b - a) / (double)n;
    double sum = 0;

    for (int i = 1; i < n; ++i)
    {
        sum += f(a + i * dx);
    }
    sum *= dx;
    if (fabs(sum - expected) < error)
    {
        printf("Sum with error %.1e error for %d samples: %.18f\n", error, n, sum);
        return 1;
    }
    printf("DIFFERENCE with error %.1e error for %d samples: %.18f\n", error, n, fabs(sum - expected));
    return 1;
}

void tryFindIntergral(double (*f)(double x), double a, double b, double expected, double error, int step)
{
    int interval = step;
    while (!calculateIntegral(f, a, b, interval, expected, error))
    {
        interval += step;
    }
}

void gslIntegral(double (*f)(double x, void* params), double expected)
{
    gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000);

    double result, error;
    double alpha = 1.0;

    gsl_function F;
    F.function = f;
    F.params = &alpha;

    gsl_integration_qags (&F, 0, 1, 0, 1e-7, 1000, w, &result, &error);

    printf ("result          = % .18f\n", result);
    printf ("exact result    = % .18f\n", expected);
    printf ("estimated error = % .18f\n", error);
    printf ("actual error    = % .18f\n", result - expected);
    printf ("intervals       = %zu\n", w->size);

    gsl_integration_workspace_free (w);
}

int main (int argc, char* argv[])
{
    // tryFindIntergral(f2, 0, 1.0, 2.0, 1e-3, 1000);
    // tryFindIntergral(f2, 0, 1.0, 2.0, 1e-4, 215000000);
    // tryFindIntergral(f2, 0, 1.0, 2.0, 1e-5, 100000);
    // tryFindIntergral(f2, 0, 1.0, 2.0, 1e-6, 1000000);

    // calculateIntegralVoid(f2, 0.0, 1.0, 100000, 2.0);

    gslIntegral(f2, 2.0);
    return 0;
}