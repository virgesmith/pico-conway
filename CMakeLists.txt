
cmake_minimum_required(VERSION 3.13)

message("Target is pico-conway")
include(pico_sdk_import.cmake)
project(pico-conway)
pico_sdk_init()
add_executable(pico-conway
  src/main.cpp
  src/conway.cpp
)
add_subdirectory(pimoroni-pico EXCLUDE_FROM_ALL)
pico_enable_stdio_usb(pico-conway 0)
pico_enable_stdio_uart(pico-conway 0)
pico_add_extra_outputs(pico-conway)
include_directories(${CMAKE_SOURCE_DIR}/pimoroni-pico)
target_compile_options(pico-conway PRIVATE -Wno-psabi -Werror -Wall)
target_link_libraries(pico-conway hardware_spi rgbled button st7789 pico_graphics)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")