#pragma once

class Fraction
{
private:
	int m_numerator;
	int m_denominator;
public:
	Fraction() = default;
	Fraction(int above, int below);
	Fraction(const Fraction& rhs); //复制构造函数
	void reset(int above, int below); //重置分数值
	void gcd(); //化简
	int up(); //返回分子的值
	int down(); //返回分母的值
};

Fraction operator+(const Fraction& left, const Fraction& right);
Fraction operator-(const Fraction& left, const Fraction& right);
Fraction operator*(const Fraction& left, const Fraction& right);
Fraction operator/(const Fraction& left, const Fraction& right);