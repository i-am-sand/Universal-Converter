#include "BigFraction.h"

#include <stdexcept>

void cut(BigFraction& f) {
  BigInteger gg = BigInteger::gcd(f.num_, f.den_);
  f.num_ /= gg;
  f.den_ /= gg;
}

BigFraction::BigFraction() = default;

BigFraction::BigFraction(BigInteger num, BigInteger den) {
  if (den.isZero()) {
      throw std::runtime_error("Zero denominator");
    }
  BigInteger gg = BigInteger::gcd(num, den);
  num /= gg;
  den /= gg;
  num_ = num;
  den_ = den;

}

BigFraction::BigFraction(BigInteger num) {
  num_ = num;
  den_ = 1;
}

BigFraction::BigFraction(const BigFraction& other) = default;

BigFraction::~BigFraction() = default;

BigInteger BigFraction::num() const {
  return num_;
}

BigInteger BigFraction::den() const {
  return den_;
}

std::ostream& operator<<(std::ostream& out, const BigFraction& fract) {
  out << fract.num_ << '/' << fract.den_;
  return out;
}

BigFraction& BigFraction::operator=(BigFraction other) {
  num_ = other.num_;
  den_ = other.den_;

  if (den_.isZero()) {
      throw std::runtime_error("Zero denominator");
    }

  return *this;
}

BigFraction& operator+=(BigFraction& lhs, const BigFraction& rhs) {
  lhs.num_ = lhs.num_ * rhs.den_ + rhs.num_ * lhs.den_;
  lhs.den_ = lhs.den_ * rhs.den_;

  cut(lhs);

  return lhs;
}

BigFraction& operator+=(BigFraction& lhs, BigInteger number) {
  lhs.num_ += number * lhs.den_;

  cut(lhs);

  return lhs;
}

BigFraction& operator-=(BigFraction& lhs, BigFraction rhs) {
  if (lhs < rhs) throw std::runtime_error("Negative fraction is not supported");
  lhs.num_ = lhs.num_ * rhs.den_ - rhs.num_ * lhs.den_;
  lhs.den_ = lhs.den_ * rhs.den_;

  cut(lhs);

  return lhs;
}

BigFraction& operator-=(BigFraction& lhs, BigInteger number) {
  if (lhs <  number) throw std::runtime_error("Negative fraction is not supported");
  lhs.num_ -= number * lhs.den_;

  cut(lhs);

  return lhs;
}

BigFraction& operator*=(BigFraction& lhs, const BigFraction& rhs) {
  lhs.num_ *= rhs.num_;
  lhs.den_ *= rhs.den_;

  cut(lhs);

  return lhs;
}

BigFraction& operator*=(BigFraction& lhs, BigInteger number) {
  lhs.num_ *= number;

  cut(lhs);

  return lhs;
}

BigFraction& operator/=(BigFraction& lhs, BigFraction rhs) {
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

BigFraction& operator/=(BigFraction& lhs, BigInteger number) {
  if (number.isZero()) {
      throw std::runtime_error("Zero denominator");
    }

  lhs.den_ *= number;

  cut(lhs);

  return lhs;
}

BigFraction operator+(BigFraction lhs, BigFraction rhs) {
  lhs += rhs;
  return lhs;
}

BigFraction operator+(BigFraction lhs, BigInteger number) {
  lhs += number;
  return lhs;
}

BigFraction operator+(BigInteger number, BigFraction rhs) {
  rhs += number;
  return rhs;
}

BigFraction operator-(BigFraction lhs, BigFraction rhs) {
  lhs -= rhs;
  return lhs;
}

BigFraction operator-(BigFraction lhs, BigInteger number) {
  lhs -= number;
  return lhs;
}

BigFraction operator-(BigInteger number, BigFraction rhs) {
  BigFraction temporary(number);

  temporary -= rhs;

  return temporary;
}

BigFraction operator*(BigFraction lhs, BigFraction rhs) {
  lhs *= rhs;
  return lhs;
}

BigFraction operator*(BigFraction lhs, BigInteger number) {
  lhs *= number;
  return lhs;
}

BigFraction operator*(BigInteger number, BigFraction rhs) {
  rhs *= number;
  return rhs;
}

BigFraction operator/(BigFraction lhs, BigFraction rhs) {
  lhs /= rhs;
  return lhs;
}

BigFraction operator/(BigFraction lhs, BigInteger number) {
  lhs /= number;
  return lhs;
}

BigFraction operator/(BigInteger number, BigFraction rhs) {
  BigFraction temporary(number);

  temporary /= rhs;

  return temporary;
}

bool operator<(const BigFraction& lhs, const BigFraction& rhs) {
  return lhs.num_ * rhs.den_ < rhs.num_ * lhs.den_;
}

bool operator>(const BigFraction& lhs, const BigFraction& rhs) {
  return rhs < lhs;
}

bool operator>=(const BigFraction& lhs, const BigFraction& rhs) {
  return !(lhs < rhs);
}

bool operator<=(const BigFraction& lhs, const BigFraction& rhs) {
  return !(lhs > rhs);
}

bool operator==(const BigFraction& lhs, const BigFraction& rhs) {
  return !(lhs < rhs) && !(lhs > rhs);
}

bool operator!=(const BigFraction& lhs, const BigFraction& rhs) {
  return !(lhs == rhs);
}

bool operator<(const BigFraction& lhs, BigInteger number) {
  BigFraction temporary(number);
  return lhs < temporary;
}

bool operator>(const BigFraction& lhs, BigInteger number) {
  BigFraction temporary(number);
  return lhs > temporary;
}

bool operator>=(const BigFraction& lhs, BigInteger number) {
  BigFraction temporary(number);
  return lhs >= temporary;
}

bool operator<=(const BigFraction& lhs, BigInteger number) {
  BigFraction temporary(number);
  return lhs <= temporary;
}

bool operator==(const BigFraction& lhs, BigInteger number) {
  BigFraction temporary(number);
  return lhs == temporary;
}

bool operator!=(const BigFraction& lhs, BigInteger number) {
  BigFraction temporary(number);
  return lhs != temporary;
}

bool operator<(BigInteger number, const BigFraction& rhs) {
  BigFraction temporary(number);
  return temporary < rhs;
}

bool operator>(BigInteger number, const BigFraction& rhs) {
  BigFraction temporary(number);
  return temporary > rhs;
}

bool operator>=(BigInteger number, const BigFraction& rhs) {
  BigFraction temporary(number);
  return temporary >= rhs;
}

bool operator<=(BigInteger number, const BigFraction& rhs) {
  BigFraction temporary(number);
  return temporary <= rhs;
}

bool operator==(BigInteger number, const BigFraction& rhs) {
  BigFraction temporary(number);
  return temporary == rhs;
}

bool operator!=(BigInteger number, const BigFraction& rhs) {
  BigFraction temporary(number);
  return temporary != rhs;
}