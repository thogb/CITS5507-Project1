/**
 * @file position.h
 * 
 * Contains struct definition of type Position and function to modify position
 * pointers.
 * 
 * @author Tao Hu
*/

#include <math.h>

typedef struct Position
{
    float x;
    float y;
} Position;

float position_distance_from_zero(Position* position) {
    float x = position->x;
    float y = position->y;
    return sqrt(x * x + y * y);
}

void position_increment(Position* position, float x, float y) {
    position->x = position->x + x;
    position->y = position->y + y;
}