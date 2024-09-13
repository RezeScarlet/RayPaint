#include <../include/raylib-cpp.hpp>
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
};
class Ellipse : public Shape {
public:
  void Draw();
};
class Polygon : public Shape {
public:
  void Draw();
};
inline void Line::Draw() { DrawLineV(start, end, lineColor); }
} // namespace Paint
