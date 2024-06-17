#include <iostream>
#include <stack>
#include <cctype>
#include <string>
#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDoc.h"
#include "CalculatorView.h"
using namespace std;

// Function to perform arithmetic operations.
double CCalculatorView::applyOp(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return b ? a / b : throw invalid_argument("Division by zero.");
    default: throw invalid_argument("Invalid operator.");
    }
}

// Function to return precedence of operators
double CCalculatorView::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to evaluate the expression
double CCalculatorView::evaluate(CString& expression) {
    stack<double> values; // Stack to store doubleegers
    stack<char> ops; // Stack to store operators

    for (double i = 0; i < expression.GetLength(); i++) {
        // Current token is a whitespace, skip it
        if (expression[i] == ' ') continue;

        // Current token is a number, push it to stack for numbers
        else if (isdigit(expression[i])) {
            double val = 0;
            // There may be more than one digits in number
            while (i < expression.GetLength() && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            values.push(val);
            i--; // since the for loop also increases i
        }

        // Current token is an opening brace, push it to 'ops'
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }

        // Closing brace encountered, solve entire brace
        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            // pop opening brace.
            ops.pop();
        }

        // Current token is an operator.
        else {
            // While top of 'ops' has same or greater precedence to current
            // token, which is an operator. Apply operator on top of 'ops'
            // to top two elements in values stack.
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            // Push current token to 'ops'.
            ops.push(expression[i]);
        }
    }

    // Entire expression has been parsed at this point, apply remaining ops to remaining values
    while (!ops.empty()) {
        double val2 = values.top();
        values.pop();

        double val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op));
    }

    // Top of 'values' contains result, return it
    return values.top();
}
