#ifndef __ParticleSwarmOptimization__Particle__
#define __ParticleSwarmOptimization__Particle__

#include <vector>

class Particle {
public:
    Particle(const int);
    void randomize(const double, const double);
    double at(const size_t index) const { return particle_[index]; }
    double getHistoryFitness() const { return history_fitness_; }
    std::vector<double> getPBest() const { return history_; }
    void fitness(const double fitness) { fitness_ = fitness; }
    void updatePBest();
    void updateVelocity(const double, const double, const double, const std::vector<double> &);
    void updatePosition();
    void print() const;
private:
    std::vector<double> particle_, velocity_, history_;
    double fitness_, history_fitness_ = INTMAX_MAX;
};

#endif /* defined(__ParticleSwarmOptimization__Particle__) */
