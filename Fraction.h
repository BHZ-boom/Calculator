#pragma once

class Fraction
{
private:
	int m_numerator;
	int m_denominator;
public:
	explicit Fraction(int above = 0, int below = 1);
	Fraction(const Fraction& rhs); //���ƹ��캯��
	Fraction(double input); //������ת���ɷ���
	void reset(int above, int below); //���÷���ֵ
	void gcd(); //����
	int up(); //���ط��ӵ�ֵ
	int down(); //���ط�ĸ��ֵ

	friend Fraction operator+(const Fraction& left, const Fraction& right);
	friend Fraction operator-(const Fraction& left, const Fraction& right);
	friend Fraction operator*(const Fraction& left, const Fraction& right);
	friend Fraction operator/(const Fraction& left, const Fraction& right);
};

