#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.h"

namespace mitkov {
  class Rectangle: public Shape
  {
  public:
    Rectangle(const point_t&, const point_t&);

    ~Rectangle() = default;

    double getArea() override;

    rectangle_t getFrameRect() override;

    void scale(double ratio);

    void move(const point_t&) override;
    void move(double deltaX, double deltaY) override;

  private:
    point_t leftBottom;
    point_t topRight;

    point_t getCenter();
  };
}

#endif