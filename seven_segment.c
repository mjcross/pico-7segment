#include <stdio.h>
#include "pico/stdlib.h"
#include "seven_segment_library.h"


const PIO pio = pio0;
const uint segment_pinbase = 8;         // gpio 8-15: shared segments 
const uint digit_pinbase = 16;          // gpio 16-19: digit mux lines

int main() {
    stdio_init_all();

    uint sm;
    if (seven_segment_init (pio, &sm, segment_pinbase, digit_pinbase)) {
        puts ("running");
        for (int i = 0; i < 1000; i += 1) {
            sleep_ms (100);
            pio_sm_put (pio, sm, int_to_seven_segment (i));
        }
    }

    puts ("halted");
    while (true);
}