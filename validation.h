#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include "customization.h"

#define MIN -100
#define MAX 100

bool a_for_bisection (const double start)
{
    return start < MIN || start > MAX || start == 0.0;
}

bool b_for_bisection (const double end)
{
    return end < MIN  || end > MAX || end == 0.0;
}
bool a_for_newton (const double start)
{
    return start <= 0.0 || start > MAX;
}

bool b_for_newton (const double end)
{
    return end <= 0.0  || end > MAX;
}

bool y_condition(const double value)
{
    return value < MIN  || value > MAX;
}

bool validate_interval(const double a, const double b)
{
    if (a == b)
    {
        printf(LIGHT_RED "Interval is too small. The root won't be found\n" RESET_COLOR);
        fflush(stdin);
        return false;
    }
    if (a > b)
    {
        printf(LIGHT_RED "The start of the interval can't be higher than the end\n" RESET_COLOR);
        fflush(stdin);
        return false;
    }
    return true;
}

double validate_floating_value(const char *message, bool (*condition)(double))
{
    bool InvalidInput;
    double value = 0;
    do
    {
        printf("%s", message);
        if (scanf("%lf", &value) != 1 || condition(value))
        {
            printf(LIGHT_RED "Please enter a valid floating value\n" RESET_COLOR);
            fflush(stdin);
            InvalidInput = true;
        }
        else
        {
            fflush(stdin);
            InvalidInput = false;
        }
    }
    while (InvalidInput);
    return value;
}

int validate_integer_accuracy(const char *message)
{
    bool InvalidInput;
    int value = 0;
    printf("%s", message);
    fflush(stdin);
    do
    {
        if (scanf("%d", &value) != 1 || value <= 0 || value > 15)
        {
            printf(LIGHT_RED "Invalid Input, please enter an integer number in given range\n" RESET_COLOR);
            fflush(stdin);
            InvalidInput = true;
        }
        else
        {
            fflush(stdin);
            InvalidInput = false;
        }
    }
    while(InvalidInput);
    return value;
}

double validate_floating_accuracy(const char *message1, const char *message2)
{
    bool InvalidInput;
    double value = 0;
    printf("%s\n", message1);
    do
    {
        if (scanf("%lf", &value) != 1 || value < 1e-15 || value > 1e-1)
        {
            printf(LIGHT_RED "%s\n" RESET_COLOR, message2);
            fflush(stdin);
            InvalidInput = true;
        }
        else
        {
            fflush(stdin);
            InvalidInput = false;
        }
    }
    while(InvalidInput);
    return value;
}

char validate_input_getch(const char *message, const unsigned option1, const unsigned option2)
{
    printf("%s", message);
    char input = getch();
    do
    {
        if (input < option1 || input > option2)
        {
            printf(LIGHT_RED "Please enter a number in given range\n" RESET_COLOR);
            fflush(stdin);
        }
        else
        {
            fflush(stdin);
            return input;
        }
        input = getch();
    }
    while (input < option1 || input > option2);
}
#endif //VALIDATION_H
