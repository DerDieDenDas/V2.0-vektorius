// Įtraukiamos antraštės failai, kurie turi reikiamas funkcijas ir apibrėžimus
#include "mylib.h"
#include "file_functions.h"

// Globalaus kintamojo "paz_skaicius" deklaracija
extern int paz_skaicius;

// Funkcija, kuri nuskaito studentų informaciją iš failo ir grąžina skaitymo laiką
double failo_nuskaitymas(Vector<Studentas>& grupe, int uzkl_2){
    paz_skaicius = -3;  // Pradinė pažymių vertė
    Studentas temp;  // Laikinas studento objektas
    string eilute, eilute2, readfile, zodis;  // Eilučių ir žodžių kintamieji
    int p;  // Laikinas kintamasis pažymiui

    // Išveda informaciją apie pasiekiamus failus
    cout << "Pasiekiami failai:\n";
    cout << "-----------------------\n";
    system("dir /B *.txt");  // Komanda, kuri parodo esančius txt failus direktorijoje
    cout << "-----------------------\nIveskite failo pavadinima, is kurio norite nuskaityti duomenis: ";
    
    ifstream fd;  // Failo skaitymo srautas
    char buffer[1048576];  // Buferio masyvas (1MB)
    fd.rdbuf()->pubsetbuf(buffer,1048576);  // Pakeičiamas buferio dydis į 1MB

    // Ciklas, kuriame prašoma įvesti failo pavadinimą tol, kol jis bus rastas
    while(1){
        cin >> readfile;  // Įveda failo pavadinimą
        fd.open(readfile);  // Atidaro failą skaitymui
        if(!(fd.good()))  // Jei failo atidaryti nepavyksta, praneša apie klaidą
            cout << "Toks failas nerastas. Bandykite dar karta. \n";
        else
            break;  // Jei failas rastas, baigia ciklą
    }
    
    Timer t;  // Laiko matavimo objektas
    getline(fd,eilute);  // Nuskaito pirmąją eilutę
    stringstream s(eilute);  // Eilutę konvertuoja į srautą
    while(s >> zodis)  // Skaičiuoja žodžius eilutėje
        paz_skaicius++;

    getline(fd,eilute);  // Nuskaito antrąją eilutę

    if(paz_skaicius > 0){  // Tikrina ar yra bent vienas pažymys
        stringstream buf;
        buf << fd.rdbuf();  // Perkelia visą failo turinį į "buf" srautą
        string vardas, pavarde;
        Vector<int> paz;
        int egz;
        float gal_vid = 0, gal_med = 0;

        int n = 0;
        while( getline( buf, eilute ) )  // Skaičiuoja studentų kiekį
            n++;
        grupe.reserve(n);  // Rezervuoja vietą studentams "grupe" vektoriuje
        buf.clear();  // Išvalo srautą
        buf.seekg(0);  // Grąžina rodyklę į pradžią

        // Skaitymas ir informacijos įrašymas
        while(buf >> vardas >> pavarde){
            paz.reserve(paz_skaicius);  // Rezervuoja vietą pažymiams
            for(int i=0;i<paz_skaicius;i++){
                buf >> p;
                paz.push_back(p);  // Įdeda pažymį į vektorių
            }
            buf >> egz;
            switch(uzkl_2){
            case 1:
                gal_vid = vidurkis(paz, egz);  // Skaičiuoja vidurkį
                break;
            case 2:
                gal_med = mediana(paz, egz);  // Skaičiuoja medianą
                break;
            case 3:
                gal_vid = vidurkis(paz, egz);
                gal_med = mediana(paz, egz);  // Skaičiuoja vidurkį ir medianą
                break;
            case 4:
                break;  // Neveikia nieko
            }
            paz.clear();  // Išvalo pažymių vektorių
            grupe.push_back(Studentas(vardas,pavarde,paz,egz,gal_vid,gal_med));  // Prideda studentą į vektorių
        }
    } else {
        cout << "Klaida: duomenu faile nerasta pazymiu.";
        exit(0);  // Išeina iš programos, jei nėra pažymių
    }

    cout << "Skaitymas is failo uztruko: "<< t.elapsed() << "s\n";  // Išveda kiek laiko truko skaitymas
    fd.close();  // Uždaro failą
    return t.elapsed();  // Grąžina kiek laiko truko skaitymas
}

// Funkcija, kuri spausdina studentų informaciją į failą
void spausd_i_faila(Vector<Studentas>& grupe, int uzkl_1, int uzkl_2, string filename){
    ofstream fr (filename);  // Atidaro arba sukuria failą rašymui
    unique_ptr<ostringstream> oss(new ostringstream());  // Sukuria dinaminę atmintį saugančią eilutės srauto rodyklę
    (*oss) <<left<<setw(15)<<"Vardas"<<setw(20)<<"Pavarde";  // Formuoja antraštę

    switch(uzkl_2){  // Spausdina galutinio balo pavadinimą pagal pasirinkimą
        case 1:
            (*oss)<<setw(15)<<"Galutinis (Vid.)\n";
            break;
        case 2:
            (*oss)<<setw(15)<<"Galutinis (Med.)\n";
            break;
        case 3:
            (*oss)<<setw(15)<<"Galutinis (Vid. / Med.)\n";
            break;
        case 4:
            for(int i=1;i<=paz_skaicius;i++)  // Spausdina pažymių pavadinimus
                (*oss)<<"ND"<<setw(4)<<to_string(i);
            (*oss)<<"Egz.\n";  // Spausdina egzamino pavadinimą
            break;
    }

    (*oss)<<"----------------------------------------------------------------------------------------------------------------------\n";  // Brūkšnys skiriantis antraštę nuo informacijos
    fr << oss->str();  // Išveda informaciją į failą
    oss->str("");  // Išvalo srautą

    switch(uzkl_2){  // Spausdina studentų informaciją į srautą pagal pasirinkimą
        // [Panašūs blokai kaip aukščiau]
    }

    fr << oss->str();  // Išveda informaciją į failą
    oss->str("");  // Išvalo srautą
    fr.close();  // Uždaro failą
}
