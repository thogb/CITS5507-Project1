/**
 * @file fish.h
 * 
 * Contains the struct definition of type Fish.
 * 
 * @author Tao Hu
*/

#ifndef FISH_H
#define FISH_H

#include <math.h>
#include "position.h"
#include "sim_util.h"

#define FISH_WEIGHT_MAX_SCALE 2
#define FISH_WEIGHT_MIN 0.5f
#define FISH_WEIGHT_MAX 2.0f
#define FISH_SWIM_MIN -0.1f
#define FISH_SWIM_MAX 0.1f

/**
 * @brief Represent a fish in the simulation.
 * 
 * Contains information about a fish.
 */
typedef struct Fish
{
    Position position;
    float initialWeight;
    float weight;   
} Fish;

/**
 * Initializes a fish object with the given position.
 *
 * @param fish a pointer to the Fish object to be initialized
 * @param position the position of the fish
 *
 * @return void
 */
void fish_init(Fish* fish, Position position) {
    fish->position = position;
    fish->initialWeight = rand_float(FISH_WEIGHT_MIN, FISH_WEIGHT_MAX);
    fish->weight = fish->initialWeight;
}

/**
 * @brief Performs a fish's swim in the simulation
 * 
 * The input fish will swim in both x and y direction randomly depending on the
 * value defined by FISH_SWIM_MIN and FISH_SWIM_MAX.
 * 
 * @param fish the fish that will perofmr a swim
 * @return Position the new position of the fish
 */
Position fish_swim(Fish* fish) {
    position_increment(
        &(fish->position), 
        rand_float(FISH_SWIM_MIN, FISH_SWIM_MAX), 
        rand_float(FISH_SWIM_MIN, FISH_SWIM_MAX)
    );
    return fish->position;
}

/**
 * Updates the weight of a fish based on the weight gain. The fish's weight will
 *  not go below 0.0 and will not go above its initial weight * 
 * FISH_WEIGHT_MAX_SCALE.
 *
 * @param fish A pointer to the Fish object.
 * @param weight_gain The amount of weight gained by the fish.
 */
void fish_eat(Fish* fish, float weight_gain) {
    float newWeight = fish->weight + weight_gain;
    fish->weight = max_float(
        min_float(
            newWeight,
            0.0f
        ),
        fish->initialWeight * FISH_WEIGHT_MAX_SCALE
    );
}

#endif
