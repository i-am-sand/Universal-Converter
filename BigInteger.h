#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>


class BigInteger {
public:
  BigInteger(); // *
  BigInteger(uint64_t value); // *
  BigInteger(const std::string& decimal); // *
  ~BigInteger();

  std::string toString() const; // *
  bool isZero() const; // *
  void trim(); // *

  friend std::ostream& operator<<(std::ostream& os, const BigInteger& i); // *
  friend std::istream& operator>>(std::istream& is, BigInteger& i); // *
  friend BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs); // *
  friend BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs); // *
  friend BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs); // *
  friend BigInteger operator*(const BigInteger& lhs, int rhs); // *
  friend BigInteger operator*(int lhs, const BigInteger& rhs); // *
  friend BigInteger operator/(const BigInteger& lhs, int rhs); // *
  friend int operator%(const BigInteger& lhs, int rhs); // *
  friend BigInteger operator/(const BigInteger& lhs, const BigInteger& rhs); // *
  friend BigInteger operator%(const BigInteger& lhs, const BigInteger& rhs); // *
  static BigInteger gcd(BigInteger lhs, BigInteger rhs); // *
  friend bool operator<(const BigInteger& lhs, const BigInteger& rhs); // *
  friend bool operator<=(const BigInteger& lhs, const BigInteger& rhs); // *
  friend bool operator>(const BigInteger& lhs, const BigInteger& rhs); // *
  friend bool operator>=(const BigInteger& lhs, const BigInteger& rhs); // *
  friend bool operator==(const BigInteger& lhs, const BigInteger& rhs); // *
  friend bool operator!=(const BigInteger& lhs, const BigInteger& rhs); // *
  BigInteger& operator+=(const BigInteger& rhs);
  BigInteger& operator-=(const BigInteger& rhs);
  BigInteger& operator*=(const BigInteger& rhs);
  BigInteger& operator/=(const BigInteger& rhs);
  BigInteger& operator*=(int rhs);
  BigInteger& operator/=(int rhs);

private:
  static const int Mbase_ = 1000*1000*1000;
  static const int Mbase_digits = 9;
  std::vector<int> digits_;
};
