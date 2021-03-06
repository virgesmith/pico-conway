
#include "display.h"
#include "conway.h"

#include "drivers/button/button.hpp"
#include "drivers/rgbled/rgbled.hpp"
#include "libraries/pico_display_2/pico_display_2.hpp"

#include <vector>

#include <cmath>
#include <cstdlib>

using namespace pimoroni;

class Renderer
{
public:

  Renderer(Display& d, Conway& m) : display(d), model(m)
  {
    int xsize = display.bounds.w / model.width;
    int ysize = display.bounds.h / model.height;

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
      display.set_pen(model.states[i] * 257);
      display.rectangle(cells[i]);
    }
    display.update();
  }

private:
  Display& display;
  Conway& model;
  std::vector<Rect> cells;
};


int main()
{
  Display display;
  Conway conway(80, 60);
  Renderer renderer(display, conway);
  bool dimmed = false;

  Button button_a(PicoDisplay2::A);
  Button button_b(PicoDisplay2::B);
  Button button_x(PicoDisplay2::X);
  Button button_y(PicoDisplay2::Y);

  RGBLED led(PicoDisplay2::LED_R, PicoDisplay2::LED_G, PicoDisplay2::LED_B);

  led.set_rgb(0, 127, 0);

  for (;;)
  {
    conway.evolve();
    if (button_a.raw())
    {
      sleep_ms(1000);
      conway.reset();
    }
    else if (button_b.raw())
    {
      sleep_ms(1000);
      conway.clear();
    }
    else if (button_x.raw())
    {
      conway.add_glider();
      sleep_ms(100);
    }
    else if (button_y.raw())
    {
      display.set_backlight(dimmed ? Display::MAX_BRIGHTNESS : Display::MAX_BRIGHTNESS/2);
      dimmed = !dimmed;
      sleep_ms(100);
    }
    renderer.render();
  }
}

