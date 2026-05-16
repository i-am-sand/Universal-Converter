#pragma once
#include <string>
#include <map>
#include "BigFraction.h"


class Formatter {
public:
  std::string format(const BigFraction& num, int base);
private:
  std::string digit_to_string(const BigInteger& digit);
  std::string integer_to_base(BigInteger num, int base);
};

