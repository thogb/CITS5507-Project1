/**
 * @file sim_util.h
 * 
 * Contains helping functions that will be commonly used in this project
 * 
 * @author Tao Hu
*/

#include <stdlib.h>

float rand_float(float min, float max);

float rand_float(float min, float max) {
    float randFloat = (float) rand() / (float) RAND_MAX;
    return min + randFloat * (max - min);
}