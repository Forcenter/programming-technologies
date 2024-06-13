#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "Shape.h"
#include <string>
namespace mitkov {
  class Polygon: public Shape
  {
  public:
    Polygon(std::unique_ptr< point_t[] >&&, size_t size);

    double getArea() override;

    rectangle_t getFrameRect() override;

    void scale(double ratio) override;

    void move(const point_t&) override;
    void move(double deltaX, double deltaY) override;

  private:
    size_t vertexesAmount;
    std::unique_ptr< point_t[] > vertexes;

    point_t getCenter();
  };
}

#endif