#if !defined(POSITIONS_H)
#define POSITIONS_H

#include <stdint.h>

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
