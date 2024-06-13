#include "Diamond.h"

mitkov::Diamond::Diamond(const point_t& a, const point_t& b, const point_t& c):
  center_p(getCenter(a, b, c)),
  hor_p(getHorPoint(a, b, c)),
  vert_p(getVertPoint(a, b, c))
{}


mitkov::rectangle_t mitkov::Diamond::getFrameRect()
{
  double width = std::abs(hor_p.x - center_p.x) * 2;
  double height = std::abs(vert_p.y - center_p.y) * 2;
  return rectangle_t{ center_p, width, height };
}

void mitkov::Diamond::scale(double ratio)
{
  hor_p.x = center_p.x + (hor_p.x - center_p.x) * ratio;
  hor_p.y = center_p.y + (hor_p.y - center_p.y) * ratio;
  vert_p.x = center_p.x + (vert_p.x - center_p.x) * ratio;
  vert_p.y = center_p.y + (vert_p.y - center_p.y) * ratio;
}

double mitkov::Diamond::getArea()
{
  rectangle_t frameRect = getFrameRect();
  return frameRect.width * frameRect.height / 2;
}

void mitkov::Diamond::move(const point_t& target)
{
  move(target.x - center_p.x, target.y - center_p.y);
}

void mitkov::Diamond::move(double deltaX, double deltaY)
{
  center_p.x += deltaX;
  center_p.y += deltaY;
  hor_p.x += deltaX;
  hor_p.y += deltaY;
  vert_p.x += deltaX;
  vert_p.y += deltaY;
}

const mitkov::point_t& mitkov::Diamond::getHorPoint(const point_t& a, const point_t& b, const point_t& c)
{
  const char* UNABLE_TO_CREATE_A_SHAPE_ERROR = "Couldn't create a Shape with this inputs";
  double sideAB = getDistanceBetween(a, b);
  double sideAC = getDistanceBetween(a, c);
  double sideBC = getDistanceBetween(c, b);

  double hyp = std::max(sideAB, sideAC);
  hyp = std::max(hyp, sideBC);

  if (hyp == sideAB) {
    if (c.x != a.x && c.y != a.y) {
      throw std::invalid_argument(UNABLE_TO_CREATE_A_SHAPE_ERROR);
    }
    if (c.y == a.y) {
      return a;
    }
    return b;
  }
  if (hyp == sideAC) {
    if (b.x != a.x && b.y != a.y) {
      throw std::invalid_argument(UNABLE_TO_CREATE_A_SHAPE_ERROR);
    }
    if (b.y == a.y) {
      return a;
    }
    return c;
  }
  if (c.x != a.x && c.y != a.y) {
    throw std::invalid_argument(UNABLE_TO_CREATE_A_SHAPE_ERROR);
  }
  if (c.y == a.y) {
    return c;
  }
  return b;
}

const mitkov::point_t& mitkov::Diamond::getVertPoint(const point_t& a, const point_t& b, const point_t& c)
{
  double sideAB = getDistanceBetween(a, b);
  double sideAC = getDistanceBetween(a, c);
  double sideBC = getDistanceBetween(c, b);

  double hyp = std::max(sideAB, sideAC);
  hyp = std::max(hyp, sideBC);

  if (hyp == sideAB) {
    if (hor_p == a) {
      return b;
    }
    return a;
  }
  if (hyp == sideAC) {
    if (hor_p == a) {
      return c;
    }
    return a;
  }
  if (hor_p == b) {
    return c;
  }
  return b;
}

const mitkov::point_t& mitkov::Diamond::getCenter(const point_t& a, const point_t& b, const point_t& c)
{
  const char* UNABLE_TO_CREATE_A_SHAPE_ERROR = "Couldn't create a Shape with this inputs";
  double sideAB = getDistanceBetween(a, b);
  double sideAC = getDistanceBetween(a, c);
  double sideBC = getDistanceBetween(c, b);

  double hyp = std::max(sideAB, sideAC);
  hyp = std::max(hyp, sideBC);
  double squareAB = sideAB * sideAB;
  double squareAC = sideAC * sideAC;
  double squareBC = sideBC * sideBC;
  if (std::abs(squareAB + squareAC + squareBC - 2 * hyp * hyp) > 0.01) {
    throw std::invalid_argument(UNABLE_TO_CREATE_A_SHAPE_ERROR);
  }

  if (hyp == sideAB) {
    return c;
  }
  if (hyp == sideAC) {
    return b;
  }
  return a;
}