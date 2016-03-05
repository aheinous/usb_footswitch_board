/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

void board_init(void){
	ioport_set_pin_dir(SW1, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(SW2, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(SW3, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(SW4, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(SW5, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(SW6, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(SW7, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(SW8, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(SW9, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(SW10, IOPORT_DIR_INPUT);
	
	/*
	ioport_set_pin_dir(AIN1, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(AIN2, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(AIN3, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(AIN4, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(AIN5, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(AIN6, IOPORT_DIR_INPUT);
	
	ioport_set_pin_dir(BRIGHTNESS, IOPORT_DIR_INPUT);
	*/
	

}
