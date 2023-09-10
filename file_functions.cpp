#include "mylib.h"
#include "file_functions.h"

extern int paz_skaicius;

double failo_nuskaitymas(Vector<Studentas>& grupe, int uzkl_2){
    paz_skaicius = -3;
    Studentas temp;
    string readfile;
    cout << "Pasiekiami failai:\n-----------------------\n";
    system("dir /B *.txt");
    cout << "-----------------------\nIveskite failo pavadinima, is kurio norite nuskaityti duomenis: ";
    
    ifstream fd;
    char buffer[1048576];
    fd.rdbuf()->pubsetbuf(buffer, sizeof(buffer));

    while(true){
        cin >> readfile;
        fd.open(readfile);
        if(fd.is_open())
            break;
        else
            cout << "Toks failas nerastas. Bandykite dar karta. \n";
    }

    Timer t;
    string eilute;
    getline(fd,eilute);
    paz_skaicius = count(eilute.begin(), eilute.end(), ' ') + 1;

    stringstream buf;
    buf << fd.rdbuf();
    Vector<int> paz;
    int egz;
    float gal_vid = 0, gal_med = 0;

    while(buf >> temp.vardas >> temp.pavarde){
        for(int i = 0; i < paz_skaicius; i++){
            buf >> egz; // pakeista, nes egzaminas yra paskutinis įrašas
            paz.push_back(egz);
        }
        buf >> egz;
        if(uzkl_2 == 1 || uzkl_2 == 3) gal_vid = vidurkis(paz, egz);
        if(uzkl_2 == 2 || uzkl_2 == 3) gal_med = mediana(paz, egz);

        grupe.push_back(Studentas(temp.vardas, temp.pavarde, paz, egz, gal_vid, gal_med));
        paz.clear();
    }

    cout << "Skaitymas is failo uztruko: "<< t.elapsed() << "s\n";
    return t.elapsed();
}

void spausd_i_faila(Vector<Studentas>& grupe, int uzkl_1, int uzkl_2, string filename){
    ofstream fr (filename);
    ostringstream oss;

    oss <<left << setw(15) << "Vardas" << setw(20) << "Pavarde";
    switch(uzkl_2){
        case 1: oss << setw(15) << "Galutinis (Vid.)\n"; break;
        case 2: oss << setw(15) << "Galutinis (Med.)\n"; break;
        case 3: oss << setw(15) << "Galutinis (Vid. / Med.)\n"; break;
        case 4: 
            for(int i=1; i <= paz_skaicius; i++)
                oss << "ND" << setw(4) << i;
            oss << "Egz.\n";
            break;
    }
    oss << "----------------------------------------------------------------------------------------------------------------------\n";

    for(const auto &student: grupe){
        oss << setw(15) << student.vardas() << setw(20) << student.pavarde();

        switch(uzkl_2){
            case 1: oss << setw(3) << fixed << setprecision(2) << student.gal_vid() << "       \n"; break;
            case 2: oss << setw(3) << fixed << setprecision(2) << student.gal_med() << "       \n"; break;
            case 3: oss << setw(3) << fixed << setprecision(2) << student.gal_vid() << " / " << student.gal_med() << "\n"; break;
            case 4: 
                for (const auto &pazymys: student.paz()) 
                    oss << setw(5) << pazymys << " ";
                oss << setw(5) << student.egz() << "\n";
                break;
        }
    }

    fr << oss.str();
}
