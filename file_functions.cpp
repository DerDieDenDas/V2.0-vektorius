#include "mylib.h"

extern int paz_skaicius;

double failo_nuskaitymas(Vector<Studentas>& grupe, int uzkl_2) {
    paz_skaicius = -3;
    Studentas temp;
    string eilute, eilute2, readfile, zodis;
    int p;

    cout << "Pasiekiami failai:\n";
    cout << "-----------------------\n";
    system("dir /B *.txt");
    cout << "-----------------------\nIveskite failo pavadinima, is kurio norite nuskaityti duomenis: ";
    
    ifstream fd;
    char buffer[1048576];
    fd.rdbuf()->pubsetbuf(buffer, 1048576); // Pakeiciamas buferio dydis is 512B i 1MB
    
    while (1) {
        cin >> readfile;
        fd.open(readfile);
        if (!fd.good())
            cout << "Toks failas nerastas. Bandykite dar karta. \n";
        else
            break;
    }

    Timer t;
    getline(fd, eilute);
    stringstream s(eilute);

    while (s >> zodis)
        paz_skaicius++;

    getline(fd, eilute);
    
    if (paz_skaicius > 0) {
        stringstream buf;
        buf << fd.rdbuf();
        string vardas, pavarde;
        Vector<int> paz;
        int egz;
        float gal_vid = 0, gal_med = 0;

        int n = 0;
        while (getline(buf, eilute)) /// skaiciuojamas studentu skaicius
            n++;

        grupe.reserve(n);
        buf.clear();
        buf.seekg(0);

        while (buf >> vardas >> pavarde) {
            paz.reserve(paz_skaicius);
            for (int i = 0; i < paz_skaicius; i++) {
                buf >> p;
                paz.push_back(p);
            }
            buf >> egz;
            
            switch (uzkl_2) {
                case 1:
                    gal_vid = vidurkis(paz, egz);
                    break;
                case 2:
                    gal_med = mediana(paz, egz);
                    break;
                case 3:
                    gal_vid = vidurkis(paz, egz);
                    gal_med = mediana(paz, egz);
                    break;
                case 4:
                    break;
            }
            
            paz.clear();
            grupe.push_back(Studentas(vardas, pavarde, paz, egz, gal_vid, gal_med));
        }
    } else {
        cout << "Klaida: duomenu faile nerasta pazymiu.";
        exit(0);
    }
    
    cout << "Skaitymas is failo uztruko: " << t.elapsed() << "s\n";
    fd.close();
    
    return t.elapsed();
}

void spausd_i_faila(Vector<Studentas>& grupe, int uzkl_1, int uzkl_2, string filename) {
    ofstream fr(filename);
    unique_ptr<ostringstream> oss(new ostringstream());
    (*oss) << left << setw(15) << "Vardas" << setw(20) << "Pavarde";

    switch (uzkl_2) {
        case 1:
            (*oss) << setw(15) << "Galutinis (Vid.)\n";
            break;
        case 2:
            (*oss) << setw(15) << "Galutinis (Med.)\n";
            break;
        case 3:
            (*oss) << setw(15) << "Galutinis (Vid. / Med.)\n";
            break;
        case 4:
            for (int i = 1; i <= paz_skaicius; i++)
                (*oss) << "ND" << setw(4) << to_string(i);
            (*oss) << "Egz.\n";
            break;
    }

    (*oss) << "----------------------------------------------------------------------------------------------------------------------\n";
    fr << oss->str();
    oss->str(""); // oss reset

    switch (uzkl_2) {
        case 1:
            for (auto &i : grupe)
                (*oss) << setw(15) << i.vardas() << setw(20) << i.pavarde() << setw(3) << fixed << setprecision(2) << i.gal_vid() << "       \n";
            break;
        case 2:
            for (auto &i : grupe)
                (*oss) << setw(15) << i.vardas() << setw(20) << i.pavarde() << setw(3) << fixed << setprecision(2) << i.gal_med() << "       \n";
            break;
        case 3:
            for (auto &i : grupe)
                (*oss) << setw(15) << i.vardas() << setw(20) << i.pavarde() << setw(3) << fixed << setprecision(2) << i.gal_vid() << " / " << i.gal_med() << "\n";
            break;
        case 4:
            for (auto &i : grupe) {
                (*oss) << setw(15) << i.vardas() << setw(20) << i.pavarde();
                for (auto &j : i.paz())
                    (*oss) << setw(5) << j << " ";
                (*oss) << setw(5) << i.egz() << "\n";
            }
            break;
    }

    fr << oss->str();
    oss->str("");
    fr.close();
}
