#include "../include/raylib-cpp.hpp"
#include <iostream>
#include <memory>
#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"

#include "Shapes.hpp"

static void rectButton();
static void elliButton();
static void lineButton();

static int buttonPressed =
    0; // 0 = line, 1 = rectangle, 2 = ellipse, 3 = polygon

int main() {

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  raylib::Window window(854, 480);
  SetTargetFPS(60);

  float h = window.GetHeight();
  float w = window.GetWidth();

  bool lineButtonPressed = false;
  bool rectButtonPressed = false;
  bool elliButtonPressed = false;

  std::vector<std::unique_ptr<Paint::Shape>> shapes;
  raylib::Vector2 mouseClick(0, 0);
  raylib::Vector2 mouseRelease(0, 0);

  raylib::Rectangle guiGroupRect(8, 8, w - 16, 34);

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
    }

    if (IsMouseButtonReleased(0)) {
      Paint::Line tempLine(mouseClick, mouseRelease);
      shapes.push_back(tempLine); // todo arrumar essa bosta
    }

    DrawLineV(mouseClick, mouseRelease, raylib::Color::Black());

    for (auto &shape : shapes) {

      shape->Draw();
    }

    GuiGroupBox(guiGroupRect, "CONTROLS");

    lineButtonPressed = GuiButton((Rectangle){13, 13, 120, 24}, "LINHA");
    rectButtonPressed = GuiButton((Rectangle){137, 13, 120, 24}, "RETANGULO");
    elliButtonPressed = GuiButton((Rectangle){260, 13, 120, 24}, "ELIPSE");

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
static void lineButton() { buttonPressed = 0; }
static void rectButton() { buttonPressed = 1; }
static void elliButton() { buttonPressed = 2; }
static void polyButton() { buttonPressed = 3; }
