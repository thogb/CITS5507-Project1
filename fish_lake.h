/**
 * @file fish_lake.h
 * 
 * Contains the struct definition of type FishLake and functions to create, 
 * modify and free from heap.
 * 
 * @author Tao Hu
*/

#ifndef FISH_LAKE_H
#define FISH_LAKE_H

#include <stdlib.h>
#include "fish.h"

/**
 * @brief Fishlake in the simulation.
 * 
 * Contains 
 */
typedef struct FishLake
{
    float coord_min_x;
    float coord_max_x;
    float coord_min_y;
    float coord_max_y;
    int fish_amount;
    Fish* fish;
} FishLake;

/**
 * Creates a new instance of FishLake with the specified fish amount.
 *
 * @param fish_amount the amount of fish in the lake
 *
 * @return a pointer to the newly created FishLake instance
 */
FishLake* fish_lake_new(
    int fish_amount,
    float width,
    float height
    ) {
    FishLake* fishLake = (FishLake*) malloc(sizeof(FishLake));

    float half_width = width / 2.0f;
    float half_height = height / 2.0f;

    fishLake->fish_amount = fish_amount;
    fishLake->fish = (Fish*) malloc(fish_amount * sizeof(Fish));
    fishLake->coord_min_x = -half_width;
    fishLake->coord_max_x = half_width;
    fishLake->coord_min_y = -half_height;
    fishLake->coord_max_y = half_height;

    // give each fish a random coordinate
    for (int i = 0; i < fish_amount; i++) {
        Position pos = {
            rand_float(
            fishLake->coord_min_x,
            fishLake->coord_max_x
            ),
            rand_float(
            fishLake->coord_min_y,
            fishLake->coord_max_y
            )};
        // initialise the fish, also sets a random weight
        fish_init(&(fishLake->fish[i]),pos);
    }

    return fishLake;
}

/**
 * Frees the memory allocated for a FishLake object.
 *
 * @param fishLake the pointer to the FishLake object to be freed
 */
void fish_lake_free(FishLake* fishLake) {
    free(fishLake->fish);
    free(fishLake);
}

#endif
