#if !defined(PHYSICS_H)
#define PHYSICS_H
// STD
#include <stdint.h>
// USER
#include <lcd_char_disp.h>
#include <particle_char_generator.h>
#include <positions.h>
#include <hardware_rand.h>

/*
Position 0;0 is LCD top left corner. x+ axis is right direction; y+ axis is up direction;
Physics calculates and displays particles position based on acceleration and velocity.
*/

struct velocity
{
    int8_t x;
    int8_t y;
};
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

static struct relative_position char_pos_from_absolute(struct position *position);
static void force_lcd_borders(struct particle *particle);
static void add_wall_bounce(struct particle *particle);
static void bump_y_stationary(struct particle *particle);

void add_particle(struct particle *particle);
void randomize_particle(struct particle *particle);
void update_particle(struct particle *particle);
void update_all_particles();
void display_all_particles();
void free_all_particles();

#endif // PHYSICS_H
