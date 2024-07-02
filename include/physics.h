#if !defined(PHYSICS_H)
#define PHYSICS_H

#include <stdint.h>
#include <lcd_char_disp.h>
#include <particle_char_generator.h>
#include <positions.h>

// Position 0;0 is LCD top left corner. x+ axis is right direction; y+ axis is up direction;

struct velocity
{
    int8_t x;
    int8_t y;
};
// Can be negative
struct acceleration
{
    int8_t x;
    int8_t y;
};
struct particle
{
    struct position pos;
    struct velocity vel;
    struct acceleration acc;
};

static struct particle *particle_array = NULL;
static uint32_t particle_count = 0;

void add_particle(struct particle *particle);
void update_particle(struct particle *particle);
void update_all_particles();
void display_all_particles();
void free_all_particles();

static struct relative_position char_pos_from_absolute(struct position *position); // Gets char box positon and pixel position from absolute coordinates
#endif                                                                             // PHYSICS_H
