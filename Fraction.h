#pragma once

class Fraction
{
private:
	int m_numerator;
	int m_denominator;
public:
	explicit Fraction(int above = 0, int below = 1);
	Fraction(const Fraction& rhs); //复制构造函数
	Fraction(double input); //有理数转化成分数
	void reset(int above, int below); //重置分数值
	void gcd(); //化简
	int up(); //返回分子的值
	int down(); //返回分母的值

	friend Fraction operator+(const Fraction& left, const Fraction& right);
	friend Fraction operator-(const Fraction& left, const Fraction& right);
	friend Fraction operator*(const Fraction& left, const Fraction& right);
	friend Fraction operator/(const Fraction& left, const Fraction& right);
};

