#include "Formatter.h"
#include <vector>
#include <map>
#include <string>
#include <stdexcept>

std::string Formatter::digit_to_string(const BigInteger& digit) {
  BigInteger ten(10), thirtyfive(35);
  if (digit < ten) {
      return digit.toString();
    }
  if (digit <= thirtyfive) {
      int d = std::stoi(digit.toString());
      char c = static_cast<char>('A' + d - 10);
      return std::string(1, c);
    }
  return "[" + digit.toString() + "]";
}

std::string Formatter::integer_to_base(BigInteger num, int base) {
  if (num.isZero()) {
      return "0";
    }
  std::vector<std::string> digits;
  BigInteger q(static_cast<uint64_t>(base));
  while(!num.isZero()) {
      BigInteger digit = num % q;
      num /= q;
      digits.push_back(digit_to_string(digit));
    }
  std::string res = "";
  for (int i = static_cast<int>(digits.size() - 1); i >= 0; --i) {
      res += digits[i];
    }
  return res;
}

std::string Formatter::format(const BigFraction& num, int base) {
  if (base < 2 || base > 500) {
      throw std::runtime_error("Error: invalid base");
    }
  BigInteger integer_part = num.integerPart();
  BigInteger remainder = num.remainder();
  BigInteger denominator = num.den();
  std::string result = integer_to_base(integer_part, base);
  if (result.size() > MAX_OUTPUT_LENGTH) {
      return result.substr(0, MAX_OUTPUT_LENGTH) +
             "...\nПолная запись результата слишком длинная. Показаны первые 100000 символов.";
    }
  if (remainder.isZero()) {
      return result;
    }
  result += ".";
  std::vector <std::string> fractional_digits;
  std::map<BigInteger, size_t> check_period;
  BigInteger q(static_cast<uint64_t>(base));
  while(!remainder.isZero()) {
      if (check_period.count(remainder)) {
          size_t period_start = check_period[remainder];
          for (size_t i = 0; i < fractional_digits.size(); ++i) {
              if (i == period_start) result += "(";
              result += fractional_digits[i];
              if (result.size() > MAX_OUTPUT_LENGTH) {
                  return result.substr(0, MAX_OUTPUT_LENGTH) +
                         "...\nПолная запись результата слишком длинная. Показаны первые 100000 символов.";
                }
            }
          result += ")";
          if (result.size() > MAX_OUTPUT_LENGTH) {
              return result.substr(0, MAX_OUTPUT_LENGTH) +
                     "...\nПолная запись результата слишком длинная. Показаны первые 100000 символов.";
            }
          return result;
        }
      check_period[remainder] = fractional_digits.size();
      remainder *= q;
      BigInteger digit = remainder / denominator;
      remainder %= denominator;
      fractional_digits.push_back(digit_to_string(digit));
      size_t current_length = result.size();
      for (const std::string& d : fractional_digits) {
          current_length += d.size();
        }
      if (current_length > MAX_OUTPUT_LENGTH) {
          for (const std::string& d : fractional_digits) {
              result += d;
              if (result.size() > MAX_OUTPUT_LENGTH) {
                  return result.substr(0, MAX_OUTPUT_LENGTH) +
                         "...\nПолная запись результата слишком длинная. Показаны первые 100000 символов.";
                }
            }
        }
    }
  for (const std::string& digit : fractional_digits) {
      result += digit;
      if (result.size() > MAX_OUTPUT_LENGTH) {
          return result.substr(0, MAX_OUTPUT_LENGTH) +
                 "...\nПолная запись результата слишком длинная. Показаны первые 100000 символов.";
        }
    }
  return result;
}