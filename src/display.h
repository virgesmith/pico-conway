#pragma once

#include "libraries/pico_display_2/pico_display_2.hpp"
#include "font8_data.hpp"

#include <tuple>

using pimoroni::PicoDisplay2, pimoroni::Rect;

namespace {
  uint16_t buffer[PicoDisplay2::WIDTH * PicoDisplay2::HEIGHT];
}


// Lightweight RAII wrapper for PicoDisplay2
class Display final : public PicoDisplay2
{
public:
  static const uint8_t MAX_BRIGHTNESS = 255;
  explicit Display(uint8_t brightness=MAX_BRIGHTNESS) : PicoDisplay2(buffer)
  {
    init();
    set_backlight(brightness);
  }

  ~Display()
  {
    clear();
    set_backlight(0);
  }
};

