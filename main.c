#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <math.h>
#include "function.h"
#include "calculation.h"
#include "validation.h"

#define ONE 49
#define TWO 50
#define ENTER 13


int main()
{
    do
    {
        printf("\nThis program calculates roots of non-linear equations on the specified interval [a, b] for functions:\n");
        double a = 0, b = 0, y = 0, e = 0;

        printf("Choose function for roots calculation:\n");
        const char function_choice = validate_input_getch(LIGHT_BLUE "1. cos(y / x) - 2 * sin(1 / x) + 1 / x = 0\n"
                                                          "2. sin(ln(x)) - cos(ln(x)) + y * ln(x) = 0\n" RESET_COLOR, ONE, TWO);

        double (*user_choice_function)(double, double) = 0;
        switch (function_choice)
        {
            case ONE:
                user_choice_function = function1;
                printf("\nYou chose the function: " LIGHT_GREEN "cos(y / x) - 2 * sin(1 / x) + 1 / x = 0\n" RESET_COLOR);

                printf("\nEnter the interval [a, b]\n" LIGHT_BLUE "Coefficients of the interval can't be zero due to division in the function\n" RESET_COLOR);
                do
                {
                    a = validate_floating_value("Enter " LIGHT_GREEN "a [-100; 100]:\n" RESET_COLOR , a_for_bisection);
                    b = validate_floating_value("Enter " LIGHT_GREEN "b [-100; 100]:\n" RESET_COLOR, b_for_bisection);
                }
                while (!validate_interval(a, b));

                y = validate_floating_value("Enter the parameter " LIGHT_GREEN "y [-100; 100] " RESET_COLOR "for the formula:\n", y_condition);
                break;

            case TWO:
                user_choice_function = function2;
                printf("\nYou chose the function: " LIGHT_GREEN "sin(ln(x)) - cos(ln(x)) + y * ln(x) = 0\n" RESET_COLOR);

                printf("\nEnter the interval [a, b]\n" LIGHT_BLUE "Coefficients of the interval can't be zero or less due to logarithm in the function\n" RESET_COLOR);
                a = validate_floating_value("Enter " LIGHT_GREEN "a (0; 100]:\n" RESET_COLOR , a_for_newton);
                b = validate_floating_value("Enter " LIGHT_GREEN "b (0; 100]:\n" RESET_COLOR, b_for_newton);
                y = validate_floating_value("Enter the parameter " LIGHT_GREEN "y [-100; 100] " RESET_COLOR "for the formula:\n", y_condition);
                break;

            default:
                printf(LIGHT_RED "Please a number between 1 or 2" RESET_COLOR);
                fflush(stdin);
                break;
        }
        e = get_accuracy();

        const char method_choice = validate_input_getch(LIGHT_BLUE "\nChoose method for roots calculation:\n"
                                                        "1. Bisection method\n"
                                                        "2. Newton method\n", ONE, TWO);

        double roots[MAX_ROOTS];
        unsigned num_roots = 0;

        switch (method_choice)
        {
            case ONE:
                printf("You chose: " LIGHT_GREEN "Bisection method\n\n" RESET_COLOR);
                num_roots = find_all_roots(user_choice_function, a, b, y, e, roots, bisection_method);
                break;
            case TWO:
                printf("You chose: " LIGHT_GREEN "Newton method\n\n" RESET_COLOR);
                num_roots = find_all_roots(user_choice_function, a, b, y, e, roots, newton_method);
                break;
            default:
                fflush(stdin);
                break;
        }

        const unsigned precision = (unsigned)-log10(e);
        if (num_roots > 0)
        {
            printf("Roots found on the interval [%.*lf, %.*lf]\n", precision, a, precision, b);
            for (int i = 0; i < num_roots; i++)
            {
                printf(SKY_BLUE "x[%u]: %.*lf\n" RESET_COLOR, i + 1, precision, roots[i]);
            }
        }
        else
        {
            printf(LIGHT_RED "No roots were found in the interval [%.*lf, %.*lf]\n" RESET_COLOR, precision, a, precision, b);
        }

        printf("\nTo continue press " LIGHT_GREEN "ENTER, " RESET_COLOR "to exit press " LIGHT_RED "any other key\n" RESET_COLOR);
    }
    while (getch() == ENTER);
    return 0;
}


