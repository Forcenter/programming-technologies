#ifndef BASE_STRUCTS_HPP
#define BASE_STRUCTS_HPP

#include <vector>

namespace mitkov {
  struct Point {
    int x, y;
  };

  struct Polygon {
    std::vector< Point > points;
  };
}

#endif