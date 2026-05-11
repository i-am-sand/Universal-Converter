#include "BigFraction.h"

#include <stdexcept>

void cut(Fraction& f) {
  BigInteger gg = BigInteger::gcd(f.num_, f.den_);
  f.num_ /= gg;
  f.den_ /= gg;
}

Fraction::Fraction() = default;

Fraction::Fraction(BigInteger num, BigInteger den) {
  if (den.isZero()) {
      throw std::runtime_error("Zero denominator");
    }
  BigInteger gg = BigInteger::gcd(num, den);
  num /= gg;
  den /= gg;
  num_ = num;
  den_ = den;

}

Fraction::Fraction(BigInteger num) {
  num_ = num;
  den_ = 1;
}

Fraction::Fraction(const Fraction& other) = default;

Fraction::~Fraction() = default;

BigInteger Fraction::num() const {
  return num_;
}

BigInteger Fraction::den() const {
  return den_;
}

std::ostream& operator<<(std::ostream& out, const Fraction& fract) {
  out << fract.num_ << '/' << fract.den_;
  return out;
}

Fraction& Fraction::operator=(Fraction other) {
  num_ = other.num_;
  den_ = other.den_;

  if (den_.isZero()) {
      throw std::runtime_error("Zero denominator");
    }

  return *this;
}

Fraction& operator+=(Fraction& lhs, const Fraction& rhs) {
  lhs.num_ = lhs.num_ * rhs.den_ + rhs.num_ * lhs.den_;
  lhs.den_ = lhs.den_ * rhs.den_;

  cut(lhs);

  return lhs;
}

Fraction& operator+=(Fraction& lhs, BigInteger number) {
  lhs.num_ += number * lhs.den_;

  cut(lhs);

  return lhs;
}

Fraction& operator-=(Fraction& lhs, Fraction rhs) {
  lhs.num_ = lhs.num_ * rhs.den_ - rhs.num_ * lhs.den_;
  lhs.den_ = lhs.den_ * rhs.den_;

  cut(lhs);

  return lhs;
}

Fraction& operator-=(Fraction& lhs, BigInteger number) {
  lhs.num_ -= number * lhs.den_;

  cut(lhs);

  return lhs;
}

Fraction& operator*=(Fraction& lhs, const Fraction& rhs) {
  lhs.num_ *= rhs.num_;
  lhs.den_ *= rhs.den_;

  cut(lhs);

  return lhs;
}

Fraction& operator*=(Fraction& lhs, BigInteger number) {
  lhs.num_ *= number;

  cut(lhs);

  return lhs;
}

Fraction& operator/=(Fraction& lhs, Fraction rhs) {
  if (rhs.num_.isZero()) {
      throw std::runtime_error("Zero denominator");
    }

  BigInteger tt = rhs.num_;

  rhs.num_ = rhs.den_;
  rhs.den_ = tt;

  lhs *= rhs;

  cut(lhs);

  return lhs;
}

Fraction& operator/=(Fraction& lhs, BigInteger number) {
  if (number.isZero()) {
      throw std::runtime_error("Zero denominator");
    }

  lhs.den_ *= number;

  cut(lhs);

  return lhs;
}

Fraction operator+(Fraction lhs, Fraction rhs) {
  lhs += rhs;
  return lhs;
}

Fraction operator+(Fraction lhs, BigInteger number) {
  lhs += number;
  return lhs;
}

Fraction operator+(BigInteger number, Fraction rhs) {
  rhs += number;
  return rhs;
}

Fraction operator-(Fraction lhs, Fraction rhs) {
  lhs -= rhs;
  return lhs;
}

Fraction operator-(Fraction lhs, BigInteger number) {
  lhs -= number;
  return lhs;
}

Fraction operator-(BigInteger number, Fraction rhs) {
  Fraction temporary(number);

  temporary -= rhs;

  return temporary;
}

Fraction operator*(Fraction lhs, Fraction rhs) {
  lhs *= rhs;
  return lhs;
}

Fraction operator*(Fraction lhs, BigInteger number) {
  lhs *= number;
  return lhs;
}

Fraction operator*(BigInteger number, Fraction rhs) {
  rhs *= number;
  return rhs;
}

Fraction operator/(Fraction lhs, Fraction rhs) {
  lhs /= rhs;
  return lhs;
}

Fraction operator/(Fraction lhs, BigInteger number) {
  lhs /= number;
  return lhs;
}

Fraction operator/(BigInteger number, Fraction rhs) {
  Fraction temporary(number);

  temporary /= rhs;

  return temporary;
}

bool operator<(const Fraction& lhs, const Fraction& rhs) {
  return lhs.num_ * rhs.den_ < rhs.num_ * lhs.den_;
}

bool operator>(const Fraction& lhs, const Fraction& rhs) {
  return rhs < lhs;
}

bool operator>=(const Fraction& lhs, const Fraction& rhs) {
  return !(lhs < rhs);
}

bool operator<=(const Fraction& lhs, const Fraction& rhs) {
  return !(lhs > rhs);
}

bool operator==(const Fraction& lhs, const Fraction& rhs) {
  return !(lhs < rhs) && !(lhs > rhs);
}

bool operator!=(const Fraction& lhs, const Fraction& rhs) {
  return !(lhs == rhs);
}

bool operator<(const Fraction& lhs, BigInteger number) {
  Fraction temporary(number);
  return lhs < temporary;
}

bool operator>(const Fraction& lhs, BigInteger number) {
  Fraction temporary(number);
  return lhs > temporary;
}

bool operator>=(const Fraction& lhs, BigInteger number) {
  Fraction temporary(number);
  return lhs >= temporary;
}

bool operator<=(const Fraction& lhs, BigInteger number) {
  Fraction temporary(number);
  return lhs <= temporary;
}

bool operator==(const Fraction& lhs, BigInteger number) {
  Fraction temporary(number);
  return lhs == temporary;
}

bool operator!=(const Fraction& lhs, BigInteger number) {
  Fraction temporary(number);
  return lhs != temporary;
}

bool operator<(BigInteger number, const Fraction& rhs) {
  Fraction temporary(number);
  return temporary < rhs;
}

bool operator>(BigInteger number, const Fraction& rhs) {
  Fraction temporary(number);
  return temporary > rhs;
}

bool operator>=(BigInteger number, const Fraction& rhs) {
  Fraction temporary(number);
  return temporary >= rhs;
}

bool operator<=(BigInteger number, const Fraction& rhs) {
  Fraction temporary(number);
  return temporary <= rhs;
}

bool operator==(BigInteger number, const Fraction& rhs) {
  Fraction temporary(number);
  return temporary == rhs;
}

bool operator!=(BigInteger number, const Fraction& rhs) {
  Fraction temporary(number);
  return temporary != rhs;
}