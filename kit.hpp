#pragma once

#include "Bunny.hpp"
#include <random>

class Kit: public Bunny{
private:
    size_t programmedMaturity;
public:
    Kit(): Bunny((getRandom()<0.5), 0){
        programmedMaturity = 5 + 4*getRandom();
    }
    bool fastForwardEvolution(double crowdedSurvival = 1.0) override;
    bool reachedMaturity();
};
