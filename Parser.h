#pragma once
#include <string>
#include <vector>
#include "BigFraction.h"

struct ParsedNumber{
public:
  std::vector<int> integer_digits;
  std::vector<int> fractional_digits;
  std::vector<int> period_digits;

  bool has_point = false;
  bool has_period = false;
};


class Parser {
public:
  BigFraction parse(const std::string& input, int base);
private:
  int ReadDigit(const std::string& input, size_t& pos, int base);
  ParsedNumber split(const std::string& input, int base);
  BigInteger to_BigInteger(const std::vector<int>& digits, int base);
};

