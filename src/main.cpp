#include <../include/raylib-cpp.hpp>
#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"

#include "Shapes.hpp"

static void rectButton();
static void elliButton();
static void lineButton();

int main() {

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  raylib::Window window(854, 480);
  SetTargetFPS(60);

  float h = window.GetHeight();
  float w = window.GetWidth();

  bool lineButtonPressed = false;
  bool rectButtonPressed = false;
  bool elliButtonPressed = false;

  std::vector<Paint::Line> linha;
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
      Paint::Line linhaa(mouseRelease, mouseClick, raylib::Color::Black(), raylib::Color::Black());
      Paint::Line linhaTemp(mouseClick, mouseRelease);
      linha.push_back(linhaTemp);
    }
    DrawLineV(mouseClick, mouseRelease, raylib::Color::Black());
    for (Paint::Line x : linha) {

      DrawLineV(x.start, x.end, raylib::Color::Black());
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
static void rectButton() {
  // TODO: Implement control logic
}
static void elliButton() {
  // TODO: Implement control logic
}
static void lineButton() {
  // TODO: Implement control logic
}
