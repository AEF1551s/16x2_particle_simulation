#include <physics.h>

void spawn_particle(struct particle *particle)
{
    // Check for valid absolute positions
    // Left side
    if (particle->pos.x < 0)
        particle->pos.x = 0;
    // Right side
    if (particle->pos.x > 79)
        particle->pos.x = 79;
    // Top
    if (particle->pos.y < 0)
        particle->pos.y = 0;
    // Buttom
    if (particle->pos.y > 15)
        particle->pos.y = 15;

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
    output_char(&(uint8_t){0x00}, rel_pos.char_seq);
}
void update_particle(struct particle *particle)
{
    // Gravity
    uint8_t g = 1;

    // Calculate new velocity
    particle->vel.y -= g;

    // New position from velocity
    particle->pos.x += particle->vel.x;
    particle->pos.y -= particle->vel.y;

    // Make sure the particle stays within the LCD screen borders
    // Left sied
    if (particle->pos.x < 0)
        particle->pos.x = 0;
    // Right side
    if (particle->pos.x > 79)
        particle->pos.x = 79;
    // Top
    if (particle->pos.y < 0)
    {
        particle->pos.y = 0;
        particle->acc.y = 0;
        particle->vel.y = 0;
    }
    // Buttom
    if (particle->pos.y > 15)
        particle->pos.y = 15;

    // Display particle
    struct relative_position rel_pos;
    rel_pos = char_pos_from_absolute(&particle->pos);
    generate_single_pixel_char(rel_pos.pixel_position.y, rel_pos.pixel_position.x);
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
    rel_pos.char_position.x = abs_pos_x / 5;
    rel_pos.char_position.y = abs_pos_y / 8;
    rel_pos.pixel_position.x = abs_pos_x % 5;
    rel_pos.pixel_position.y = abs_pos_y % 8;

    rel_pos.char_seq = rel_pos.char_position.y * 16 + rel_pos.char_position.x;
    return rel_pos;
}
