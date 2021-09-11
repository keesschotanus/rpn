# RPN Calculator

This is my interpretation of an RPN calculator,
as suggested by K&R

## Capabilities

Apart from the basic operations like +, -, * and /
the calculator supports a number of mathematical functions.

See fnc.c for an exhaustive list of all supported functions.

## Limitations

The calculator lacks functions like n!, nPr, nCr and quite a few others.
It also lacks storing values in memory.

## Compile and Run

```
gcc *.c -lm -Wall -o rpn
./rpn
```