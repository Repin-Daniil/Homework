#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <numeric>

#include "rational.h"
#include "rational.h"  // check include guards

SCENARIO("Rational Constructors", "[Rational]")
{
  SECTION("Default constructor")
  {
    Rational x;

    CHECK(x.GetNumerator() == 0);
    CHECK(x.GetDenominator() == 1);
  }

  SECTION("Construction from int")
  {
    SECTION("Positive integer") {
      Rational x(15);

      CHECK(x.GetNumerator() == 15);
      CHECK(x.GetDenominator() == 1);
    }

    SECTION("Negative integer") {
      Rational x(-15);

      CHECK(x.GetNumerator() == -15);
      CHECK(x.GetDenominator() == 1);
    }
  }

  SECTION("Construction from numerator and denominator")
  {
    SECTION("Construction from positive integers") {
      Rational x(15, 19);

      CHECK(x.GetNumerator() == 15);
      CHECK(x.GetDenominator() == 19);
    }

    SECTION("Construction with negative denominator") {
      Rational x(15, -19);

      CHECK(x.GetNumerator() == -15);
      CHECK(x.GetDenominator() == 19);
    }

    SECTION("Construction from both negative integers") {
      Rational x(-15, -19);

      CHECK(x.GetNumerator() == 15);
      CHECK(x.GetDenominator() == 19);
    }

    SECTION("Construction from not coprime integers")
    {
      Rational x(15, 60);

      CHECK(x.GetNumerator() == 1);
      CHECK(x.GetDenominator() == 4);
    }

    SECTION("Construction with zero in denominator")
    {
      CHECK_THROWS_AS(Rational(0, 0), RationalDivisionByZero);
    }
  }

  SECTION("Construction from other Rational")
  {
    Rational a(15, 19);
    Rational b(a);

    CHECK(b.GetNumerator() == 15);
    CHECK(b.GetDenominator() == 19);
  }
}

SCENARIO("Rational Setters", "[Rational]")
{
  Rational x(5, 6);

  SECTION("SetNumerator")
  {
    WHEN("we set normal numerator, that don't need reduce")
    {
      x.SetNumerator(1);

      THEN("it will not reduce")
      {
        CHECK(x == Rational(1, 6));
      }
    }

    WHEN("Set non-coprime integer in numerator")
    {
      x.SetNumerator(3);

      THEN("It will reduce")
      {
        CHECK(x == Rational(1, 2));
      }
    }
  }

  SECTION("SetDenominator")
  {
    WHEN("we set normal denominator, that don't need reduce")
    {
      x.SetDenominator(9);

      THEN("it will not reduce")
      {
        CHECK(x == Rational(5, 9));
      }
    }

    WHEN("Set non-coprime integer in denominator")
    {
      x.SetDenominator(25);

      THEN("It will reduce")
      {
        CHECK(x == Rational(1, 5));
      }
    }

    WHEN("We set zero as a denominator")
    {
      THEN("We catch exception RationalDivisionByZero")
      {
        CHECK_THROWS_AS(x.SetDenominator(0), RationalDivisionByZero);
      }
    }
  }
}

SCENARIO("Binary arithmetic operations", "[Rational]")
{
  Rational a(1, 6);
  Rational b(3, 7);

  SECTION("Addition")
  {
    SECTION("a + b")
    {
      Rational c = a + b;
      CHECK(c == Rational(25, 42));
    }

    SECTION("b + a")
    {
      Rational c = b + a;
      CHECK(c == Rational(25, 42));
    }

    SECTION("Rational + int")
    {
      Rational c = a + 6;
      CHECK(c == Rational(37, 6));
    }

    SECTION("a + 0 = a")
    {
      Rational c = a + 0;
      CHECK(c == Rational(1, 6));
    }
  }

  SECTION("Subtraction")
  {
    SECTION("b - a > 0")
    {
      Rational c = b - a;
      CHECK(c == Rational(11, 42));
    }

    SECTION("a - b < 0")
    {
      Rational c = a - b;
      CHECK(c == Rational(-11, 42));
    }

    SECTION("Rational - int")
    {
      Rational c = a - 6;
      CHECK(c == Rational(-35, 6));
    }

    SECTION("a - 0 = a")
    {
      Rational c = a - 0;
      CHECK(c == Rational(1, 6));
    }
  }

  SECTION("Multiplication")
  {
    SECTION("a * b")
    {
      Rational c = a * b;
      CHECK(c == Rational(1, 14));
    }

    SECTION("b * a")
    {
      Rational c = b * a;
      CHECK(c == Rational(1, 14));
    }

    SECTION("Rational * int")
    {
      Rational c = a * 6;
      CHECK(c == Rational(1, 1));
    }

    SECTION("a * 1 = a")
    {
      Rational c = a * 1;
      CHECK(c == Rational(1, 6));
    }

    SECTION("a * 0 = 0")
    {
      Rational c = a * 0;

      CHECK(c.GetNumerator() == 0);
      CHECK(c.GetDenominator() == 1);
    }
  }

  SECTION("Division")
  {
    SECTION("a / b")
    {
      Rational c = a / b;
      CHECK(c == Rational(7, 18));
    }

    SECTION("b / a")
    {
      Rational c = b / a;
      CHECK(c == Rational(18, 7));
    }

    SECTION("Rational / int")
    {
      Rational c = a / 6;
      CHECK(c == Rational(1, 36));
    }

    SECTION("a / 1 = a")
    {
      Rational c = a / 1;
      CHECK(c == Rational(1, 6));
    }

    SECTION("1 / a ")
    {
      Rational c = 1 / a;
      CHECK(c == Rational(6, 1));
    }

    SECTION("a / 0")
    {
      CHECK_THROWS_AS(a / 0, RationalDivisionByZero);
    }
  }
}

SCENARIO("Assignment arithmetic operators", "[Rational]")
{
  Rational a(1, 6);
  Rational b(3, 7);

  SECTION("Addition")
  {
    SECTION("a += b")
    {
      a += b;
      CHECK(a == Rational(25, 42));
    }

    SECTION("Rational += int")
    {
      a += 6;
      CHECK(a == Rational(37, 6));
    }

    SECTION("a += 0")
    {
      a += 0;
      CHECK(a == Rational(1, 6));
    }
  }

  SECTION("Substraction")
  {
    SECTION("b -= a > 0")
    {
      b -= a;
      CHECK(b == Rational(11, 42));
    }

    SECTION("a -= b < 0")
    {
      a -= b;
      CHECK(a == Rational(-11, 42));
    }

    SECTION("Rational -= int")
    {
      a -= 6;
      CHECK(a == Rational(-35, 6));
    }

    SECTION("a -= 0")
    {
      a -= 0;
      CHECK(a == Rational(1, 6));
    }
  }

  SECTION("Multiplication")
  {
    SECTION("a *= b")
    {
      a *= b;
      CHECK(a == Rational(1, 14));
    }

    SECTION("Rational *= int")
    {
      a *= 6;
      CHECK(a == Rational(1, 1));
    }

    SECTION("a *= 1")
    {
      a *= 1;
      CHECK(a == Rational(1, 6));
    }

    SECTION("a *= 0")
    {
      a *= 0;
      CHECK(a == Rational(0, 1));
    }
  }

  SECTION("Division")
  {
    SECTION("a /= b")
    {
      a /= b;
      CHECK(a == Rational(7, 18));
    }

    SECTION("b / a")
    {
      b /= a;
      CHECK(b == Rational(18, 7));
    }

    SECTION("Rational /= int")
    {
      a /= 6;
      CHECK(a == Rational(1, 36));
    }

    SECTION("a /= 1 = a")
    {
      a /= 1;
      CHECK(a == Rational(1, 6));
    }

    SECTION("a /= 0 ")
    {
      CHECK_THROWS_AS(a /= 0, RationalDivisionByZero);
    }
  }
}

SCENARIO("Unary arithmetic operators", "[Rational]")
{
  Rational a(1, 3);
  Rational b(-1, 3);

  SECTION("Unary +")
  {
    SECTION("+ positive Rational") {
      Rational c = +a;
      CHECK(c == Rational(1, 3));
    }

    SECTION("+ negative Rational") {
      Rational c = +b;
      CHECK(c == Rational(-1, 3));
    }
  }

  SECTION("Unary -")
  {
    SECTION("- positive Rational") {
      Rational c = -a;
      CHECK(c == Rational(-1, 3));
    }

    SECTION("- negative Rational") {
      Rational c = -b;
      CHECK(c == Rational(1, 3));
    }
  }

  SECTION("Increment") {
    Rational a(2, 3);
    Rational b(3, 4);

    SECTION("Prefix") {
      Rational c = ++a;

      CHECK(a == Rational(5, 3));
      CHECK(c == Rational(5, 3));
    }

    SECTION("Postfix") {
      CHECK(a++ == Rational(2, 3));
      CHECK(a == Rational(5, 3));
    }

    SECTION("Complex") {
      Rational c = ++a++;

      CHECK(c == Rational(5, 3));
      CHECK(a == Rational(5, 3));
    }
  }

  SECTION("Decrement") {
    Rational a(2, 3);
    Rational b(3, 4);

    SECTION("Prefix") {
      Rational c = --a;

      CHECK(a == Rational(-1, 3));
      CHECK(c == Rational(-1, 3));
    }

    SECTION("Postfix") {
      CHECK(a-- == Rational(2, 3));
      CHECK(a == Rational(-1, 3));
    }

    SECTION("Complex") {
      Rational c = --a--;
      CHECK(c == Rational(-1, 3));
      CHECK(a == Rational(-1, 3));
    }
  }

  SECTION("Postfix + Prefix") {
    Rational a(-5, 4);
    Rational b(6, 9);

    CHECK(a-- + --b == Rational(-19, 12));
    CHECK(a++ - ++b == Rational(-35, 12));
  }

  SECTION("Comparison operators", "[Rational]") {
    Rational a(2, 3);
    Rational b(3, 4);

    CHECK(a < b);
    CHECK(b > a);
    CHECK(a >= a);
    CHECK(a <= a);
    CHECK(a <= b);
    CHECK(b >= a);
    CHECK(a == Rational(2, 3));
    CHECK(a != b);
  }
}

SCENARIO("Input and output operators", "[Rational]") {
  SECTION("Operator >>") {
    SECTION("Positive Rational from string") {
      std::string input_string = "3/4";
      std::istringstream input(input_string);

      Rational a;
      input >> a;

      CHECK(a == Rational(3, 4));
    }

    SECTION("Negative Rational from string") {
      std::string input_string = "-55/8";
      std::istringstream input(input_string);

      Rational a;
      input >> a;

      CHECK(a == Rational(-55, 8));
    }

    SECTION("Integer from string") {
      std::string input_string = "165";
      std::istringstream input(input_string);

      Rational a;
      input >> a;

      CHECK(a == Rational(165));
    }

    SECTION("Negative Integer from string, that need reduce") {
      std::string input_string = "-330/165";
      std::istringstream input(input_string);

      Rational a;
      input >> a;

      CHECK(a == Rational(-2));
    }

    SECTION("Non coprime Rational from string") {
      std::string input_string = "3/27";
      std::istringstream input(input_string);

      Rational a;
      input >> a;

      CHECK(a == Rational(1, 9));
    }

    SECTION("Two Rationals from one string") {
      std::string input_string = "-12/144 2";
      std::istringstream input(input_string);

      Rational a, b;
      input >> a >> b;

      CHECK(a == Rational(-1, 12));
      CHECK(b == Rational(2));
    }
  }

  SECTION("Operator <<") {
    Rational a(3, 4);
    Rational b(-55, 8);
    Rational c(165);

    std::stringstream ss;

    SECTION("Positive Rational to string") {
      ss << a;
      CHECK(ss.str() == "3/4");
    }

    SECTION("Negative Rational to string") {
      ss << b;
      CHECK(ss.str() == "-55/8");
    }

    SECTION("Integer to string") {
      ss << c;
      CHECK(ss.str() == "165");
    }
  }
}

SCENARIO("Operations with max int", "[Rational]") {
  int max = std::numeric_limits<int>::max();
  Rational a(15996, max);
  Rational b(397, max);

  CHECK(a + b == Rational(15996 + 397, max));
}