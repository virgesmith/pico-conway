#pragma once

#include "libraries/pico_display_2/pico_display_2.hpp"
#include "libraries/generic_st7789/generic_st7789.hpp"
#include "font8_data.hpp"

#include <tuple>

using pimoroni::ST7789Generic, pimoroni::PicoDisplay2, pimoroni::Rect;

namespace {
  uint16_t buffer[PicoDisplay2::WIDTH * PicoDisplay2::HEIGHT];
}


// Lightweight RAII wrapper for PicoDisplay2
class Display final : public ST7789Generic
{
public:
  static const uint8_t MAX_BRIGHTNESS = 255;
  // ST7789Generic(uint16_t width, uint16_t height, bool round=false, uint16_t *frame_buffer=nullptr) :
  explicit Display(uint8_t brightness=MAX_BRIGHTNESS) : ST7789Generic(PicoDisplay2::WIDTH, PicoDisplay2::HEIGHT, false, buffer)
  {
    //init();
    set_backlight(brightness);
  }

  ~Display()
  {
    clear();
    set_backlight(0);
  }
};

