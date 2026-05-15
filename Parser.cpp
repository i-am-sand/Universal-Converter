#include "Parser.h"

int Parser::ReadDigit(const std::string& input, size_t& pos, int base) {
  if (pos >= input.size()) throw std::runtime_error("Unexpected end of input");
  int digit = -1;
  if (input[pos] >= '0' && input[pos] <= '9') {
      digit = input[pos] - '0';
      ++pos;
    } else if (input[pos] >= 'A' && input[pos] <= 'Z') {
      digit = input[pos] - 'A' + 10;
      ++pos;
    } else if (input[pos] >= 'a' && input[pos] <= 'z') {
      digit = input[pos] - 'a' + 10;
      ++pos;
    } else if (input[pos] == '[') {
      ++pos;
      if (pos >= input.size() || !std::isdigit(static_cast<unsigned char>(input[pos]))) {
          throw std::runtime_error("Error: empty digit in brackets");
        }
      int value = 0;
      while(pos < input.size() && std::isdigit(static_cast<unsigned char>(input[pos]))) {
          value = value * 10 + (input[pos] - '0');
          ++pos;
        }
      if (pos >= input.size() || input[pos] != ']') {
          throw std::runtime_error("Error: missing closing bracket");
        }
      ++pos;
      digit = value;
    } else {
      throw std::runtime_error("Error: invalid digit");
    }
  if (digit >= base) throw std::runtime_error("Error: digit is not valid for this base");
  return digit;
}

ParsedNumber Parser::split(const std::string& input, int base) {
  if (input.empty()) {
      throw std::runtime_error("Error: input string is empty");
    }
  ParsedNumber result;
  enum class State {
    Integer,
    Fractional,
    Period
  };
  State state = State::Integer;
  size_t pos = 0;
  while(pos < input.size()) {
      char c = input[pos];
      if (std::isspace(static_cast<unsigned char>(c))) {
          throw std::runtime_error("Error: spaces are not allowed");
        }
      if (c == '.') {
          if (result.has_point) {
              throw std::runtime_error("Error: more than one dot");
            }
          if (result.integer_digits.empty()) {
              throw std::runtime_error("Error: missing integer part");
            }
          result.has_point = true;
          state = State::Fractional;
          ++pos;
          if (pos >= input.size()) {
              throw std::runtime_error("Error: missing fractional part after dot");
            }
        } else if (c == '(') {
          if (!result.has_point) {
              throw std::runtime_error("Error: period without fractional part");
            }
          if (result.has_period) {
              throw std::runtime_error("Error: more than one period");
            }
          result.has_period = true;
          state = State::Period;
          ++pos;
          if (pos < input.size() && input[pos] == ')') {
              throw std::runtime_error("Error: period cannot be empty");
            }
        } else if (c == ')') {
          if (!result.has_period || state != State::Period) {
              throw std::runtime_error("Error: unexpected closing parenthesis");
            }
          ++pos;
          if (pos != input.size()) {
              throw std::runtime_error("Error: symbols after period are not allowed");
            }
          break;
        } else {
          int digit = ReadDigit(input, pos, base);
          if (state == State::Integer) result.integer_digits.push_back(digit);
          else if (state == State::Fractional) result.fractional_digits.push_back(digit);
          else result.period_digits.push_back(digit);
        }
    }
  if (result.integer_digits.empty()) {
      throw std::runtime_error("Error: missing integer part");
    }
  if (result.has_point && result.fractional_digits.empty() && !result.has_period) {
      throw std::runtime_error("Error: missing fractional part after dot");
    }
  if (result.has_period && result.period_digits.empty()) {
      throw std::runtime_error("Error: period cannot be empty");
    }
  return result;
}

BigInteger Parser::to_BigInteger(const std::vector<int>& digits, int base) {
  BigInteger result = BigInteger(0);
  for (int digit : digits) {
      result *= base;
      result += BigInteger(static_cast<uint64_t>(digit));
    }
  return result;
}

BigInteger powBigInteger(BigInteger base, size_t power) {
  BigInteger result(1);
  for (size_t i = 0; i < power; ++i) {
      result *= base;
    }
  return result;
}

BigFraction Parser::parse(const std::string& input, int base) {
  if (base < 2 || base > 500) {
      throw std::runtime_error("Error: invalid base");
    }
  ParsedNumber parsed = split(input, base);
  BigInteger I = to_BigInteger(parsed.integer_digits, base);
  BigInteger F = to_BigInteger(parsed.fractional_digits, base);
  BigInteger P = to_BigInteger(parsed.period_digits, base);
  size_t k = parsed.fractional_digits.size();
  size_t m = parsed.period_digits.size();
  BigInteger p(static_cast<uint64_t>(base));
  BigInteger pk = powBigInteger(p, k);

  if (!parsed.has_period) {
      BigInteger numerator = I * pk + F;
      BigInteger denomenator = pk;
      return BigFraction(numerator, denomenator);
    }
  BigInteger pm = powBigInteger(p, m);
  BigInteger pm_minus_1 = pm - BigInteger(1);
  BigInteger numerator = I * pk * pm_minus_1 + F * pm_minus_1 + P;
  BigInteger denomenator = pk * pm_minus_1;
  return BigFraction(numerator, denomenator);
}