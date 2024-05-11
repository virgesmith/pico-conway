#pragma once

#include "conway.h"

#include "drivers/button/button.hpp"
#include "drivers/rgbled/rgbled.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_display_2/pico_display_2.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"

#include <vector>

#include <cmath>
#include <cstdlib>
#include <cstring>

using namespace pimoroni;

class Renderer {
public:
  Renderer(PicoGraphics& g, DisplayDriver& d, Conway& m);

  void render() const;

  void toggle_brightness();

private:
  PicoGraphics& graphics;
  DisplayDriver& display;
  Conway& model;
  std::vector<Rect> cells;
  bool dimmed;
};
