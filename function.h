#ifndef FUNCTION_H
#define FUNCTION_H

#include <math.h>
#include "validation.h"
#include "customization.h"

#define ONE 49
#define TWO 50
#define THREE 51

double get_accuracy()
{
    double e = 0;
    printf("\nChoose the type to enter accuracy (e):\n");
    printf("If the option doesn't lay in one of three categories the section will restart\n");

    const char accuracy = validate_input_getch("1 - Decimal places\n"
                                    "2 - Real number\n"
                                    "3 - Exponential form\n", ONE, THREE);
    switch (accuracy)
    {
        case ONE:
            e = pow(10, -validate_integer_accuracy("Enter the number of decimal places:\n"
                        "The input range is [1 - 15]\n"));
            printf("In exponential form the accuracy is: " LIGHT_GREEN "%e\n" RESET_COLOR, e);
            break;

        case TWO:
            e = validate_floating_accuracy("Enter accuracy as a real number (e.g. 0.001)\n"
                                           "The input range is [0.000000000000001 - 0.1]",
                                           "Invalid input, pLease enter a real value in given range");
            printf("In exponential form the accuracy is: " LIGHT_GREEN "%e\n" RESET_COLOR, e);
            break;

        case THREE:
            e = validate_floating_accuracy("Enter accuracy as an exponential number (e.g. 1e-3):\n"
                                           "The input range is [1e-5 - 1e-1]",
                                           "Invalid input, pLease enter an exponential value in given range");
            printf("The accuracy is: " LIGHT_GREEN "%e\n" RESET_COLOR, e);
            break;

        default:
            printf(LIGHT_RED "Invalid option, please enter a given number (1 - 3)\n" RESET_COLOR);
            fflush(stdin);
            break;
    }
    return e;
}
#endif //FUNCTION_H
