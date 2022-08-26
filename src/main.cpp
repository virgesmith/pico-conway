
//#include "display.h"
#include "conway.h"

#include "drivers/button/button.hpp"
#include "drivers/rgbled/rgbled.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "libraries/pico_display_2/pico_display_2.hpp"

#include <vector>

#include <cmath>
#include <cstdlib>
#include <cstring>

using namespace pimoroni;

namespace {
static const uint8_t MAX_BRIGHTNESS = 255;
}
class Renderer
{
public:

  Renderer(PicoGraphics& g, DisplayDriver& d, Conway& m) : graphics(g), display(d), model(m)
  {
    int xsize = display.width / model.width;
    int ysize = display.height / model.height;

    cells.reserve(model.height * model.width);
    for (size_t h = 0; h < model.height; ++h)
      for (size_t w = 0; w < model.width; ++w)
        cells.push_back(Rect(w * xsize, h * ysize, xsize-1, ysize-1));

    render();
  }

  void render() const
  {
    for (size_t i = 0; i < model.height * model.width; ++i)
    {
      graphics.set_pen(model.states[i] * 257);
      graphics.rectangle(cells[i]);
    }
    display.update(&graphics);
  }

private:
  PicoGraphics& graphics;
  DisplayDriver& display;
  Conway& model;
  std::vector<Rect> cells;
};


int main()
{
  ST7789 st7789(320, 240, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
  PicoGraphics_PenRGB565 graphics(st7789.width, st7789.height, nullptr);
  graphics.clear();

  Conway conway(80, 60);
  Renderer renderer(graphics, st7789, conway);
  bool dimmed = false;

  Button button_a(PicoDisplay2::A);
  Button button_b(PicoDisplay2::B);
  Button button_x(PicoDisplay2::X);
  Button button_y(PicoDisplay2::Y);

  RGBLED led(PicoDisplay2::LED_R, PicoDisplay2::LED_G, PicoDisplay2::LED_B);

  led.set_rgb(0, 63, 0);

  for (;;)
  {
    conway.evolve();
    if (button_a.raw())
    {
      conway.reset();
      sleep_ms(1000);
    }
    else if (button_b.raw())
    {
      conway.clear();
      sleep_ms(1000);
    }
    else if (button_x.raw())
    {
      conway.add_glider();
      sleep_ms(100);
    }
    else if (button_y.raw())
    {
      st7789.set_backlight(dimmed ? MAX_BRIGHTNESS : MAX_BRIGHTNESS >> 1);
      dimmed = !dimmed;
      sleep_ms(100);
    }
    renderer.render();
  }
}

