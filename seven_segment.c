#include <stdio.h>
#include "pico/stdlib.h"
#include "seven_segment_library.h"


const PIO pio = pio0;
const uint segment_pinbase = 8;         // shared segments gpio 8..15
const uint digit_pinbase = 16;          // digit mux gpio 16..19

int main() {
    stdio_init_all();

    uint sm;
    if (seven_segment_init (pio, &sm, segment_pinbase, digit_pinbase)) {
        puts ("running");
        while(true) {
            // todo: write simple usage example
        }
    }

    puts ("halted");
    while (true);
}