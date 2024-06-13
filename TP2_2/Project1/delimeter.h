#ifndef DELIMETER_H
#define DELIMETER_H
#include <ios>

namespace mitkov {
  struct delimeterIO {
    char value;
  };

  std::istream& operator>>(std::istream& stream, delimeterIO&&);
}

#endif