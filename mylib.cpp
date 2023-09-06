#include "mylib.h"                 // Įtraukiamos bibliotekos iš "mylib.h" failo
#include "file_functions.h"        // Įtraukiamos bibliotekos iš "file_functions.h" failo

extern size_t paz_skaicius;        // Deklaruojamas globalus kintamasis "paz_skaicius", kurio reikšmė yra apibrėžta kitoje kode esančioje vietoje

void skirstymas(int& uzkl_6, int& uzkl_2, int& uzkl_1, Vector<Studentas>& grupe, double& visa_trukme){
    // Funkcija skirta studentų skirstymui į dvi grupes pagal jų pasiekimus

    if(uzkl_6 == 1) {       // Tikrinama, ar reikia skaidyti studentus į du naujus konteinerius
        Vector<Studentas> tinginiai, mokslinciai;   // Sukuriami du nauji konteineriai studentams
        Timer tinginiai_mokslinciai;    // Laiko matavimo objektas
        
        // Jei galutinis įvertinimas yra vidurkis arba vidurkis/mediana
        if(uzkl_2 == 1 || uzkl_2 == 3){ 
            // Studentai skaidomi į dvi grupes pagal jų vidurkį
            auto it = partition(grupe.begin(), grupe.end(), [](Studentas s)
            {
                return s.gal_vid()>5.0;  // Grąžina tiesą, jei studento vidurkis didesnis nei 5
            });
            tinginiai = {it, grupe.end()};         // Priskiriami studentai su vidurkiu mažesniu už 5
            mokslinciai = {grupe.begin(), it};     // Priskiriami studentai su vidurkiu didesniu už 5
        }
        
        // Jei galutinis įvertinimas yra mediana
        if(uzkl_2 == 2){       
            // Studentai skaidomi į dvi grupes pagal jų medianą
            auto it = partition(grupe.begin(), grupe.end(), [](Studentas s)
            {
                return s.gal_med()>5.0;  // Grąžina tiesą, jei studento mediana didesnė nei 5
            });
            tinginiai = {it, grupe.end()};         // Priskiriami studentai su mediana mažesne už 5
            mokslinciai = {grupe.begin(), it};     // Priskiriami studentai su mediana didesne už 5
        }

        // Spausdinama, kiek laiko užtruko studentų skaidymas
        cout << "Studentu rusiavimas i dvi grupes truko: "<< tinginiai_mokslinciai.elapsed() << "s\n";
        visa_trukme += tinginiai_mokslinciai.elapsed();

        // Optimizuojama atminties naudojimas
        tinginiai.shrink_to_fit();
        mokslinciai.shrink_to_fit();

        Timer rusiavimas;  // Laiko matavimo objektas

        // Rūšiuojami studentai abiejuose konteineriuose pagal vardą ir pavardę
        sort(tinginiai.begin(), tinginiai.end());
        sort(mokslinciai.begin(), mokslinciai.end());

        // Spausdinama, kiek laiko užtruko studentų rūšiavimas
        cout << "Studentu rusiavimas didejimo tvarka uztruko: " << rusiavimas.elapsed() << "s\n";
        visa_trukme += rusiavimas.elapsed();

        Timer rus_spausd;  // Laiko matavimo objektas

        // Išvedami studentų duomenys į failus
        spausd_i_faila(tinginiai,uzkl_1,uzkl_2,"output_tinginiai.txt");
        spausd_i_faila(mokslinciai,uzkl_1,uzkl_2,"output_mokslinciai.txt");

        // Spausdinama, kiek laiko užtruko duomenų išvedimas
        cout << "Studentu rusiavimas didejimo tvarka uztruko: " << rus_spausd.elapsed() << "s\n";
        visa_trukme += rus_spausd.elapsed();
    }
}
