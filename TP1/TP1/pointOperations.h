#ifndef POINT_OPERATIONS_HPP
#define POINT_OPERATIONS_HPP

#include <utility>
#include <ostream>
#include "base-types.h"

namespace mitkov {
  std::ostream& operator<<(std::ostream& stream, const point_t& pt);
  std::pair< point_t, point_t > getPointsOfRectangle(const rectangle_t& rect);
  double getDistanceBetween(const point_t& a, const point_t& b);
  bool operator==(const point_t& a, const point_t& b);
}

#endif