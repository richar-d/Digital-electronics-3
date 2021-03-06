/***********************************************************************
 * 
 * Decimal counter with 7-segment output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "segment.h"        // Seven-segment display library for AVR-GCC


<<<<<<< HEAD
static uint8_t singles = 0;
static uint8_t decimals = 0;

=======
>>>>>>> f55adf830af54c1d2cb0333976218bd34b48d27b
/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Display decimal 
 * counter values on SSD (Seven-segment display) when 16-bit 
 * Timer/Counter1 overflows.
 */
int main(void)
{
    // Configure SSD signals
    SEG_init();
<<<<<<< HEAD
	
    /* Configure 8-bit Timer/Counter0
     * Set prescaler and enable overflow interrupt */
	TIM0_overflow_4096us();
	TIM0_overflow_interrupt_enable();

    /* Configure 16-bit Timer/Counter1
     * Set prescaler and enable overflow interrupt */
	TIM1_overflow_262ms();
	TIM1_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
	sei();
=======

    SEG_update_shift_regs(3,0);
    /* Configure 16-bit Timer/Counter1
     * Set prescaler and enable overflow interrupt */
	TIM1_overflow_1s();
	TIM1_overflow_interrupt_enable();
	
    // Enables interrupts by setting the global interrupt mask
    sei();
>>>>>>> f55adf830af54c1d2cb0333976218bd34b48d27b
    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }
    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**
 * ISR starts when Timer/Counter1 overflows. Increment decimal counter value
 * value 
 */

/* */


ISR(TIMER1_OVF_vect)
{
<<<<<<< HEAD
   singles++;
   if (singles > 9)
   {
	   singles =0;
	   decimals++;
	   if (decimals>5)
	   {
		   decimals = 0;
	   }
   }
}

/* Interrupt service routines ----------------------------------------*/
/**
 * ISR starts when Timer/Counter1 overflows.  display value on SSD.
 */

ISR(TIMER0_OVF_vect)
{
	static uint8_t position = 0;
	if (position ==0)
	{
		SEG_update_shift_regs(singles,0);
		position=1;
	}
	else
	{
		SEG_update_shift_regs(decimals,1);
		position=0;
	}
}
=======
	static uint8_t snake = 0;
	SEG_update_shift_regs(snake, 0);
	snake++;
	if (snake>5)
	{
		snake=0;
	}
}
>>>>>>> f55adf830af54c1d2cb0333976218bd34b48d27b
