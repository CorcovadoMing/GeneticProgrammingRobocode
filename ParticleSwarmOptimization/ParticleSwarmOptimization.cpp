#include "ParticleSwarmOptimization.h"
#include "Particle.h"
#include <cmath>
#include <iostream>

ParticleSwarmOptimization::ParticleSwarmOptimization(const int particle_num, const int dimension, const double w, const double c1, const double c2):particle_num_(particle_num), dimension_(dimension), w_(w), c1_(c1), c2_(c2) {
    particles_ = std::vector<Particle>(particle_num_, Particle(dimension_));
}

void ParticleSwarmOptimization::initialize(const double min, const double max) {
    for (size_t i = 0; i < particle_num_; i += 1) {
        particles_[i].randomize(min, max);
    }
}

const double ParticleSwarmOptimization::fitness_(const Particle &particle) const {
    double fitness = 0;
    return fitness;
}

void ParticleSwarmOptimization::evaluate() {
    for (size_t i = 0; i < particles_.size(); i += 1) {
        double fitness = fitness_(particles_[i]);
        particles_[i].fitness(fitness);
    }
}

void ParticleSwarmOptimization::updatePBest() {
    for (size_t i = 0; i < particles_.size(); i += 1) {
        particles_[i].updatePBest();
    }
}


void ParticleSwarmOptimization::updateGBest() {
    double min = INT32_MAX;
    size_t min_index = -1;
    for (size_t i = 0; i < particles_.size(); i += 1) {
        if (particles_[i].getHistoryFitness() < min) {
            min = particles_[i].getHistoryFitness();
            min_index = i;
        }
    }
    global_best_ = particles_[min_index].getPBest();
    global_best_fitness_ = min;
}


void ParticleSwarmOptimization::updateVelocity() {
    for (size_t i = 0; i < particles_.size(); i += 1) {
        particles_[i].updateVelocity(w_, c1_, c2_, global_best_);
    }
}


void ParticleSwarmOptimization::updatePosition() {
    for (size_t i = 0; i < particles_.size(); i += 1) {
        particles_[i].updatePosition();
    }
}

void ParticleSwarmOptimization::print() const {
    std::cout << global_best_fitness_ << std::endl;
}
