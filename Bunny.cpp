#include "Bunny.hpp"
    
inline double Bunny::surviveProbability(double crowdedSurvival) const{
    // return 1.0;
    if((state & (size_t) State::Mature)){
        static const double baseMatureYearlyProbability = 0.6;
        static double MatureSurviveProbabilityPerMonth = std::pow(baseMatureYearlyProbability,1.0/12);
        static const int ageDecline = 120;
        if(age < ageDecline)
                return MatureSurviveProbabilityPerMonth * crowdedSurvival;
        return ((age> ageDecline + 60)? 0 : std::pow((ageDecline + 60 - age) ,1.0/12))  * crowdedSurvival; //120 = 10ans, 60 = 5ans restant

    }
    //for kits
    static const double baseBabyYearlyProbability = 0.35;

    static double BabySurviveProbabilityPerMonth = std::pow(baseBabyYearlyProbability,1.0/12);

    return BabySurviveProbabilityPerMonth * crowdedSurvival ;
    
}

bool Bunny::fastForwardEvolution(double crowdedSurvival){
    age ++;
    if(surviveProbability(crowdedSurvival) <= getRandom()){
        state ^= (size_t) State::Alive ;
        return false;
    }
    return true;
}