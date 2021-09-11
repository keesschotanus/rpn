/*
 * RPN calculator as suggested by K&R,
 * but this is not a literal translation.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "rpn.h"

#define MAX_LINE_LENGTH 10

static char input[MAX_LINE_LENGTH];

void runFromStdin();
void run(char *source);

static int processNumber(char *source, int startIndex);
static int processFunction(char *source, int startIndex);
static void processOperator(char token);

/*
 * Runs the RPN calculator.
 * You can either pass  an rpn string like: 2 3 +
 * or enter data from the command line.
 */
int main(int argc, char **argv)
{
	if (argc > 2)
	{
		fprintf(stderr, "Usage: %s [\"rpn code\"]", argv[0]);
		return 1;
	}

	argc == 1 ? runFromStdin() : run(argv[1]);
	return 0;
}

/*
 * Accepts input from the user on stdin.
 */
void runFromStdin()
{
	while (true)
	{
		printf("> ");
		fgets(input, MAX_LINE_LENGTH, stdin);
		run(input);
	}
}

/*
 * Evaluates the supplied source which should contain valid RPN commands.
 */
void run(char *source)
{
	size_t sourceLength = strlen(source);

	for (int sourceIndex = 0; sourceIndex < sourceLength; )
	{
		// Skip whitespace
		while (isspace(source[sourceIndex]))
			++sourceIndex;
		
		// We might have exhausted the source here
		if (sourceIndex >= sourceLength) break;

		// Try to determine the type of token
		if (source[sourceIndex] == '-' && sourceIndex + 1 < sourceLength && source[sourceIndex + 1] != ' ')
		{
			// Process negative number
			sourceIndex = processNumber(source, sourceIndex);
		}
		else if (source[sourceIndex] == '.' || isdigit(source[sourceIndex]))
		{
			// Process positive number
			sourceIndex = processNumber(source, sourceIndex);
		}
		else if (isalpha(source[sourceIndex]))
		{
			sourceIndex = processFunction(source, sourceIndex);
		}
		else
		{
			processOperator(source[sourceIndex++]);
		}
	}
}

/*
 * Processes a number by getting it from the supplied source
 * and then pushing it on the stack.
 * Returns the index of the next character of the source,
 * that needs to be processed.
 */
static int processNumber(char *source, int startIndex)
{
	size_t sourceLength = strlen(source);

	// Find end of the number in the source string
	int endIndex, endFound;
	for (endIndex = startIndex + 1, endFound = false; endIndex < sourceLength && !endFound; ++endIndex)
	{
		if (!isdigit(source[endIndex]) && source[endIndex] != '.' && source[endIndex] != 'e' && source[endIndex] != 'E')
			break;
	}

	push(atof(&source[startIndex]));
	return endIndex;
}

/*
 * Processes a function by getting the name from the supplied source
 * and then executing the function.
 * Returns the index of the next character of the source,
 * that needs to be processed.
 */
static int processFunction(char *source, int startIndex)
{
	size_t sourceLength = strlen(source);
	char fname[10];

	// Find end of the string token in the source string
	int endIndex;
	for (endIndex = startIndex + 1; endIndex < sourceLength && isalnum(source[endIndex]); ++endIndex)
		;

	int funcNameLength = endIndex - startIndex;
	funcNameLength = funcNameLength < sizeof(fname) ? funcNameLength : sizeof(fname) - 1;
	strncpy(fname, source + startIndex, funcNameLength);
	fname[funcNameLength] = '\0';

	function_t *fp = findFunction(fname);
	if (fp)
	{
		switch (fp->params)
		{
		case 0:
			fp->fpointer.f0();
			break;
		case 1:
			push(fp->fpointer.f1(pop()));
			break;
		case 2:
		{
			double rightOperand = pop();
			push(fp->fpointer.f2(pop(), rightOperand));
		}
		break;
		default:
			fprintf(stderr, "Unknown number of arguments for function: %s\n", fname);
			break;
		}
	}
	else
	{
		fprintf(stderr, "Unknown function: %s\n", fname);
	}

	return endIndex;
}

/*
 * Processes the supplied token (operator).
 */
static void processOperator(char token)
{
	double rightOperand;
	switch (token)
	{
	case '*':
		push(pop() * pop());
		break;
	case '/':
		rightOperand = pop();
		if (rightOperand == 0.0)
		{
			fputs("Division by zero\n", stderr);
			rightOperand = 1.0;
		}
		push(pop() / rightOperand);
		break;
	case '%':
		rightOperand = pop();
		if (rightOperand == 0.0)
		{
			fputs("Division by zero\n", stderr);
			rightOperand = 1.0;
		}
		push((long)pop() % (long)rightOperand);
		break;
	case '+':
		push(pop() + pop());
		break;
	case '-':
		rightOperand = pop();
		push(pop() - rightOperand);
		break;
	default:
		fprintf(stderr, "Unknown token: %d\n", token);
		break;
	}
}
