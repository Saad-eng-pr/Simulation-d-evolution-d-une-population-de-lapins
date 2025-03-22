#pragma once

#include <deque>
#include <vector>
#include <memory>

#include "kit.hpp"
#include "Doe.hpp"

class View{
private:
    std::deque<std::shared_ptr<Kit>> kits;    
    std::deque<std::shared_ptr<Doe>> does;    
    std::deque<std::shared_ptr<Bunny>> bucks;

    std::vector<size_t> ts_does;
    std::vector<size_t> ts_kits;
    std::vector<size_t> ts_bucks;
public:
    std::vector<size_t> totalDeathsbyAge;
public:
    template<typename T>
    std::vector<size_t>& timeStamp();


    // template<typename T>
    // void genDisplay(std::ostream& stream);
    
    template<typename T>
    std::deque<std::shared_ptr<T>>& division();

    std::vector<size_t> ViewByAge();
    
    template<typename T>
    static std::string fancyVectorDisplay(const std::vector<T>& ageBuckets);

    void IncrementsDeathBucket(size_t ageofDeath);

    static std::string pythonFormatting(const std::string functionName, const std::string input);

public:
    std::string operator()();
    std::string operator()(double total);
};


// Limmitations du cpp (Translation Unit limitation): instancié dans le même ficher que la déclaration du template
template<>
inline std::vector<size_t>& View::timeStamp<Kit>(){ return ts_kits;}
template<>
inline std::vector<size_t>& View::timeStamp<Doe>(){ return ts_does;}
template<>
inline std::vector<size_t>& View::timeStamp<Bunny>(){ return ts_bucks;}


template<>
inline std::deque<std::shared_ptr<Kit>>& View::division<Kit>(){ return kits;}
template<>
inline std::deque<std::shared_ptr<Doe>>& View::division<Doe>(){ return does;}
template<>
inline std::deque<std::shared_ptr<Bunny>>& View::division<Bunny>(){ return bucks;}

template<typename T>
std::string View::fancyVectorDisplay(const std::vector<T>& ageBuckets){
    std::string str;
    str += '[';
    for (size_t i = 0; i < ageBuckets.size(); i++) {
        str += std::to_string(ageBuckets[i]);
        if (i != ageBuckets.size() - 1) {
            str += " ,";
        }
    }
    str += ']';
    return str;
}

