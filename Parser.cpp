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

