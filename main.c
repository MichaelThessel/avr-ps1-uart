#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

// http://goo.gl/kx5pLU
#include "dbg_putchar.h"

// Debounce delay
volatile uint16_t pb3_delay = 0;
volatile uint16_t pb4_delay = 0;
const uint16_t bounce_delay = 0x0FFF;

int main(void)
{
    dbg_tx_init();

    // Disable interrupts
    cli();

    // Configure PB3 & 4 as inputs
    DDRB &= ~((1 << DDB3) | (1 << DDB4));

    // Enable pin change interrupt
    GIMSK |= (1 << PCIE);

    // Enable interrupts for PB3 & 4
    PCMSK |= ((1 << PCINT3) | (1 << PCINT4));

    // Enable interrupts
    sei();

    // Set sleep mode - Power down
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    while(1) {
        // Button debounce
        if (pb3_delay > 0) pb3_delay--;
        if (pb4_delay > 0) pb4_delay--;

        cli();
        // Enter sleep mode
        if (pb3_delay == 0 && pb4_delay == 0) {
            sleep_enable();
            sleep_bod_disable();
            sei();
            sleep_cpu();
            sleep_disable();
        }
    }

    return 0;
}

ISR(PCINT0_vect) {
    // Detect pin change to high on PB3
    if (pb3_delay == 0 && PINB & (1 << PB3)) {
        pb3_delay = bounce_delay; // Debounce
        dbg_putchar('[');
    }

    // Detect pin change to high on PB4
    if (pb4_delay == 0 && PINB & (1 << PB4)) {
        pb4_delay = bounce_delay; // Debounce
        dbg_putchar(']');
    }
}
