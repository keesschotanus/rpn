typedef struct function {
	char name[10];
    int params;
    union fpointer
    {
	    void (*f0)(void);
    	double (*f1)(double);
	    double (*f2)(double, double);
    } fpointer;
} function_t;

void push(double);
double pop(void);
void clearStack(void);
void printStack(void);
function_t *findFunction(char *name);
