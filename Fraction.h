#pragma once

class Fraction
{
private:
	int m_numerator;
	int m_denominator;
public:
	Fraction() = default;
	Fraction(int above, int below);
	Fraction(const Fraction& rhs); //���ƹ��캯��
	void reset(int above, int below); //���÷���ֵ
	void gcd(); //����
	int up(); //���ط��ӵ�ֵ
	int down(); //���ط�ĸ��ֵ
};

Fraction operator+(const Fraction& left, const Fraction& right);
Fraction operator-(const Fraction& left, const Fraction& right);
Fraction operator*(const Fraction& left, const Fraction& right);
Fraction operator/(const Fraction& left, const Fraction& right);