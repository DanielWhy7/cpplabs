export module fraction;

import std;

export class Fraction {
private:
  long long numerator;
  long long denominator;

  long long gcd(long long a, long long b) const {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
      long long temp = b;
      b = a % b;
      a = temp;
    }
    return a == 0 ? 1 : a;
  }

  void reduce() {
    if (denominator == 0) {
      throw std::invalid_argument("Denominator cannot be zero");
    }
    if (denominator < 0) {
      numerator = -numerator;
      denominator = -denominator;
    }
    long long g = gcd(numerator, denominator);
    numerator /= g;
    denominator /= g;
  }

public:
  Fraction(long long num = 0, long long denom = 1) 
    : numerator(num), denominator(denom) {
    reduce();
  }

  long long a() const { return numerator; }
  long long b() const { return denominator; }

  Fraction operator+(long long num) const {
    return Fraction(numerator + num * denominator, denominator);
  }

  Fraction operator*(long long num) const {
    return Fraction(numerator * num, denominator);
  }

  Fraction operator+(const Fraction& other) const {
    return Fraction(
      numerator * other.denominator + other.numerator * denominator,
      denominator * other.denominator
    );
  }

  Fraction operator-(const Fraction& other) const {
    return Fraction(
      numerator * other.denominator - other.numerator * denominator,
      denominator * other.denominator
    );
  }

  Fraction operator*(const Fraction& other) const {
    return Fraction(numerator * other.numerator, denominator * other.denominator);
  }

  Fraction operator/(const Fraction& other) const {
    if (other.numerator == 0) {
      throw std::invalid_argument("Division by zero");
    }
    return Fraction(numerator * other.denominator, denominator * other.numerator);
  }

  bool operator<(const Fraction& other) const {
    return numerator * other.denominator < other.numerator * denominator;
  }

  bool operator==(const Fraction& other) const {
    return numerator == other.numerator && denominator == other.denominator;
  }

  bool operator<=(const Fraction& other) const {
    return *this < other || *this == other;
  }

  std::string to_string() const {
    return std::format("{}/{}", numerator, denominator);
  }
};

export std::string to_string(const Fraction& f) {
  return f.to_string();
}

export Fraction add(const Fraction& f, long long num) {
  return f + num;
}
