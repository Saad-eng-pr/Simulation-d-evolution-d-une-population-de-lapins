#pragma once

#include "View.hpp"

class Controller{
public:
    View simulationView;
    size_t sDuration; // simulation duration
public:
    Controller(size_t malesCount, size_t femalesCount, size_t babiesCount);
private:
    void tick();
public:
    // void saveResult();
    void saveResult();
    void operator()(size_t sDuration, bool SingleExperiment = false);
};
