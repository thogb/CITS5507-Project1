/**
 * @file simulation_sequential.c
 * 
 * Program to perform a very simplified version of the fish school search 
 * simulation using only one thread.
 * 
 * @author Tao Hu
 */

#include <time.h>
#include <stdio.h>
#include "fish_lake.h"
#include "sim_util.h"
#include "fish.h"

#ifdef __APPLE__
    #include "/opt/homebrew/Cellar/libomp/17.0.1/include/omp.h"
#else
    #include <omp.h>
#endif

#define SIMULATION_STEPS 20
#define FISH_AMOUNT 200000
#define FISH_LAKE_WIDTH 200.0f
#define FISH_LAKE_HEIGHT 200.0f

int main(int argc, char const *argv[])
{
    // omp_set_num_threads(16);
    printf("Prgram: omp_get_max_threads = %d\n", omp_get_max_threads());

    // Init random seed
    srand(time(NULL));
    // During some testing on my mac, first rand() is broken, generating value
    // with little change when time(NULL) changes.
    rand();

    FishLake* fishLake = fish_lake_new(
        FISH_AMOUNT, 
        FISH_LAKE_WIDTH, 
        FISH_LAKE_HEIGHT);

    double start = omp_get_wtime();

    // The simulation start with t or i = 0 representing the first time step. 
    // But before this, fish are all initialised with random weight and position 
    for (int i = 0; i < SIMULATION_STEPS; i++)
    {
        // deltaF should always be greater than 0, so -1.0 is enough
        float maxDeltaF = -1.0f;
        Fish* fishes = fishLake->fishes;

        float objectiveValue = 0.0f;
        float baryCentre = 0.0f;
        float sumOfDistWeight = 0.0f;

        // calc the value of objective function
        #pragma omp parallel for reduction(+: objectiveValue)
        for (int i = 0; i < FISH_AMOUNT; i++)
        {
            objectiveValue += fishes[i].distanceFromOrigin;
        }

        #pragma omp parallel for reduction(+: sumOfDistWeight)
        for (int i = 0; i < FISH_AMOUNT; i++)
        {
            sumOfDistWeight += fishes[i].distanceFromOrigin * fishes[i].weight;
        }

        #pragma omp parallel for
        for (int j = 0; j < FISH_AMOUNT; j++) {
            // The fish will swim and keep track of the old position, which is
            // used to calculate delta f (the change in objective function).
            // Each fish also stores a deltaF maxDeltaF is updated.
            float deltaF = fish_lake_fish_swim(fishLake, &(fishes[j]));
        }

        #pragma omp parallel for reduction(max: maxDeltaF)
        for (int i = 0; i < FISH_AMOUNT; i++)
        {
            maxDeltaF = max_float(maxDeltaF, fishes[i].deltaF);
        }

        #pragma omp parallel for
        for (int i = 0; i < FISH_AMOUNT; i++)
        {
            fish_eat(&(fishes[i]), maxDeltaF);
        }
    }
    
    double end = omp_get_wtime();
    double elapsed_secs = end - start;
    printf("Elapsed time: %f\n", elapsed_secs);

    fish_lake_free(fishLake);
    return 0;
}
