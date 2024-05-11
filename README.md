# pico-conway

Cellular automata on a pico...

![./pico-conway.png](./pico-conway.png)

Cells are colour-coded according to their age. Button A resets, B clears the screen, X adds a randomly-placed glider (this happens randomly without pressing anything). Y toggles screen brightness.

## build

### hardware

Uses the [Rasbperry Pi pico](https://www.raspberrypi.com/products/raspberry-pi-pico/) with the [Pimoroni pico-display-2](https://shop.pimoroni.com/products/pico-display-pack-2-0?variant=39374122582099)

### software

Requires pico-sdk and the pimoroni-pico](https://github.com/pimoroni/pimoroni-pico) libraries.

1. download and extract a release of the [pico C/C++ SDK](https://github.com/raspberrypi/pico-sdk)

1. symlink it into the project root as `pico-sdk`, e.g. `ln -s ../pico-sdk-1.5.1 pico-sdk`.

1. symlink the cmake import: `ln -s pico-sdk/external/pico_sdk_import.cmake`

1. download and extract a release of [pimoroni-pico](https://github.com/pimoroni/pimoroni-pico). This is needed for the graphics library and display driver.

1. symlink it in the root as `pimoroni-pico`, e.g. `ln -s ../pimoroni-pico-1.21.0 pimoroni-pico`

1. build the image with

    ```sh
    mkdir -p build
    cd build
    cmake -DPICO_SDK_PATH=../pico-sdk ..
    make -j
    ```

1. copy image to device (connected with `BOOTSEL` pressed), e.g.

    ```sh
    cp pico-conway.uf2 /media/<username>/RPI-RP2
    ```

## test

The algorithm itself can be tested/debugged on the host machine using the test harness, e.g.:

```sh
g++ -g -O0 --std=c++20 src/test_conway.cpp src/conway.cpp -o test
```
