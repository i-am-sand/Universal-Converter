#include "Converter.h"

std::string Converter::convert(const std::string& input, int from_base, int to_base) {
  Parser parser;
  Formatter formatter;
  BigFraction num = parser.parse(input, from_base);
  return formatter.format(num, to_base);
}
