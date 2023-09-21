/**
 * @file fish.h
 * 
 * Contains the struct definition of type Fish.
 * 
 * @author Tao Hu
*/

#include "position.h"

typedef struct Fish
{
    Position position;
    float initialWeight;
    float weight;
} Fish;

Position fish_swim(Fish* fish) {
    
}