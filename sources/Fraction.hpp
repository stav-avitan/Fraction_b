#pragma once

#include <iostream>
#include <stdexcept>

namespace ariel
{
	class Fraction
	{
		private:
			int _num, _den;

			static int _gcd(int num1, int num2) {
				return (num2 == 0) ? num1:_gcd(num2, num1 % num2);
			}

			void _reduce() {
				int commonfactor = _gcd(abs(_num), abs(_den));
				_num /= commonfactor;
				_den /= commonfactor;
			}

			static void _reduce(int &num, int &den) {
				int commonfactor = _gcd(abs(num), abs(den));
				num /= commonfactor;
				den /= commonfactor;
			}

		public:
			Fraction();

			Fraction(int num, int den);

			Fraction(float number);

			int getNumerator() const {
				return _num;
			}

			int getDenominator() const {
				return _den;
			}

			const Fraction operator+(const Fraction& other) const;
			const Fraction operator-(const Fraction& other) const;
			const Fraction operator*(const Fraction& other) const;
			const Fraction operator/(const Fraction& other) const;

			const Fraction operator+(const float& num) const;
			const Fraction operator-(const float& num) const;
			const Fraction operator*(const float& num) const;
			const Fraction operator/(const float& num) const;

			bool operator==(const Fraction& other) const {
				return _num == other._num && _den == other._den;
			}

			bool operator!=(const Fraction& other) const {
				return !(*this == other);
			}
			
			bool operator<(const Fraction& other) const {
				return (_num * other._den) < (other._num * _den);
			}

			bool operator>(const Fraction& other) const {
				return (_num * other._den) > (other._num * _den);
			}

			bool operator<=(const Fraction& other) const {
				return !(*this > other);
			}

			bool operator>=(const Fraction& other) const {
				return !(*this < other);
			}

			bool operator==(const float& other) const {
				return *this == Fraction(other);
			}

			bool operator!=(const float& other) const {
				return *this != Fraction(other);
			}

			bool operator<(const float& other) const {
				return *this < Fraction(other);
			}

			bool operator>(const float& other) const {
				return *this > Fraction(other);
			}

			bool operator<=(const float& other) const {
				return *this <= Fraction(other);
			}

			bool operator>=(const float& other) const {
				return *this >= Fraction(other);
			}

			friend const Fraction operator+(const float& num, const Fraction& other);
			friend const Fraction operator-(const float& num, const Fraction& other);
			friend const Fraction operator*(const float& num, const Fraction& other);
			friend const Fraction operator/(const float& num, const Fraction& other);

			friend bool operator==(const float& num, const Fraction& other);
			friend bool operator!=(const float& num, const Fraction& other);
			friend bool operator<(const float& num, const Fraction& other);
			friend bool operator>(const float& num, const Fraction& other);
			friend bool operator<=(const float& num, const Fraction& other);
			friend bool operator>=(const float& num, const Fraction& other);

			Fraction& operator++();
			Fraction& operator--();
			Fraction operator++(int);
			Fraction operator--(int);

			friend std::ostream& operator<<(std::ostream& outstream, const Fraction& frac);

			friend std::istream& operator>>(std::istream& inptstream, Fraction& frac);
	};
}