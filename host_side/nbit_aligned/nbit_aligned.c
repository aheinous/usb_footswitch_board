#include "nbit_aligned.h"

#define LOWER_8(n) ((uint8_t)(n & 0xFF))
#define UPPER_8(n) ((uint8_t)((n >> 8) & 0xFF))


// writes lower bits_per_word of data to dest, starting bit_offset bits past beginning. Lower
// bits are considered earlier than higher bits. Lower index bytes are considered to occur earlier,
// than higher index bytes.
void write_bit_offset_lsb(uint8_t * dest, int16_t bit_offset, uint8_t data, int8_t bits_per_word){
	int byte_index = bit_offset / 8;
	bit_offset %= 8;

	uint16_t offset_data = data << bit_offset;
	uint16_t mask = (1<<bits_per_word)-1;
	mask <<= bit_offset; 

	offset_data &= mask;

	dest[byte_index] &= ~LOWER_8(mask);
	dest[byte_index] |= LOWER_8(offset_data);

	if(UPPER_8(mask) != 0){
		dest[byte_index+1] &= ~UPPER_8(mask);
		dest[byte_index+1] |= UPPER_8(offset_data);
	}
}

void write_nbit_aligned_lsb_8(uint8_t*dest, int16_t word_index, uint8_t data, int8_t bits_per_word){
	write_bit_offset_lsb(dest, word_index* ((int16_t)bits_per_word) , data, bits_per_word);
}

void write_nbit_aligned_lsb_16(uint8_t*dest, int16_t word_index, uint16_t data, int8_t bits_per_word){
	if(bits_per_word <= 8){
		write_nbit_aligned_lsb_8(dest, word_index, LOWER_8(data), bits_per_word);
	}

	int16_t bit_offset = word_index * ((int16_t)bits_per_word);
	write_bit_offset_lsb(dest, bit_offset, LOWER_8(data), 8);
	write_bit_offset_lsb(dest, bit_offset+8, UPPER_8(data), bits_per_word-8);
}

// writes UPPER bits_per_word bits of data to dest, starting bit_offset bits past beginning. Higher
// bits are considered earlier than lower bits. Lower index bytes are considered to occur earlier,
// than higher index bytes.
void write_bit_offset_msb(uint8_t * dest, int16_t bit_offset, uint8_t data, int8_t bits_per_word){
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
void write_nbit_aligned_msb_8(uint8_t*dest, int16_t word_index, uint8_t data, int8_t bits_per_word){
	write_bit_offset_msb(dest, word_index* ((int16_t)bits_per_word) , data, bits_per_word);
}

// writes UPPER bits_per_word bits of data to dest, starting word_index words past beginning. 
// A word is considered to be bits_per_word bits. The maximum word size is 16 bits. Higher bits 
// are considered to occur earlier  than lower bits. Lower index bytes are considered to occur 
// earlier, than higher index bytes.
void write_nbit_aligned_msb_16(uint8_t*dest, int16_t word_index, uint16_t data, int8_t bits_per_word){
	if(bits_per_word <= 8){
		write_nbit_aligned_msb_8(dest, word_index, UPPER_8(data), bits_per_word);
	}

	int16_t bit_offset = word_index * ((int16_t)bits_per_word);
	write_bit_offset_msb(dest, bit_offset, UPPER_8(data), 8);
	write_bit_offset_msb(dest, bit_offset+8, LOWER_8(data), bits_per_word-8);
}