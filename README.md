# pico-conway

Cellular automata on a pico...

![./pico-conway.png](./pico-conway.png)

Cells are colour-coded according to their age. Button A resets, B clears the screen, X adds a randomly-placed glider (this happens randomly without pressing anything). Y toggles screen brightness.

## build

### hardware

Uses the [Rasbperry Pi pico](https://www.raspberrypi.com/products/raspberry-pi-pico/) with the [Pimoroni pico-display-2](https://shop.pimoroni.com/products/pico-display-pack-2-0?variant=39374122582099)
### software

Requires the [pico C/C++ SDK](https://github.com/raspberrypi/pico-sdk) and the [pimoroni-pico](https://github.com/pimoroni/pimoroni-pico) libraries.

1. ensure `PICO_SDK_PATH` is set correctly (relative to the build dir) in your environment, e.g. `export PICO_SDK_PATH=../../pico-sdk-1.3.0`

1. (fork,) clone and build [pimoroni-pico](https://github.com/pimoroni/pimoroni-pico)

1. symlink `pimoroni-pico` in the root of this project.

1. build the image with `mkdir build && cd build && cmake .. && make -j`

1. copy image to device

1. back of the net!
