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
FishLake* fish_lake_new(int fish_amount) {
    FishLake* fishLake = (FishLake*) malloc(sizeof(FishLake));

    fishLake->fish_amount = fish_amount;
    fishLake->fish = (Fish*) malloc(fish_amount * sizeof(Fish));

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
