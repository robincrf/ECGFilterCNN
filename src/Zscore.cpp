#include "../includes/extract.hpp"
#include "../includes/all.hpp"
#include "./stats.cpp"




vector<double> ECGmetadata::Zscore(vector<double> sig, int length) 
{   
    Stats stat;
    stat = stats(sig, length);
    double Zscore = 0;
    vector<double> Zsig; // sig align with Zscore
    for (const auto& s : sig) 
    {
        Zscore = (s-stat.mean) / stat.sd;

    }
};