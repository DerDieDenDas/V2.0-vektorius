#include "mylib.h"
#include "funkcijos_su_failais.h"

extern size_t pazymiu_kiekis;

void skirstymas(int& uzkl_6, int& uzkl_2, int& uzkl_1, Vector<Studentas>& grupe, double& visa_trukme){
    if(uzkl_6 == 1) {       /// Jei du nauji konteineriai
        Vector<Studentas> tinginiai, mokslinciai;
        Timer tinginiai_mokslinciai;
        if(uzkl_2 == 1 || uzkl_2 == 3){     /// skaiciuojama pagal vidurki, jei galutinis yra vidurkis arba vidurkis/mediana
            auto it = partition(grupe.begin(), grupe.end(), [](Studentas s)
            {
                return s.gal_vid()>5.0;
            });
            tinginiai = {it, grupe.end()};
            mokslinciai = {grupe.begin(), it};
        }
        if(uzkl_2 == 2){        /// skaiciuojama pagal mediana, jei galutinis yra mediana
            auto it = partition(grupe.begin(), grupe.end(), [](Studentas s)
            {
                return s.gal_med()>5.0;
            });
            tinginiai = {it, grupe.end()};
            mokslinciai = {grupe.begin(), it};
        }
        cout << "Studentu rusiavimas i dvi grupes truko: "<< tinginiai_mokslinciai.elapsed() << "s\n";
        visa_trukme += tinginiai_mokslinciai.elapsed();
        tinginiai.shrink_to_fit();
        mokslinciai.shrink_to_fit();
        Timer rusiavimas;
        sort(tinginiai.begin(), tinginiai.end());
        sort(mokslinciai.begin(), mokslinciai.end());
        cout << "Studentu rusiavimas didejimo tvarka uztruko: " << rusiavimas.elapsed() << "s\n";
        visa_trukme += rusiavimas.elapsed();
        Timer rus_spausd;
        spausd_i_faila(tinginiai,uzkl_1,uzkl_2,"output_tinginiai.txt");
        spausd_i_faila(mokslinciai,uzkl_1,uzkl_2,"output_mokslinciai.txt");
        cout << "Surusiuotu studentu isvedimas i du failus uztruko: " << rus_spausd.elapsed() << "s\n";
        visa_trukme += rus_spausd.elapsed();
        tinginiai.clear();
        mokslinciai.clear();
    } else {        /// Jei vienas naujas konteineris
        Vector<Studentas> tinginiai;
        Timer tinginiai_mokslinciai;


        if(uzkl_2 == 1 || uzkl_2 == 3){      /// Jei galutinis yra vidurkis arba vidurkis/mediana - skaiciuojama pagal vidurki
            auto it = partition(grupe.begin(), grupe.end(), [](Studentas s)
            {
                return s.gal_vid()>5.0;
            });

            tinginiai = {it, grupe.end()};
            grupe.erase(it, grupe.end());
        }
        if(uzkl_2 == 2){        /// Jei galutinis yra mediana - skaiciuojama pagal mediana
            auto it = partition(grupe.begin(), grupe.end(), [](Studentas s)
            {
                return s.gal_med()>5.0;
            });
            tinginiai = {it, grupe.end()};
            grupe.erase(it, grupe.end());
        }
        cout << "Studentu rusiavimas i dvi grupes truko: "<< tinginiai_mokslinciai.elapsed() << "s\n";
        visa_trukme += tinginiai_mokslinciai.elapsed();
        tinginiai.shrink_to_fit();
        grupe.shrink_to_fit();
        Timer rusiavimas;
        sort(grupe.begin(), grupe.end());
        sort(tinginiai.begin(), tinginiai.end());
        cout << "Studentu rusiavimas didejimo tvarka uztruko: " << rusiavimas.elapsed() << "s\n";
        visa_trukme += rusiavimas.elapsed();
        Timer rus_spausd;
        spausd_i_faila(tinginiai,uzkl_1,uzkl_2,"output_tinginiai.txt");
        spausd_i_faila(grupe,uzkl_1,uzkl_2,"output_mokslinciai.txt");
        cout << "Surusiuotu studentu isvedimas i du failus uztruko: " << rus_spausd.elapsed() << "s\n";
        visa_trukme += rus_spausd.elapsed();
        tinginiai.clear();
    }
}

void stud_ivest(Vector<Studentas> &grupe, int uzkl_2){
    string uzkl;
    cout << "\nKiek daugiausia pazymiu gales tureti kiekvienas studentas? ";
    cin >> pazymiu_kiekis;
    while(pazymiu_kiekis < 1 || pazymiu_kiekis > 20){
            cout << "Neteisinga ivestis. Iveskite skaiciu tarp 1 ir 20. " << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }
    do{
        pild(grupe,uzkl_2);
        cout<<"Noredami baigti, iveskite 'n' arba iveskite bet koki klavisa ir toliau veskite kito studento duomenis\n";
        //statistika(grupe);
        cin.ignore();
        getline(cin, uzkl);
    } while (uzkl != "n" && uzkl != "N");
}

void isvedimas_i_ekrana(Vector<Studentas> &grupe,int& uzkl_4,int& uzkl_2,int& uzkl_1){
    cout<<endl<<left<<setw(15)<<"Vardas"<<setw(20)<<"Pavarde";
    switch(uzkl_2){
    case 1:
        cout<<setw(15)<<"Galutinis (Vid.)"<<endl;
        break;
    case 2:
        cout<<setw(15)<<"Galutinis (Med.)"<<endl;
        break;
    case 3:
        cout<<setw(15)<<"Galutinis (Vid. / Med.)"<<endl;
        break;
    case 4:
        cout<<setw(15)<<"Pazymiai"<<endl;
        break;
    }
    cout<<"---------------------------------------------------"<<endl;
    for(const auto &i:grupe)
        spausd(i,uzkl_2,uzkl_1);
    if(uzkl_2 != 4){    /// Jei pazymiai dar nebuvo spausdinti
        cout << "\nAr norite spausdinti pazymius? (jei taip - iveskite '4', jei ne - '0')";
        int_input_check(uzkl_4,(Vector<int>){4, 0});
        if(uzkl_4 == 4){
            cout<<endl<<left<<setw(15)<<"Vardas"<<setw(20)<<"Pavarde"<<setw(15)<<"Pazymiai"<<endl;
            cout<<"---------------------------------------------------"<<endl;
            for(const auto &i:grupe)
                spausd(i,uzkl_4,uzkl_1);
        }
    }
}

void pild(Vector<Studentas> &grupe, int uzkl_2){
    int p;
    string vardas, pavarde;
    Vector<int> paz;
    int egz;
    float gal_vid = 0, gal_med = 0;
    cout<<"\nIveskite studento varda ir pavarde: ";
    cin >> vardas >> pavarde;
    while(tik_raides(vardas) || tik_raides(pavarde)){
        cin.clear();
        std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout<<"Neteisinga ivestis. Varde gali buti tik raides. Bandykite dar karta. ";
        cin >> vardas >> pavarde;
    }
    cout << "Iveskite " << pazymiu_kiekis << " paz. (Veskite tik sveikuosius skaicius. Noredami nutraukti pazymiu ivedima, iveskite bet kokia raide). ";
    do{
        bool pushback = true;
        cin>>p;
        if(!cin){
            if(paz.empty()){
                cin.clear();
                std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "Iveskite bent viena pazymi. ";
                pushback = false;
            }
            else
                break;
        }
        if(p >= 0 && p <= 10 && pushback)
            paz.push_back(p);
        else
            cout << "Pazymys turi buti tarp 0 (negautas) ir 10\n";
        if(paz.size() > pazymiu_kiekis){
            cout << "Ivedete per daug pazymiu. Bus irasyti tik pirmi " << pazymiu_kiekis << " pazymiai.\n";
            break;
        }
        //statistika(paz);
    } while((paz.size() < pazymiu_kiekis) || paz.empty()); /// ar cia viskas gerai?
    cin.clear();
    std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    cout << "Iveskite egzamino paz. ";
    cin>>egz;
    while(1){
        if(cin.fail() || egz < 1 || egz > 10 ){
            cin.clear();
            std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Pazymys turi buti tarp 1 ir 10. ";
            cin >> egz;
        }
        else
            break;
    }
    switch(uzkl_2){
    case 1:
        gal_vid = vidurkis(paz,egz);
        break;
    case 2:
        gal_med = mediana(paz,egz);
        break;
    case 3:
        gal_vid = vidurkis(paz,egz);
        gal_med = mediana(paz,egz);
        break;
    case 4:
        break;
    }
    grupe.push_back(Studentas(vardas,pavarde,paz,egz,gal_vid,gal_med));
    cout << "Duomenys irasyti." << endl;
}

void spausd(const Studentas &temp, int uzkl_2, int uzkl_1){
    cout<<left<<setw(15)<<temp.vardas()<<setw(20)<<temp.pavarde();
    switch(uzkl_2){
    case 1:
        cout<<setw(3)<<fixed<<setprecision(2)<<temp.gal_vid()<<"       \n";
        break;
    case 2:
        cout<<setw(3)<<fixed<<setprecision(2)<<temp.gal_med()<<"       \n";
        break;
    case 3:
        cout<<setw(3)<<fixed<<setprecision(2)<<temp.gal_vid()<<" / "<<temp.gal_med()<<"\n";
        break;
    case 4:
        for (const auto &i: temp.paz()) cout << setw(3) << i << " ";
        cout << right << setw(10+(pazymiu_kiekis-temp.paz().size())*4) << "Egz.: " << temp.egz() << endl;
        break;
    }
}

void gen_paz(int kelintas, int uzkl_2, Studentas &temp){
    Vector<int> pazymiai;
    int egz;
    float gal_vid,gal_med;
    static std::random_device _rd;
    static std::mt19937 _rnd{_rd()};
    static std::uniform_int_distribution<int> dist(0,10);
    static std::uniform_int_distribution<int> dist_egz(1,10);
    temp.vardas("Vardas" + to_string(kelintas));
    temp.pavarde("Pavarde" + to_string(kelintas));
    egz = dist_egz(_rnd);
    temp.egz(egz);
    for(size_t i=0;i<pazymiu_kiekis;i++)
        pazymiai.push_back(dist(_rnd));
    temp.paz(pazymiai);

    switch(uzkl_2){
    case 1:
        gal_vid = vidurkis(pazymiai,egz);
        break;
    case 2:
        gal_med = mediana(pazymiai,egz);
        break;
    case 3:
        gal_vid = vidurkis(pazymiai,egz);
        gal_med = mediana(pazymiai,egz);
        break;
    case 4:
        break;
    }
    pazymiai.clear();
    temp.gal_med(gal_med);
    temp.gal_vid(gal_vid);
}

double stud_gen(Vector<Studentas> &grupe, Studentas &temp, int uzkl_2){
    int stud_sk;
    cout << "Kiek studentu norite generuoti? ";
    cin >> stud_sk;
    while (stud_sk < 1){
            cout << "Neteisinga ivestis. Iveskite skaiciu, didesni uz 0.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    cout << "Kiek daugiausia pazymiu norite skirti kiekvienam studentui? ";
    cin >> pazymiu_kiekis;
    while(pazymiu_kiekis < 1){
            cout << "Neteisinga ivestis. Iveskite skaiciu, didesni uz 0.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    Timer gen;
    for(int i=0;i<stud_sk;i++){
        gen_paz(i,uzkl_2,temp);
        grupe.push_back(temp);
    }
    cout << "Studentu duomenu generavimas uztruko: " << gen.elapsed() << "s\n";
    return gen.elapsed();
}



float vidurkis(Vector<int> paz, int egz){
    float paz_suma = accumulate(paz.begin(),paz.end(),0.);
    return (0.6*egz+0.4*paz_suma/pazymiu_kiekis);
}

float mediana(Vector<int> paz, int egz){
    float med;
    sort(paz.begin(),paz.end());
    if(paz.size()%2 == 0) /// jei pazymiu skaicius lyginis
        med = (paz[paz.size()/2-1]+paz[paz.size()/2])/2.0;
    else                /// jei pazymiu skaicius nelyginis
        med = paz[paz.size()/2];
    return (0.4*med+0.6*egz);
}

bool tik_raides(string name){
    return !std::regex_match(name, std::regex("^[A-Za-z]+$"));
}

void int_input_check(int& input, Vector<int> correct){
    if (!(cin >> input)) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    for(int i : correct)
        if(input == i)
            return;
    cout << "Klaidinga ivestis. Turite ivesti viena is siu skaiciu: ";
    for(size_t i=0;i<correct.size();i++)
        if(correct.size()-i-1 != 0)
            cout << "'" << correct[i] << "', ";
        else
            cout << "'" << correct[i] << "'.\n";
    int_input_check(input,correct);
}
