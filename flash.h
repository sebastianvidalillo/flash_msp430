#ifndef FLASH__H
#define FLASH__H
/*  Include section
*
***************************************************/
#include "msp430_version.h"

/*  Defines section
*
***************************************************/

/*  Function Prototype Section
*
***************************************************/

void flash_erase_segment(int);
void flash_write_byte(int , char, char, char, char, char, char, char);
void flash_read_data(int);
void flash_operation (int, char, char, char, char, char, char, char);


#endif