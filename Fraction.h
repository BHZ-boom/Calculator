#pragma once

class Fraction
{
private:
	long long m_numerator;
	long long m_denominator;
public:
	explicit Fraction(long long above = 0, long long below = 1);
	Fraction(const Fraction& rhs); //���ƹ��캯��
	Fraction(long double input); //������ת���ɷ���
	void reset(long long above, long long below); //���÷���ֵ
	void gcd(); //����
	long long up(); //���ط��ӵ�ֵ
	long long down(); //���ط�ĸ��ֵ

	friend Fraction operator+(const Fraction& left, const Fraction& right);
	friend Fraction operator-(const Fraction& left, const Fraction& right);
	friend Fraction operator*(const Fraction& left, const Fraction& right);
	friend Fraction operator/(const Fraction& left, const Fraction& right);
};

