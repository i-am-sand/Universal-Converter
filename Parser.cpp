#include "Parser.h"

std::string posMessage(size_t pos) {
  return " в позиции " + std::to_string(pos + 1);
}

int Parser::ReadDigit(const std::string& input, size_t& pos, int base) {
  if (pos >= input.size()) throw std::runtime_error("Ошибка: неожиданный конец строки");
  size_t start_pos = pos;
  std::string digit_text;
  int digit = -1;
  if (input[pos] >= '0' && input[pos] <= '9') {
      digit = input[pos] - '0';
      digit_text = std::string(1, input[pos]);
      ++pos;
    } else if (input[pos] >= 'A' && input[pos] <= 'Z') {
      digit = input[pos] - 'A' + 10;
      digit_text = std::string(1, input[pos]);
      ++pos;
    } else if (input[pos] >= 'a' && input[pos] <= 'z') {
      digit = input[pos] - 'a' + 10;
      digit_text = std::string(1, input[pos]);
      ++pos;
    } else if (input[pos] == '[') {
      ++pos;
      if (pos >= input.size() || !std::isdigit(static_cast<unsigned char>(input[pos]))) {
          throw std::runtime_error(
              "Ошибка: внутри квадратных скобок должна быть непустая десятичная запись числа" +
              posMessage(start_pos)
              );
        }
      int value = 0;
      std::string inside = "";
      while(pos < input.size() && std::isdigit(static_cast<unsigned char>(input[pos]))) {
          value = value * 10 + (input[pos] - '0');
          inside += input[pos];
          ++pos;
        }
      if (pos >= input.size() || input[pos] != ']') {
          throw std::runtime_error(
              "Ошибка: отсутствует закрывающая квадратная скобка" +
              posMessage(start_pos)
              );
        }
      ++pos;
      digit = value;
      digit_text = "[" + inside + "]";
    } else {
      throw std::runtime_error(
          "Ошибка: недопустимый символ '" + std::string(1, input[pos]) + "'" +
          posMessage(pos)
          );
    }
  std::string quot = "'";
  if (digit >= base) {
      throw std::runtime_error(
        "Ошибка: цифра " + quot + digit_text + quot +
        " недопустима в системе счисления с основанием " +
        std::to_string(base)
        );
    }
  return digit;
}

ParsedNumber Parser::split(const std::string& input, int base) {
  if (input.empty()) {
      throw std::runtime_error("Ошибка: входная строка пуста");
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
          throw std::runtime_error(
              "Ошибка: пробелы внутри числа не допускаются" +
              posMessage(pos)
              );
        }
      if (c == '.') {
          if (result.has_point) {
              throw std::runtime_error(
                  "Ошибка: точка встречается более одного раза" +
                  posMessage(pos)
                  );
            }
          if (result.integer_digits.empty()) {
              throw std::runtime_error("Ошибка: отсутствует целая часть");
            }
          if (state == State::Period) {
              throw std::runtime_error(
                  "Ошибка: точка не может находиться внутри периода" +
                  posMessage(pos)
                  );
            }
          result.has_point = true;
          state = State::Fractional;
          ++pos;
          if (pos >= input.size()) {
              throw std::runtime_error("Ошибка: отсутствует дробная часть после точки");
            }
        } else if (c == '(') {
          if (!result.has_point) {
              throw std::runtime_error("Ошибка: период не может быть записан без точки" + posMessage(pos));
            }
          if (result.has_period) {
              throw std::runtime_error(
                  "Ошибка: период указан более одного раза" +
                  posMessage(pos)
                  );
            }
          result.has_period = true;
          state = State::Period;
          ++pos;
          if (pos >= input.size()) {
              throw std::runtime_error("Ошибка: отсутствует закрывающая круглая скобка периода");
            }
          if (pos < input.size() && input[pos] == ')') {
              throw std::runtime_error("Ошибка: период не может быть пустым");
            }
        } else if (c == ')') {
          if (!result.has_period || state != State::Period) {
              throw std::runtime_error(
                  "Ошибка: лишняя закрывающая круглая скобка" +
                  posMessage(pos)
                  );
            }
          ++pos;
          if (pos != input.size()) {
              throw std::runtime_error("Ошибка: символы после закрывающей скобки периода недопустимы");
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
      throw std::runtime_error("Ошибка: отсутствует целая часть");
    }
  if (result.has_point && result.fractional_digits.empty() && !result.has_period) {
      throw std::runtime_error("Ошибка: отсутствует дробная часть после точки");
    }
  if (result.has_period && result.period_digits.empty()) {
      throw std::runtime_error("Ошибка: период не может быть пустым");
    }
  if (result.has_period && input.back() != ')') {
      throw std::runtime_error("Ошибка: отсутствует закрывающая круглая скобка периода");
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
      throw std::runtime_error("Ошибка: основание исходной системы должно быть целым числом от 2 до 500");
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