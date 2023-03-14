/*******************************************************************************
*                                  SD_CRC
* This is a library to handle CRC7 redundancy checks.
* Due to Arduino (Uno etc) not having 64bit storage registers, All the CRC
* algorithm is done in 32bit buffers, juggling new bits in.
*
* If this library is in use within another project, please see the original 
* github page: https://github.com/ADBeta/Arduino_SD_CRC
*
* v1.0.0   14 Mar 2023
* (c) ADBeta 
*******************************************************************************/

#include <Arduino.h>

#ifndef SD_CRC_H
#define SD_CRC_H

// Function that returns the position of the left-most 1 bit in a 32bit long
uint8_t leftBitPos(uint32_t input);

// CRC7 generator that returns SD/MMC card standard of CRC[7-1] 1[0]
uint8_t crc7(const uint8_t cmd, const uint32_t arg);

#endif
