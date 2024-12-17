#ifndef CALCULATION_H
#define CALCULATION_H

#include <math.h>
#include "customization.h"
#define MAX_INTERVAL_STEP 1e-3

#define MAX_DERIVATIVE 1e-3

#define MAX_ITERATIONS 100

#define MAX_ROOTS 1000

#define ONE 49
#define TWO 50
#define ENTER 13


double function1(const double x, const double y)
{
    return cos(y / x) - 2.0 * sin(1.0 / x) + 1.0 / x;
}

double function2(const double x, const double y)
{
    return sin(log(x)) - cos(log(x)) + y * log(x);
}

double bisection_method(double (*f)(double, double), double a, double b, const double y, const double e)
{
    int iteration = 0;
    double x = 0;
    do
    {
        x = (a + b) / 2.0;
        if (f(a, y) * f(x, y) > 0)
        {
            a = x;
        }
        else
        {
            b = x;
        }
        iteration++;
        if (iteration > MAX_ITERATIONS)
        {
            printf(LIGHT_YELLOW "Maximum number of iterations (%d) reached\n" RESET_COLOR, MAX_ITERATIONS);
            return NAN;
        }
    }
    while (fabs(b - a) > e);
    printf("Number of iterations: %d\n", iteration);
    return x;
}

double newton_method(double (*f)(double, double), const double a, const double b, const double y, const double e)
{
    double x = (a + b) / 2.0, delta = 0;
    int iteration = 0;
    double derivative = 0;
    do
    {
        derivative = (f(x + MAX_DERIVATIVE, y) - f(x, y)) / MAX_DERIVATIVE;
        if (derivative == 0)
        {
            printf("Error: Derivative is zero\n");
            return NAN;
        }
        delta = f(x, y) / derivative;
        x -= delta;
        iteration++;
        if (iteration > MAX_ITERATIONS)
        {
            printf(LIGHT_YELLOW "Maximum number of iterations (%d) reached\n" RESET_COLOR, MAX_ITERATIONS);
            return NAN;
        }
    }
    while (fabs(delta) > e);
    printf("Number of iterations: %d\n", iteration);
    return x;
}

int find_all_roots(double (*f)(double, double), const double a, const double b, const double y, const double e, double *roots, double (*method)(double (*)(double, double), double, double, double, double)) {
    unsigned num_roots = 0;
    double start = a;
    do
    {
        const double end = fmin(start + MAX_INTERVAL_STEP, b);
        if (start <= 0 && end >= 0)
        {
            start = end;
            continue;
        }
        if (f(start, y) * f(end, y) < 0)
        {
            roots[num_roots++] = method(f, start, end, y, e);
            if (num_roots >= MAX_ROOTS)
            {
                printf(LIGHT_PURPLE "Maximum number of roots (%d) reached. Some roots may not be found.\n" RESET_COLOR, MAX_ROOTS);
                break;
            }
        }
        start += MAX_INTERVAL_STEP;
    }
    while (start < b);
    return num_roots;
}
#endif //CALCULATION_H
