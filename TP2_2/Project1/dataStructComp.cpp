#include "dataStructComp.h"

namespace mitkov
{
  double complexCompareFormat(std::complex< double > value) {
    return value.real() * value.real() + value.imag() * value.imag();
  }
}

bool mitkov::compLess::operator()(const dataStruct& lhs, const dataStruct& rhs)
{
  if (lhs.key1 != rhs.key1) {
    return lhs.key1 < rhs.key1;
  }
  if (lhs.key2 != rhs.key2) {
    return complexCompareFormat(lhs.key2) < complexCompareFormat(rhs.key2);
  }
  return lhs.key3.size() < lhs.key3.size();
}