/*******************************************************************************
*                                  SD_CRC
* This is a library to handle CRC7 redundancy checks.
* Due to Arduino (Uno etc) not having 64bit storage registers, All the CRC
* algorithm is done in 32bit buffers, juggling new bits in.
*
* If this library is in use within another project, please see the original 
* github page: https://github.com/ADBeta/Arduino_SD_CRC
*
* (c) ADBeta 2023
*******************************************************************************/

#include "sd_crc.h"

// Function that returns the position of the left-most 1 bit in a 32bit long
uint8_t leftBitPos(uint32_t input) {
	uint8_t cPos = 31;
	
	// Shift the input by cPos, until the output is a 1 bit
	while( (input >> cPos) == 0x00 ) {
			--cPos;
			// if the leftBitPos decriments to 0, break from function
			if(cPos == 0) return 0;
	}
	
	return cPos;
}

// CRC7 generator that returns SD/MMC card standard of CRC[7-1] 1[0]
uint8_t crc7(const uint8_t cmd, const uint32_t arg) {
	uint16_t chunk[3]; // 3x 16bit chunks to use for the input
	uint32_t buffer; // 32bit buffer to work with the chunks inside of.
	
	/*** Generate the chunks ***************************************************
	                               NOTE: 
	All of the following bit shifts are biased one to the right, so << 8 becomes
	<< 7, and >> 8 becomes >> 9
	***************************************************************************/
	// The first chunk is the cmd byte and upper-most byte of arg
	chunk[0] = ((uint16_t)cmd << 7) | (arg >> 25);	
	// The second chunk is byte 2 and 3 of arg
	chunk[1] = arg >> 9;
	// The last chunk is the lower-most byte of arg
	chunk[2] = arg << 7;
	
	/*** Calculate the CRC7 checksum ******************************************/
	// We can instantly load chunk[0] and chunk[1] into the buffer.
	buffer = chunk[0];
	buffer = (buffer << 16) | chunk[1];
	
	// CRC Loop variables
	bool chunkSwapped = false; // Has the third chunk been swapped in?
	
	// Loop until a break event happens (when bitPos is less than 7)
	while(true) {
		// Find the left-most 1 bit in the buffer
		uint8_t bitPos = leftBitPos(buffer);
		
		// If the leftmost bit is below b7 there are 2 things that can happen
		if(bitPos < 7) {
			// If the chunk[2] hasn't been moved in, do that, then continue
			if(chunkSwapped == false) {
				buffer = (buffer << 16) | chunk[2];
				chunkSwapped = true;
				continue;
							
			} else {			
			// Otherwise, the CRC is finished
				break;		
			}
		}
		
		// If the bitPos is above 7 (nominal), Calculate long division on the
		// Polynomial. bitPos - 7 is to align the polynomial and the buffer on
		// the leftmost 1 bit
		// 0x89 (0b10001001) is the CRC polynomial P(x) = x^7 + x^3 + x^0
		uint32_t polynomial = (uint32_t)0x89 << (bitPos - 7);
		
		// XOR the buffer and the polynomial, then repeat the loop
		buffer = buffer ^ polynomial;
	}
	
	//Convert buffer to uint8_t, Shift buffer left 1, OR it with 0x01
	return (((uint8_t)buffer << 1) | 0x01);
}

