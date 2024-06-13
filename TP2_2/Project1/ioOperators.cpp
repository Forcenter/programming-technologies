#include "ioOperators.h"
#include "delimeter.h"
#include <iostream>

std::istream& mitkov::operator>>(std::istream& stream, ullIO&& ull)
{
  iofmtguard format(stream);
  return stream >> std::oct >> ull.value;
}

std::istream& mitkov::operator>>(std::istream& stream, complexIO&& val)
{
  iofmtguard format(stream);
  using del = delimeterIO;
  stream >> del{ '#' } >> del{ 'c' } >> del{ '(' };
  double real = 0;
  double imag = 0;
  stream >> real >> imag;

  val.value = std::complex< double >(real, imag);

  stream >> del{ ')' };
  return stream;
}

std::istream& mitkov::operator>>(std::istream& stream, stringIO&& val)
{
  iofmtguard format(stream);
  stream >> delimeterIO{ '\"' };
  return std::getline(stream, val.value, '\"');
}

std::istream& mitkov::operator>>(std::istream& stream, dataStruct& ds)
{
  std::istream::sentry sentry(stream);
  if (!sentry) {
    return stream;
  }
  mitkov::dataStruct input;
  {
    using del = mitkov::delimeterIO;
    using ull = mitkov::ullIO;
    using complex = mitkov::complexIO;
    using str = mitkov::stringIO;

    std::string keyString = "";
    stream >> del{ '(' } >> del{ ':' };
    for (int i = 0; i < 3; ++i) {
      stream >> keyString;
      if (keyString == "key1") {
        stream >> ull{ input.key1 };
      }
      else if (keyString == "key2") {
        stream >> complex{ input.key2 };
      }
      else if (keyString == "key3") {
        stream >> str{ input.key3 };
      }
      else {
        stream.setstate(std::ios::failbit);
      }
      stream >> del{ ':' };
    }
    stream >> del{ ')' };
  }
  if (stream) {
    ds = input;
  }
  return stream;
}

std::ostream& mitkov::operator<<(std::ostream& stream, const dataStruct& ds)
{
  iofmtguard format(stream);
  std::ostream::sentry sentry(stream);
  if (!sentry){
    return stream;
  }
  stream << "(:key1 0" << std::oct << ds.key1;
  stream.precision(1);
  stream << ":key2 #c(" << std::fixed << ds.key2.real() << ' ' << ds.key2.imag() << ')';
  stream << ":key3 \"" << ds.key3 << "\":)";
  return stream;
}