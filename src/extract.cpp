#include "../includes/extract.hpp"

using namespace std;



ECGmetadata::ECGmetadata(int f, int l, bool c, string lab, vector<double> sig) 
    : frequency(f), length(l), centered(c), label(lab), signal(sig)
{
}


ECGmetadata::~ECGmetadata()
{

}




std::vector<ECGmetadata> allECG;



void extract_metadata(const std::string& filepath)
{
    string line;
    ifstream file(filepath, ios::in);
    if (!file.is_open()) {
        cerr << "error lors de l'ouverture du fichier";
        return ;
    }
    else {
        int f;
        int len;
        string c; // centré sur R ou non 
        string lab; // normal ou non
        vector<double> sig; 
        bool is_centered;


        getline(file, line, '=');
        getline(file, line, ',');
        f = std::stoi(line); // récupere la fréquence d'échantillonnage
        getline(file, line, '=');
        getline(file, line, ',');
        c = line;
        getline(file, line, '=');
        getline(file, line, ',');
        len = std::stoi(line); // récupere la longueur du signal
        getline(file, line, '=');
        getline(file, line, '\n');

        // donner les valeurs au fichier de visualisation
        ofstream file_sig("../data/only_data.csv", ios::trunc);
        lab = line; // récupere le label
        while (std::getline(file, line, ',')) {  // s'arrête quand plus rien à lire
            if (!line.empty()) {
                sig.push_back(std::stod(line));
                file_sig << line << '\n';
            }
            if (sig.size() == len) break; // stoppe après 256 valeurs
        }
        if (c != "R") {
            is_centered = false;
        }
        else {
            is_centered = true;
        }

        
        ECGmetadata ecg(f, len, is_centered, lab, sig);
        allECG.push_back(ecg);
        file.close();
    }
} 


void display_all_ECG()
{
    for (const auto& ecg : allECG) {
       ecg.print();
    }
}

int main()
{
    extract_metadata("../data/ecg.csv");
    display_all_ECG();
    return 0;
}

