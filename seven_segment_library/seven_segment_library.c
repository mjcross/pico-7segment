#include <stdio.h>
#include "hardware/gpio.h"
#include "seven_segment_library.h"

static const uint8_t segments[] = {
    //ABCDEFG.
    0b11111100,     // 0
    0b01100000,     // 1
    0b11011010,     // 2
    0b11110010,     // 3
    0b01100110,     // 4
    0b10110110,     // 5
    0b10111110,     // 6
    0b11100000,     // 7
    0b11111110,     // 8
    0b11110110      // 9
};

uint32_t int_to_seven_segment (int num) {
    uint32_t word = 0;

    if (num == 0) {
        return segments[0];
    }
    for (int bitshift = 0; bitshift < 32 && num > 0; bitshift += 8) {
        word |= segments[num % 10] << bitshift;
        num /= 10;
    }
    return word;
}


bool seven_segment_init (PIO pio, uint *p_sm, 
                         uint segment_pinbase, uint digit_pinbase) {
    // add the program to the PIO shared instruction memory
    if (pio_can_add_program (pio, &seven_segment_program) == false) {
        puts ("could not add the pio program");
        return false;
    }
    uint offset = pio_add_program (pio, &seven_segment_program);

    // claim a free state machine
    int sm = pio_claim_unused_sm (pio, false);
    if (sm == -1) {
        puts ("could not claim a state machine");
        return false;
    } else {
        *p_sm = (uint)sm;
    }

    // set segment pins to PIO output
    for (int pin = 0; pin < 8; pin += 1) {
        pio_gpio_init (pio, segment_pinbase + pin);
    }
    pio_sm_set_consecutive_pindirs (pio, *p_sm, segment_pinbase, 8, true);

    // set digit mux pins to PIO output
    for (int pin = 0; pin < 4; pin += 1) {
        pio_gpio_init (pio, digit_pinbase + pin);
    }
    pio_sm_set_consecutive_pindirs (pio, *p_sm, digit_pinbase, 4, true);

    // initialise X register to zero
    pio_sm_exec_wait_blocking (pio, *p_sm, pio_encode_mov (pio_x, pio_null));

    // configure and enable the state machine
    seven_segment_sm_init (pio, *p_sm, offset, 
                           segment_pinbase, digit_pinbase);

    return true;
}