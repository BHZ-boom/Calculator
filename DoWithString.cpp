#include "pch.h"
#include <stack>
#include <cctype>
#include <string>
#include <cmath> 
#include <stdexcept>
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDoc.h"
#include "CalculatorView.h"
using namespace std;

// Function to perform arithmetic operations.
double CCalculatorView::applyOp(double a, double b, wchar_t op) {
    switch (op) {
    case L'+': return a + b;
    case L'-': return a - b;
    case L'*': return a * b;
    case L'/': return b ? a / b : throw invalid_argument("Division by zero.");
    default: throw invalid_argument("Invalid operator.");
    }
}

// Function to return precedence of operators
double CCalculatorView::precedence(wchar_t op) {
    if (op == L'+' || op == L'-') return 1;
    if (op == L'*' || op == L'/') return 2;
    return 0;
}

// Function to evaluate the expression
void CCalculatorView::evaluate(CString& expression) {
    stack<double> values; // Stack to store doubleegers
    stack<wchar_t> ops; // Stack to store operators

    for (double i = 0; i < expression.GetLength(); i++) {
        // Current token is a whitespace, skip it
        if (expression[i] == ' ') continue;

        // Current token is a number, push it to stack for numbers
        else if (isdigit(expression[i])) {
            double val = 0;
            // There may be more than one digits in number
            BOOL ifDecimal = FALSE;
            while (i < expression.GetLength() && (isdigit(expression[i]) || expression[i] == L'.')) {
                if (expression[i] == L'.') {
                    ifDecimal = TRUE;
                    i++;
                    continue;
                }
                val = (val * 10) + (expression[i] - '0');
                if (ifDecimal) val /= 10;
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

                wchar_t op = ops.top();
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
            wchar_t opt = expression[i];
            if (opt == L'\u00D7') {
                opt = '*';
            }
            if (opt == L'\u00F7') {
                opt = '/';
            }
            while (!ops.empty() && precedence(ops.top()) >= precedence(opt)) {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                wchar_t op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            // Push current token to 'ops'.
            ops.push(opt);
        }
    }

    // Entire expression has been parsed at this point, apply remaining ops to remaining values
    while (!ops.empty()) {
        double val2 = values.top();
        values.pop();

        double val1 = values.top();
        values.pop();

        wchar_t op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op));
    }

    // Top of 'values' contains result, return it
    ConvertResult(values.top(), expression);
}

void CCalculatorView::ConvertResult(double result, CString& input) {
    // 如果结果转换为整数后与自身相等，则它是一个整数
    if (floor(result) == result) {
        input.Format(_T("%d"), static_cast<int>(result));
    }
    else {
        input.Format(_T("%.12f"), result);
    }
}


