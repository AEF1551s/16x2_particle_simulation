#include <physics.h>

void display_single_particle(struct particle *particle)
{
    struct relative_position rel_pos;
    rel_pos = char_pos_from_absolute(&particle->pos);
    generate_single_pixel_char(rel_pos.pixel_position.y, rel_pos.pixel_position.x);
    //TODO: Based on particle counter change cgram adress, so it is possible to display up to 8 particles at the same time
    output_char(&(uint8_t){0x00}, rel_pos.char_seq);
}
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

    display_single_particle(particle);
}
void update_particle(struct particle *particle)
{
    // Gravity
    uint8_t g = 1;

    // Calculate new velocity with gravity
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
    display_single_particle(particle);
}
void spawn_all_particles()
{
    for (uint8_t i = 0; i < particle_count; i++)
    {
        spawn_particle(&particle_array[i]);
        for (volatile int i = 0; i < 50000; i++)
        {
            ;
        }
    }
}
void update_all_particles()
{
    for (uint8_t i = 0; i < particle_count; i++)
    {
        update_particle(&particle_array[i]);
        for (volatile int i = 0; i < 50000; i++)
        {
            ;
        }
        clear_display();
    }
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
void add_particle(struct particle *particle)
{
    // MAX 8 PARTICLES
    if (particle_count > 8)
    {
        return;
    }
    // Allocate space for particles
    if (particle_count == 0)
    {
        particle_array = (struct particle *)malloc(sizeof(struct particle));
    }
    if (particle_count > 0)
    {
        // Copy previous particles, add new
        struct particle *temp = realloc(particle_array, sizeof(struct particle) * particle_count + sizeof(struct particle));
        particle_array = temp;
    }

    particle_array[particle_count] = *particle;
    particle_count++;
}
void free_all_particles()
{
    free(particle_array);
    particle_count = 0;
    particle_array = NULL;
}