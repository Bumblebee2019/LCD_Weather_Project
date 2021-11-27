#!/bin/bash
avr-gcc -mmcu=atmega1284 -I/home/daria/simavr/ -Iheader/ -D_SIMULATE_ -Wall -g -Og -Wl,--undefined=_mmcu,--section-start=.mmcu=910000 -o build/objects/main.elf source/main.c
