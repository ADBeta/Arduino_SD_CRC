#include <sd_crc.h>

void setup() {
	Serial.begin(9600);
	
	Serial.println( crc7(0x40, 0x00000000), HEX );
}

void loop() {
}
