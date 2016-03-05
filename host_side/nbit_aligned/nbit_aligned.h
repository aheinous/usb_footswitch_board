
#ifndef NBIT_ALIGNED_H
#define NBIT_ALIGNED_H

#include <stdint.h>


// writes lower bits_per_word of data to dest, starting bit_offset bits past beginning. Lower
// bits are considered earlier than higher bits. Lower index bytes are considered to occur earlier,
// than higher index bytes.
void 
write_bit_offset_lsb (	uint8_t * dest, 
						int16_t bit_offset, 
						uint8_t data, 
						int8_t bits_per_word);

void 
write_nbit_aligned_lsb_8(	uint8_t*dest, 
							int16_t word_index, 
							uint8_t data,	
							int8_t bits_per_word);

void 
write_nbit_aligned_lsb_16(	uint8_t*dest, 
							int16_t word_index, 
							uint16_t data, 
							int8_t bits_per_word);

// writes UPPER bits_per_word bits of data to dest, starting bit_offset bits past beginning. Higher
// bits are considered earlier than lower bits. Lower index bytes are considered to occur earlier,
// than higher index bytes.
void
write_bit_offset_msb(	uint8_t * dest, 
						int16_t bit_offset, 
						uint8_t data, 
						int8_t bits_per_word);

// writes UPPER bits_per_word bits of data to dest, starting word_index words past beginning. 
// A word is considered to be bits_per_word bits. The maximum word size is 8 bits. Higher bits 
// are considered to occur earlier  than lower bits. Lower index bytes are considered to occur 
// earlier, than higher index bytes.
void 
write_nbit_aligned_msb_8(	uint8_t*dest, 
							int16_t word_index, 
							uint8_t data, 
							int8_t bits_per_word);

// writes UPPER bits_per_word bits of data to dest, starting word_index words past beginning. 
// A word is considered to be bits_per_word bits. The maximum word size is 16 bits. Higher bits 
// are considered to occur earlier  than lower bits. Lower index bytes are considered to occur 
// earlier, than higher index bytes.
void 
write_nbit_aligned_msb_16(	uint8_t*dest, 
							int16_t word_index, 
							uint16_t data, 
							int8_t bits_per_word);

#endif