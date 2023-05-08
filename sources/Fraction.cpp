#include "Fraction.hpp"

using namespace std;

namespace ariel
{
	Fraction::Fraction(): _num(0), _den(1) { };

	Fraction::Fraction(int num, int den): _num(num), _den(den) {
		if (den == 0)
			throw invalid_argument("Undefined");

		if (den < 0)
		{
			_num *= -1;
			_den *= -1;
		}

		_reduce();
	}

	Fraction::Fraction(float number): _num(1000 * number), _den(1000) {
		_reduce();
	}

	const Fraction Fraction::operator+(const Fraction& other) const {
		int a, b, numerator, denominator;

		if (__builtin_smul_overflow(_num, other._den, &a) || __builtin_smul_overflow(other._num, _den, &b), __builtin_smul_overflow(_den, other._den, &denominator))
			throw overflow_error("Overflow");

		if (__builtin_sadd_overflow(a, b, &numerator))
			throw overflow_error("Overflow");

        return Fraction(numerator, denominator);
	}

	const Fraction Fraction::operator-(const Fraction& other) const {
		int a, b, numerator, denominator;

		if (__builtin_smul_overflow(_num, other._den, &a) || __builtin_smul_overflow(other._num, _den, &b) || __builtin_smul_overflow(_den, other._den, &denominator))
			throw overflow_error("Overflow");

		if (__builtin_ssub_overflow(a, b, &numerator))
			throw overflow_error("Overflow");

        return Fraction(numerator, denominator);
	}

	const Fraction Fraction::operator*(const Fraction& other) const {
		int numerator, denominator;

		if (__builtin_smul_overflow(_num, other._num, &numerator) || __builtin_smul_overflow(_den, other._den, &denominator))
			throw overflow_error("Overflow");

        return Fraction(numerator, denominator);
	}

	const Fraction Fraction::operator/(const Fraction& other) const {
		if (other._num == 0)
			throw runtime_error("Can't divide by zero!");

		int numerator, denominator;

		if (__builtin_smul_overflow(_num, other._den, &numerator) || __builtin_smul_overflow(_den, other._num, &denominator))
			throw overflow_error("Overflow");

        return Fraction(numerator, denominator);
	}

	const Fraction Fraction::operator+(const float& num) const {
		return *this + Fraction(num);
	}

	const Fraction Fraction::operator-(const float& num) const {
		return *this - Fraction(num);
	}

	const Fraction Fraction::operator*(const float& num) const {
		return *this * Fraction(num);
	}

	const Fraction Fraction::operator/(const float& num) const {
		return *this / Fraction(num);
	}

	const Fraction operator+(const float& num, const Fraction& other) {
		return Fraction(num) + other;
	}

	const Fraction operator-(const float& num, const Fraction& other) {
		return Fraction(num) - other;
	}

	const Fraction operator*(const float& num, const Fraction& other) {
		return Fraction(num) * other;
	}

	const Fraction operator/(const float& num, const Fraction& other) {
		return Fraction(num) / other;
	}

	bool operator==(const float& num, const Fraction& other) {
		return Fraction(num) == other;
	}

	bool operator!=(const float& num, const Fraction& other) {
		return Fraction(num) != other;
	}

	bool operator<(const float& num, const Fraction& other)  {
		return Fraction(num) < other;
	}

	bool operator>(const float& num, const Fraction& other)  {
		return Fraction(num) > other;
	}

	bool operator<=(const float& num, const Fraction& other)  {
		return Fraction(num) <= other;
	}

	bool operator>=(const float& num, const Fraction& other)  {
		return Fraction(num) >= other;
	}

	Fraction &Fraction::operator++() {
		_num += _den;
		return *this;
	}

	Fraction &Fraction::operator--() {
		_num -= _den;
		return *this;	
	}

	Fraction Fraction::operator++(int) {
		Fraction temp(_num, _den);
		++(*this);
		return temp;
	}

	Fraction Fraction::operator--(int) {
		Fraction temp(_num, _den);
		--(*this);
		return temp;
	}

	ostream& operator<<(ostream& outstream, const Fraction& frac) {
		outstream << frac._num << "/" << frac._den;
		return outstream;
	}

	istream& operator>>(istream& inptstream, Fraction& frac) {
		int num = 0, den = 0;
		inptstream >> num >> den;

		if (inptstream.fail() || den == 0)
			throw runtime_error("Input error");

		if (den < 0)
		{
			num *= -1;
			den *= -1;
		}

		frac._num = num;
		frac._den = den;

		frac._reduce();

		return inptstream;
	}
}