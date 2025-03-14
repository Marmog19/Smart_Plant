#!/usr/bin/env bash

cmake -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE:PATH=".\toolchain.cmake" -B build

cmake --build build

cd build

arm-none-eabi-objcopy -O binary firmware.elf firmware.bin

#st-flash --reset write firmware.bin 0x8000000

