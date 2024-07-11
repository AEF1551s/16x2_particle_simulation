#include <physics.h>
// Calculates relative position (LCD character, pixel within character and LCD character index/address) from absolute (x:0-79 y:0-15)
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
// Make sure the particle stays within the LCD screen borders
static void force_lcd_borders(struct particle *particle)
{
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
}
// When hits a wall, bounces back with reduced acceleration.
static void add_wall_bounce(struct particle *particle)
{
    const int8_t top_buttom_const = 1;
    const int8_t left_rigt_const = 1;
    // Left side
    if (particle->pos.x <= 0 && particle->vel.x < 0)
        particle->vel.x = -particle->vel.x - left_rigt_const; // Reverse direction and reduce speed
    // Right side
    if (particle->pos.x >= 79 && particle->vel.x > 0)
        particle->vel.x = -particle->vel.x + left_rigt_const;
    // Top
    if (particle->pos.y <= 0 && particle->vel.y > 0)
        particle->vel.y = -particle->vel.y + top_buttom_const;
    // Bottom
    if (particle->pos.y >= 15 && particle->vel.y < 0)
        particle->vel.y = -particle->vel.y - top_buttom_const;
}
// Add linear rolling resistance
static void add_rolling_resistance(struct particle *particle)
{
    // If is on ground, and vertical velocity is 0
    if (particle->pos.y >= 15)
    {
        if (particle->vel.x < 0)
            particle->vel.x += 1;

        if (particle->vel.x > 0)
            particle->vel.x -= 1;
    }
}
// Check if any particle is stationary+1, if so add random acceleration in +y and velocity
static void bump_y_stationary(struct particle *particle)
{
    // If particle is rolling on gound without vertical velocity
    if (particle->vel.y <= 0 && particle->vel.x <= 1 && particle->vel.x >= -1 && particle->pos.y >= 15)
    {
        particle->vel.x = random_uint32() % 8;
        particle->vel.y = random_uint32() % 8;
    }
}
// Add particle to particle array for further use
void add_particle(struct particle *particle)
{
    // MAX 8 PARTICLES
    if (particle_count > 8)
    {
        // If particle count stays 9, it can interfere with other functions that take particle_count as argument
        particle_count = 8;
        return;
    }

    force_lcd_borders(particle);

    // Allocate space for particles, if particle_array = NULL the it works same as malloc()
    particle_array = realloc(particle_array, sizeof(struct particle) * (particle_count + 1));
    assert(particle_array != NULL);

    particle_array[particle_count] = *particle;
    particle_count++;
}
// Randomize particle velocity and position
void randomize_particle(struct particle *particle)
{
    particle->pos.x = random_uint32() % 80;
    particle->pos.y = random_uint32() % 18;
    particle->vel.x = random_uint32() % 8;
    particle->vel.y = random_uint32() % 8;
}
// Update particle position, velocity and acceleration.
void update_particle(struct particle *particle)
{
    // Gravity
    uint8_t g = 1;

    // Calculate new velocity with gravity
    particle->vel.y -= g;

    // Overflow check for Y axis due to gravity
    // Screen is only 80x16 pixels wide, so no need to check more
    if (particle->vel.y > 80)
        particle->vel.y = 80;

    if (particle->vel.y < -80)
        particle->vel.y = -80;

    // New position from velocity
    particle->pos.x += particle->vel.x;
    particle->pos.y -= particle->vel.y;

    add_wall_bounce(particle);
    force_lcd_borders(particle);
}
// Update all particles position, velocity and acceleration.
void update_all_particles()
{
    for (uint8_t i = 0; i < particle_count; i++)
    {
        update_particle(&particle_array[i]);
        add_rolling_resistance(&particle_array[i]);
        bump_y_stationary(&particle_array[i]);
    }
}
// Display all particles
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
// Displa all particles from buffer parameter
void display_particles(struct char_seq_cgram_count *cgram_count)
{
    for (uint8_t i = 0; i < cgram_count->addr_count; i++)
    {
        output_char(&(uint8_t){i}, cgram_count->char_index_arr[i]);
    }
    free(cgram_count->char_index_arr);
    cgram_count->char_index_arr = NULL;
    free(cgram_count);
    cgram_count = NULL;
}
// Buffer single particle into CGRAM
struct char_seq_cgram_count *buffer_particles()
{
    if (particle_count == 0)
        return NULL;

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
    return cgram_count;
}

// Free particle_array memory
void free_all_particles()
{
    free(particle_array);
    particle_count = 0;
    particle_array = NULL;
}
