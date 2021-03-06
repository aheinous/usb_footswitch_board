/**
 * \file
 *
 * \brief User board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

// FOOTSWITCHES

#define SW9 IOPORT_CREATE_PIN(PORTD, 1)
#define SW8 IOPORT_CREATE_PIN(PORTD, 2)
#define SW10 IOPORT_CREATE_PIN(PORTD, 3)
#define SW6 IOPORT_CREATE_PIN(PORTD, 4)
#define SW5 IOPORT_CREATE_PIN(PORTD, 5)

#define SW4 IOPORT_CREATE_PIN(PORTE, 0)
#define SW3 IOPORT_CREATE_PIN(PORTE, 1)
#define SW2 IOPORT_CREATE_PIN(PORTE, 2)
#define SW1 IOPORT_CREATE_PIN(PORTE, 3)

#define SW7 IOPORT_CREATE_PIN(PORTB, 3)

// ANALOG INPUTS

/*
#define AIN1 IOPORT_CREATE_PIN(PORTA, 0)
#define AIN2 IOPORT_CREATE_PIN(PORTA, 1)
#define AIN3 IOPORT_CREATE_PIN(PORTA, 2)
#define AIN4 IOPORT_CREATE_PIN(PORTA, 3)
#define AIN5 IOPORT_CREATE_PIN(PORTA, 4)
#define AIN6 IOPORT_CREATE_PIN(PORTA, 5)

#define BRIGHTNESS IOPORT_CREATE_PIN(PORTA, 6)

*/


// LED DRIVERS

#define BLANK IOPORT_CREATE_PIN(PORTD, 0)
#define XLAT IOPORT_CREATE_PIN(PORTC, 3)
#define SCLK IOPORT_CREATE_PIN(PORTC, 7)
#define SDATA IOPORT_CREATE_PIN(PORTC, 5)
#define MODE IOPORT_CREATE_PIN(PORTC, 1)
#define GSCLK IOPORT_CREATE_PIN(PORTC, 0)
#define SLAVE_SELECT IOPORT_CREATE_PIN(PORTC,4)

#define BOARD_SPI SPIC


#endif // CONF_BOARD_H
