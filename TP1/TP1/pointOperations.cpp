#include "pointOperations.h"
#include <cmath>

std::ostream& mitkov::operator<<(std::ostream& stream, const point_t& pt)
{
  stream << pt.x << ' ' << pt.y;
  return stream;
}

std::pair<mitkov::point_t, mitkov::point_t> mitkov::getPointsOfRectangle(const mitkov::rectangle_t& rect)
{
  point_t a{ rect.pos.x - rect.width / 2, rect.pos.y - rect.height / 2 };
  point_t b{ rect.pos.x + rect.width / 2, rect.pos.y + rect.height / 2 };
  return std::pair< point_t, point_t >(a, b);
}

double mitkov::getDistanceBetween(const point_t& a, const point_t& b)
{
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool mitkov::operator==(const point_t& a, const point_t& b)
{
  return a.x == b.x && a.y == b.y;
}
