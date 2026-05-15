#pragma once

#include <iostream>
#include "BigInteger.h"

class BigFraction {
public:
  BigFraction();
  BigFraction(BigInteger num, BigInteger den);
  explicit BigFraction(BigInteger num);
  BigFraction(const BigFraction& other);
  ~BigFraction();

  BigInteger num() const;
  BigInteger den() const;

  BigFraction& operator=(BigFraction other);

  friend BigFraction& operator+=(BigFraction& lhs, const BigFraction& rhs);
  friend BigFraction& operator+=(BigFraction& lhs, BigInteger number);

  friend BigFraction& operator-=(BigFraction& lhs, BigFraction rhs);
  friend BigFraction& operator-=(BigFraction& lhs, BigInteger number);

  friend BigFraction& operator*=(BigFraction& lhs, const BigFraction& rhs);
  friend BigFraction& operator*=(BigFraction& lhs, BigInteger number);

  friend BigFraction& operator/=(BigFraction& lhs, BigFraction rhs);
  friend BigFraction& operator/=(BigFraction& lhs, BigInteger number);

  friend BigFraction operator+(BigFraction lhs, BigFraction rhs);
  friend BigFraction operator+(BigFraction lhs, BigInteger number);
  friend BigFraction operator+(BigInteger number, BigFraction rhs);

  friend BigFraction operator-(BigFraction lhs, BigFraction rhs);
  friend BigFraction operator-(BigFraction lhs, BigInteger number);
  friend BigFraction operator-(BigInteger number, BigFraction rhs);

  friend BigFraction operator*(BigFraction lhs, BigFraction rhs);
  friend BigFraction operator*(BigFraction lhs, BigInteger number);
  friend BigFraction operator*(BigInteger number, BigFraction rhs);

  friend BigFraction operator/(BigFraction lhs, BigFraction rhs);
  friend BigFraction operator/(BigFraction lhs, BigInteger number);
  friend BigFraction operator/(BigInteger number, BigFraction rhs);

  friend bool operator<(const BigFraction& lhs, const BigFraction& rhs);
  friend bool operator>(const BigFraction& lhs, const BigFraction& rhs);
  friend bool operator>=(const BigFraction& lhs, const BigFraction& rhs);
  friend bool operator<=(const BigFraction& lhs, const BigFraction& rhs);
  friend bool operator==(const BigFraction& lhs, const BigFraction& rhs);
  friend bool operator!=(const BigFraction& lhs, const BigFraction& rhs);

  friend bool operator<(const BigFraction& lhs, BigInteger number);
  friend bool operator>(const BigFraction& lhs, BigInteger number);
  friend bool operator>=(const BigFraction& lhs, BigInteger number);
  friend bool operator<=(const BigFraction& lhs, BigInteger number);
  friend bool operator==(const BigFraction& lhs, BigInteger number);
  friend bool operator!=(const BigFraction& lhs, BigInteger number);

  friend bool operator<(BigInteger number, const BigFraction& rhs);
  friend bool operator>(BigInteger number, const BigFraction& rhs);
  friend bool operator>=(BigInteger number, const BigFraction& rhs);
  friend bool operator<=(BigInteger number, const BigFraction& rhs);
  friend bool operator==(BigInteger number, const BigFraction& rhs);
  friend bool operator!=(BigInteger number, const BigFraction& rhs);

  friend std::ostream& operator<<(std::ostream& out, const BigFraction& fract);

  BigInteger integerPart() const {
    return num_ / den_;
  }
  BigInteger remainder() const {
    return num_ % den_;
  }

private:
  BigInteger num_ = BigInteger(0);
  BigInteger den_ = BigInteger(1);

  friend void cut(BigFraction& f);
};
