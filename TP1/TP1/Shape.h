#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <stdexcept>
#include <memory>
#include "base-types.h"

namespace mitkov {
  class Shape {
  public:
    virtual double getArea() = 0;

    virtual rectangle_t getFrameRect() = 0;

    virtual void scale(double ratio) = 0;

    virtual void move(const point_t&) = 0;
    virtual void move(double deltaX, double deltaY) = 0;

    virtual ~Shape() = default;
  };
}
#endif