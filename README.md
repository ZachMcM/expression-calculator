# Expression Calculator

## How It Works

We first transform the expression to postfix notation

1. Scan the infix expression from left to right. 
2. If the scanned character is an operand, put it in the postfix expression. 
Otherwise, do the following
3. If the precedence of the current scanned operator is higher than the precedence of the operator on top of the stack, or if the stack is empty, or if the stack contains a ‘(‘, then push the current operator onto the stack.
Else, pop all operators from the stack that have precedence higher than or equal to that of the current operator. After that push the current operator onto the stack.
4. If the scanned character is a ‘(‘, push it to the stack. 
5. If the scanned character is a ‘)’, pop the stack and output it until a ‘(‘ is encountered, and discard both the parenthesis. 
6. Repeat steps 2-5 until the infix expression is scanned. 
7. Once the scanning is over, Pop the stack and add the operators in the postfix expression until it is not empty.

Then we evaluate the postfix expression using a stack

## Compilation
```
g++ -std=c++11 -o calculate stack.cpp calculator.cpp
```

## Future Features
- Support for more constant literals such as pi and Euler's number (e)
- Support for trignometric functions
- Support for roots 
- support for logarithms# expression-calculator
