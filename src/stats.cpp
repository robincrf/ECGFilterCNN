#include "../includes/extract.hpp"
#include "../includes/all.hpp"


Stats stats(vector<double> sig, int length) 
{
    // moyenne
    double mean = 0;
    for (const auto& s : sig) {
        mean += s;
    }
    mean = mean / length;

    // écart-type
    double sd = 0;
    for (const auto& s : sig) {
        sd += (s-mean)*(s-mean);

    }
    sd = sqrt( sd / (length-1)) ;

    return {mean, sd};
};