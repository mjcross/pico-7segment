#include <stdio.h>
#include "pico/stdlib.h"
#include "seven_segment_library.h"


const PIO pio = pio0;
const uint first_segment_pin = 8;   // gpio 8-15: shared segments (A-G, dp)
const uint first_digit_pin = 16;    // gpio 16-19: digit cathodes (1, 10, 100, 1000)

//                      .GFEDCBA
const uint32_t Pico = 0b01110011 << 24 |    // 'P'
                      0b00010000 << 16 |    // 'i'
                      0b01011000 <<  8 |    // 'c'
                      0b01011100;           // 'o'

int main() {
    uint sm;
    stdio_init_all();
    
    if (seven_segment_init (pio, &sm, first_segment_pin, first_digit_pin)) {
        puts ("running");

        // display scrolling 'Pico'
        for (int shift = 24; shift >= 0; shift -= 8) {
            pio_sm_put (pio, sm, Pico >> shift);
            sleep_ms (1000);
        }

        // count to 9999
        for (int i = 0; i < 10000; i += 1) {
            sleep_ms (100);
            pio_sm_put (pio, sm, int_to_seven_segment (i));
        }
    }

    puts ("done");
    while (true);
}