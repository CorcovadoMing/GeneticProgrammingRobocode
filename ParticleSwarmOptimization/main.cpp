#include <iostream>
#include "ParticleSwarmOptimization.h"

int main(int argc, const char * argv[]) {

    // TODO:
    // Get all "constant" node in robot and fit in particles

    ParticleSwarmOptimization pso(100, 10, 0.6, 2.8, 1.3);  // particle_number, dimension, w, c1, c2
    pso.initialize(-100, 100);  // min, max allow in values

    int times = 1;
    while (times--) {
        pso.evaluate();
        pso.updatePBest();
        pso.updateGBest();
        pso.updateVelocity();
        pso.updatePosition();
        pso.print();
    }
    return 0;
}
