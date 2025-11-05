#include "../includes/extract.hpp"
#include "../includes/all.hpp"
#include "./stats.cpp"

// on enleve la moyenne des signaux 

vector<double> detrend(vector<double> sig, int length) {
    Stats stat;
    stat = stats(sig, length);
    vector<double> sig_detrend;
    for (const auto& s : sig) {
        sig_detrend.push_back(s-stat.mean);
    }
    return sig_detrend;
}

    


