#include <particle_char_generator.h>

// As LSB, pixel moves from right to left. For convenience we convert this to MSB
void generate_single_pixel_char(uint8_t row, uint8_t col)
{
    if (row >= CHAR_HEIGTH || col >= CHAR_WIDTH)
        return;
    
    //col is from 0 to 4, char width is from 1-5
    col = CHAR_WIDTH - col -1;

    // Allocates 8 bytes for array
    uint8_t *array = (uint8_t *)malloc(sizeof(uint8_t) * CHAR_HEIGTH);

    // Initialize to empty char
    for (uint8_t i = 0; i < CHAR_HEIGTH; i++)
    {
        array[i] = 0x00;
    }

    uint8_t value = 0x00 | 1U << col;

    array[row] = value;

    uint8_t base_addr = 0x00;
    add_custom_char(base_addr, array, CHAR_HEIGTH);

    free(array);
}