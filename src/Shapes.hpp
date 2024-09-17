#include "../include/raylib-cpp.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <raylib.h>

namespace Paint {

class Shape {
public:
  raylib::Vector2 start;
  raylib::Vector2 end;
  raylib::Color lineColor;
  raylib::Color fillColor;

  inline Shape(raylib::Vector2 start, raylib::Vector2 end,
               raylib::Color lineColor = raylib::Color::Black(),
               raylib::Color fillColor = raylib::Color::White())
      : start(start), end(end), lineColor(lineColor), fillColor(fillColor) {}
  virtual void Draw() = 0;
  virtual ~Shape() = default;
};

class Line : public Shape {
public:
  void Draw();
  Line(raylib::Vector2 start, raylib::Vector2 end,
       raylib::Color lineColor = raylib::Color::Black(),
       raylib::Color fillColor = raylib::Color::White())
      : Shape(start, end, lineColor, fillColor) {}
};

class Rectangle : public Shape {
public:
  void Draw();
  Rectangle(raylib::Vector2 start, raylib::Vector2 end,
            raylib::Color lineColor = raylib::Color::Black(),
            raylib::Color fillColor = raylib::Color::White())
      : Shape(start, end, lineColor, fillColor) {}
};
class Ellipse : public Shape {
public:
  void Draw();
  Ellipse(raylib::Vector2 start, raylib::Vector2 end,
          raylib::Color lineColor = raylib::Color::Black(),
          raylib::Color fillColor = raylib::Color::White())
      : Shape(start, end, lineColor, fillColor) {}
};
class Polygon : public Shape {
public:
  int sides;
  void Draw();
  Polygon(raylib::Vector2 start, raylib::Vector2 end,
          raylib::Color lineColor = raylib::Color::Black(),
          raylib::Color fillColor = raylib::Color::White(), int sides = 3)
      : Shape(start, end, lineColor, fillColor), sides(sides) {}
};

inline void Line::Draw() { DrawLineV(start, end, lineColor); }
inline void Rectangle::Draw() {
  float xStartD = start.x < end.x ? start.x : end.x;
  float xEndD = start.x < end.x ? end.x : start.x;

  float yStartD = start.y < end.y ? start.y : end.y;
  float yEndD = start.y < end.y ? end.y : start.y;

  raylib::Vector2 size = {xEndD - xStartD, yEndD - yStartD};

  DrawRectangleV({xStartD, yStartD}, size, fillColor);
  DrawRectangleLines(xStartD, yStartD, xEndD - xStartD, yEndD - yStartD,
                     lineColor);
}
inline void Ellipse::Draw() {
  raylib::Vector2 center = (start + end) / 2.0f;

  float radiusX = fabs(end.x - start.x) / 2.0f;
  float radiusY = fabs(end.y - start.y) / 2.0f;

  DrawEllipse(center.x, center.y, radiusX, radiusY, fillColor);

  DrawEllipseLines(center.x, center.y, radiusX, radiusY, lineColor);
}
inline void Polygon::Draw() {

  float radius = fabs(end.x - start.x);

  float rotation = atan2(end.y - start.y, end.x - start.x) * (180.0f / PI);

  DrawPoly(start, sides, radius, rotation, fillColor);
  DrawPolyLines(start, sides, radius, rotation, lineColor);
}
} // namespace Paint
