#include "Polygon.h"

mitkov::Polygon::Polygon(std::unique_ptr< point_t[] >&& arr, size_t size):
  vertexesAmount(size),
  vertexes(std::move(arr))
{}

double mitkov::Polygon::getArea()
{
  double result = 0;
  for (size_t i = 0; i < vertexesAmount - 1; ++i) {
    result += vertexes[i].x * vertexes[i + 1].y;
    result -= vertexes[i + 1].x * vertexes[i].y;
  }
  result += vertexes[vertexesAmount - 1].x * vertexes[0].y;
  result -= vertexes[0].x * vertexes[vertexesAmount - 1].y;
  result /= 2;
  return std::abs(result);
}

mitkov::rectangle_t mitkov::Polygon::getFrameRect()
{
  double x = (vertexes[0].x + vertexes[1].x) / 2;
  double y = (vertexes[0].y + vertexes[1].y) / 2;
  double width = abs(vertexes[0].x - vertexes[1].x);
  double height = abs(vertexes[0].y - vertexes[1].y);
  double temp = 0;

  for (size_t i = 2; i < vertexesAmount; ++i) {
    if (vertexes[i].x < x - width / 2) {
      temp = x - width / 2 - vertexes[i].x;
      x -= temp / 2;
      width += temp;
    }
    if (vertexes[i].x > x + width / 2) {
      temp = vertexes[i].x - width / 2 - x;
      x += temp / 2;
      width += temp;
    }
    if (vertexes[i].y < y - height / 2) {
      temp = y - height / 2 - vertexes[i].y;
      y -= temp / 2;
      height += temp;
    }
    if (vertexes[i].y > y + height / 2) {
      temp = vertexes[i].y - height / 2 - y;
      y += temp / 2;
      height += temp;
    }
  }

  return rectangle_t{ { x, y }, width, height };
}

void mitkov::Polygon::scale(double ratio)
{
  point_t center = getCenter();
  for (size_t i = 0; i < vertexesAmount; ++i) {
    vertexes[i].x = center.x + (vertexes[i].x - center.x) * ratio;
    vertexes[i].y = center.y + (vertexes[i].y - center.y) * ratio;
  }
}

void mitkov::Polygon::move(const point_t& point)
{
  point_t center = getCenter();
  move(point.x - center.x, point.y - center.y);
}

void mitkov::Polygon::move(double deltaX, double deltaY)
{
  for (size_t i = 0; i < vertexesAmount; ++i) {
    vertexes[i].x += deltaX;
    vertexes[i].y += deltaY;
  }
}

mitkov::point_t mitkov::Polygon::getCenter()
{
  double x = 0;
  double y = 0;
  for (size_t i = 0; i < vertexesAmount; ++i) {
    x += vertexes[i].x;
    y += vertexes[i].y;
  }
  x /= static_cast< double >(vertexesAmount);
  y /= static_cast< double >(vertexesAmount);
  return point_t{ x, y };
}
