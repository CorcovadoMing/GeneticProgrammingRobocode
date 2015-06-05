#ifndef __ParticleSwarmOptimization__ParticleSwarmOptimization__
#define __ParticleSwarmOptimization__ParticleSwarmOptimization__

#include <vector>
#include "Particle.h"

class ParticleSwarmOptimization {
public:
    ParticleSwarmOptimization(const int, const int, const double w, const double c1, const double c2);
    void initialize(const double, const double);
    void evaluate();
    void updatePBest();
    void updateGBest();
    void updateVelocity();
    void updatePosition();
    void print() const;

private:
    const double fitness_(const Particle &) const;

    const int particle_num_, dimension_;
    const double w_, c1_, c2_;
    std::vector<Particle> particles_;
    std::vector<double> global_best_;
    double global_best_fitness_;
};
#endif /* defined(__ParticleSwarmOptimization__ParticleSwarmOptimization__) */
