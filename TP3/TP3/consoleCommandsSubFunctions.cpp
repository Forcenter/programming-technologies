#include "consoleCommandsSubFunctions.h"
#include <numeric>
#include <algorithm>
#include <functional>

bool mitkov::hasOddVertexesAmount(const Polygon& pol)
{
  return pol.points.size() % 2 == 1;
}

double mitkov::calculateArea::operator()(double area, const Point& pt)
{
  area += static_cast< double >(prev.x) * pt.y;
  area -= static_cast< double >(pt.x) * prev.y;
  prev = pt;
  return area;
}

double mitkov::getArea(double area, const Polygon& pol)
{
  calculateArea calc{ *pol.points.begin() };
  double result = 0;
  result += std::accumulate(pol.points.begin() + 1, pol.points.end(), 0.0, calc);
  result += static_cast< double >(pol.points[pol.points.size() - 1].x) * pol.points[0].y;
  result -= static_cast< double >(pol.points[0].x) * pol.points[pol.points.size() - 1].y;
  return area + std::abs(result / 2);
}

bool mitkov::isAreaSmaller(const Polygon& a, const Polygon& b)
{
  return getArea(0.0, a) < getArea(0.0, b);
}

bool mitkov::hasLessVertexes(const Polygon& a, const Polygon& b)
{
  return a.points.size() < b.points.size();
}

bool mitkov::hasNVertexes(const Polygon& a, size_t N)
{
  return a.points.size() == N;
}

bool mitkov::isRect(const Polygon& pol)
{
  if (pol.points.size() != 4) {
    return false;
  }
  bool flag = true;
  flag = flag && (distance(pol.points[0], pol.points[2]) == distance(pol.points[1], pol.points[3]));
  flag = flag && (distance(pol.points[0], pol.points[1]) == distance(pol.points[2], pol.points[3]));
  flag = flag && (distance(pol.points[1], pol.points[2]) == distance(pol.points[0], pol.points[3]));
  return flag;
}

bool mitkov::hasLessX(const Point& a, const Point& b)
{
  return a.x < b.x;
}

bool mitkov::hasLessY(const Point& a, const Point& b)
{
  return a.y < b.y;
}

int mitkov::distance(const Point& a, const Point& b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int mitkov::getMinPolygonX(int a, const Polygon& b)
{
  using namespace std::placeholders;
  int temp = std::min_element(b.points.begin(), b.points.end(), std::bind(hasLessX, _1, _2))->x;
  return a < temp ? a : temp;
}

int mitkov::getMaxPolygonX(int a, const Polygon& b)
{
  using namespace std::placeholders;
  int temp = std::max_element(b.points.begin(), b.points.end(), std::bind(hasLessX, _1, _2))->x;
  return a > temp ? a : temp;
}

int mitkov::getMinPolygonY(int a, const Polygon& b)
{
  using namespace std::placeholders;
  int temp = std::min_element(b.points.begin(), b.points.end(), std::bind(hasLessY, _1, _2))->y;
  return a < temp ? a : temp;
}

int mitkov::getMaxPolygonY(int a, const Polygon& b)
{
  using namespace std::placeholders;
  int temp = std::max_element(b.points.begin(), b.points.end(), std::bind(hasLessY, _1, _2))->y;
  return a > temp ? a : temp;
}

bool mitkov::isPointInframe(const Point& a, int x, int y, int width, int height)
{
  return a.x >= x && a.x <= x + width && a.y >= y && a.y <= y + height;
}
