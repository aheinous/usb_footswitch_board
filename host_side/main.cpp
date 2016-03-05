// g++ main.cpp nbit_aligned/nbit_aligned.c -o main -lhidapi-libusb -std=gnu++11

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <unistd.h>
#include "hidapi/hidapi.h"
#include "nbit_aligned/nbit_aligned.h"

const uint16_t VENDOR_ID = 0xf055;
const uint16_t PRODUCT_ID = 0x0101;
// const int WSTR_BUFFER_SIZE = 256;
// const int STR_BUFFER_SIZE = 512;

const char * LEFT_FMT = "%-30s";
const char * RIGHT_FMT = "%20s\n";

// hid_device* device = NULL;

static inline uint16_t bytes_to_uint16_t(uint8_t lower, uint8_t higher){
	return (((uint16_t)higher)<<8) | ((uint16_t) lower);
}


#define RED 0
#define GREEN 1
#define BLUE 2

#define BITS_PER_LED_CHANNEL (12)
#define LEN_LED_GS_DATA (48)
#define NUM_LEDS 10
// static uint8_t led_gs_data[LEN_LED_GS_DATA] = {0};
// #define LEN_LED_DC_DATA (24)
// static uint8_t led_dc_data[LEN_LED_DC_DATA] = {0};

// python3:
// for i in range(0,30,3): print('\t{{{}, {}, {}}},'.format(i,i+1,i+2) )
const static int8_t LED_MAP[NUM_LEDS][3] = {
	{0, 1, 2},
	{3, 4, 5},
	{6, 7, 8},
	{9, 10, 11},
	{12, 13, 14},
	{15, 16, 17},
	{18, 19, 20},
	{21, 22, 23},
	{24, 25, 26},
	{27, 28, 29}
};



void print_bin(uint8_t n){
	// printf("%d: ", n);
	for(int i=0; i<8; i++){
		printf( (n&0x80) ? "1" : "0" );
		n<<=1;
	}
}

void print_buffer_bin_msb(uint8_t * buffer, int len){
	printf("[0] ");
	for(int i=0;  i<len; i++){
		print_bin(buffer[i]);
		printf(" ");

	}
	printf("[%d] \n", len-1);
}



void quit(int error_code){
	// if (device != NULL){
	// 	printf("Releasing device.\n");
	// 	hid_close(device);
	// }
	printf("Exiting HID.\n");
	hid_exit();
	if(error_code==0){
		printf("No errors. Good bye.\n");
	}else{
		fprintf(stderr, "ERROR CODE: %d\n", error_code);
	}
	exit(error_code);
}

uint16_t left_align(uint16_t data, int8_t bits_per_word){
	return data << (16-bits_per_word);
}

void print_switches(uint16_t bit_vec){
	// printf("bit_vec: %x\n",bit_vec);
	bool first = true;
	printf("Foot Switches: ");
	for(int i=1; i<=10; i++){
		if(bit_vec & (1<<(i-1))){
			if( ! first){
				printf(", ");
			}
			first = false;
			printf("%d", i);
		}
	}
	if(first) printf("None.");
	printf("\n");
}

class FootswitchBoard {
private:
	hid_device * device = NULL;
	//wchar_t wstr_buffer[WSTR_BUFFER_SIZE];
	int64_t reports_received = 0;
	uint8_t led_data_buffer[LEN_LED_GS_DATA+1] = {0};


public:
	FootswitchBoard(){}

	bool open(bool retry_forever=false){
		bool success;
		printf(LEFT_FMT, "Opening device ...");
		if(device!=NULL){
			printf(RIGHT_FMT, "... Already open.");
			return true;
		}
		device = hid_open(VENDOR_ID, PRODUCT_ID, NULL);
		success = (device != NULL);
		printf(RIGHT_FMT, success?"... SUCCESS":"... FAILED");
		if( ! success && retry_forever){
			printf(LEFT_FMT, "Retrying forever ...");
			fflush(stdout);
			while( ! success){
				sleep(1);
				device = hid_open(VENDOR_ID, PRODUCT_ID, NULL);
				success = (device != NULL);
			}
			printf(RIGHT_FMT, "... SUCCESS");
		}
		return success;
	}
	
	bool isOpen(){
		return device != NULL;
	}

	void print_buffer(){
		print_buffer_bin_msb(&led_data_buffer[1], LEN_LED_GS_DATA);
	}

	void read_loop(){
		uint8_t report[128];
		while(true){
			int bytes_read = hid_read(device, &report[0], 128);
			if(bytes_read == -1){
				fprintf(stderr, "Error during read. Disconnected.\n");
				return;
			}
			reports_received ++;
			printf("Report %ld:\n", reports_received);
			printf("Received %d byte(s)\n", bytes_read);
			print_switches( bytes_to_uint16_t(report[0], report[1]) );

			// for(int i=2; i<bytes_read; i+=1){
			// 	printf("%d\n", report[i]);
			// }
		}
	}

	void set_led_color (int led_num, int color, uint16_t value){
		int index = LED_MAP[led_num][color];
		value = left_align(value, BITS_PER_LED_CHANNEL);
		write_nbit_aligned_msb_16(&led_data_buffer[1], index, value, BITS_PER_LED_CHANNEL);
	}

	void set_led_rgb(int led_num, uint16_t r, uint16_t g, uint16_t b){
		set_led_color(led_num, RED, r);
		set_led_color(led_num, GREEN, g);
		set_led_color(led_num, BLUE, b);
	}

	bool send_led_data(){
		int bytes_wrote;
		bytes_wrote = hid_write(device, led_data_buffer, LEN_LED_GS_DATA+1);
		return bytes_wrote != -1;
	}

	virtual ~FootswitchBoard(){
		if(device != NULL){
			printf("Releasing device.\n");
			hid_close(device);
		}
	}
};



int main(void){
	FootswitchBoard footy;

	footy.open(true);
	//printf("Entering read loop:\n");
	//footy.read_loop();

	for(int i=0; i<NUM_LEDS; i++){
		footy.set_led_rgb(i, 0xAA, 0xBB,0xCC);
	}

	footy.print_buffer();

	while(true){
		sleep(1);
		printf("Sending LED data.\n");

		bool success = footy.send_led_data();
		if(!success){
			printf("Failed.\n");
			break;
		}
	}
	
}