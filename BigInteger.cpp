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
  for (int i = digits_.size() - 2; i >= 0; --i) {
      std::string block = std::to_string(digits_[i]);
      int zeros = Mbase_digits - static_cast<int>(block.length());
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

std::ostream& operator<<(std::ostream& os, const BigInteger& i) {
  os << i.toString();
  return os;
}

std::istream& operator>>(std::istream& is, BigInteger& i) {
  std::string s;
  is >> s;
  i = BigInteger(s);
  return is;
}

BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs) {
  int carry = 0;
  BigInteger res = lhs;
  for (size_t i = 0; i < std::max(res.digits_.size(), rhs.digits_.size()) || carry; ++i) {
      if (i == res.digits_.size()) {
          res.digits_.push_back(0);
        }
      res.digits_[i] += carry + (i < rhs.digits_.size() ? rhs.digits_[i] : 0);
      carry = (res.digits_[i] >= BigInteger::Mbase_);
      if (carry) res.digits_[i] -= BigInteger::Mbase_;
    }
  return res;
}

BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs) {
  if (lhs < rhs) throw std::runtime_error("Incorrect number");
  int carry = 0;
  BigInteger res = lhs;
  for (size_t i = 0; i < res.digits_.size() || carry; ++i) {
      res.digits_[i] -= carry + (i < rhs.digits_.size() ? rhs.digits_[i] : 0);
      carry = res.digits_[i] < 0;
      if (carry) res.digits_[i] += BigInteger::Mbase_;
    }
  res.trim();
  return res;
}

BigInteger operator*(const BigInteger& lhs, int rhs) {
  if (rhs < 0) throw std::runtime_error("Negative multiplier is not supported");
  if (rhs >= BigInteger::Mbase_) {
      return lhs * BigInteger(static_cast<uint64_t>(rhs));
    }
  if (lhs.isZero() || rhs == 0) {
      return BigInteger();
    }
  BigInteger res = lhs;
  int carry = 0;
  for (size_t i = 0; i < res.digits_.size() || carry; ++i) {
      if (i == res.digits_.size()) {
          res.digits_.push_back(0);
        }
      long long cur = carry + static_cast<long long>(res.digits_[i]) * rhs;
      res.digits_[i] = static_cast<int>(cur % BigInteger::Mbase_);
      carry = static_cast<int>(cur / BigInteger::Mbase_);
    }
  res.trim();
  return res;
}

BigInteger operator*(int lhs, const BigInteger& rhs) {
  return rhs * lhs;
}

BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs) {
  BigInteger res;
  res.digits_.resize(lhs.digits_.size() + rhs.digits_.size());
  for (size_t i = 0; i < lhs.digits_.size(); ++i) {
      for (int j = 0, carry = 0; j < static_cast<int>(rhs.digits_.size()) || carry; ++j) {
          long long cur = res.digits_[i + j] + static_cast<long long>(lhs.digits_[i]) *
          (j < static_cast<int>(rhs.digits_.size()) ? rhs.digits_[j] : 0) + carry;
          res.digits_[i + j] = static_cast<int>(cur % BigInteger::Mbase_);
          carry = static_cast<int>(cur / BigInteger::Mbase_);
        }
    }
  res.trim();
  return res;
}

BigInteger operator/(const BigInteger& lhs, int rhs) {
  if (rhs <= 0) throw std::runtime_error("Division by zero or negative number");
  BigInteger res = lhs;
  int carry = 0;
  for (int i = static_cast<int>(res.digits_.size()) - 1; i >= 0; --i) {
      long long cur = res.digits_[i] + static_cast<long long>(carry) * BigInteger::Mbase_;
      res.digits_[i] = static_cast<int>(cur / rhs);
      carry = static_cast<int>(cur % rhs);
    }
  res.trim();
  return res;
}

int operator%(const BigInteger& lhs, int rhs) {
  if (rhs <= 0) throw std::runtime_error("Division by zero or negative number");
  long long remain = 0;
  for (int i = static_cast<int>(lhs.digits_.size()) - 1; i >= 0; --i) {
      long long cur = lhs.digits_[i] + remain * BigInteger::Mbase_;
      remain = cur % rhs;
    }
  return static_cast<int>(remain);
}

BigInteger operator/(const BigInteger& lhs, const BigInteger& rhs) {
  if (rhs.isZero()) {
      throw std::runtime_error("Division by zero");
    }
  if (lhs < rhs) {
      return BigInteger();
    }
  BigInteger res;
  res.digits_.resize(lhs.digits_.size());
  BigInteger cur;
  for (int i = static_cast<int>(lhs.digits_.size()) - 1; i >= 0; --i) {
      cur.digits_.insert(cur.digits_.begin(), lhs.digits_[i]);
      cur.trim();
      int left = 0;
      int right = BigInteger::Mbase_ - 1;
      int x = 0;
      while(left <= right) {
          int mid = left + (right - left)/2;
          BigInteger prod = mid * rhs;
          if (prod <= cur) {
              x = mid;
              left = mid + 1;
            } else {
              right = mid - 1;
            }
        }
      res.digits_[i] = x;
      cur = cur - rhs * x;
    }
  res.trim();
  return res;
}

BigInteger operator%(const BigInteger& lhs, const BigInteger& rhs) {
  if (rhs.isZero()) {
      throw std::runtime_error("Modulo by zero");
    }
  BigInteger quot = lhs / rhs;
  BigInteger remain = lhs - quot * rhs;
  remain.trim();
  return remain;
}

BigInteger BigInteger::gcd(BigInteger lhs, BigInteger rhs) {
  while (!rhs.isZero()) {
      BigInteger r = lhs % rhs;
      lhs = rhs;
      rhs = r;
    }
  return lhs;
}

bool operator<(const BigInteger& lhs, const BigInteger& rhs) {
  if (lhs.digits_.size() != rhs.digits_.size()) {
      return lhs.digits_.size() < rhs.digits_.size();
    }
  for (int i = static_cast<int>(lhs.digits_.size()) - 1; i >= 0; --i) {
      if (lhs.digits_[i] != rhs.digits_[i]) {
          return lhs.digits_[i] < rhs.digits_[i];
        }
    }
  return false;
}

bool operator>(const BigInteger& lhs, const BigInteger& rhs) {
  return rhs < lhs;
}

bool operator==(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs < rhs) && !(lhs > rhs);
}

bool operator<=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(rhs < lhs);
}

bool operator>=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs < rhs);
}

bool operator!=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs == rhs);
}

BigInteger& BigInteger::operator+=(const BigInteger& rhs) {
  *this = *this + rhs;
  return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& rhs) {
  *this = *this - rhs;
  return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& rhs) {
  *this = *this * rhs;
  return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& rhs) {
  *this = *this / rhs;
  return *this;
}

BigInteger& BigInteger::operator*=(int rhs) {
  *this = *this * rhs;
  return *this;
}

BigInteger& BigInteger::operator/=(int rhs) {
  *this = *this / rhs;
  return *this;
}