#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// http://goo.gl/kx5pLU
#include "dbg_putchar.h"

// Debounce delay
volatile uint16_t pb3_delay = 0;
volatile uint16_t pb4_delay = 0;
uint16_t bounce_delay = 0x0FFF;

int main(void)
{
	dbg_tx_init();
	
	// Disable interrupts
	cli();
	
	// Configure PB3 & 4 as inputs
	DDRB &= ~(1 << DDB3);
	DDRB &= ~(1 << DDB4);
	// Enable pin change interrupt
	GIMSK |= (1 << PCIE);	// Enable interrupts for PB3 & 4	PCMSK |= (1 << PCINT3);	PCMSK |= (1 << PCINT4);		sei();
	while(1) {
		// Button debounce
		if (pb3_delay > 0) pb3_delay--;
		if (pb4_delay > 0) pb4_delay--;
	}
	
	return 0;
}

ISR(PCINT0_vect) {
	if(pb3_delay == 0 && PINB & (1 << PB3)) {
		pb3_delay = bounce_delay; // Debounce
		dbg_putchar('[');
    }

	if(pb4_delay == 0 && PINB & (1 << PB4)) {
		pb4_delay = bounce_delay; // Debounce
		dbg_putchar(']');
	}
}