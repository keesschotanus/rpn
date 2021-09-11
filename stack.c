/*
 * Simple stack that stores computed values.
 */

#include <stdio.h>
#include <stdlib.h>

#include "rpn.h"

#define MAX_STACK_SIZE 100

static int stackPointer = 0;
static double values[MAX_STACK_SIZE];

/*
 * Clears the stack.
 */
void clearStack(void)
{
	stackPointer = 0;
}

/*
 * Pushes the supplied value on the stack.
 * On overflow a message is sent to stderr and the program is terminated
 * with an error code of 1.
 */
void push(double value)
{
	if (stackPointer < MAX_STACK_SIZE)
	{
		printf("%f\n", value);
		values[stackPointer++] = value;
	} else
	{
		fprintf(stderr, "Error: stack overflow!");
		exit(1);
	}
}

/*
 * Pops and returns the top value from the stack.
 * On underflow a message is printed to stderr.
 */
double pop(void)
{
	if (stackPointer > 0)
	{
		return values[--stackPointer];
	}
	else {
		fprintf(stderr, "Error: stack is empty");
		return 0.0;
	}
}

/*
 * Prints the stack to stdout.
 */
void printStack(void)
{
	for (int i = stackPointer -1; i >= 0; --i)
	{
		printf("%g ", values[i]);
	}
	puts("\n");
}