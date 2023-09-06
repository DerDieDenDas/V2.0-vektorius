#include "mylib.h" // Įterpiamas vartotojo apibrėžtas "mylib.h" antraštės failas.
#include "file_functions.h" // Įterpiamas kitas vartotojo apibrėžtas "file_functions.h" antraštės failas.

int paz_skaicius; // Globalus kintamasis skirtas pažymių skaičiui.

int main()
{
    // Kintamieji, skirti vartotojo pasirinkimams fiksuoti. Pradinė reikšmė yra -1.
    int uzkl_1 = -1, uzkl_2 = -1, uzkl_3 = -1, uzkl_4 = -1, uzkl_5 = -1, uzkl_6 = -1;
    Vector<Studentas> grupe; // Kintamasis grupės studentų saugojimui.
    Studentas temp; // Laikinas "Studentas" objektas.
    double visa_trukme = 0; // Kintamasis tam tikrų operacijų trukmės saugojimui.

    // Vartotojo pasirinkimai
    cout << "Ar norite: ..."; // Klausiama vartotojo apie duomenų įvedimo būdą.
    int_input_check(uzkl_1,(Vector<int>){1, 2, 3}); // Tikrinamas įvedimas. Užtikrinama, kad pasirinkimas yra tinkamas.
    // ... Panašūs vartotojo pasirinkimai ir jų patikra.

    switch(uzkl_1) { // Pasirenkama pagal pirmąjį pasirinkimą.
        case 1:
            stud_ivest(grupe,uzkl_2); // Jei pasirinkimas yra 1, rankiniu būdu įvedami studentų duomenys.
            break;
        case 3:
            visa_trukme += failo_nuskaitymas(grupe,uzkl_2); // Jei pasirinkimas yra 3, studentų duomenys yra nuskaitomi iš failo.
            break;
        default:
            visa_trukme += stud_gen(grupe,temp,uzkl_2); // Numatytoji reikšmė (tikriausiai 2): generuojami studentų duomenys.
            break;
    }

    // Priklausomai nuo ankstesnių pasirinkimų, duomenys arba rodomi ekrane, arba saugomi faile.
    // ... Daugiau operacijų pagal vartotojo pasirinkimus.

    cout << "Visas programos darbas truko: "<< visa_trukme << "s\n"; // Rodomas bendras programos vykdymo laikas.

    system("pause"); // Programa sustabdoma kol vartotojas nespaus klavišo.
}
