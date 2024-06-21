#if !defined(PARTICLE_CHAR_H)
#define PARTICLE_CHAR_H

#include <stdint.h>
#include <stdlib.h>

#include <lcd_char_disp.h>

#define CHAR_WIDTH 5
#define CHAR_HEIGTH 8

//TODO: Add description

//Generated pixel character in CGRAM base address 0x00
void generate_single_pixel_char(uint8_t row, uint8_t col);

#endif // PARTICLE_CHAR_H
