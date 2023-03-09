#include "rational.h"

Rational::Rational() {
  numerator_ = 0;
  denominator_ = 1;
}

Rational::Rational(int p, int q) {
  if (q == 0) {
    throw RationalDivisionByZero{};
  }

  numerator_ = p;
  denominator_ = q;
  Reduce();
}

Rational::Rational(const Rational &other) {
  numerator_ = other.numerator_;
  denominator_ = other.denominator_;
}

int Rational::GetNumerator() const {
  return numerator_;
}

int Rational::GetDenominator() const {
  return denominator_;
}

void Rational::SetNumerator(int numerator) {
  numerator_ = numerator;
  Reduce();
}

void Rational::SetDenominator(int denominator) {
  if (denominator == 0) {
    throw RationalDivisionByZero{};
  }

  denominator_ = denominator;
  Reduce();
}

void Rational::Reduce() {
  int gcd = std::gcd(numerator_, denominator_);
  numerator_ /= gcd;
  denominator_ /= gcd;

  this->numerator_ = (denominator_ < 0) ? -numerator_ : numerator_;
  this->denominator_ = (denominator_ < 0) ? -denominator_ : denominator_;
}

Rational &Rational::operator+=(const Rational &other) {
  numerator_ = numerator_ * other.denominator_ + other.numerator_ * denominator_;
  denominator_ = denominator_ * other.denominator_;
  Reduce();
  return *this;
}

Rational &Rational::operator-=(const Rational &other) {
  numerator_ = numerator_ * other.denominator_ - other.numerator_ * denominator_;
  denominator_ = denominator_ * other.denominator_;
  Reduce();
  return *this;
}

Rational &Rational::operator*=(const Rational &other) {
  numerator_ = numerator_ * other.numerator_;
  denominator_ = denominator_ * other.denominator_;
  Reduce();
  return *this;
}

Rational &Rational::operator/=(const Rational &other) {
  if (other.numerator_ == 0) {
    throw RationalDivisionByZero{};
  }

  numerator_ = numerator_ * other.denominator_;
  denominator_ = denominator_ * other.numerator_;
  Reduce();
  return *this;
}

Rational &Rational::operator++() {
  *this += 1;
  return *this;
}

Rational Rational::operator++(int) {
  Rational copy = *this;
  ++*this;
  return copy;
}

Rational &Rational::operator--() {
  *this -= 1;
  return *this;
}

Rational Rational::operator--(int) {
  Rational copy = *this;
  --*this;
  return copy;
}

Rational operator+(const Rational &first, const Rational &second) {
  Rational copy = first;
  copy += second;
  return copy;
}

Rational operator-(const Rational &first, const Rational &second) {
  Rational copy = first;
  copy -= second;
  return copy;
}

Rational operator*(const Rational &first, const Rational &second) {
  Rational copy = first;
  copy *= second;
  return copy;
}

Rational operator/(const Rational &first, const Rational &second) {
  Rational copy = first;
  copy /= second;
  return copy;
}

bool operator<(const Rational &first, const Rational &second) {
  return first.GetNumerator() * second.GetDenominator() < second.GetNumerator() * first.GetDenominator();
}

bool operator>(const Rational &first, const Rational &second) {
  return second < first;
}

bool operator==(const Rational &first, const Rational &second) {
  return !(second < first) && !(second > first);
}

bool operator!=(const Rational &first, const Rational &second) {
  return !(second == first);
}

bool operator>=(const Rational &first, const Rational &second) {
  return !(first < second);
}

bool operator<=(const Rational &first, const Rational &second) {
  return !(first > second);
}

// Unary minus
Rational operator-(const Rational &elem) {
  return 0 - elem;
}

// Unary plus
Rational operator+(const Rational &elem) {
  return elem;
}

// Input
std::istream &operator>>(std::istream &is, Rational &r) {
  int num = 0, den = 1;
  std::string inp, num_str, den_str;
  is >> inp;
  int i = 0;

  while (inp[i] != '/' && inp[i] != '\0' && inp[i] != ' ') {
    num_str.push_back(inp[i]);
    ++i;
  }

  num = std::atoi(num_str.c_str());

  if (inp[i] != '\0' && inp[i] != ' ') {
    ++i;

    while (inp[i] != '\0' && inp[i] != ' ') {
      den_str.push_back(inp[i]);
      ++i;
    }

    den = std::atoi(den_str.c_str());
  }

  r = Rational(num, den);
  return is;
}

// Output
std::ostream &operator<<(std::ostream &os, Rational &r) {
  if (r.GetDenominator() == 1) {
    os << r.GetNumerator();
    return os;
  }

  os << r.GetNumerator() << '/' << r.GetDenominator();
  return os;
}

std::ostream &operator<<(std::ostream &os, const Rational &r) {
  if (r.GetDenominator() == 1) {
    os << r.GetNumerator();
    return os;
  }

  os << r.GetNumerator() << '/' << r.GetDenominator();
  return os;
}