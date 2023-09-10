#ifndef STUDENTAS_H
#define STUDENTAS_H

class Zmogus
{
    protected:
        string vardas_, pavarde_;
    public:
        Zmogus() : vardas_(""), pavarde_("") {}
        Zmogus(string vardas, string pavarde) : vardas_(vardas), pavarde_(pavarde) {}
        virtual string vardas() const = 0;
        ~Zmogus() {}
};

class Studentas : public Zmogus
{
    private:
        Vector<int> paz_;
        int egz_;
        float gal_vid_, gal_med_;

    public:
        Studentas() : Zmogus(), egz_(0), gal_vid_(0), gal_med_(0) {}
        Studentas(string vardas, string pavarde, Vector<int> paz, int egz, float gal_vid, float gal_med) : Zmogus(vardas,pavarde), paz_(paz), egz_(egz), gal_vid_(gal_vid), gal_med_(gal_med) {}
        ~Studentas() { paz_.clear(); };

        //setteriai
        void vardas(string vardas) { vardas_ = vardas; }
        void pavarde(string pavarde) { pavarde_ = pavarde; }
        void paz(Vector<int> paz) { paz_ = paz; }
        void egz(int egz) { egz_ = egz; }
        void gal_med(float gal_med) { gal_med_ = gal_med; }
        void gal_vid(float gal_vid) { gal_vid_ = gal_vid; }

        //getteriai
        string vardas() const { return vardas_; }
        string pavarde() const { return pavarde_; }
        Vector<int> paz() const { return paz_; }
        int egz() const { return egz_; }
        float gal_med() const { return gal_med_; }
        float gal_vid() const { return gal_vid_; }

        const string& vardas1() const { return vardas_; }
        const string& pavarde1() const { return pavarde_; }


        friend std::ostream& operator<<(std::ostream &out, const Studentas &st){
            out<<left<<setw(15)<<st.vardas_<<setw(20)<<st.pavarde_;
            for (const auto &j: st.paz_)
                out << setw(5) << j << " ";
            out << setw(5) << st.egz_ << " | "<<setw(3)<<fixed<<setprecision(2)<<st.gal_vid_<<" / "<<st.gal_med_<<"\n";
            return out;
        }
        //rusiavimas pagal varda ir pavarde
        bool operator < (const Studentas& st) const { return tie(vardas_, pavarde_) < tie(st.vardas1(), st.pavarde1()); }

        Studentas(const Studentas& st) : Zmogus(st.vardas_,st.pavarde_),paz_(st.paz_),egz_(st.egz_),gal_vid_(st.gal_vid_),gal_med_(st.gal_med_) {}
        //            cout << "copy konstruktorius \n";


        Studentas& operator = (const Studentas& st) {
//            cout << "copy priskyrimo operatorius \n";
            if (&st != this){
                vardas_ = st.vardas_;
                pavarde_ = st.pavarde_;
                paz_ = st.paz_;
                egz_ = st.egz_;
                gal_vid_ = st.gal_vid_;
                gal_med_ = st.gal_med_ ;
            }
            return *this;
        }

        Studentas(Studentas&& st) : Zmogus(move(st.vardas_), move(st.pavarde_)), paz_(move(st.paz_)), egz_(move(st.egz_)), gal_vid_(move(st.gal_vid_)), gal_med_(move(st.gal_med_)) {
//            cout << "move konstruktorius \n";
            st.gal_med_ = 0;
            st.gal_vid_ = 0;
            st.egz_ = 0;
        }

        Studentas& operator = (Studentas&& st){
//            cout << "move priskyrimo operatorius \n";
            if (&st != this){
                vardas_ = std::move(st.vardas_);
                pavarde_ = std::move(st.pavarde_);
                paz_ = std::move(st.paz_);
                egz_ = std::move(st.egz_) ;
                gal_vid_ = std::move(st.gal_vid_) ;
                gal_med_ = std::move(st.gal_med_) ;
                st.gal_med_ = 0;
                st.gal_vid_ = 0;
                st.egz_ = 0;
                st.paz_.clear();
            }
            return *this;
        }
};

#endif // STUDENTAS_H
