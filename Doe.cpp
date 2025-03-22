#include "Doe.hpp"

void Doe::selectLitteringfrequency(){
    double p = getRandom();
    littersPer12months = 0;

    for(; yearlyLitteringPorbability[littersPer12months+1] < p ; littersPer12months++);
    monthsLeft = 12;
}

size_t Doe::countBornKits(){
    return kitsSize;
}

bool Doe::fastForwardEvolution(double crowdedSurvival) {
    if(!Bunny::fastForwardEvolution(crowdedSurvival))
        return false;
    kitsSize = 0;
    if(monthsLeft){

        bool p = getRandom() < (littersPer12months/12.0);
        if(p){
            kitsSize = 3 + 3*getRandom();
        }
        monthsLeft--;
    }

    //reload
    if(!monthsLeft)
        selectLitteringfrequency();

    return true;
}


const std::array<double, 13> Doe::yearlyLitteringPorbability = {
        0.0000110452484993,
        0.000203476008722,
        0.00233886749052, //(2)
        0.0169474267623, //(3)
        0.0786496035251,//(4)
        0.239750061093,
        0.5, //(6)
        0.760249938907,
        0.921350396475,
        0.983052573238, //(9)
        0.997661132509, //(10)
        0.999796523991,
        1.0
};