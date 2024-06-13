#include "Rectangle.h"

mitkov::Rectangle::Rectangle(const point_t& vertex1_, const point_t& vertex2_):
  leftBottom(vertex1_),
  topRight(vertex2_)
{}

double mitkov::Rectangle::getArea()
{
  return std::abs(leftBottom.x - topRight.x) * std::abs(leftBottom.y - topRight.y);
}

mitkov::rectangle_t mitkov::Rectangle::getFrameRect()
{
  double x = (leftBottom.x + topRight.x) / 2;
  double y = (leftBottom.y + topRight.y) / 2;
  double width = std::abs(leftBottom.x - topRight.x);
  double height = std::abs(leftBottom.y - topRight.y);
  return rectangle_t{ { x, y }, width, height };
}

void mitkov::Rectangle::scale(double ratio)
{
  point_t center = getCenter();

  leftBottom.x = center.x + (leftBottom.x - center.x) * ratio;
  leftBottom.y = center.y + (leftBottom.y - center.y) * ratio;
  topRight.x = center.x + (topRight.x - center.x) * ratio;
  topRight.y = center.y + (topRight.y - center.y) * ratio;
}

void mitkov::Rectangle::move(const point_t& center_)
{
  point_t center = getCenter();
  move(center_.x - center.x, center_.y - center.y);
}

void mitkov::Rectangle::move(double deltaX, double deltaY)
{
  leftBottom.x += deltaX;
  leftBottom.y += deltaY;
  topRight.x += deltaX;
  topRight.y += deltaY;
}

mitkov::point_t mitkov::Rectangle::getCenter()
{
  return point_t{ (leftBottom.x + topRight.x) / 2, (leftBottom.y + topRight.y) / 2 };
}
