#pragma once

#include <iostream>
#include <random>

class Bunny{

protected:
    size_t age; // months
public:
    size_t state;
public:
    enum class State{
        Female  = 0b001,
        Mature  = 0b010,
        Alive   = 0b100
    };


public:
    size_t getAge(){ return age;}
    Bunny(size_t entryFlags, size_t age = 0): age(age), state(entryFlags | (size_t) State::Alive ){}
    Bunny(const Bunny& copiedFrom, size_t enforcedflags = 0): age(copiedFrom.age), state(copiedFrom.state ^ enforcedflags){}

protected:
    inline double getRandom() const;
    inline double surviveProbability(double crowdedSurvival = 1.0) const;
    
public:
    virtual bool fastForwardEvolution(double crowdedSurvival = 1.0);

};


//inline linkage limitation.
inline double Bunny::getRandom() const{
    static std::mt19937 myGenerator((1<<11) -1 );
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(myGenerator);
}