#ifndef __SWARM_UTILS__
#define __SWARM_UTILS__
#include "FunctionalUtilities.h"
#include <cstdlib>
namespace swarm_utils{
    auto getUniform(){
        return (double)rand()/RAND_MAX;
    }
    template<typename T, typename U>
    auto getTruncatedParameter(const T& lower, const T& upper, const U& result){
        return result>upper?upper:(result<lower?lower:result);
    }
    template<typename T, typename U>
    auto getRandomParameter(const T& lower, const T& upper, const U& rand){
        return lower+rand*(upper-lower);
    }
    template<typename Array>
    auto getRandomParameters(const Array& ul){
        return futilities::for_each(0, (int)ul.size(), [&](const auto& index){
            return getRandomParameter(ul[index].lower, ul[index].upper, getUniform());
        });
    }

    template<typename T,  typename U>
    auto getLevy(const T& alpha, const U& rand){
        return pow(rand, -1.0/alpha);
    }

    template<typename T, typename U>
    auto getLevyFlight(const T& currVal, const T& stepSize, const T& lambda, U&& rand, U&& normRand){
        return currVal+stepSize*getLevy(lambda, rand)*normRand;
    }
    template<typename Array, typename ObjFn>
    auto getNewParameterAndFn(const Array& ul, const ObjFn& objFn){
        auto parameters=swarm_utils::getRandomParameters(ul);
        return std::pair<std::vector<double>, double>(parameters, objFn(parameters));
    }
    constexpr int optparms=0;
    constexpr int fnval=1;
    template<typename T>
    struct upper_lower{
        T upper;
        T lower;
        upper_lower(T&& lower_, T&& upper_){
            upper=upper_;
            lower=lower_;
        }
    };

}


#endif