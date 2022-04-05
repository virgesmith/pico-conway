#!/bin/bash

#export PICO_SDK_PATH=../../pico-sdk-1.3.0
PIMORONI_PICO=../pimoroni-pico

ln -s $PIMORONI_PICO
mkdir -p build
cd build
PICO_IMAGE=$PICO_IMAGE cmake ..
make -j
