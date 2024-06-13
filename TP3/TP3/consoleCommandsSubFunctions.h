#ifndef LOGICAL_FUNCTIONS_H
#define LOGICAL_FUNCTIONS_H
#include <string>
#include "base-structs.h"
namespace mitkov {
  bool hasOddVertexesAmount(const Polygon& pol);
  struct calculateArea {
    Point prev;
    double operator()(double area, const Point& pt);
  };
  double getArea(double area, const Polygon& pol);
  bool isAreaSmaller(const Polygon& a, const Polygon& b);
  bool hasLessVertexes(const Polygon& a, const Polygon& b);
  bool hasNVertexes(const Polygon& a, size_t N);
  bool isRect(const Polygon& pol);
  bool hasLessX(const Point& a, const Point& b);
  bool hasLessY(const Point& a, const Point& b);
  int distance(const Point& a, const Point& b);
  int getMinPolygonX(int a, const Polygon& b);
  int getMaxPolygonX(int a, const Polygon& b);
  int getMinPolygonY(int a, const Polygon& b);
  int getMaxPolygonY(int a, const Polygon& b);
  bool isPointInframe(const Point& a, int x, int y, int width, int height);
}

#endif