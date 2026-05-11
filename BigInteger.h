#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <sstream>
#include <iomanip>

class BigInteger {
public:
  BigInteger();
  BigInteger(uint64_t value);
  BigInteger(const std::string& decimal);
  ~BigInteger();

  std::string toString() const;
  bool isZero() const;
  void trim();

  friend std::ostream& operator<<(std::ostream& os, const BigInteger& i);
  friend BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs);
  friend BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs);
  friend BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs);
  friend BigInteger operator/(const BigInteger& lhs, const BigInteger& rhs);
  friend BigInteger operator%(const BigInteger& lhs, const BigInteger& rhs);
  friend BigInteger operator<(const BigInteger& lhs, const BigInteger& rhs);
  friend BigInteger operator<=(const BigInteger& lhs, const BigInteger& rhs);
  friend BigInteger operator>(const BigInteger& lhs, const BigInteger& rhs);
  friend BigInteger operator>=(const BigInteger& lhs, const BigInteger& rhs);
  friend BigInteger operator==(const BigInteger& lhs, const BigInteger& rhs);
  friend BigInteger operator!=(const BigInteger& lhs, const BigInteger& rhs);

private:
  static const int Mbase_ = 1000*1000*1000;
  static const int Mbase_digits = 9;
  std::vector<int> digits_;
};
