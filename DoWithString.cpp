#include "pch.h"
#include <stack>
#include <cctype>
#include <string>
#include <cmath> 
#include <iostream>
#include <sstream>
#include <iomanip>
#include <locale>
#include <stdexcept>
#include <type_traits>
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDoc.h"
#include "CalculatorView.h"
#define E     L"2.7182818"
#define Pi    L"3.1415926"

long double factorial(long double n) {
    if (n == 0) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

// Function to perform arithmetic operations.
template <typename T>
T CCalculatorView::applyOp(T a, T b, wchar_t op) {
    switch (op) {
        case L'+': return a + b;
        case L'-': return a - b;
        case L'*': return a * b;
        case L'/': return a / b;
        case L'^':return pow(a, b);
        case L'n':return log(a);
        case L'g':return log10(a);
        case L's':return sin(a);
        case L'c':return cos(a);
        case L't':return tan(a);
        default: throw std::invalid_argument("Invalid operator.");
    }
}

// Function to return precedence of operators
long double CCalculatorView::precedence(wchar_t op) {
    if (op == L'+' || op == L'-') return 1;
    if (op == L'*' || op == L'/') return 2;
    if (op == L'n' || op == L'g' || op == L's' || op == L'c' || op == L't') return 3;
    if (op == L'^')return 4;
    return 0;
}

// Function to evaluate the expression
void CCalculatorView::evaluate(CString& expression, int mode) {
    for (int i = 0; i < expression.GetLength(); i++) {
        if (i < expression.GetLength() - 1) {
            if (expression[i] == 'l') {
                expression.Delete(i);
                if (i != 0 && isdigit(expression[i - 1])) {
                    expression.Insert(i, L"*");
                }
            }
        }
        if (i < expression.GetLength() - 2) {
            if (expression[i] == 's' && expression[i + 1] == 'i' && expression[i + 2] == 'n') {
                expression.Delete(i + 2);
                expression.Delete(i + 1);
                if (i != 0 && isdigit(expression[i - 1])) {
                    expression.Insert(i, L"*");
                }
            }
            if (expression[i] == 'c' && expression[i + 1] == 'o' && expression[i + 2] == 's') {
                expression.Delete(i + 2);
                expression.Delete(i + 1);
                if (i != 0 && isdigit(expression[i - 1])) {
                    expression.Insert(i, L"*");
                }
            }
            if (expression[i] == 't' && expression[i + 1] == 'a' && expression[i + 2] == 'n') {
                expression.Delete(i + 2);
                expression.Delete(i + 1);
                if (i != 0 && isdigit(expression[i - 1])) {
                    expression.Insert(i, L"*");
                }
            }
        }

        if (expression[i] == 'e') {
            if (i == 0) {
                expression.Delete(i);
                expression.Insert(i, E);
            }
            else if (isdigit(expression[i - 1])) {
                expression.Delete(i);
                expression.Insert(i, L"*");
                expression.Insert(i + 1, E);
            }
            else {
                expression.Delete(i);
                expression.Insert(i, E);
            }
        }
        if (expression[i] == L'\u03C0') {
            if (i == 0) {
                expression.Delete(i);
                expression.Insert(i, Pi);
            }
            else if (isdigit(expression[i - 1])) {
                expression.Delete(i);
                expression.Insert(i, L"*");
                expression.Insert(i + 1, Pi);
            }
            else {
                expression.Delete(i);
                expression.Insert(i, Pi);
            }
        }
    }
    std::stack<long double> values; // Stack to store doubleegers
    std::stack<Fraction> fvalues;
    std::stack<wchar_t> ops; // Stack to store operators

    for (int i = 0; i < expression.GetLength(); i++) {
        // Current token is a whitespace, skip it
        if (expression[i] == ' ') continue;

        // Current token is a number, push it to stack for numbers
        else if (isdigit(expression[i])) {
            long double val = 0,val1=0;
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

                if (expression[i] == '/') {
                    i++;
                    ifDecimal = FALSE;
                    decimalDigit = 1; 
                    while (i < expression.GetLength() && (isdigit(expression[i]) || expression[i] == L'.')) {
                        if (expression[i] == L'.') {
                            ifDecimal = TRUE;
                            i++;
                            continue;
                        }
                        val1 = (val1 * 10) + (expression[i] - '0');
                        if (ifDecimal) decimalDigit *= 10;
                        i++;
                    }
                    val1 /= decimalDigit;
                    fvalues.push(Fraction(val / val1));
                }
                else {
                    fvalues.push(Fraction(val));
                }
           
            }
            
            i--; // since the for loop also increases i
        }

        // Current token is an opening brace, push it to 'ops'
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }

        // Closing brace encountered, solve entire brace
        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                long double val2 = values.top();
                values.pop();

                long double val1 = values.top();
                values.pop();

                wchar_t op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            // pop opening brace.
            ops.pop();
        }
        else if (expression[i] == '!') 
        {
            long double val = values.top();
            values.push(factorial(val));
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
                wchar_t op = ops.top();
                ops.pop();
                if (mode == 1) {
                    if (op == L'n' || op == L'g' || op == L's' || op == L'c' || op == L't') {
                        long double num = values.top();
                        values.pop();
                        values.push(applyOp(num, (long double)0, op));
                    }
                    else
                    {
                        long double val1, val2;

                        val2 = values.top();
                        values.pop();

                        val1 = values.top();
                        values.pop();
                        values.push(applyOp(val1, val2, op));
                    }
                }
                else {
                    if (op == L'n' || op == L'g' || op == L's' || op == L'c' || op == L't') {
                        Fraction val;
                        val = fvalues.top();
                        fvalues.pop();
                        fvalues.push(applyOp(val, (Fraction)((long double)1.0), op));
                    }
                    else
                    {
                        Fraction val1, val2;

                        val2 = fvalues.top();
                        fvalues.pop();

                        val1 = fvalues.top();
                        fvalues.pop();
                        fvalues.push(applyOp(val1, val2, op));
                    }
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
            if (op == L'n' || op == L'g' || op == L's' || op == L'c' || op == L't') {
                long double num = values.top();
                values.pop();
                values.push(applyOp(num, (long double)0, op));
            }
            else
            {
                long double val1, val2;

                val2 = values.top();
                values.pop();

                val1 = values.top();
                values.pop();
                values.push(applyOp(val1, val2, op));
            }
        }
        else {
            if (op == L'n' || op == L'g' || op == L's' || op == L'c' || op == L't') {
                Fraction val;
                val = fvalues.top();
                fvalues.pop();
                fvalues.push(applyOp(val, (Fraction)((long double)1.0), op));
            }
            else
            {
                Fraction val1, val2;

                val2 = fvalues.top();
                fvalues.pop();

                val1 = fvalues.top();
                fvalues.pop();
                fvalues.push(applyOp(val1, val2, op));
            }
        }
    }

    // Top of 'values' contains result, return it
    if (mode == 1) {
        ConvertDouble(values.top(), expression);
    }
    else {
        Fraction result = fvalues.top();
        if (result.down() == 1) {
            expression.Format(_T("%lld"), result.up());
        }
        else {
            expression.Format(_T("%lld/%lld"), result.up(), result.down());
        }
       
    }
  
}


void CCalculatorView::ConvertDouble(long double result, CString& input) {
    // 如果结果转换为整数后与自身相等，则它是一个整数
    BOOL intPart = FALSE;
    if (floor(result) == result) {
        input.Format(_T("%lld"), static_cast<long long>(result));
        int i = input.GetLength();
        while (i > 3) {
            input.Insert(i - 3, L',');
            i -= 3;
        }
    }
    else {
        input.Format(_T("%f"), result);
        for (int i = input.GetLength() - 1; i > 0; i--) {
            if (input[i] == L'.') intPart = TRUE;
            if (intPart) {
                while (i > 3) {
                    input.Insert(i - 3, L',');
                    i -= 3;
                }
            }
        }
    } 
}

Fraction pow(Fraction& left, Fraction& right) {
    long long above, below;
    below = pow(left.down(), right.up() / right.down());
    above = pow(left.up(), right.up() / right.down());
    Fraction result(above, below);
    result.gcd();
    return result;
}

Fraction log(Fraction& right) {
    long double a = log(right.up()) - log(right.down());
    return (Fraction(a));
}

Fraction log10(Fraction& right) {
    long double a = log10(right.up()) - log10(right.down());
    return (Fraction(a));
}

Fraction sin(Fraction& right) {
    long double a = sin((long double)right.up() / right.down());
    return (Fraction(a));
}

Fraction cos(Fraction& right) {
    long double a = cos((long double)right.up() / right.down());
    return (Fraction(a));
}

Fraction tan(Fraction& right) {
    long double a = tan((long double)right.up() / right.down());
    return (Fraction(a));
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


    
        
   
