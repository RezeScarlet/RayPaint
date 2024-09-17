#include "../include/raylib-cpp.hpp"
#include <memory>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"

#include "Shapes.hpp"

int drawMode = 0;
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
  std::unique_ptr<Paint::Shape> tempShape;
  raylib::Vector2 mouseClick(0, 0);
  raylib::Vector2 mouseRelease(0, 0);
  int polySides = 3;
  bool sidesMode = false;
  while (WindowShouldClose() == false) {

    BeginDrawing();

    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    if (raylib::Mouse::IsButtonPressed(0)) {
      mouseClick.SetX(raylib::Mouse::GetX());
      mouseClick.SetY(raylib::Mouse::GetY());
    }

    if (IsMouseButtonReleased(0)) {

      switch (drawMode) {
      case 0: {

        shapes.push_back(
            std::make_unique<Paint::Line>(mouseClick, mouseRelease, lineColor));
        break;
      }
      case 1: {
        shapes.push_back(std::make_unique<Paint::Rectangle>(
            mouseClick, mouseRelease, lineColor, fillColor));
        break;
      }
      case 2: {
        shapes.push_back(std::make_unique<Paint::Ellipse>(
            mouseClick, mouseRelease, lineColor, fillColor));
        break;
      }
      case 3: {
        shapes.push_back(std::make_unique<Paint::Polygon>(
            mouseClick, mouseRelease, lineColor, fillColor, polySides));
        break;
      }
      }
    }

    for (auto &shape : shapes) {
      shape->Draw();
    }

    if (IsMouseButtonDown(0)) {
      mouseRelease.x = GetMouseX();
      mouseRelease.y = GetMouseY();

      switch (drawMode) {
      case 0: {
        Paint::Line tempLine(mouseClick, mouseRelease, lineColor);
        DrawLineV(mouseClick, mouseRelease, lineColor);
        tempLine.Draw();
        break;
      }
      case 1: {
        Paint::Rectangle tempRect(mouseClick, mouseRelease, lineColor,
                                  fillColor);
        tempRect.Draw();
        break;
      }
      case 2: {
        Paint::Ellipse tempEl(mouseClick, mouseRelease, lineColor, fillColor);
        tempEl.Draw();
        break;
      }
      case 3: {
        Paint::Polygon tempPoly(mouseClick, mouseRelease, lineColor, fillColor,
                                polySides);
        tempPoly.Draw();
        break;
      }
      }
    }

    // InterFace
    raylib::Rectangle guiGroupRect(8, 8, w - 16, 34);

    guiGroupRect.Draw(raylib::Color::RayWhite());

    GuiGroupBox(guiGroupRect, "CONTROLS");
    GuiToggleGroup(
        (Rectangle){13, 13, 60, 24},
        "Line; Rectangle; Ellipse; Polygon; Line Color; Fill Color",
        &Mode); // serve pra qnd vc clicar em cada button, o Mode mudar

    if (GuiSpinner((Rectangle){460, 13, 80, 24}, "Polygon Sides", &polySides, 3,
                   100, sidesMode))
      sidesMode = !sidesMode;

    if (Mode < 4) {
      drawMode = Mode;
    }

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
