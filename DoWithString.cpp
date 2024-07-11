#include "pch.h"
#include <stack>
#include <cctype>
#include <string>
#include <cmath> 
#include <stdexcept>
#include <type_traits>
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDoc.h"
#include "CalculatorView.h"


// Function to perform arithmetic operations.
template <typename T>
T CCalculatorView::applyOp(T a, T b, wchar_t op) {
    switch (op) {
        case L'+': return a + b;
        case L'-': return a - b;
        case L'*': return a * b;
        case L'/': return a / b;
        default: throw std::invalid_argument("Invalid operator.");
    }
}

// Function to return precedence of operators
long double CCalculatorView::precedence(wchar_t op) {
    if (op == L'+' || op == L'-') return 1;
    if (op == L'*' || op == L'/') return 2;
    return 0;
}

// Function to evaluate the expression
void CCalculatorView::evaluate(CString& expression, int mode) {
    std::stack<long double> values; // Stack to store doubleegers
    std::stack<Fraction> fvalues;
    std::stack<wchar_t> ops; // Stack to store operators

    for (int i = 0; i < expression.GetLength(); i++) {
        // Current token is a whitespace, skip it
        if (expression[i] == ' ') continue;

        // Current token is a number, push it to stack for numbers
        else if (isdigit(expression[i])) {
            long double val = 0;
            // There may be more than one digits in number
            BOOL ifDecimal = FALSE;
            long  decimalDigit = 1; //小数位数
            while (i < expression.GetLength() && (isdigit(expression[i]) || expression[i] == L'.')) {
                if (expression[i] == L'.') {
                    ifDecimal = TRUE;
                    i++;
                    continue;
                }
                val = (val * 10) + (expression[i] - '0');
                if (ifDecimal) decimalDigit *= 10;
                i++;
            }
            val /= decimalDigit;
            if (mode == 1) {
                values.push(val);
            }
            else if (mode == 2) {
                fvalues.push(Fraction(val));
            }
            
            i--; // since the for loop also increases i
        }

        // Current token is an opening brace, push it to 'ops'
        /*else if (expression[i] == '(') {
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
        */

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
                wchar_t op = ops.top();
                ops.pop();
                if (mode == 1) {
                    long double val1, val2;

                    val2 = values.top();
                    values.pop();

                    val1 = values.top();
                    values.pop();
                    values.push(applyOp(val1, val2, op));
                }
                else {
                    Fraction val1, val2;

                    val2 = fvalues.top();
                    fvalues.pop();

                    val1 = fvalues.top();
                    fvalues.pop();
                    fvalues.push(applyOp(val1, val2, op));
                } 
            }

            // Push current token to 'ops'.
            ops.push(opt);
        }
    }

    // Entire expression has been parsed at this point, apply remaining ops to remaining values
    while (!ops.empty()) {
        wchar_t op = ops.top();
        ops.pop();
        if (mode == 1) {
            long double val1, val2;

            val2 = values.top();
            values.pop();

            val1 = values.top();
            values.pop();
            values.push(applyOp(val1, val2, op));
        }
        else {
            Fraction val1, val2;

            val2 = fvalues.top();
            fvalues.pop();

            val1 = fvalues.top();
            fvalues.pop();
            fvalues.push(applyOp(val1, val2, op));
        }
    }

    // Top of 'values' contains result, return it
    if (mode == 1) {
        ConvertDouble(values.top(), expression);
    }
    else {
        Fraction result = fvalues.top();
        expression.Format(_T("%lld/%lld"), result.up(), result.down());
    }
  
}


void CCalculatorView::ConvertDouble(long double result, CString& input) {
    // 如果结果转换为整数后与自身相等，则它是一个整数
    if (floor(result) == result) {
        input.Format(_T("%lld"), static_cast<long long>(result));
    }
    else {
        input.Format(_T("%f"), result);
    } 
}


Fraction operator+(Fraction& left, Fraction& right) {
    long long above, below;
    below = left.down() * right.down();
    above = left.up() * right.down() + right.up() * left.down();
    Fraction result(above, below);
    result.gcd();
    return result;
}


Fraction operator-(Fraction& left, Fraction& right) {
    long long above, below;
    below = left.down() * right.down();
    above = left.up() * right.down() - right.up() * left.down();
    Fraction result(above, below);
    result.gcd();
    return result;
}


Fraction operator*(Fraction& left, Fraction& right) {
    long long above, below;
    below = left.down() * right.down();
    above = left.up() * right.up();
    Fraction result(above, below);
    result.gcd();
    return result;
}


Fraction operator/(Fraction& left, Fraction& right) {
    long long above, below;
    below = left.down() * right.up();
    above = left.up() * right.down();
    Fraction result(above, below);
    result.gcd();
    return result;
}
    
        
   
