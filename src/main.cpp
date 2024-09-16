#include "../include/raylib-cpp.hpp"
#include <iostream>
#include <memory>
#include <raylib.h>
#include <sys/types.h>
#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"

#include "Shapes.hpp"

int drawMode = 0; // 0 = line, 1 = rectangle, 2 = ellipse, 3 = polygon
int Mode = 0;     // 0 = line, 1 = rectangle, 2 = ellipse, 3 = polygon, 4 =
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

      switch (drawMode) {
      case 0: { // não sei se isso vai ser o melhor. desse jeito qnd vc
                // seleciona
        // cor e depois vai desenhar ele não desenha o temp pq o mode tá
        // como 4 PQ ACABOU DE SELECIONAR COLOR PICKER
        DrawLineV(mouseClick, mouseRelease, lineColor);
        break;
      }
      case 1: {
        DrawRectangleV(mouseClick, mouseRelease - mouseClick, fillColor);
        break;
      }
      }
    }

    if (IsMouseButtonReleased(0)) {

      switch (drawMode) {
      case 0: {
        Paint::Line tempLine(mouseClick, mouseRelease, lineColor);
        shapes.push_back(
            std::make_unique<Paint::Line>(mouseClick, mouseRelease, lineColor));
        break;
      }
      case 1: {
        Paint::Rectangle tempRect(mouseClick, mouseRelease, lineColor,
                                  fillColor);
        shapes.push_back(std::make_unique<Paint::Rectangle>(
            mouseClick, mouseRelease - mouseClick, lineColor, fillColor));
        break;
      }
      }
    }

    for (auto &shape : shapes) {
      shape->Draw();
    }

    // InterFace

    raylib::Rectangle guiGroupRect(8, 8, w - 16, 34);

    guiGroupRect.Draw(raylib::Color::RayWhite());

    GuiGroupBox(guiGroupRect, "CONTROLS");
    GuiToggleGroup(
        (Rectangle){13, 13, 120, 24},
        "Line;Rectangle;Ellipse;Polygon;Line Color;Fill Color",
        &Mode); // serve pra qnd vc clicar em cada button, o Mode mudar

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
