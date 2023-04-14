#include <stdio.h>
#include "hardware/gpio.h"
#include "seven_segment_library.h"

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

    // set the gpio pin function to PIO output
    pio_gpio_init (pio, gpio);
    pio_sm_set_consecutive_pindirs (pio, *p_sm, gpio, 1, true);

    // initialise X register to zero
    pio_sm_exec_wait_blocking (pio, *p_sm, pio_encode_mov (pio_x, pio_null));

    // configure and enable the state machine
    seven_segment_sm_init (pio, *p_sm, offset, 
                           segment_pinbase, digit_pinbase);

    return true;
}