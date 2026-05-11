#include "BigInteger.h"

BigInteger::BigInteger(): digits_() {}

BigInteger::BigInteger(uint64_t value) {
  while (value > 0) {
      digits_.push_back(value % Mbase_);
      value /= Mbase_;
    }
}

BigInteger::BigInteger(const std::string& decimal) {
  for (int i = decimal.length(); i > 0; i -= Mbase_digits) {
      int start = std::max(0, i - Mbase_digits);
      int len = i - start;
      int block = std::stoi(decimal.substr(start, len));
      digits_.push_back(block);
    }
  trim();
}

void BigInteger::trim() {
  while (!digits_.empty() && digits_.back() == 0) {
      digits_.pop_back();
    }
}

std::string BigInteger::toString() const {
  if (digits_.empty()) {
      return "0";
    }
  std::string result = "";
  result += std::to_string(digits_.back());
  for (int i = digits_.size() - 2; i > 0; --i) {
      std::string block = std::to_string(digits_[i]);
      int zeros = Mbase_digits - block.length();
      for (int j = 0; j < zeros; ++j) {
          result += "0";
        }
      result += block;
    }
  return result;
}

bool BigInteger::isZero() const
{
  return digits_.empty();
}














