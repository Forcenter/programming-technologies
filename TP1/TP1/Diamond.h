#ifndef DIAMOND_HPP
#define DIAMOND_HPP

#include "Shape.h"
#include "pointOperations.h"

namespace mitkov {
  class Diamond: public Shape
  {
  public:
    Diamond(const point_t&, const point_t&, const point_t&);

    ~Diamond() = default;

    rectangle_t getFrameRect() override;

    void scale(double ratio) override;

    double getArea() override;

    void move(const point_t&) override;
    void move(double deltaX, double deltaY) override;

  private:
    point_t center_p;
    point_t hor_p;
    point_t vert_p;

    const point_t& getCenter(const point_t& a, const point_t& b, const point_t& c);
    const point_t& getHorPoint(const point_t& a, const point_t& b, const point_t& c);
    const point_t& getVertPoint(const point_t& a, const point_t& b, const point_t& c);
  };
}

#endif