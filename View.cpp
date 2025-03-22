#include "View.hpp"

std::string View::operator()(){
    return "[B:" + std::to_string(bucks.size())
            + ",\tD:" + std::to_string(does.size())
            + ",\tK:" + std::to_string(kits.size()) + "]";
}
std::string View::operator()(double total){
    return "[B:" + std::to_string(100 * bucks.size()/total)
            + ",\tD:" + std::to_string(100 * does.size()/total)
            + ",\tK:" + std::to_string(100 * kits.size()/total) + "]";
}

std::vector<size_t> View::ViewByAge() {
    std::vector<size_t> ageBuckets;

    // Helper lambda to process entities
    auto processEntities = [&ageBuckets](auto& division) {
        for (const auto& entity : division) {
            if (entity->getAge() >= ageBuckets.size()) {
                ageBuckets.resize(entity->getAge() + 1, 0);
            }
            ageBuckets[entity->getAge()]++;
        }
    };

    // Process all divisions
    processEntities(division<Kit>());
    processEntities(division<Doe>());
    processEntities(division<Bunny>());

    return ageBuckets;
}

void View::IncrementsDeathBucket(size_t ageofDeath){
    if(totalDeathsbyAge.size() <= ageofDeath){
        totalDeathsbyAge.resize(ageofDeath+1, 0);
    }
    totalDeathsbyAge[ageofDeath]++;
}

std::string View::pythonFormatting(const std::string functionName, const std::string input){
    return "\n" + functionName +" = np.array("+input + ")\n";
}
