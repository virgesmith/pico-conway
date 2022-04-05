
#include "display.h"
#include "conway.h"

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

  for (;;)
  {
    conway.evolve();
    if (display.is_pressed(display.A))
    {
      sleep_ms(1000);
      conway.reset();
    }
    else if (display.is_pressed(display.B))
    {
      sleep_ms(1000);
      conway.clear();
    }
    else if (display.is_pressed(display.X))
    {
      conway.add_glider();
      sleep_ms(100);
    }
    else if (display.is_pressed(display.Y))
    {
      display.set_backlight(dimmed ? Display::MAX_BRIGHTNESS : Display::MAX_BRIGHTNESS/2);
      dimmed = !dimmed;
      sleep_ms(100);
    }
    renderer.render();
  }
}

