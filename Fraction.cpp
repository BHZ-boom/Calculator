#include "pch.h"
#include <stdexcept>
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


Fraction::Fraction(int above, int below) :m_numerator(above), m_denominator(below){}


Fraction::Fraction(const Fraction& rhs) 
    :m_numerator(rhs.m_numerator), m_denominator(rhs.m_denominator) {}


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