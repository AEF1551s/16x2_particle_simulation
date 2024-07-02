#if !defined(PARTICLE_CHAR_H)
#define PARTICLE_CHAR_H

#include <stdint.h>
#include <stdlib.h>

#include <lcd_char_disp.h>
#include <positions.h>

#define CHAR_WIDTH 5
#define CHAR_HEIGTH 8

// TODO: Add description

struct char_seq_cgram_count *generate_pixel_chars(uint8_t *rows, uint8_t *cols, uint8_t *char_indexes, uint8_t particle_count);

#endif // PARTICLE_CHAR_H
