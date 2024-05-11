cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH ../pico-sdk)
include(pico_sdk_import.cmake)

project(pico-conway C CXX ASM)

set(TARGET pico-conway)

message("Target is ${TARGET}")

set(PICO_BOARD pico)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

pico_sdk_init()

include_directories(${CMAKE_SOURCE_DIR}/pimoroni-pico)

add_subdirectory(pimoroni-pico/drivers/rgbled EXCLUDE_FROM_ALL)
add_subdirectory(pimoroni-pico/drivers/button EXCLUDE_FROM_ALL)
add_subdirectory(pimoroni-pico/drivers/st7789 EXCLUDE_FROM_ALL)
add_subdirectory(pimoroni-pico/libraries/pico_graphics EXCLUDE_FROM_ALL)
add_subdirectory(pimoroni-pico/common EXCLUDE_FROM_ALL)

add_executable(${TARGET}
  src/main.cpp
  src/conway.cpp
  src/renderer.cpp
)

target_compile_options(${TARGET} PRIVATE -O3 -Wno-psabi -Werror -Wall)

target_link_libraries(${TARGET}
  hardware_spi
  rgbled
  button
  st7789
  pico_graphics
  button
)

pico_enable_stdio_usb(${TARGET} 0)
pico_enable_stdio_uart(${TARGET} 0)
pico_add_extra_outputs(${TARGET})


