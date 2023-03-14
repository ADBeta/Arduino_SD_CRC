# SD_CRC

This is an arduino library just to add SD/MMC card CRC (cyclic redundancy check)
support. 
**NOTE: ONLY CRC7 IS SUPPORTED AT THE MOMMENT**

I have tested this libraries CRC7 accuracy using an [online calculator](https://www.ghsi.de/pages/subpages/Online%20CRC%20Calculation/index.php)

The Arduino Uno/Nano/ATTiny cores only have 32bit storage units, so this library
switched the required 48 bits into a 32bit buffer to perform the calculations. 

## Usage
SD_CRC can be included in any project using
```C++
#include <sd_crc.h>
```

and from there you can use the lib functions as such
```C++
// CRC7 take a byte and a long, and will return a byte in the correct formatting
// of the SD/MMC Standard (xxxxxxx1), which you can transmit straight to the SD
crc7( cmd_8bit, arg_32bit ); 
```

----
<b> (c) ADBeta 2023</b>
This software is under the GPL v2.0 licence please read the LICENCE file
