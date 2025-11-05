#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "./all.hpp"

using namespace std;

class ECGmetadata
{
private:
    int frequency;
    int length;
    bool centered; // centré sur R ou non 
    string label; // normal ou non
    vector<double> signal; // acceuil les 256 valeurs du signal

public:
    ECGmetadata(int f, int l, bool c, string lab, vector<double> sig);
    ~ECGmetadata();
    Stats stats(vector<double> sig, int length);
    vector<double> Zscore(vector<double> sig, int length);

    void print() const
    {
        cout << "Frequency : " << frequency << "\n"
             << "length : " << length << "\n"
             << "centered : " << (centered ? "true" : "false") << "\n"
             << "label : " << label << "\n"
             << "signal : " << endl; 
             for (const auto& s : signal) {
                cout << s << "," << endl;

             };
    }
};