// Tikrina, ar FILE_FUNCTIONS_H_INCLUDED simbolis dar nėra apibrėžtas.
// Jei nėra, tai jį apibrėžia, kad būtų galima saugiai įtraukti šį antraštės failą daugiau nei kartą.
#ifndef FILE_FUNCTIONS_H_INCLUDED  
#define FILE_FUNCTIONS_H_INCLUDED  // Apibrėžia FILE_FUNCTIONS_H_INCLUDED simbolį.

// Funkcijos prototipas, kuris grąžina 'double' tipo reikšmę. Funkcija nuskaito studentų informaciją iš failo.
// Ji priima dviem kintamaisiais: vektoriumi "grupe", kurio elementai yra 'Studentas' tipo objektai ir 
// 'int' tipo kintamuoju "uzkl_2".
double failo_nuskaitymas(Vector<Studentas>& grupe, int uzkl_2);  

// Funkcijos prototipas, kuris nieko negrąžina ('void'). Funkcija spausdina studentų informaciją į failą.
// Ji priima keturiais kintamaisiais: vektoriumi "grupe", kurio elementai yra 'Studentas' tipo objektai, 
// dviem 'int' tipo kintamaisiais "uzkl_1" ir "uzkl_2", bei 'string' tipo kintamuoju, kuris yra failo pavadinimas.
void spausd_i_faila(Vector<Studentas>& grupe, int uzkl_1, int uzkl_2, string filename);

// Užbaigia sąlyginį kompiliavimą ir užkerta kelią tolesniam antraštės failo turinio apdorojimui,
// jei FILE_FUNCTIONS_H_INCLUDED jau buvo apibrėžtas.
#endif // FILE_FUNCTIONS_H_INCLUDED  
