#if !defined(PARTICLE_CHAR_H)
#define PARTICLE_CHAR_H

// STD
#include <stdint.h>
#include <stdlib.h>
// USER
#include <lcd_char_disp.h>
#include <positions.h>

#define CHAR_WIDTH 5
#define CHAR_HEIGTH 8

/*
Generates up to 8 custom characters based on up to 8 particle positions.
If multiple particles are in single LCD character, all of particle pixels are written into the same CGRAM address.
*/

// Generates pixel characters based on given particles x, y, and LCD character indexes.
struct char_seq_cgram_count *generate_pixel_chars(uint8_t *rows, uint8_t *cols, uint8_t *char_indexes, uint8_t particle_count);

#endif // PARTICLE_CHAR_H
