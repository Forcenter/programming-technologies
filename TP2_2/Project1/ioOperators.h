#ifndef IO_OPERATORS
#define IO_OPERATORS
#include <ios>
#include "basicStructs.h"
#include "ioGuard.h"

namespace mitkov {
  std::istream& operator>>(std::istream& stream, ullIO&&);
  std::istream& operator>>(std::istream& stream, complexIO&&);
  std::istream& operator>>(std::istream& stream, stringIO&&);
  std::istream& operator>>(std::istream& stream, dataStruct&);

  std::ostream& operator<<(std::ostream& stream, const dataStruct&);
}

#endif