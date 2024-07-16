#include "pch.h"
#include <stdexcept>
#include <string>
#include <cmath>
#include "Fraction.h"


void Fraction::gcd() {
    long long a = this->m_numerator;
    long long b = this->m_denominator;
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    this->m_numerator /= a;
    this->m_denominator /= a;
}


Fraction::Fraction(long long above, long long below){
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

Fraction::Fraction(long double decimal) {
    long long intPart = static_cast<long long>(decimal);
    if (intPart == decimal) {
        // 没有找到小数点，说明是整数
        m_denominator = 1;
        m_numerator = intPart;
    }
    else {
        const long precision = 1000000; // 定义精度
        this->m_numerator = static_cast<long long>(round(decimal * precision));
        this->m_denominator = precision;
    }
    this->gcd();
}


void Fraction::reset(long long above, long long below) {
    this->m_numerator = above;
    if (below) {
        this->m_denominator = below;
    } 
    else {
        throw std::invalid_argument("Zero can't be denominator.");
    }
}


long long Fraction::up() {
    return m_numerator;
}


long long Fraction::down() {
    return m_denominator;
}
