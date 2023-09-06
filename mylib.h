#ifndef MYLIB_H_INCLUDED                  // Saugiklis, kuris užtikrina, kad šis antraštės failas bus įtrauktas tik kartą.
#define MYLIB_H_INCLUDED                  // Apibrėžiamas saugiklis.

#include <iostream>                       // Įtraukiamos C++ standartinės bibliotekos: įvedimui, išvedimui...
// Įtraukiamos reikiamos bibliotekos
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
//#include <Vector>  // pasirenkama naudoti savo rašytą Vector klasę ne standartinę
#include "myVector.h"
#include <random>
#include <ctime>
#include <numeric>
#include <chrono>
#include <regex>
#include <fstream>
#include <sstream>
#include <tuple>
#include <utility>

using std::cout;          // Nustatomi vardų pravardžiai, kad būtų paprasčiau naudotis bibliotekomis
using std::cin;
using std::endl;
using std::left;
using std::right;
using std::fixed;
using std::setw;
using std::setprecision;
using std::string;
//using std::Vector;  // Ši eilutė yra užkomentuota, nes, kaip minėta aukščiau, buvo pasirinkta naudoti savo Vector klasę
using std::numeric_limits;
using std::to_string;
using std::sort;
using std::accumulate;
using std::getline;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::unique_ptr;
using std::ostringstream;
using std::istringstream;
using std::partition;
using std::tie;
using std::move;

#include "Studentas.h"  // Įtraukiama sukurta Studentas klasė

// Ši funkcija rodo tam tikrų Vector tipo konteinerių statistiką
template <class T>
void statistika (Vector <T> &temp){
    cout<<" Vector size: "<<temp.size()<<" Vector capacity: "<<temp.capacity()<<"\n";
}

// Timer klasė skirta matuoti vykdymo laiką
class Timer {
    private:
       std::chrono::time_point<std::chrono::high_resolution_clock> start;  // Pradžios laiko taškas
    public:
        Timer() : start{std::chrono::high_resolution_clock::now()} {}  // Konstruktorius inicijuoja pradžios laiką
        void reset() {
            start = std::chrono::high_resolution_clock::now();  // Funkcija nustato naują pradžios laiką
        }
        double elapsed() const {
            return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();  // Grąžina praeitusį laiką nuo pradžios iki šio momento
        }
};

// Prototipai funkcijoms, kurios bus aprašytos kituose šaltinio failuose
bool tik_raides(string name);
void int_input_check(int& input, Vector<int> correct);
void skirstymas(int& uzkl_6, int& uzkl_2, int& uzkl_1, Vector<Studentas>& grupe, double& visa_trukme);
void stud_ivest(Vector<Studentas> &grupe, int uzkl_2);
void isvedimas_i_ekrana(Vector<Studentas> &grupe,int& uzkl_4,int& uzkl_2,int& uzkl_1);
void pild(Vector<Studentas> &grupe, int uzkl_2);
void spausd(const Studentas &temp, int uzkl_2, int uzkl_1);
double stud_gen(Vector<Studentas> &grupe, Studentas &temp, int uzkl_2);
void gen_paz(int kelintas, int uzkl_2, Studentas &temp);
float mediana(Vector<int> paz, int egz);
float vidurkis(Vector<int> paz, int egz);

#endif // MYLIB_H_INCLUDED
