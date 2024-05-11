
#include "conway.h"
#include "renderer.h"

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

int main() {
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

  for (;;) {
    conway.evolve();
    if (button_a.raw()) {
      conway.reset();
      sleep_ms(250);
    } else if (button_b.raw()) {
      conway.clear();
      sleep_ms(250);
    } else if (button_x.raw()) {
      conway.add_glider();
      sleep_ms(100);
    } else if (button_y.raw()) {
      renderer.toggle_brightness();
      sleep_ms(100);
    }
    renderer.render();
  }
}
