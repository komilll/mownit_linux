#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_chebyshev.h>
#include <gsl/gsl_fit.h>

double funcExp(double x, void *p)
{
    (void)(p); //avoid unused parameter warning
    return exp(pow(x, 2));
}

double funcAbs(double x, void *p)
{
    (void)(p); //avoid unused parameter warning
    return fabs(x + pow(x, 3));
}

double funcSign(double x, void *p)
{
    (void)(p); //avoid unused parameter warning
    if (x == 0) return 0.0;
    else if (x < 0) return -1.0;

    return 1.0;
}

void calculateExp()
{
    const int stepsCount = 1000;
    FILE* outputR1 = fopen("cheb_exp_r1.txt", "w");
    FILE* outputR2 = fopen("cheb_exp_r2.txt", "w");
    FILE* outputR4 = fopen("cheb_exp_r4.txt", "w");
    FILE* outputR8 = fopen("cheb_exp_r8.txt", "w");
    FILE* outputR16 = fopen("cheb_exp_r16.txt", "w");
    FILE* outputR25 = fopen("cheb_exp_r25.txt", "w");
    FILE* outputR40 = fopen("cheb_exp_r40.txt", "w");

    gsl_cheb_series* cs = gsl_cheb_alloc(40);

    gsl_function function;

    function.function = funcExp;
    function.params = 0;

    gsl_cheb_init(cs, &function, -1.0, 1.0);
    for (int i = -stepsCount; i <= stepsCount; i++)
    {
        double x = (double)i / (double)stepsCount;
        double r1 = GSL_FN_EVAL(&function, x);
        double r2 = gsl_cheb_eval_n(cs, 2, x);
        double r4 = gsl_cheb_eval_n(cs, 4, x);
        double r8 = gsl_cheb_eval_n(cs, 8, x);
        double r16 = gsl_cheb_eval_n(cs, 16, x);
        double r25 = gsl_cheb_eval_n(cs, 25, x);
        double r40 = gsl_cheb_eval_n(cs, 40, x);

        fprintf (outputR1,"%g %g\n", x, r1);
        fprintf (outputR2,"%g %g\n", x, r2);
        fprintf (outputR4,"%g %g\n", x, r4);
        fprintf (outputR8,"%g %g\n", x, r8);
        fprintf (outputR16,"%g %g\n", x, r16);
        fprintf (outputR25,"%g %g\n", x, r25);
        fprintf (outputR40,"%g %g\n", x, r40);
    }

    gsl_cheb_free(cs);
}


void calculateAbs()
{
    const int stepsCount = 1000;
    FILE* outputR1 = fopen("cheb_abs_r1.txt", "w");
    FILE* outputR2 = fopen("cheb_abs_r2.txt", "w");
    FILE* outputR4 = fopen("cheb_abs_r4.txt", "w");
    FILE* outputR8 = fopen("cheb_abs_r8.txt", "w");
    FILE* outputR16 = fopen("cheb_abs_r16.txt", "w");
    FILE* outputR25 = fopen("cheb_abs_r25.txt", "w");
    FILE* outputR40 = fopen("cheb_abs_r40.txt", "w");

    gsl_cheb_series* cs = gsl_cheb_alloc(40);

    gsl_function function;

    function.function = funcAbs;
    function.params = 0;

    gsl_cheb_init(cs, &function, -1.0, 1.0);
    for (int i = -stepsCount; i <= stepsCount; i++)
    {
        double x = (double)i / (double)stepsCount;
        double r1 = GSL_FN_EVAL(&function, x);
        double r2 = gsl_cheb_eval_n(cs, 2, x);
        double r4 = gsl_cheb_eval_n(cs, 4, x);
        double r8 = gsl_cheb_eval_n(cs, 8, x);
        double r16 = gsl_cheb_eval_n(cs, 16, x);
        double r25 = gsl_cheb_eval_n(cs, 25, x);
        double r40 = gsl_cheb_eval_n(cs, 40, x);

        fprintf (outputR1,"%g %g\n", x, r1);
        fprintf (outputR2,"%g %g\n", x, r2);
        fprintf (outputR4,"%g %g\n", x, r4);
        fprintf (outputR8,"%g %g\n", x, r8);
        fprintf (outputR16,"%g %g\n", x, r16);
        fprintf (outputR25,"%g %g\n", x, r25);
        fprintf (outputR40,"%g %g\n", x, r40);
    }

    gsl_cheb_free(cs);
}

void calculateSign()
{
    const int stepsCount = 1000;
    FILE* outputR1 = fopen("cheb_sign_r1.txt", "w");
    FILE* outputR2 = fopen("cheb_sign_r2.txt", "w");
    FILE* outputR4 = fopen("cheb_sign_r4.txt", "w");
    FILE* outputR8 = fopen("cheb_sign_r8.txt", "w");
    FILE* outputR16 = fopen("cheb_sign_r16.txt", "w");
    FILE* outputR25 = fopen("cheb_sign_r25.txt", "w");
    FILE* outputR40 = fopen("cheb_sign_r40.txt", "w");

    gsl_cheb_series* cs = gsl_cheb_alloc(40);

    gsl_function function;

    function.function = funcSign;
    function.params = 0;

    gsl_cheb_init(cs, &function, -1.0, 1.0);
    for (int i = -stepsCount; i <= stepsCount; i++)
    {
        double x = (double)i / (double)stepsCount;
        double r1 = GSL_FN_EVAL(&function, x);
        double r2 = gsl_cheb_eval_n(cs, 2, x);
        double r4 = gsl_cheb_eval_n(cs, 4, x);
        double r8 = gsl_cheb_eval_n(cs, 8, x);
        double r16 = gsl_cheb_eval_n(cs, 16, x);
        double r25 = gsl_cheb_eval_n(cs, 25, x);
        double r40 = gsl_cheb_eval_n(cs, 40, x);

        fprintf (outputR1,"%g %g\n", x, r1);
        fprintf (outputR2,"%g %g\n", x, r2);
        fprintf (outputR4,"%g %g\n", x, r4);
        fprintf (outputR8,"%g %g\n", x, r8);
        fprintf (outputR16,"%g %g\n", x, r16);
        fprintf (outputR25,"%g %g\n", x, r25);
        fprintf (outputR40,"%g %g\n", x, r40);
    }

    gsl_cheb_free(cs);
}

void fitLinear()
{
    const int stepsCount = 1000;
    double xArray[stepsCount * 2];
    double yArray[stepsCount * 2];

    FILE* outputOriginal = fopen("linear_original.txt", "w");
    FILE* outputFit = fopen("linear_fit.txt", "w");
    FILE* outputCheb = fopen("linear_cheb.txt", "w");

    for (int i = -stepsCount; i <= stepsCount; i++)
    {
        double x = (double)i / (double)stepsCount;
        double y = pow(0.5, pow(x, 2) + 2 * x);

        xArray[i + stepsCount] = x;
        yArray[i + stepsCount] = y;

        fprintf (outputOriginal,"%g %g\n", x, y);
    }

    double c0 = 0;
    double c1 = 0;
    double cov00 = 0;
    double cov01 = 0;
    double cov11 = 0;
    double sumsq = 0;
    gsl_fit_linear(xArray, 1, yArray, 1, stepsCount * 2, &c0, &c1, &cov00, &cov01, &cov11, &sumsq);

//------
    for (int i = -stepsCount; i <= stepsCount; i++)
    {
        double x = (double)i / (double)stepsCount;
        double y = c0 + c1 * x;

        xArray[i + stepsCount] = x;
        yArray[i + stepsCount] = y;

        fprintf (outputFit,"%g %g\n", x, y);
    }

    printf("c0: %f --- c1: %f\n", c0, c1);
}

int main (int argc, char* argv[])
{
    calculateExp();
    calculateSign();
    calculateAbs();
    fitLinear();
    return 0;
}

/* 

plot "cheb_exp_r1.txt" with lines, \
    "cheb_exp_r2.txt" with lines, \
    "cheb_exp_r4.txt" with lines, \
    "cheb_exp_r8.txt" with lines, \
    "cheb_exp_r16.txt" with lines, \
    "cheb_exp_r25.txt" with lines, \
    "cheb_exp_r40.txt" with lines

plot "cheb_abs_r1.txt" with lines, \
    "cheb_abs_r2.txt" with lines, \
    "cheb_abs_r4.txt" with lines, \
    "cheb_abs_r8.txt" with lines, \
    "cheb_abs_r16.txt" with lines, \
    "cheb_abs_r25.txt" with lines, \
    "cheb_abs_r40.txt" with lines

plot "cheb_sign_r1.txt" with lines, \
    "cheb_sign_r2.txt" with lines, \
    "cheb_sign_r4.txt" with lines, \
    "cheb_sign_r8.txt" with lines, \
    "cheb_sign_r16.txt" with lines, \
    "cheb_sign_r25.txt" with lines, \
    "cheb_sign_r40.txt" with lines

================

plot "linear_original.txt" with lines, \
    "linear_fit.txt" with lines

*/