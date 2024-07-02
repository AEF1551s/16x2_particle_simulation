#include <particle_char_generator.h>

// Returns count of used CGRAM addresses
struct char_seq_cgram_count *generate_pixel_chars(uint8_t *rows, uint8_t *cols, uint8_t *char_indexes, uint8_t particle_count)
{
    // TODO: check rows/columns if correct put
    if (particle_count == 0 || particle_count > 8)
    {
        return NULL;
    }

    // Return space
    struct char_seq_cgram_count *result = (struct char_seq_cgram_count *)malloc(sizeof(struct char_seq_cgram_count));

    uint8_t used_addr = particle_count;
    uint8_t current_addr = 0;

    // used_index to keep track of already checked indexes.
    // bool *checked = (bool *)calloc(particle_count, sizeof(bool));
    bool checked[particle_count];
    // array to write into CGRAM
    uint8_t *array = (uint8_t *)calloc(CHAR_HEIGTH, sizeof(uint8_t));

    uint8_t result_char_array_size = 1;
    uint8_t result_char_array_count = 0;
    uint8_t *result_char_array = (uint8_t *)malloc(sizeof(uint8_t) * result_char_array_size);

    bool first_time = true;

    // Check for same particles in single LCD character
    for (uint8_t i = 0; i < particle_count; i++)
    {
        if (checked[i] == true)
        {
            continue;
        }
        else
        {

            // 0 the array for new particle
            for (uint8_t k = 0; k < CHAR_HEIGTH; k++)
            {
                array[k] = 0x00;
            }
            // TODO: FIX EXTRA SPACE ALLOCATION
            // Saves primary char indexes into array
            result_char_array[result_char_array_count] = char_indexes[i];
            result_char_array_size++;
            result_char_array_count++;
            result_char_array = (uint8_t *)realloc(result_char_array, sizeof(uint8_t) * result_char_array_size);
        }

        uint8_t base_row = rows[i];
        uint8_t base_col = cols[i];

        if (base_row >= CHAR_HEIGTH || base_col >= CHAR_WIDTH)
            return NULL;
        // col is from 0 to 4, char width is from 1-5
        base_col = CHAR_WIDTH - base_col - 1;

        array[base_row] |= 1U << base_col;

        checked[i] = true;

        for (uint8_t j = 0; j < particle_count; j++)
        {
            // Skip check with itself
            if (i == j)
                continue;
            if (checked[j] == true)
                continue;
            if (char_indexes[i] == char_indexes[j])
            {
                checked[j] = true;

                uint8_t row = rows[j];
                uint8_t col = cols[j];

                if (row >= CHAR_HEIGTH || col >= CHAR_WIDTH)
                    return NULL;
                col = CHAR_WIDTH - col - 1;

                array[row] |= 1U << col;

                used_addr--;
            }
        }

        add_custom_char(current_addr, array, CHAR_HEIGTH, first_time);
        first_time = false;
        current_addr++;
    }

    // free(checked);
    // checked = NULL;
    free(array);
    array = NULL;

    result->addr_count = current_addr;
    result->char_index_arr = result_char_array;
    return result;
}