/**
 * @file simulation_sequential.c
 * 
 * Program to perform a very simplified version of the fish school search 
 * simulation using only one thread.
 * 
 * @author Tao Hu
 */

#include <time.h>
#include "fish_lake.h"


#define SIMULATION_STEPS 100
#define FISH_AMOUNT 100
#define FISH_LAKE_WIDTH 200.0f
#define FISH_LAKE_HEIGHT 200.0f

int main(int argc, char const *argv[])
{
    FishLake* fishLake = fish_lake_new(
        FISH_AMOUNT, 
        FISH_LAKE_WIDTH, 
        FISH_LAKE_HEIGHT);

    clock_t start = clock();

    for (int i = 0; i < SIMULATION_STEPS; i++)
    {
        for (int j = 0; j < FISH_AMOUNT; j++) {
            // The fish will swim and keep track of the old position, which is
            // used to calculate delta f (the change in objective functi)
            Position oldPos = fishLake->fish[j].position;
            Position newPos = fish_swim(&(fishLake->fish[j]));
        }
    }
    
    clock_t end = clock();
    double elapsed_secs = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f\n", elapsed_secs);

    fish_lake_free(fishLake);
    return 0;
}
