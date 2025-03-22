#include "Controller.hpp"

extern bool keepRunning;

Controller::Controller(size_t malesCount, size_t femalesCount, size_t babiesCount){
    simulationView = View();

    size_t commonFlag = (size_t) Bunny::State::Mature;
    for(size_t it = malesCount; it; it--)
        simulationView.division<Bunny>().emplace_back(std::make_shared<Bunny>(commonFlag, 7));

    for(size_t it = femalesCount; it; it--)
        simulationView.division<Doe>().emplace_back(std::make_shared<Doe>(7));

    for(size_t it = babiesCount; it; it--)
        simulationView.division<Kit>().emplace_back(std::make_shared<Kit>());
}

void Controller::tick(){
    size_t grandTotal = simulationView.division<Bunny>().size() + 
        simulationView.division<Doe>().size() + simulationView.division<Kit>().size();

    double crowdedSurvival = (grandTotal && grandTotal <= 2* 1e4 )?  (grandTotal/((double) 2* 1e4)) : 0;

    crowdedSurvival = std::pow(1.0 - std::pow(crowdedSurvival,0.9),1/0.9);

    size_t new_borns = 0;
    // updates females
    {
        
        // double crowdedSurvival = (grandTotal)? 
        //     static_cast<double>(simulationView.division<Doe>().size())/grandTotal : 0;

        // crowdedSurvival = 1.0;
                //std::pow(1.0 - std::pow(crowdedSurvival,1.4),1/1.4);

        for(size_t count = simulationView.division<Doe>().size() ; count ; count--){
            auto current_entity = simulationView.division<Doe>().front();
            simulationView.division<Doe>().pop_front();

            if(current_entity->fastForwardEvolution(crowdedSurvival)) // still alive ?
            {
                if(simulationView.division<Bunny>().size()) new_borns += current_entity->countBornKits(); // au moins un Benny Exists !
                simulationView.division<Doe>().emplace_back(current_entity);
            }
            else simulationView.IncrementsDeathBucket(current_entity->getAge());
        }
    }

    // updates males
    {
        // double crowdedSurvival = (grandTotal)? 
        //     static_cast<double>(simulationView.division<Bunny>().size())/grandTotal : 0;

        // crowdedSurvival = 1.0;
                //std::pow(1.0 - std::pow(crowdedSurvival,1.4),1/1.4);

        for(size_t count = simulationView.division<Bunny>().size() ; count ; count--){
            auto current_entity = simulationView.division<Bunny>().front();
            simulationView.division<Bunny>().pop_front();
            if(current_entity->fastForwardEvolution(crowdedSurvival)) // still alive ?
            {
                simulationView.division<Bunny>().emplace_back(current_entity);
            }
            else simulationView.IncrementsDeathBucket(current_entity->getAge());
        }
    }


    // updates babies, and remove/re-instance when matured.
    {
    //     double crowdedSurvival = (grandTotal)? 
    //         static_cast<double>(simulationView.division<Kit>().size())/grandTotal : 0;

    //     crowdedSurvival = 
    //             std::pow(1.0 - std::pow(crowdedSurvival,1.8),1/1.8);

        // crowdedSurvival = std::pow(1.0 - (crowdedSurvival),0.5);

        for(size_t count = simulationView.division<Kit>().size() ; count ; count--){
            auto current_entity = simulationView.division<Kit>().front();
            simulationView.division<Kit>().pop_front();
            if(current_entity->fastForwardEvolution(crowdedSurvival)) // still alive ?
            {
                simulationView.division<Kit>().emplace_back(current_entity);
            }
            else if(current_entity->reachedMaturity()){
                if(current_entity->state & (size_t) Bunny::State::Female){ //it's a female
                    simulationView.division<Doe>().emplace_back(std::make_shared<Doe>(current_entity->getAge()));
                }
                else
                    simulationView.division<Bunny>().emplace_back(std::make_shared<Bunny>(current_entity->getAge()));
            }
            else simulationView.IncrementsDeathBucket(current_entity->getAge());
        }

    }

    // add new bornes to the bascket
    for( ; new_borns ; new_borns--){
        simulationView.division<Kit>().emplace_back(std::make_shared<Kit>());
    }


}

void Controller::saveResult(){
    std::string fancyVector;
    std::cerr << "import numpy as np # type: ignore\n";
    fancyVector = View::fancyVectorDisplay(simulationView.timeStamp<Bunny>());

    std::cerr << View::pythonFormatting("bunnies", View::fancyVectorDisplay(simulationView.timeStamp<Bunny>()));
    std::cerr << View::pythonFormatting("does", View::fancyVectorDisplay(simulationView.timeStamp<Doe>()));
    std::cerr << View::pythonFormatting("kits", View::fancyVectorDisplay(simulationView.timeStamp<Kit>()));
}

void Controller::operator()(size_t sDuration, bool SingleExperiment){

    if(SingleExperiment){
        std::cout << "starting simulation\n";
        std::cout << " - - - - - - - - - - - - \n";
        std::cout << "total duration : " << sDuration << "\n";
        std::cout << "initial composition: " << simulationView() << "\n";
    }
    for(size_t i = 0; i< sDuration && keepRunning; i++){ //
        tick();
        if(SingleExperiment){
            std::cout << i << ":composition: " << simulationView() << "\n";
            double grandTotal = simulationView.division<Bunny>().size() + simulationView.division<Doe>().size() + simulationView.division<Kit>().size();
            std::cout << i << ":composition: " << simulationView(grandTotal) << "\n";
        }
        simulationView.timeStamp<Kit>().push_back(simulationView.division<Kit>().size());
        simulationView.timeStamp<Doe>().push_back(simulationView.division<Doe>().size());
        simulationView.timeStamp<Bunny>().push_back(simulationView.division<Bunny>().size());
        
    }
    std::cout << "\n- - - - - - - - - - - - \n";
}
