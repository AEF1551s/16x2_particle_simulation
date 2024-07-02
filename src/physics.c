#include <physics.h>

void add_particle(struct particle *particle)
{
    // MAX 8 PARTICLES
    if (particle_count > 8)
    {
        return;
    }

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

    // Allocate space for particles
    if (particle_count == 0)
    {
        particle_array = (struct particle *)malloc(sizeof(struct particle));
    }
    if (particle_count > 0)
    {
        // Copy previous particles, add new
        struct particle *temp = realloc(particle_array, sizeof(struct particle) * (particle_count + 1));
        particle_array = temp;
    }

    particle_array[particle_count] = *particle;
    particle_count++;
}
void update_particle(struct particle *particle)
{
    // Gravity
    uint8_t g = 1;

    // Calculate new velocity with gravity
    particle->vel.y -= g;

    // Overflow check for Y axis due to gravity
    // Screen is only 80x16 pixels wide, so no need to check more then that
    if (particle->vel.y > 80)
    {
        particle->vel.y = 80;
    }
    if (particle->vel.y < -80)
    {
        particle->vel.y = -80;
    }

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
}
void update_all_particles()
{
    for (uint8_t i = 0; i < particle_count; i++)
    {
        update_particle(&particle_array[i]);
    }
}
void display_all_particles()
{
    if (particle_count == 0)
        return;

    // Save all particle relative positions into array
    // struct relative_position *rel_pos_array = (struct relative_position *)malloc(sizeof(struct relative_position) * particle_count);
    uint8_t rows_array[particle_count];
    uint8_t cols_array[particle_count];
    uint8_t char_index_array[particle_count];

    for (uint32_t i = 0; i < particle_count; i++)
    {
        struct relative_position rel_pos = char_pos_from_absolute(&particle_array[i].pos);
        rows_array[i] = rel_pos.pixel_position.y;
        cols_array[i] = rel_pos.pixel_position.x;
        char_index_array[i] = rel_pos.char_seq;
    }

    struct char_seq_cgram_count *cgram_count = generate_pixel_chars(rows_array, cols_array, char_index_array, particle_count);
    if (cgram_count == NULL)
        return;

    for (uint8_t i = 0; i < cgram_count->addr_count; i++)
    {
        output_char(&(uint8_t){i}, cgram_count->char_index_arr[i]);
    }
    // output_char(&(uint8_t){0}, cgram_count->char_index_arr[0]);
    // output_char(&(uint8_t){1}, cgram_count->char_index_arr[1]);
    free(cgram_count->char_index_arr);
    cgram_count->char_index_arr = NULL;
    free(cgram_count);
    cgram_count = NULL;
}
void free_all_particles()
{
    free(particle_array);
    particle_count = 0;
    particle_array = NULL;
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