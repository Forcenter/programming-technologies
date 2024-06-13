#include "delimeter.h"
#include <iostream>

std::istream& mitkov::operator>>(std::istream& stream, delimeterIO&& val)
{
  std::istream::sentry sentry(stream);
  if (!sentry) {
    return stream;
  }
  char c = '0';
  stream >> c;
  if (stream && c != val.value) {
    stream.setstate(std::ios::failbit);
  }
  return stream;
}