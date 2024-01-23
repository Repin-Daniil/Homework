#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <numeric>
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 public:
  // Constructors
  Rational();
  Rational(int p, int q = 1);  // NOLINT
  Rational(const Rational &);

  // Setters
  void SetNumerator(int numerator);
  void SetDenominator(int denominator);

  // Getters
  int GetNumerator() const;
  int GetDenominator() const;

  // Operators overloading
  Rational &operator+=(const Rational &other);
  Rational &operator-=(const Rational &other);
  Rational &operator*=(const Rational &other);
  Rational &operator/=(const Rational &other);

  Rational &operator++();    // Prefix increment
  Rational operator++(int);  // Postfix increment
  Rational &operator--();    // Prefix decrement
  Rational operator--(int);  // Postfix decrement

 private:
  int numerator_;
  int denominator_;

  // Methods
  void Reduce();
};

// Operators overloading
Rational operator+(const Rational &first, const Rational &second);
Rational operator-(const Rational &first, const Rational &second);
Rational operator*(const Rational &first, const Rational &second);
Rational operator/(const Rational &first, const Rational &second);

bool operator<(const Rational &first, const Rational &second);
bool operator>(const Rational &first, const Rational &second);
bool operator==(const Rational &first, const Rational &second);
bool operator!=(const Rational &first, const Rational &second);
bool operator>=(const Rational &first, const Rational &second);
bool operator<=(const Rational &first, const Rational &second);

Rational operator-(const Rational &elem);  // Unary minus
Rational operator+(const Rational &elem);  // Unary plus

std::istream &operator>>(std::istream &is, Rational &r);        // input
std::ostream &operator<<(std::ostream &os, Rational &r);        // output
std::ostream &operator<<(std::ostream &os, const Rational &r);  // output

#endif