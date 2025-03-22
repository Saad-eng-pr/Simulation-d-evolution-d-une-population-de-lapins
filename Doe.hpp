#pragma once

#include "Bunny.hpp"
#include <array>

class Doe: public Bunny{
protected:
    size_t littersPer12months;
    size_t monthsLeft;
    size_t kitsSize;

protected:
    void selectLitteringfrequency();

public:
    Doe(const Bunny& copiedFrom, size_t enforcedflags = 0): Bunny(copiedFrom, enforcedflags),
        littersPer12months(0),monthsLeft(0), kitsSize(0) {}

    Doe(size_t age): Bunny((size_t) State::Mature | (size_t) State::Female ,age), littersPer12months(0),monthsLeft(0), kitsSize(0){
        selectLitteringfrequency();
    }
    size_t countBornKits();
public:
    bool fastForwardEvolution(double crowdedSurvival = 1.0) override;

private:
    static const std::array<double, 13> yearlyLitteringPorbability;
};
