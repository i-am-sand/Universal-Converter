#pragma once
#include <string>
#include "BigFraction.h"
const size_t MAX_OUTPUT_LENGTH = 100000;


class Formatter {
public:
  std::string format(const BigFraction& num, int base);
private:
  std::string digit_to_string(const BigInteger& digit);
  std::string integer_to_base(BigInteger num, int base);
};

