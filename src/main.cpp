
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

// reverse bits, to prevent "yellowing"  (B only has 2 bits, RG have 3)
uint8_t reverse(uint8_t b)
{
  static const uint8_t lookup[] = {0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe, 0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf};
   return (lookup[b & 0xf] << 4) | lookup[b >>4 ];
}

}

class Renderer
{
public:

  Renderer(PicoGraphics& g, DisplayDriver& d, Conway& m) : graphics(g), display(d), model(m), dimmed(true)
  {
    display.set_backlight(MAX_BRIGHTNESS >> 1);

    graphics.set_pen(0);
    graphics.clear();

    int xsize = display.width / model.width;
    int ysize = display.height / model.height;

    cells.reserve(model.height * model.width);
    for (size_t h = 0; h < model.height; ++h)
      for (size_t w = 0; w < model.width; ++w)
        cells.push_back(Rect(w * xsize, h * ysize, xsize, ysize));

    render();
  }

  void render() const
  {
    for (size_t i = 0; i < model.height * model.width; ++i)
    {
      graphics.set_pen(reverse(model.states[i]));
      graphics.rectangle(cells[i]);
    }
    display.update(&graphics);
  }

  void toggle_brightness()
  {
    display.set_backlight(dimmed ? MAX_BRIGHTNESS : MAX_BRIGHTNESS >> 1);
    dimmed = !dimmed;
  }

private:
  PicoGraphics& graphics;
  DisplayDriver& display;
  Conway& model;
  std::vector<Rect> cells;
  bool dimmed;
};


int main()
{
  ST7789 st7789(320, 240, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
  PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

  Conway conway(106, 80);

  Renderer renderer(graphics, st7789, conway);

  Button button_a(PicoDisplay2::A);
  Button button_b(PicoDisplay2::B);
  Button button_x(PicoDisplay2::X);
  Button button_y(PicoDisplay2::Y);

  RGBLED led(PicoDisplay2::LED_R, PicoDisplay2::LED_G, PicoDisplay2::LED_B);

  led.set_rgb(0, 32, 0);

  for (;;)
  {
    conway.evolve();
    if (button_a.raw())
    {
      conway.reset();
      sleep_ms(250);
    }
    else if (button_b.raw())
    {
      conway.clear();
      sleep_ms(250);
    }
    else if (button_x.raw())
    {
      conway.add_glider();
      sleep_ms(100);
    }
    else if (button_y.raw())
    {
      renderer.toggle_brightness();
      sleep_ms(100);
    }
    renderer.render();
  }
}

