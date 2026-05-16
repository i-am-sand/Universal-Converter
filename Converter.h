#pragma once
#include "Formatter.h"
#include "Parser.h"

class Converter
{
public:
  std::string convert(const std::string& input, int from_base, int to_base);
};
