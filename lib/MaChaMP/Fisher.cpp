
#include "TwoSampleTests.cpp"
#include "Vector_arithmetics.cpp"
#include <boost/math/distributions/chi_squared.hpp> //Difficult for windows
#include <limits>


// store mean and std of a vector
struct MeanStd{
    double m; //Mean
    double s; // VARIANCE!!!!11
};
// store cp index and p-value
struct Changepoint{
    unsigned i; //index in sequence
    long double p; //p-value
};

// store cp index and p-value
struct MC{
    std::vector<Changepoint> Change; //A vector of single changes are multiple changes
    long double p; //the combined p-value
};


long double Fisher(std::vector<Changepoint> &Changes);
long double Chisq(long double logp);
long double LogComb(std::vector<Changepoint> &Changes);

long double LogComb(std::vector<Changepoint> &Changes){
    long double stat = 0.0;
    for(auto const& change: Changes) {
        stat += std::log(change.p);
    }
    stat *= -2;

    return stat;

}


long double Chisq(long double logp,int dof){
    boost::math::chi_squared dist(dof);
    return  boost::math::cdf(boost::math::complement(dist, std::abs(logp)));
}

//Combine p-values of multiple tests under fishers method
long double Fisher(std::vector<Changepoint> &Changes){
    long double stat = LogComb(Changes);
    int k = 2*static_cast<int>(Changes.size());
    long double q = Chisq(stat, k);


    return q;
}

