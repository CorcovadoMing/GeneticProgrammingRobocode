#include <iostream>
#include "ParticleSwarmOptimization.h"

int main(int argc, const char * argv[]) {
    ParticleSwarmOptimization pso(100, 10, 0.6, 2.8, 1.3);
    pso.initialize(-100, 100);

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
