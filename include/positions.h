#if !defined(POSITIONS_H)
#define POSITIONS_H

// STD
#include <stdint.h>

/*
position - x and y coordinates
relative_position - LCD character and index positions; Also pixel position in singel character
char_seq_cgram_count - contains used CGRAM address count and pointer to LCD character index array 
*/

struct position
{
    int8_t x; // 0 - 79
    int8_t y; // 0 - 17
};
struct relative_position
{
    struct position char_position;  // 0-15
    struct position pixel_position; // 0-39
    uint8_t char_seq;               // 0-31
};
struct char_seq_cgram_count
{
    uint8_t addr_count;
    uint8_t *char_index_arr;
};
#endif // POSITIONS_H
