#pragma once

#include <iostream>
#include "BigInteger.h"

class Fraction {
public:
  Fraction();
  Fraction(BigInteger num, BigInteger den);
  explicit Fraction(BigInteger num);
  Fraction(const Fraction& other);
  ~Fraction();

  BigInteger num() const;
  BigInteger den() const;

  Fraction& operator=(Fraction other);

  friend Fraction& operator+=(Fraction& lhs, const Fraction& rhs);
  friend Fraction& operator+=(Fraction& lhs, BigInteger number);

  friend Fraction& operator-=(Fraction& lhs, Fraction rhs);
  friend Fraction& operator-=(Fraction& lhs, BigInteger number);

  friend Fraction& operator*=(Fraction& lhs, const Fraction& rhs);
  friend Fraction& operator*=(Fraction& lhs, BigInteger number);

  friend Fraction& operator/=(Fraction& lhs, Fraction rhs);
  friend Fraction& operator/=(Fraction& lhs, BigInteger number);

  friend Fraction operator+(Fraction lhs, Fraction rhs);
  friend Fraction operator+(Fraction lhs, BigInteger number);
  friend Fraction operator+(BigInteger number, Fraction rhs);

  friend Fraction operator-(Fraction lhs, Fraction rhs);
  friend Fraction operator-(Fraction lhs, BigInteger number);
  friend Fraction operator-(BigInteger number, Fraction rhs);

  friend Fraction operator*(Fraction lhs, Fraction rhs);
  friend Fraction operator*(Fraction lhs, BigInteger number);
  friend Fraction operator*(BigInteger number, Fraction rhs);

  friend Fraction operator/(Fraction lhs, Fraction rhs);
  friend Fraction operator/(Fraction lhs, BigInteger number);
  friend Fraction operator/(BigInteger number, Fraction rhs);

  friend bool operator<(const Fraction& lhs, const Fraction& rhs);
  friend bool operator>(const Fraction& lhs, const Fraction& rhs);
  friend bool operator>=(const Fraction& lhs, const Fraction& rhs);
  friend bool operator<=(const Fraction& lhs, const Fraction& rhs);
  friend bool operator==(const Fraction& lhs, const Fraction& rhs);
  friend bool operator!=(const Fraction& lhs, const Fraction& rhs);

  friend bool operator<(const Fraction& lhs, BigInteger number);
  friend bool operator>(const Fraction& lhs, BigInteger number);
  friend bool operator>=(const Fraction& lhs, BigInteger number);
  friend bool operator<=(const Fraction& lhs, BigInteger number);
  friend bool operator==(const Fraction& lhs, BigInteger number);
  friend bool operator!=(const Fraction& lhs, BigInteger number);

  friend bool operator<(BigInteger number, const Fraction& rhs);
  friend bool operator>(BigInteger number, const Fraction& rhs);
  friend bool operator>=(BigInteger number, const Fraction& rhs);
  friend bool operator<=(BigInteger number, const Fraction& rhs);
  friend bool operator==(BigInteger number, const Fraction& rhs);
  friend bool operator!=(BigInteger number, const Fraction& rhs);

  friend std::ostream& operator<<(std::ostream& out, const Fraction& fract);

private:
  BigInteger num_ = BigInteger(0);
  BigInteger den_ = BigInteger(1);

  friend void cut(Fraction& f);
};
