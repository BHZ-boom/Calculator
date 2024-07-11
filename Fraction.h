#pragma once

class Fraction
{
private:
	long long m_numerator;
	long long m_denominator;
public:
	explicit Fraction(long long above = 0, long long below = 1);
	Fraction(const Fraction& rhs); //复制构造函数
	Fraction(long double input); //有理数转化成分数
	void reset(long long above, long long below); //重置分数值
	void gcd(); //化简
	long long up(); //返回分子的值
	long long down(); //返回分母的值

	friend Fraction operator+(const Fraction& left, const Fraction& right);
	friend Fraction operator-(const Fraction& left, const Fraction& right);
	friend Fraction operator*(const Fraction& left, const Fraction& right);
	friend Fraction operator/(const Fraction& left, const Fraction& right);
};

