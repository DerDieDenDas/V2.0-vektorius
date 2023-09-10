#include "mylib.h"                       // Įtraukiamos bibliotekos, kurios yra reikalingos kode.
#include "file_functions.h"

const std::string STUDENTS_FILE_PREFIX = "studentai";  // Konstantos su studentų failo prefiksu.
const std::string OUTPUT_FILE = "output.txt";          // Konstantos su išvesties failo pavadinimu.

// Funkcija skirta užklausoms gauti iš vartotojo.
void selectInput(Vector<Studentas>& grupe, int& uzkl_1, int& uzkl_2, int& uzkl_3, int& uzkl_5, int& uzkl_6) {
    // Pirmoji užklausa: kaip gauti duomenis.
    cout << "Ar norite: \n 1. Ivesti vardus ir pazymius (iveskite '1')\n 2. Generuoti vardus ir pazymius atsitiktinai (iveskite '2')\n 3. Skaityti vardus ir pazymius is failo (iveskite '3')\n";
    int_input_check(uzkl_1, {1, 2, 3});  // Tikrina ar vartotojo įvestis yra viena iš galimų reikšmių.

    // Antroji užklausa: kokį veiksmą atlikti su gautais duomenimis.
    cout << "\nAr norite:\n 1. Skaiciuoti vidurki (iveskite '1')\n 2. Skaiciuoti mediana (iveskite '2')\n 3. Skaiciuoti mediana ir vidurki (iveskite '3')\n 4. Spausdinti pazymius (iveskite '4')\n";
    int_input_check(uzkl_2, {1, 2, 3, 4});

    // Trečioji užklausa: kur rodyti rezultatus, jei buvo pasirinkta generuoti duomenis.
    if (uzkl_1 == 2) {
        cout << "\nAr norite: \n 1. Isvesti pazymius i ekrana (iveskite '1')\n 2. Isvesti rezultata i faila (iveskite '2')\n";
        int_input_check(uzkl_3, {1, 2});
    }

    // Ketvirtoji užklausa: ar norima skirstyti studentus pagal jų pasiekimus.
    if (uzkl_1 == 3 || uzkl_3 == 2) {
        cout << "\nAr norite skirstyti studentus i mokslincius ir tinginius? Iveskite '1', jei taip, '0', jei ne.\n";
        int_input_check(uzkl_5, {1, 0});
    }

    // Penktoji užklausa: kurią strategiją naudoti studentų skirstymui.
    if (uzkl_5 == 1) {
        cout << "\nIveskite '1', jei norite naudoti 1 strategija (du nauji konteineriai) arba '2', jei norite naudoti 2 strategija (vienas naujas konteineris).\n";
        int_input_check(uzkl_6, {1, 2});
    }
}

// Pagrindinė programa.
int main() {
    Vector<Studentas> grupe;  // Vektorius, kuriame saugomi studentai.
    Studentas temp;           // Laikinas studentas naudojamas generavimui.
    double visa_trukme = 0;  // Kintamasis saugantis programos vykdymo trukmę.

    // Užklausų kintamieji.
    std::array<int, 6> uzklusos;
    uzklusos.fill(-1);  // Pradinis užklausų kintamųjų užpildymas -1 reikšme.
    int& uzkl_1 = uzklusos[0];
    int& uzkl_2 = uzklusos[1];
    int& uzkl_3 = uzklusos[2];
    int& uzkl_4 = uzklusos[3];
    int& uzkl_5 = uzklusos[4];
    int& uzkl_6 = uzklusos[5];

    selectInput(grupe, uzkl_1, uzkl_2, uzkl_3, uzkl_5, uzkl_6);  // Užklausų funkcijos iškvietimas.

    // Pagal pirmosios užklausos rezultatą nustatoma, kaip gauti duomenis.
    switch (uzkl_1) {
        case 1:
            stud_ivest(grupe, uzkl_2);  // Duomenų įvedimas ranka.
            break;
        case 3:
            visa_trukme += failo_nuskaitymas(grupe, uzkl_2);  // Duomenų skaitymas iš failo.
            break;
        default:
            visa_trukme += stud_gen(grupe, temp, uzkl_2);  // Duomenų generavimas.
            break;
    }

    // Rezultatų išvedimas.
    if (uzkl_1 != 3 && uzkl_3 != 2)  // Jei rezultatai turėtų būti rodomi ekrane.
        isvedimas_i_ekrana(grupe, uzkl_4, uzkl_2, uzkl_1);
    else {  // Jei rezultatai turėtų būti išsaugoti faile.
        if (uzkl_5 == 0) {
            Timer print;  // Laikmatis, matuojantis išvedimo į failą trukmę.
            spausd_i_faila(grupe, uzkl_1, uzkl_2, (uzkl_2 == 4) ? STUDENTS_FILE_PREFIX + std::to_string(grupe.size()) + ".txt" : OUTPUT_FILE);  // Išvedimas į failą.
            cout << "Studentu duomenu spausdinimas i faila uztruko: " << print.elapsed() << "s\n";
            visa_trukme += print.elapsed();  // Pridedama išvedimo trukmė prie bendros programos trukmės.
        } else {
            skirstymas(uzkl_6, uzkl_2, uzkl_1, grupe, visa_trukme);  // Studentų skirstymo funkcija.
        }
        cout << "Visas programos darbas truko: " << visa_trukme << "s\n";  // Bendros programos trukmės išvedimas.
    }

    system("pause");  // Laikina programa, kol vartotojas nuspaudžia klavišą.
}
