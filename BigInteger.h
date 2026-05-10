#include <vector>
#include <string>
#include <cstdint>

class BigInteger {
public:
  BigInteger();
  BigInteger(uint64_t value);
  BigInteger(const std::string& decimal);

  std::string toString() const;
  bool isZero() const;

  ~BigInteger();
private:
  static const int Mbase = 1000*1000*1000;
  std::vector<int> digits;
};
