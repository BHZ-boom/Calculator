#include "pch.h"
#include <stdexcept>
#include <string>
#include <cmath>
#include "Fraction.h"


void Fraction::gcd() {
    int a = this->m_numerator;
    int b = this->m_denominator;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    this->m_numerator /= a;
    this->m_denominator /= a;
}


Fraction::Fraction(int above, int below){
    if (below) {
        this->m_denominator = below;
    }
    else {
        throw std::invalid_argument("Zero can't be denominator.");
    }
    m_numerator = above;
}


Fraction::Fraction(const Fraction& rhs) {
    if (rhs.m_denominator) {
        this->m_denominator = rhs.m_denominator;
    }
    else {
        throw std::invalid_argument("Zero can't be denominator.");
    }
    m_numerator = rhs.m_numerator;
}

Fraction::Fraction(double num) {
    std::string numStr = std::to_string(num);
    // 查找小数点的位置
    size_t decimalPos = numStr.find('.');
    if (decimalPos == std::string::npos) {
        // 没有找到小数点，说明是整数
        m_denominator = 1;
        m_numerator = static_cast<int>(num);
    }
    else {
        int countDecimalPlaces = numStr.size() - decimalPos - 1;
        m_denominator = pow(10, countDecimalPlaces);
        m_numerator = static_cast<int>(num * pow(10, countDecimalPlaces));
    }
    this->gcd();
}


void Fraction::reset(int above, int below) {
    this->m_numerator = above;
    if (below) {
        this->m_denominator = below;
    } 
    else {
        throw std::invalid_argument("Zero can't be denominator.");
    }
}


int Fraction::up() {
    return m_numerator;
}


int Fraction::down() {
    return m_denominator;
}


/*
Fraction operator+(Fraction& left, Fraction& right) {
    int above, below;
    below = left.down() * right.down();
    above = left.up() * right.down() + right.up() * left.down();
    Fraction result(above, below);
    result.gcd();
    return result;
}


Fraction operator-(Fraction& left, Fraction& right) {
    int above, below;
    below = left.down() * right.down();
    above = left.up() * right.down() - right.up() * left.down();
    Fraction result(above, below);
    result.gcd();
    return result;
}


Fraction operator*(Fraction& left, Fraction& right) {
    int above, below;
    below = left.down() * right.down();
    above = left.up() * right.up();
    Fraction result(above, below);
    result.gcd();
    return result;
}


Fraction operator/(Fraction& left, Fraction& right) {
    int above, below;
    below = left.down() * right.up();
    above = left.up() * right.down();
    Fraction result(above, below);
    result.gcd();
    return result;
}
*/