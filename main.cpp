#include "mylib.h"          // Įtraukiama savo sukurtų bibliotekų byla
#include "file_functions.h" // Įtraukiama failų valdymo funkcijų byla

int paz_skaicius;

int main() {
    int uzkl_1, uzkl_2, uzkl_3, uzkl_4, uzkl_5, uzkl_6; // Deklaruojami kintamieji programos veikimo kontrolės reikmėms
    Vector<Studentas> grupe; // Sukuriamas vektorius, skirtas laikyti Studentas tipo objektus
    Studentas temp; // Sukuriamas laikinas Studentas tipo objektas
    double visa_trukme = 0; // Inicializuojamas kintamasis, skirtas matuoti visos programos veikimo trukmę

    // Meniu pasirinkimams
    cout << "Ar norite: \n 1. Įvesti vardus ir pažymius (įveskite '1')\n"
            " 2. Generuoti vardus ir pažymius atsitiktinai (įveskite '2')\n"
            " 3. Skaityti vardus ir pažymius iš failo (įveskite '3')\n";
    int_input_check(uzkl_1, {1, 2, 3}); // Nuskaitomas ir patikrinamas naudotojo pasirinkimas

    cout << "\nAr norite:\n 1. Skaičiuoti vidurkį (įveskite '1')\n"
            " 2. Skaičiuoti medianą (įveskite '2')\n"
            " 3. Skaičiuoti medianą ir vidurkį (įveskite '3')\n"
            " 4. Spausdinti pažymius (įveskite '4')\n";
    int_input_check(uzkl_2, {1, 2, 3, 4}); // Nuskaitomas ir patikrinamas naudotojo pasirinkimas

    if (uzkl_1 == 2) {
        // Jei generuojami pažymiai, klausti, ar juos išvesti į ekraną arba į failą
        cout << "\nAr norite: \n 1. Išvesti pažymius į ekraną (įveskite '1')\n"
                " 2. Išvesti rezultatus į failą (įveskite '2')\n";
        int_input_check(uzkl_3, {1, 2}); // Nuskaitomas ir patikrinamas naudotojo pasirinkimas
    }

    if (uzkl_1 == 3 || uzkl_3 == 2) {
        // Jei skaitomi arba generuojami studentai, klausti, ar juos skirstyti į protingus ir tingius
        cout << "\nAr norite skirstyti studentus į mokslinčius ir tinginius? Įveskite '1', jei taip, '0', jei ne.\n";
        int_input_check(uzkl_5, {1, 0}); // Nuskaitomas ir patikrinamas naudotojo pasirinkimas
    }

    if (uzkl_5 == 1) {
        // Jei skirstomi studentai, klausti, kokią strategiją naudoti
        cout << "\nĮveskite '1', jei norite naudoti 1 strategiją (du nauji konteineriai), arba '2', jei norite naudoti 2 strategiją (vienas naujas konteineris).\n";
        int_input_check(uzkl_6, {1, 2}); // Nuskaitomas ir patikrinamas naudotojo pasirinkimas
    }

    switch (uzkl_1) {
        case 1:
            stud_ivest(grupe, uzkl_2); // Įvedimas: vardai ir pažymiai
            break;
        case 3:
            visa_trukme += failo_nuskaitymas(grupe, uzkl_2); // Skaitomi vardai ir pažymiai iš failo
            break;
        default:
            visa_trukme += stud_gen(grupe, temp, uzkl_2); // Generuojami studentai
            break;
    }

    if (uzkl_1 != 3 && uzkl_3 != 2) {
        // Jei rezultatai nėra rašomi į failą, juos išvesti į ekraną
        isvedimas_i_ekrana(grupe, uzkl_4, uzkl_2, uzkl_1); // Rezultatų išvedimas į ekraną
    } else {
        if (uzkl_5 == 0) {
            // Jei studentai neskirstomi, rezultatus rašyti į failą
            Timer print; // Laiko matavimo pradžia
            if (uzkl_2 == 4) {
                spausd_i_faila(grupe, uzkl_1, uzkl_2, "studentai" + to_string(grupe.size()) + ".txt"); // Spausdinimas į failą
            } else {
                spausd_i_faila(grupe, uzkl_1, uzkl_2, "output.txt"); // Spausdinimas į failą
            }
            cout << "Studentų duomenų spausdinimas į failą užtruko: " << print.elapsed() << "s\n"; // Laiko matavimo pabaiga
            visa_trukme += print.elapsed(); // Atnaujinama bendra veikimo trukmė
        } else {
            // Studentai skirstomi pagal pasirinktą strategiją
            skirstymas(uzkl_6, uzkl_2, uzkl_1, grupe, visa_trukme); // Studentų skirstymas
        }
        cout << "Visas programos darbas truko: " << visa_trukme << "s\n"; // Visos programos veikimo trukmė
    }

    system("pause"); // Laukimas, kol naudotojas spaus paspaus ENTER
    // return 0; // Programos pabaiga, grąžinamas nulinis kodas
}
