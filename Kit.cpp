#include "kit.hpp"


bool Kit::fastForwardEvolution(double crowdedSurvival){
    if(!Bunny::fastForwardEvolution(crowdedSurvival))
        return false;
    if(reachedMaturity()){
        state ^= (size_t) State::Mature;
        return false;
    }
    return true;
}
bool Kit::reachedMaturity(){
    return age == programmedMaturity;
}
