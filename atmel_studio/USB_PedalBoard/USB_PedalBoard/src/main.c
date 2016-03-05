/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>


/////////////////// CONSTANTS /////////////////////////////

static const uint8_t adca_channels[] = {
	ADC_CH0,
	ADC_CH1,
	ADC_CH2,
	ADC_CH3
};

static const uint8_t adca_input[] = {
	ADCCH_POS_PIN0,
	ADCCH_POS_PIN1,
	ADCCH_POS_PIN2,
	ADCCH_POS_PIN3,
	ADCCH_POS_PIN4,
	ADCCH_POS_PIN5,
	ADCCH_POS_PIN6,
	ADCCH_POS_PIN7
};

#define AIN1 0
#define AIN2 1
#define AIN3 2
#define AIN4 3
#define AIN5 4
#define AIN6 5
#define BRIGHTNESS_IN 6

#define NUM_ADCA_CH  (sizeof(adca_channels))
#define NUM_ADCA_INPUTS (sizeof(adca_input))

#define BOARD_ADCA ADCA
#define BOARD_ADC_REF ADC_REF_AREFB

#define ADC_TIMER TCC1

#define NUM_LED_CHANNELS (32)
#define NUM_LEDS (10)

#define LEN_LED_GS_DATA (48)
#define LEN_LED_DC_DATA (24)

/////////////////// STATIC VARIABLES ////////////////////

static volatile bool authorize_hid_events = false;

static volatile int8_t adc_group_num = -1;
static volatile uint8_t adc_readings[NUM_ADCA_INPUTS] = {0};
static volatile bool group_complete = false;

static volatile bool brightness_set_once = false;
static volatile bool colors_set_once = false;
static volatile bool _force_blanked = true;


static uint8_t led_gs_data[LEN_LED_GS_DATA] = {0};
	
static uint8_t led_dc_data[LEN_LED_DC_DATA] = {0};
	
static int8_t cur_brightness = -1;

static volatile bool led_gs_data_ready = false;

static struct spi_device spi_device_conf = {
	.id = XLAT
};


//////////////////// UTILITY FUNCTIONS ////////////////////////////////

#define LOWER_8(n) ((uint8_t)(n & 0xFF))
#define UPPER_8(n) ((uint8_t)((n >> 8) & 0xFF))

// writes UPPER bits_per_word bits of data to dest, starting bit_offset bits past beginning. Higher
// bits are considered earlier than lower bits. Lower index bytes are considered to occur earlier,
// than higher index bytes.
static inline void write_bit_offset_msb(uint8_t * dest, int16_t bit_offset, uint8_t data, int8_t bits_per_word){
	int byte_index = bit_offset / 8;
	bit_offset %= 8;

	uint16_t offset_data = (((uint16_t)data)<<8);
	offset_data >>= bit_offset;
	//offset_data <<=8;
	uint16_t mask = (1<<bits_per_word)-1;
	mask <<= (8-bits_per_word);
	mask <<= 8;
	mask >>= bit_offset;

	offset_data &= mask;

	dest[byte_index] &= ~UPPER_8(mask);
	dest[byte_index] |= UPPER_8(offset_data);

	if(LOWER_8(mask) != 0){
		dest[byte_index+1] &= ~LOWER_8(mask);
		dest[byte_index+1] |= LOWER_8(offset_data);
	}
}

// writes UPPER bits_per_word bits of data to dest, starting word_index words past beginning.
// A word is considered to be bits_per_word bits. The maximum word size is 8 bits. Higher bits
// are considered to occur earlier  than lower bits. Lower index bytes are considered to occur
// earlier, than higher index bytes.
static inline void write_nbit_aligned_msb_8(uint8_t*dest, int16_t word_index, uint8_t data, int8_t bits_per_word){
	write_bit_offset_msb(dest, word_index* ((int16_t)bits_per_word) , data, bits_per_word);
}


static void vserprintf(const char* fmt, va_list argp){
	char str_buffer[128] = {0};
	vsprintf(str_buffer, fmt, argp);
	//str_buffer[0] = 'w';
	udi_hid_generic_send_report_in((uint8_t*)str_buffer);
}

static void serprintf(const char* fmt, ...){
	va_list argp;
	va_start(argp, fmt);
	vserprintf(fmt, argp);
}


///////// CALLBACKS ///////////
bool hid_enable(void);
void hid_disable(void);
void hid_report_out(uint8_t* report);

bool hid_enable(void){
	authorize_hid_events = true;
	return true;
}

void hid_disable(void){
	authorize_hid_events = false;
}

static void usb_init(void){
	udc_start();
}

static inline uint16_t read_buttons(void){
	uint16_t reading = 0;
	if( ! ioport_get_pin_level(SW1)) reading |= (1<<0);
	if( ! ioport_get_pin_level(SW2)) reading |= (1<<1);
	if( ! ioport_get_pin_level(SW3)) reading |= (1<<2);
	if( ! ioport_get_pin_level(SW4)) reading |= (1<<3);
	if( ! ioport_get_pin_level(SW5)) reading |= (1<<4);
	if( ! ioport_get_pin_level(SW6)) reading |= (1<<5);
	if( ! ioport_get_pin_level(SW7)) reading |= (1<<6);
	if( ! ioport_get_pin_level(SW8)) reading |= (1<<7);
	if( ! ioport_get_pin_level(SW9)) reading |= (1<<8);
	if( ! ioport_get_pin_level(SW10)) reading |= (1<<9);
	
	return reading;
}

static inline void send_report_in(void){
	uint8_t report[UDI_HID_REPORT_IN_SIZE];
	
	uint16_t button_reading = read_buttons();
	
	report[0] = LOWER_8(button_reading);
	report[1] = UPPER_8(button_reading);
	report[2] = adc_readings[AIN1];
	report[3] = adc_readings[AIN2];
	report[4] = adc_readings[AIN3];
	report[5] = adc_readings[AIN4];
	report[6] = adc_readings[AIN5];
	report[7] = adc_readings[AIN6];
	
	
	/*for(int8_t i=0; i<NUM_ADCA_CH; i++){
		report[2 + 2*i] = LOWER_8(adc_readings[i]);
		report[3 + 2*i] = UPPER_8(adc_readings[i]);
	}*/

	udi_hid_generic_send_report_in( & report[0]);
}

static void handle_adc(ADC_t *adc, uint8_t channel_mask, adc_result_t result){
	if(adc_group_num == -1){
		return;
	}
	uint8_t index = 0;
	bool end_of_sweep = false;
	switch(channel_mask){
		case ADC_CH0:
			index = 0;
			break;
		case ADC_CH1:
			index = 1;
			break;
		case ADC_CH2:
			index = 2;
			break;
		case ADC_CH3:
			index = 3;
			end_of_sweep = true;
			break;
		default:
			break;
	}
	index += (adc_group_num*4);
	adc_readings[index] = result;
	if(end_of_sweep){
		group_complete = true;
	}
	//adc_readings[0] = adc_group_num;
	//adc_readings[1] = index;
	//adc_readings[2] |= (1<<index);
	//send_report_in();
	/*
	static int16_t num_sweeps = 0;
	num_sweeps ++;
	adc_readings[3] = 1027;
	*/
	//adc_readings[1] = NUM_ADCA_CH;
	//adc_readings[2] = 
	//report_due = true;
	

	
}

static void set_adc_group_num(int8_t new_group_num){
	adc_group_num = -1;
	
	struct adc_channel_config adcch_conf;
	adcch_read_configuration(&BOARD_ADCA, ADC_CH0, &adcch_conf);
	adcch_enable_interrupt(&adcch_conf);
		
	for(int i=0; i<NUM_ADCA_CH; i++){
		int8_t input_index = (new_group_num*NUM_ADCA_CH) + i;
		adcch_set_input(&adcch_conf, adca_input[ input_index ], ADCCH_NEG_NONE, 1);
		adcch_write_configuration(&BOARD_ADCA, adca_channels[i], &adcch_conf);
	}
		
	adc_group_num = new_group_num;
}

static void evsys_init(void){
	sysclk_enable_module(SYSCLK_PORT_GEN, SYSCLK_EVSYS);
	EVSYS.CH3MUX = EVSYS_CHMUX_TCC1_OVF_gc;
}

static void tc_init_adc(void){
	tc_enable(&ADC_TIMER);
	tc_set_wgm(&ADC_TIMER, TC_WG_NORMAL);
	tc_write_period(&ADC_TIMER, 200);
	tc_set_resolution(&ADC_TIMER, 200);	
}

static void adc_init(void){
	struct adc_config adc_conf;
	adc_read_configuration(&BOARD_ADCA, &adc_conf);
	adc_set_conversion_parameters(&adc_conf, ADC_SIGN_OFF, ADC_RES_8, BOARD_ADC_REF);
	adc_set_conversion_trigger(&adc_conf, ADC_TRIG_EVENT_SWEEP, NUM_ADCA_CH, 3);
	adc_set_clock_rate(&adc_conf, 200000UL);
	adc_set_callback(&BOARD_ADCA, &handle_adc);
	adc_write_configuration(&BOARD_ADCA, &adc_conf);
}

static void auto_blank_callback(void){
	ioport_set_pin_level(BLANK, true);
}

static void auto_unblank_callback(void){
	if( ! _force_blanked){
		if(colors_set_once && brightness_set_once){
			ioport_set_pin_level(BLANK, false);
		}
		TCD0.CNT = 0;
	}
}

static inline void hold_blank_forced_high(void){
	_force_blanked = true;
	//ioport_set_pin_level(BLANK,true);
	while( ! ioport_get_pin_level(BLANK) ){}
}

static inline void release_blank_forced_high(void){
	if(_force_blanked){
		//ioport_set_pin_level(BLANK, false);
		if(colors_set_once && brightness_set_once){
			ioport_set_pin_level(BLANK, false);
		}
		TCD0.CNT = 0;
		_force_blanked = false;
	}
}

static void tc_init_led(void){
	tc_enable(&TCC0);
	tc_set_wgm(&TCC0, TC_WG_FRQ );
	tc_write_cc(&TCC0, TC_CCA, 0);
	tc_enable_cc_channels(&TCC0,TC_CCAEN);
	tc_write_clock_source(&TCC0, TC_CLKSEL_DIV256_gc);
		
	EVSYS.CH0MUX = 	EVSYS_CHMUX_TCC0_CCA_gc;
	
	tc_enable(&TCD0);
	tc_set_wgm(&TCD0, TC_WG_NORMAL);
	
	//#warning using gs test values
	//tc_write_cc(&TCD0,TC_CCA, 0x10);
	//tc_write_cc(&TCD0,TC_CCB, 0x14);
	
	tc_write_cc(&TCD0,TC_CCA, 0xFFF);
	tc_write_cc(&TCD0,TC_CCB, 0x1004);
	
	tc_enable_cc_channels(&TCD0, TC_CCAEN | TC_CCBEN);
	tc_set_cca_interrupt_callback(&TCD0, auto_blank_callback);
	tc_set_ccb_interrupt_callback(&TCD0, auto_unblank_callback);
	
	tc_write_period(&TCD0, 0xFFFF);
		
	tc_set_cca_interrupt_level(&TCD0, TC_INT_LVL_MED);
	tc_set_ccb_interrupt_level(&TCD0, TC_INT_LVL_MED);
	
	tc_write_clock_source(&TCD0, TC_CLKSEL_EVCH0_gc);
}

static void led_init(void){
	ioport_set_pin_level(BLANK, true);
	ioport_set_pin_dir(BLANK, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(XLAT, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(SCLK, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(SDATA, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(MODE, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(GSCLK, IOPORT_DIR_OUTPUT);
	
	ioport_set_pin_level(SLAVE_SELECT, true);
	ioport_set_pin_dir(SLAVE_SELECT, IOPORT_DIR_OUTPUT);
}

static void spi_init(void){	
	spi_master_init(&BOARD_SPI);
	//BOARD_SPI.CTRL |= SPI_DORD_bm;
	spi_master_setup_device(&BOARD_SPI, &spi_device_conf, SPI_MODE_0,1000000,0);
	spi_enable(&BOARD_SPI);
}

static int16_t gs_set_count = 0;

static void spi_send_led_gs(void){
	ioport_set_pin_level(MODE, false);
	//uint8_t data[4] = {0xAA,0xBB,0xCC,0xDD};
	hold_blank_forced_high();
	spi_select_device(&BOARD_SPI, &spi_device_conf)	;
	spi_write_packet(&BOARD_SPI, &led_gs_data[0], LEN_LED_GS_DATA);
	spi_deselect_device(&BOARD_SPI, &spi_device_conf);
	
	colors_set_once = true; 
	release_blank_forced_high();
	gs_set_count ++;
}

void hid_report_out(uint8_t* report){
	memcpy(&led_gs_data[0], report, LEN_LED_GS_DATA);
	led_gs_data_ready = true;
}


static int16_t dc_set_count = 0;
static void spi_send_led_dc(void){
	ioport_set_pin_level(MODE, true);
	
	spi_select_device(&BOARD_SPI, &spi_device_conf)	;
	spi_write_packet(&BOARD_SPI, &led_dc_data[0], LEN_LED_DC_DATA);
	spi_deselect_device(&BOARD_SPI, &spi_device_conf);
	
	brightness_set_once = true;
	dc_set_count++;
	ioport_set_pin_level(MODE, false);
}

// set led brightness (0 -> 64)
static void led_set_brightness(int8_t brightness){
	uint8_t data_6bit;
	brightness = (brightness >= 64) ? 63 : brightness;
	brightness = (brightness < 0) ? 0 : brightness;
	data_6bit = brightness;
	data_6bit <<= 2;
	for(int i=0; i<NUM_LED_CHANNELS;i++){
		write_nbit_aligned_msb_8(&led_dc_data[0], i, data_6bit, 6);
	}
	spi_send_led_dc();
}

static void update_brightness(void){
	// 0 -> 255 (8 bits)
	uint8_t raw_reading = adc_readings[BRIGHTNESS_IN];

	// cur_brightness: 0 -> 63 (6 bits)
	int16_t diff = cur_brightness*4;
	diff -= ((int16_t)raw_reading);
	if(diff >= 6 || diff <= -6){
		cur_brightness = raw_reading/4;
		led_set_brightness(cur_brightness);
	}
}

int main (void){
	sysclk_init();
	irq_initialize_vectors();
	cpu_irq_enable();
	evsys_init();
	tc_init_adc();
	adc_init();
	set_adc_group_num(0);
		
	pmic_init();
	usb_init();

	board_init();
	
	led_init();
	tc_init_led();
	
	adc_enable(&BOARD_ADCA);
	spi_init();

	spi_send_led_gs(); // set to black
	int16_t count = 0;
	/*
	while(true){
		
		ioport_set_pin_level(MODE, true);
		serprintf("high: %d\n", ioport_get_pin_level(MODE));
		ioport_set_pin_level(MODE, false);
		serprintf("low: %d\n", ioport_get_pin_level(MODE));
	}*/
	
	//while(true){
	//	led_set_brightness(5);
	//	for(int i=0; i<LEN_LED_DC_DATA; i++){
	//		led_dc_data[i] = 3;
	//	}
	//	uint8_t data_6bit = 0xF0;
	//	for(int i=0; i<NUM_LED_CHANNELS;i++){
	//		write_nbit_aligned_msb_8(&led_dc_data[0], i, data_6bit, 6);
	//	}
	//	spi_send_led_dc();
		
	//}
	
	while(true){
		count++;
		if(count % 100 == 0){
			//serprintf("brightness_set_once: %d, colors_set_once: %d \n", brightness_set_once, colors_set_once);
			serprintf("brightness sets: %d, colors sets: %d \n", dc_set_count, gs_set_count);
		}
		if(group_complete && adc_group_num==0){
			group_complete = false;
			set_adc_group_num(1);
		} 
		if(group_complete && adc_group_num==1){
			group_complete = false;
			send_report_in();
			update_brightness();
			set_adc_group_num(0);
		}
		if(led_gs_data_ready){
			led_gs_data_ready = false;
			spi_send_led_gs();
		}
	}

}