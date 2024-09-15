#include "../include/raylib-cpp.hpp"
#include <iostream>
#include <memory>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"

#include "Shapes.hpp"

int Mode = 0; // 0 = line, 1 = rectangle, 2 = ellipse, 3 = polygon, 4 =
              // lineColor, 5 = fillColor
raylib::Color lineColor = raylib::Color::Black();
raylib::Color fillColor = raylib::Color::Black();
int main() {

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  raylib::Window window(854, 480);
  SetTargetFPS(60);

  float h = window.GetHeight();
  float w = window.GetWidth();

  std::vector<std::unique_ptr<Paint::Shape>> shapes;
  raylib::Vector2 mouseClick(0, 0);
  raylib::Vector2 mouseRelease(0, 0);

  while (WindowShouldClose() == false) {

    BeginDrawing();

    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    if (raylib::Mouse::IsButtonPressed(0)) {
      mouseClick.SetX(raylib::Mouse::GetX());
      mouseClick.SetY(raylib::Mouse::GetY());
    }

    if (IsMouseButtonDown(0)) {
      mouseRelease.x = GetMouseX();
      mouseRelease.y = GetMouseY();
      
      DrawLineV(mouseClick, mouseRelease, lineColor);
    }

    if (IsMouseButtonReleased(0)) {
      Paint::Line tempLine(mouseClick, mouseRelease);
      shapes.push_back(std::make_unique<Paint::Line>(mouseClick, mouseRelease));
    }

    for (auto &shape : shapes) {

      shape->Draw();
    }

    // InterFace

    raylib::Rectangle guiGroupRect(8, 8, w - 16, 34);
    guiGroupRect.Draw(raylib::Color::RayWhite());
    GuiGroupBox(guiGroupRect, "CONTROLS");
    GuiToggleGroup((Rectangle){13, 13, 120, 24},
                   "Line;Rectangle;Ellipse;Polygon;Line Color;Fill Color",
                   &Mode);
    if (Mode == 4) {
      GuiColorPicker((Rectangle){w - 149, 8, 120, 120}, NULL, &lineColor);
    }

    if (Mode == 5) {
      GuiColorPicker((Rectangle){w - 149, 8, 120, 120}, NULL, &fillColor);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
