#include <physics.h>

void spawn_particle(struct particle *particle)
{
    // Single particle only
    if (particle_count >= 1)
    {
        return;
    }

    particle_array[particle_count] = particle;
    // particle_count++;

    struct relative_position rel_pos;

    rel_pos = char_pos_from_absolute(&particle->pos);

    generate_single_pixel_char(rel_pos.pixel_position.y, rel_pos.pixel_position.x);

    // for (volatile int i = 0; i < 100000; i++)
    //     ;

    output_char(&(uint8_t){0x00}, rel_pos.char_seq);
}
static struct relative_position char_pos_from_absolute(struct position *position)
{
    struct relative_position rel_pos;

    // Returns char position and pixel position in char
    int8_t abs_pos_x = position->x;
    int8_t abs_pos_y = position->y;

    // 16x2 5x8 ;16x5 = 80 absolute x;
    // 2*8 = 16 absolute y
    rel_pos.char_position.x = ((abs_pos_x ) / 5);
    rel_pos.char_position.y = ((abs_pos_y ) / 8);
    rel_pos.pixel_position.x = ((abs_pos_x ) % 5);
    rel_pos.pixel_position.y = ((abs_pos_y ) % 8);

    rel_pos.char_seq = rel_pos.char_position.y * 16 + rel_pos.char_position.x;
    return rel_pos;
}
