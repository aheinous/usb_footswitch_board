// gcc nbit_aligned.c nbit_aligned_test.c -o nbit_test -std=gnu11


#include <stdio.h>
#include "nbit_aligned.h"


void print_bin(uint8_t n){
	// printf("%d: ", n);
	for(int i=0; i<8; i++){
		printf( (n&0x80) ? "1" : "0" );
		n<<=1;
	}
}

void print_bin_16(uint16_t n){
	// printf("%d: ", n);
	for(int i=0; i<16; i++){
		printf( (n&0x8000) ? "1" : "0" );
		n<<=1;
		if(i==7) printf(" ");
	}
}

void print_buffer_bin_lsb(uint8_t * buffer, int len){
	printf("[%d] ", len-1);
	for(int i=len-1;  i>=0; i--){
		print_bin(buffer[i]);
		if(i != 0){
			printf(" ");
		}
	}
	printf(" [0]\n");
}

void lsb_test(){
	for(int i=0; i<20; i++){
		uint8_t buff[4] = {0};
		printf("\ni=%d:\n",i );
		write_bit_offset_lsb(buff, i, 0xFF, 8);
		print_buffer_bin_lsb(buff, 4);
		
	}

	printf("-------------------------------------------------------------------\n");

	for(int i=0; i<4; i++){
		uint8_t buff[4] = {0};
		printf("\ni=%d:\n",i );
		write_nbit_aligned_lsb_8(buff, i, 0xFF, 6);
		print_buffer_bin_lsb(buff, 4);
	}

	
	printf("-------------------------------------------------------------------\n");

	for(int i=0; i<4; i++){
		uint8_t buff[6] = {0};
		printf("\ni=%d:\n",i );
		write_nbit_aligned_lsb_16(buff, i, 0x2AB, 10);
		print_buffer_bin_lsb(buff, 6);
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

void msb_test(){
	for(int i=0; i<20; i++){
		uint8_t buff[4] = {0};
		printf("\ni=%d:\n",i );
		write_bit_offset_msb(buff, i, 0xFF, 8);
		print_buffer_bin_msb(buff, 4);
		
	}

	printf("-------------------------------------------------------------------\n");

	for(int i=0; i<4; i++){
		uint8_t buff[4] = {0};
		printf("\ni=%d:\n",i );
		write_nbit_aligned_msb_8(buff, i, 0xFF, 6);
		print_buffer_bin_msb(buff, 4);
	}

	
	printf("-------------------------------------------------------------------\n");

	for(int i=0; i<4; i++){
		uint8_t buff[6] = {0};
		printf("\ni=%d:\n",i );
		write_nbit_aligned_msb_16(buff, i, 0xAFC0, 10);
		print_buffer_bin_msb(buff, 6);
	}	
}

int main(){
	
	printf("-------------------------------------------------------------------\n");
	printf("------------------------- LSB TESTS -------------------------------\n");
	printf("-------------------------------------------------------------------\n");

	lsb_test();

	printf("-------------------------------------------------------------------\n");
	printf("------------------------- MSB TESTS -------------------------------\n");
	printf("-------------------------------------------------------------------\n");

	msb_test();
}
