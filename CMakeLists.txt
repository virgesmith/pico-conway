cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

set(PICO_SDK_PATH ../../pico-sdk)
set(PIMORONI_PATH ../pimoroni-pico) # NB relative to project root

# ensure we have the correct pico_sdk_import.cmake
execute_process (COMMAND
  bash -c "cp ${PICO_SDK_PATH}/external/pico_sdk_import.cmake .."
)

include(pico_sdk_import.cmake)

project(pico-conway C CXX ASM)

set(TARGET pico-conway)

message("Target is ${TARGET}")

pico_sdk_init()

include_directories(${PIMORONI_PATH})

add_subdirectory(${PIMORONI_PATH}/drivers/rgbled pimoroni/drivers/rgbled EXCLUDE_FROM_ALL)
add_subdirectory(${PIMORONI_PATH}/drivers/button pimoroni/drivers/button EXCLUDE_FROM_ALL)
add_subdirectory(${PIMORONI_PATH}/drivers/st7789 pimoroni/drivers/st7789 EXCLUDE_FROM_ALL)
add_subdirectory(${PIMORONI_PATH}/libraries/pico_graphics pimoroni/libraries/pico_graphics EXCLUDE_FROM_ALL)
add_subdirectory(${PIMORONI_PATH}/common pimoroni/common EXCLUDE_FROM_ALL)

add_executable(${TARGET}
  src/main.cpp
  src/conway.cpp
  src/renderer.cpp
)

target_compile_options(${TARGET} PRIVATE -O3 -Wno-psabi -Werror -Wall)

target_link_libraries(${TARGET}
  hardware_spi
  pico_rand
  rgbled
  button
  st7789
  pico_graphics
  button
)

pico_enable_stdio_usb(${TARGET} 0)
pico_enable_stdio_uart(${TARGET} 0)
pico_add_extra_outputs(${TARGET})


