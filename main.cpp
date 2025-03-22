#include "Doe.hpp"
#include "kit.hpp"
#include <deque>
#include <memory>
#include <map>
#include <vector>
#include <numeric>

#include <csignal>
#include <unistd.h>

#include "View.hpp"
#include "Controller.hpp"

Controller* Experiment;

bool keepRunning = true; // Flag to control the program loop

// Function to handle SIGINT (Ctrl + C)
void handleSIGINT(int sig) {
    std::cout << "Caught signal " << sig << ", saving results..." << std::endl;

    keepRunning = false;  // Set the flag to false to exit the program gracefully
    Experiment->saveResult();
}

template<typename T, typename B>
void mergeVectors(std::vector<T>& baseVector, const std::vector<B>& externalVector){
    if(baseVector.size() < externalVector.size()){
        baseVector.resize(externalVector.size(), 0);
    }
    for(size_t i= 0; i < std::min(baseVector.size(), externalVector.size());i++)
        baseVector[i] += (T) externalVector[i];
}

template<typename T>
std::vector<double> scaleVector(const std::vector<T>& baseVector, double scale){
    std::vector<double> newVector(baseVector.size());
    for(size_t i = 0; i< baseVector.size() ;  i++){
        newVector[i] = static_cast<T>(baseVector[i]) * scale;
    }
    return newVector;
}

int main(){
    // Register the signal handler for SIGINT
    signal(SIGINT, handleSIGINT);
    std::vector<size_t> ageBucket;
    std::vector<double> DeathBucket;
    std::vector<double> DeathBucket2;

    size_t num_Experiences = 1;

    for(size_t i = num_Experiences ; i ; i--){
        std::cout << "\nExperiment " << i << "\n ";
        if(Experiment) 
        {
            delete Experiment;
            Experiment = nullptr;
        }
        Experiment = new Controller(2, 2, 0);
        (*Experiment)(600);
        std::cout<< "finished exp\n";
        mergeVectors(ageBucket, Experiment->simulationView.ViewByAge());
        
        mergeVectors(DeathBucket2, Experiment->simulationView.totalDeathsbyAge);


        auto& tempVec = Experiment->simulationView.totalDeathsbyAge;
        int sum = std::accumulate(tempVec.begin(), tempVec.end(), 0);
        
        mergeVectors(DeathBucket, scaleVector(tempVec, 1.0/sum));
        keepRunning = true;
    }
    if(keepRunning) Experiment->saveResult();

    std::string ageString = View::fancyVectorDisplay(ageBucket);

    DeathBucket = scaleVector(DeathBucket, 1.0/ num_Experiences);
    std::string deathString = View::fancyVectorDisplay(DeathBucket);
    std::cerr << "\nage = np.array("
        << ageString
        << ")\n";

    std::cerr << "\ndeaths = np.array("
        << deathString
        << ")\n";
    
    deathString = View::fancyVectorDisplay(DeathBucket2);
    std::cerr << "\nunnormalized_deaths = np.array("
        << deathString
        << ")\n";

    double sum = std::accumulate(DeathBucket2.begin(), DeathBucket2.end(), 0);
    DeathBucket2 = scaleVector(DeathBucket2, 1.0/sum);

    deathString = View::fancyVectorDisplay(DeathBucket2);
    std::cerr << "\ndeaths2 = np.array("
        << deathString
        << ")\n";
        
    
    if(Experiment) delete Experiment;
}