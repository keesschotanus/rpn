/*
 * Definition of the different functions this rpn calculator supports.
 * It is fairly easy to see how you can add your own functions. 
 */

#include <math.h>
#include <string.h>

#include "rpn.h"

static void ce(void);
static void ca(void);
static void swap(void);
static void print(void);

static function_t functions[] = {
    {"ce", 0, {.f0 = &ce}},
    {"ca", 0, {.f0 = &ca}},
    {"swap", 0, {.f0 = &swap}},
    {"print", 0, {.f0 = &print}},

    {"abs", 1, {.f1 = &fabs}},
    {"min", 2, {.f2 = &fmin}},
    {"max", 2, {.f2 = &fmax}},

    // Trigonomic
    {"cos", 1, {.f1 = &cos}},
    {"sin", 1, {.f1 = &sin}},
    {"tan", 1, {.f1 = &tan}},

    {"acos", 1, {.f1 = &acos}},
    {"asin", 1, {.f1 = &asin}},
    {"atan", 1, {.f1 = &atan}},
    {"atan2", 2, {.f2 = &atan2}},

    {"cosh", 1, {.f1 = &cosh}},
    {"sinh", 1, {.f1 = &sinh}},
    {"tanh", 1, {.f1 = &tanh}},
    {"acosh", 1, {.f1 = &acosh}},
    {"asinh", 1, {.f1 = &asinh}},
    {"atanh", 1, {.f1 = &atanh}},

    // Exponential
    {"exp", 1, {.f1 = &exp}},
    {"exp2", 1, {.f1 = &exp2}},
    {"expm1", 1, {.f1 = &expm1}},
    {"log", 1, {.f1 = &log}},
    {"log2", 1, {.f1 = &log2}},
    {"log10", 1, {.f1 = &log10}},

    // Power
    {"cbrt", 1, {.f1 = &cbrt}},
    {"hypot", 2, {.f2 = &hypot}},
    {"pow", 2, {.f2 = &pow}},
    {"sqrt", 1, {.f1 = &sqrt}},

    // Rounding
    {"ceil", 1, {.f1 = &ceil}},
    {"floor", 1, {.f1 = &floor}},
    {"round", 1, {.f1 = &round}},
    {"trunc", 1, {.f1 = &trunc}},
};

/*
 * Finds the function with the supplied name.
 * Returns a pointer to the corresponding function structure,
 * or NULL when no function with the supplied name exists.
 */
function_t *findFunction(char *name)
{
    for (int i = 0; i < sizeof functions / sizeof functions[0]; ++i)
    {
        if (!strcmp(name, functions[i].name))
            return &functions[i];
    }

    return NULL;
}

/*
 * Clear entry.
 * Removes the last pushed entry from the stack.
 */
static void ce(void)
{
    pop();
}

/*
 * Clear all entries.
 */
static void ca(void)
{
    clearStack();
}

/*
 * Swaps to top two entries on the stack.
 */
static void swap(void)
{
    double z = pop();
    double y = pop();

    push(z);
    push(y);
}

/*
 * Prints the values on the stack.
 */
static void print(void)
{
    printStack();
}