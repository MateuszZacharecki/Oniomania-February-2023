#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

typedef map <string, pair<int, double>> MapType;

class Pozycja {
private:
    int x, y;
public:
    int dajx() const;
    int dajy() const;
    void ustawx(int);
    void ustawy(int);

    Pozycja(int x, int y);

    Pozycja() = delete;
    Pozycja(const Pozycja&) = default;
    Pozycja& operator=(const Pozycja&) = default;
    ~Pozycja() = default;
    friend ostream& operator<<(ostream&, const Pozycja&);
};

class Klient;

class Sklep;

class Siec;

class Miasto{
private:
    vector <Klient*> klienci;
    vector <Sklep*> sklepy;
    vector <Siec*> sieci;
public:
    Miasto() = default;
    Miasto(const Miasto&) = delete;
    Miasto& operator=(const Miasto&) = delete;
    ~Miasto() = default;

    Miasto& operator+=(Klient*);
    Miasto& operator+=(Sklep*);
    Miasto& operator+=(Siec*);
    vector <Sklep*> daj_sklepy() const;
    vector <Siec*> daj_sieci() const;
    void ustaw_sieci(vector <Siec*>);
    void kup_prezenty();

    friend ostream& operator<<(ostream&, const Miasto&);
};

class Element{
protected:
    Miasto* miasto = nullptr;
    double budzet;
public:
    Element() = delete;
    Element(const Element&) = default;
    Element& operator=(const Element&) = default;
    virtual ~Element() {};

    Element(double);

    void ustawMiasto(Miasto*);
    double dajbudzet() const;
    void ustawbudzet(double);
    virtual ostream& wypisz(ostream& os) const = 0;
    friend ostream& operator<<(ostream&, const Element&);
};

class Klient : public Element{
protected:
    string imie;
    Pozycja p;
    Miasto* miasto = nullptr;
    vector <string> prezenty;

public:
    Klient() = delete;
    Klient(const Klient&) = delete;
    Klient& operator=(const Klient&) = delete;
    virtual ~Klient() = default;

    Klient(double, string, Pozycja);

    Pozycja dajpozycje() const;
    void ustawpozycje(Pozycja);
    ostream& wypisz(ostream& os) const override;
    string dajimie() const;
    virtual void kup_produkt(Miasto*) = 0;
    virtual bool idz_do_sklepu(Miasto*) = 0;
};

class Towarniak : public Klient{
protected:
    string towar;
public:
    Towarniak() = delete;
    Towarniak(const Towarniak&) = delete;
    Towarniak& operator=(const Towarniak&) = delete;
    virtual ~Towarniak() = default;

    Towarniak(double, string, Pozycja, string);

    virtual Sklep* szukaj_sklepu(Miasto*) = 0;
    bool idz_do_sklepu(Miasto*) override;
    void kup_produkt(Miasto*) override {};
};

class Oszczedny : public Towarniak{
public:
    Oszczedny() = delete;
    Oszczedny(const Oszczedny&) = delete;
    Oszczedny& operator=(const Oszczedny&) = delete;
    virtual ~Oszczedny() = default;

    Oszczedny(double, string, Pozycja, string);

    Sklep* szukaj_sklepu(Miasto*) override;
    Siec* czy_w_sieci(Miasto*);
    void kup_produkt(Miasto*) override;
};

class Tradycjonalista : public Towarniak{
public:
    Tradycjonalista() = delete;
    Tradycjonalista(const Tradycjonalista&) = delete;
    Tradycjonalista& operator=(const Tradycjonalista&) = delete;
    virtual ~Tradycjonalista() = default;

    Tradycjonalista(double, string, Pozycja, string);

    double odl(Sklep*);
    Sklep* szukaj_sklepu(Miasto*) override;
    void kup_produkt(Miasto*) override;
    bool czy_jest_produkt(Miasto*);
};

class Sklepiarz : public Klient{
protected:
    Sklep* ulubiony;
public:
    Sklepiarz() = delete;
    Sklepiarz(const Sklepiarz&) = delete;
    Sklepiarz& operator=(const Sklepiarz&) = delete;
    virtual ~Sklepiarz() = default;

    Sklepiarz(double, string, Pozycja, Sklep*);

    bool idz_do_sklepu(Miasto*) override;
    virtual string znajdz_produkt(Miasto*) = 0;
    void kup_produkt(Miasto*) override {};

};

class Maksymalista : public Sklepiarz{
public:
    Maksymalista() = delete;
    Maksymalista(const Maksymalista&) = delete;
    Maksymalista& operator=(const Maksymalista&) = delete;
    virtual ~Maksymalista() = default;

    Maksymalista(double, string, Pozycja, Sklep*);

    string znajdz_produkt(Miasto*) override;
    void kup_produkt(Miasto*) override;
};

class Minimalista : public Sklepiarz{
public:
    Minimalista() = delete;
    Minimalista(const Minimalista&) = delete;
    Minimalista& operator=(const Minimalista&) = delete;
    virtual ~Minimalista() = default;

    Minimalista(double, string, Pozycja, Sklep*);

    string znajdz_produkt(Miasto*) override;
    void kup_produkt(Miasto*) override;
};

class Losowy : public Sklepiarz{
private:
    int N=3;
public:
    Losowy() = delete;
    Losowy(const Losowy&) = delete;
    Losowy& operator=(const Losowy&) = delete;
    virtual ~Losowy() = default;

    Losowy(double, string, Pozycja, Sklep*);

    string znajdz_produkt(Miasto*) override;
    void kup_produkt(Miasto*) override;
};

class Towar;

class ObiektHandlowy : public Element{
public:
    ObiektHandlowy() = delete;
    ObiektHandlowy(const ObiektHandlowy&) = delete;
    ObiektHandlowy& operator=(const ObiektHandlowy&) = delete;
    ~ObiektHandlowy() = default;

    ObiektHandlowy(double);

    virtual string dajnazwe() const = 0;
};

class Siec : public ObiektHandlowy{
protected:
    string nazwa;
    double marza;
    vector <Sklep*> sklepSieci;
public:
    Siec() = delete;
    Siec(const Siec&) = delete;
    Siec* operator=(const Siec&) = delete;
    virtual ~Siec() = default;

    Siec(double, string, double);

    void dodaj_sklep(Sklep*);
    void przejmij_siec(Siec*, Miasto*);
    vector <Sklep*> dajsklepy() const;
    double dajmarze() const;
    Sklep* sprzedaj_towar(string, double, bool);
    bool czy_stac(Sklep*, string, double);
    bool czy_jest(Sklep*, string);
    ostream& wypisz(ostream& os) const override;
    string dajnazwe() const override;
};

class Sklep : public ObiektHandlowy{
protected:
    MapType towarSklepu;
    string nazwa;
    Pozycja p;
    bool w_sieci;
    Siec* jaka_siec;
public:
    Sklep() = delete;
    Sklep(const Sklep&) = delete;
    Sklep& operator=(const Sklep&) = delete;
    ~Sklep() = default;

    Sklep(double, string, Pozycja, bool w_sieci = false, Siec* jaka_siec = nullptr);

    Sklep& dodaj_towar(Towar*, int, int, double);
    void ustaw_w_sieci(bool);
    bool daj_w_sieci() const;
    void ustaw_jaka_siec(Siec*);
    MapType dajtowary() const;
    bool sprzedaj_towar(string, double);
    Siec* daj_jaka_siec() const;
    void ustaw_towarSklepu(MapType);
    bool czy_stac(string, double);
    bool czy_jest(string);
    Sklep& opusc_siec();

    Pozycja dajpozycje() const;
    void ustawpozycje(Pozycja);
    ostream& wypisz(ostream& os) const override;
    string dajnazwe() const override;
};

class Towar{
private:
    vector <string> towary;
public:
    Towar() = default;
    Towar(const Klient&) = delete;
    Towar& operator=(const Towar&) = delete;
    ~Towar() = default;

    void dodaj_towar(string);
    string daj_towar(int) const;
};

//Pozycja

int Pozycja::dajx() const {
    return x;
}

int Pozycja::dajy() const {
    return y;
}

void Pozycja::ustawx(int x){
    this->x = x;
}

void Pozycja::ustawy(int y){
    this->y = y;
}

Pozycja::Pozycja(int _x, int _y) : x(_x), y(_y) {};

ostream& operator<<(ostream& os, const Pozycja& p) {
    os << "(" << p.dajx() << "," << p.dajy() << ")";
    return os;
}

//Miasto

Miasto& Miasto::operator+=(Klient* k){
    klienci.push_back(k);
    k->ustawMiasto(this);
    return *this;
}

Miasto& Miasto::operator+=(Sklep* s){
    sklepy.push_back(s);
    s->ustawMiasto(this);
    return *this;
}

Miasto& Miasto::operator+=(Siec* s){
    sieci.push_back(s);
    s->ustawMiasto(this);
    return *this;
}

ostream& operator<<(ostream& os, const Miasto& m) {
    os << "Miasto(Klienci:" << m.klienci.size() << ":";
    for (Klient* kwsk : m.klienci) {
        os << *kwsk << ",";
    }
    os << "\n";
    os << "Sklepy:" << m.sklepy.size() << ":";
    for (Sklep* swsk : m.sklepy) {
        os << *swsk << ",";
    }
    os << "\n";
    os << "Sieci:" << m.sieci.size() << ":";
    for (Siec* swsk : m.sieci) {
        os << *swsk << ",";
    }
    os << ")";

    return os;
}

vector <Sklep*> Miasto::daj_sklepy() const
{
    return sklepy;
}

vector <Siec*> Miasto::daj_sieci() const
{
    return sieci;
}

void Miasto::ustaw_sieci(vector <Siec*> sieci)
{
    this->sieci=sieci;
}

void Miasto::kup_prezenty()
{
    for (Klient* kwsk : klienci)
    {
        kwsk->kup_produkt(this);
    }
}

//Element

Element::Element(double _budzet) : budzet(_budzet) {};

void Element::ustawMiasto(Miasto* m) {
    miasto = m;
}

double Element::dajbudzet() const {
    return budzet;
}

void Element::ustawbudzet(double budzet) {
    this->budzet = budzet;
}

ostream& operator<<(ostream& os, const Element& e) {
    return e.wypisz(os);
}

//Klient

Klient::Klient(double _budzet, string _imie, Pozycja _p) : Element(_budzet), imie(_imie), p(_p) {};

Pozycja Klient::dajpozycje() const {
    return p;
};

void Klient::ustawpozycje(Pozycja p) {
    this->p = p;
}

ostream& Klient::wypisz(ostream& os) const
{
    os << "Klient(" << dajbudzet() << "@" << dajimie() << "@" << dajpozycje() << ")";
    return os;
}

string Klient::dajimie() const
{
    return imie;
}

//Towarniak

Towarniak::Towarniak(double _budzet, string _imie, Pozycja _p, string _towar) : Klient(_budzet, _imie, _p), towar(_towar) {};

bool Towarniak::idz_do_sklepu(Miasto* m)
{
    Sklep* s = szukaj_sklepu(m);
    if(s!=nullptr)
    {
        if(s->daj_w_sieci()==false) ustawpozycje(s->dajpozycje());
    }
    return (s!=nullptr);
}

Oszczedny::Oszczedny(double _budzet, string _imie, Pozycja _p, string _towar) : Towarniak(_budzet, _imie, _p, _towar) {};

Sklep* Oszczedny::szukaj_sklepu(Miasto* m)
{
    Sklep* sklep = nullptr;
    double c = 1000000;
    for (Sklep* s : m->daj_sklepy())
    {
        for (auto const& x : s->dajtowary())
        {
            if(x.first == towar)
            {
                if(s->daj_w_sieci())
                {
                    Siec* siec = s->daj_jaka_siec();
                    if((x.second).second+(siec->dajmarze()*((x.second).second))<=c)
                    {
                        sklep = s;
                        c=(x.second).second;
                    }
                }
                else
                {
                    if((x.second).second<=c)
                    {
                        sklep = s;
                        c=(x.second).second;
                    }
                }
            }
        }
    }
    return sklep;
}

Siec* Oszczedny::czy_w_sieci(Miasto* m)
{
    Sklep* s = szukaj_sklepu(m);
    return s->daj_jaka_siec();
}

void Oszczedny::kup_produkt(Miasto* m)
{
    if (idz_do_sklepu(m))
    {
        Siec* siec = czy_w_sieci(m);
        if(siec!=nullptr)
        {
            Sklep* sklep = siec->sprzedaj_towar(towar, budzet, true);
            if(sklep!=nullptr)
            {
                auto it = (sklep->dajtowary()).find(towar);
                prezenty.push_back(towar);
                budzet-=(it->second).second;
                budzet-=(sklep->daj_jaka_siec()->dajmarze())*(it->second).second;
                cout<<"Zakup sie powiodl"<<endl;
            }
            else cout<<"Nie udalo sie kupic towaru"<<endl;
        }
        else
        {
            Sklep* sklep = szukaj_sklepu(m);
            if(sklep!=nullptr)
            {
                if(sklep->sprzedaj_towar(towar, budzet))
                {
                    auto it = (sklep->dajtowary()).find(towar);
                    budzet-=(it->second).second;
                    prezenty.push_back(towar);
                    cout<<"Zakup sie powiodl"<<endl;
                }
                else cout<<"Nie udalo sie kupic towaru"<<endl;
            }
            else cout<<"Nie udalo sie kupic towaru"<<endl;
        }
    }
    else cout<<"Nie udalo sie kupic towaru"<<endl;
}

//Tradycjonalista

Tradycjonalista::Tradycjonalista(double _budzet, string _imie, Pozycja _p, string _towar) : Towarniak(_budzet, _imie, _p, _towar) {};

double Tradycjonalista::odl(Sklep* s)
{
    return sqrt(((p.dajx()+(s->dajpozycje()).dajx())*(p.dajx()+(s->dajpozycje()).dajy()))
                +((p.dajy()+(s->dajpozycje()).dajy())*(p.dajy()+(s->dajpozycje()).dajy())));
}

Sklep* Tradycjonalista::szukaj_sklepu(Miasto* m)
{
    Sklep* sklep = nullptr;
    double o = 1000;
    for (Sklep* s : m->daj_sklepy())
    {
        if(s->daj_w_sieci()==false)
        {
            if(odl(s)<o)
            {
                sklep = s;
                o=odl(s);
            }
        }
    }
    return sklep;
}

void Tradycjonalista::kup_produkt(Miasto* m)
{
    Sklep* s = szukaj_sklepu(m);
    if (idz_do_sklepu(m))
    {
        if(s!=nullptr)
        {
            if(czy_jest_produkt(m))
            {
                if(s->sprzedaj_towar(towar, budzet))
                {
                    auto it = (s->dajtowary()).find(towar);
                    budzet-=(it->second).second;
                    prezenty.push_back(towar);
                    cout<<"Zakup sie powiodl"<<endl;
                }
                else cout<<"Nie udalo sie kupic towaru"<<endl;
            }
            else cout<<"Nie udalo sie kupic towaru"<<endl;
        }
        else cout<<"Nie udalo sie kupic towaru"<<endl;
    }
    else cout<<"Nie udalo sie kupic towaru"<<endl;
}

bool Tradycjonalista::czy_jest_produkt(Miasto* m)
{
    Sklep* s = szukaj_sklepu(m);
    for (auto const& x : s->dajtowary())
    {
        if (x.first == towar) return true;
    }
    return false;
}

//Sklepiarz

Sklepiarz::Sklepiarz(double _budzet, string _imie, Pozycja _p, Sklep* _ulubiony) : Klient(_budzet, _imie, _p), ulubiony(_ulubiony) {};

bool Sklepiarz::idz_do_sklepu(Miasto* m)
{
    if(ulubiony->daj_w_sieci()==false) ustawpozycje(ulubiony->dajpozycje());
    return (ulubiony->daj_w_sieci()==false);
}

//Maksymalista

Maksymalista::Maksymalista(double _budzet, string _imie, Pozycja _p, Sklep* _ulubiony) : Sklepiarz(_budzet, _imie, _p, _ulubiony) {};

string Maksymalista::znajdz_produkt(Miasto* m)
{
    string t=" ";
    if(idz_do_sklepu(m))
    {
        double c=0;
        for(auto const& x : ulubiony->dajtowary())
        {
            if((x.second).second>c && (x.second).second<=budzet)
            {
                t=x.first;
                c=(x.second).second;
            }
        }
    }
    return t;
}

void Maksymalista::kup_produkt(Miasto* m)
{
    string produkt=znajdz_produkt(m);
    if (produkt!=" ")
    {
        if(ulubiony->sprzedaj_towar(produkt, budzet))
        {
            auto it = (ulubiony->dajtowary()).find(produkt);
            budzet-=(it->second).second;
            prezenty.push_back(produkt);
            cout<<"Zakup sie powiodl"<<endl;
        }
        else cout<<"Nie udalo sie kupic towaru"<<endl;
    }
    else cout<<"Nie udalo sie kupic towaru"<<endl;
}

//Minimalista

Minimalista::Minimalista(double _budzet, string _imie, Pozycja _p, Sklep* _ulubiony) : Sklepiarz(_budzet, _imie, _p, _ulubiony) {};

string Minimalista::znajdz_produkt(Miasto* m)
{
    string t=" ";
    if(idz_do_sklepu(m))
    {
        double c=1000000;
        for(auto const& x : ulubiony->dajtowary())
        {
            if((x.second).second<=c)
            {
                t=x.first;
                c=(x.second).second;
            }
        }
    }
    return t;
}

void Minimalista::kup_produkt(Miasto* m)
{
    string produkt=znajdz_produkt(m);
    if (produkt!=" ")
    {
        if(ulubiony->sprzedaj_towar(produkt, budzet))
        {
            auto it = (ulubiony->dajtowary()).find(produkt);
            budzet-=(it->second).second;
            prezenty.push_back(produkt);
            cout<<"Zakup sie powiodl"<<endl;
        }
        else cout<<"Nie udalo sie kupic towaru"<<endl;
    }
    else cout<<"Nie udalo sie kupic towaru"<<endl;
}

//Losowy

Losowy::Losowy(double _budzet, string _imie, Pozycja _p, Sklep* _ulubiony) : Sklepiarz(_budzet, _imie, _p, _ulubiony) {};

string Losowy::znajdz_produkt(Miasto* m)
{
    if(idz_do_sklepu(m))
    {
        int n = rand()%(ulubiony->dajtowary()).size();
        int j=0;
        for(auto const& x : ulubiony->dajtowary())
        {
            if(j==n)
            {
                return x.first;
            }
            j++;
        }
    }
    return " ";
}

void Losowy::kup_produkt(Miasto* m)
{
    for(int i=0; i<N; i++)
    {
        string produkt=znajdz_produkt(m);
        if (produkt!=" ")
        {
            if(ulubiony->sprzedaj_towar(produkt, budzet))
            {
                auto it = (ulubiony->dajtowary()).find(produkt);
                budzet-=(it->second).second;
                prezenty.push_back(produkt);
                cout<<"Zakup sie powiodl"<<endl;
                break;
            }
            else cout<<"Nie udalo sie kupic towaru za"<< i <<"razem"<<endl;
        }
        else cout<<"Nie udalo sie kupic towaru za"<< i <<"razem"<<endl;
    }
}

//ObiektHandlowy

ObiektHandlowy::ObiektHandlowy(double _budzet) : Element(_budzet) {};

//Siec

Siec::Siec(double _budzet, string _nazwa, double _marza) : ObiektHandlowy(_budzet), nazwa(_nazwa), marza(_marza) {};

void Siec::dodaj_sklep(Sklep* s){
    if(s->daj_w_sieci())
    {
        cout<<"Ten sklep jest juz w sieci"<<endl;
    }
    else
    {
        sklepSieci.push_back(s);
        s->ustaw_w_sieci(true);
        s->ustaw_jaka_siec(this);
        cout<<"Dodano sklep"<<endl;
    }
}

vector <Sklep*> Siec::dajsklepy() const
{
    return sklepSieci;
}

void Siec::przejmij_siec(Siec* s, Miasto* m)
{
    for (Sklep* swsk : s->dajsklepy()) {
        swsk->ustaw_jaka_siec(this);
        sklepSieci.push_back(swsk);
    }
    budzet += s->dajbudzet();
    vector <Siec*> temp = m->daj_sieci();
    auto it = find(temp.begin(), temp.end(), s);
    if (it != temp.end()) {
        swap(*it, temp.back());
        temp.pop_back();
    }
    m->ustaw_sieci(temp);
}

double Siec::dajmarze() const
{
    return marza;
}

bool Siec::czy_stac(Sklep* s, string towar, double tempbudzet)
{
    auto it = (s->dajtowary()).find(towar);
    return ((it->second).second + (marza*(it->second).second)<=tempbudzet);
}

bool Siec::czy_jest(Sklep* s, string towar)
{
    auto it = (s->dajtowary()).find(towar);
    return ((it->second).first!=0);
}

Sklep* Siec::sprzedaj_towar(string towar, double tempbudzet, bool kryterium_ceny)
{
    Sklep* sklep = nullptr;
    if(kryterium_ceny)
    {
        double c = 1000000;
        for(Sklep* s : sklepSieci)
        {
            for (auto const& x : s->dajtowary())
            {
                if(x.first == towar)
                {
                    if (czy_stac(s, towar, tempbudzet) && czy_jest(s, towar))
                    {
                        if((x.second).second + marza*(x.second).second <= c)
                        {
                            c = (x.second).second + marza*(x.second).second;
                            sklep = s;
                        }
                    }
                }
            }
        }
    }
    else
    {
        for(Sklep* s : sklepSieci)
        {
            for (auto const& x : s->dajtowary())
            {
                if(x.first == towar)
                {
                    if (czy_stac(s, towar, tempbudzet) && czy_jest(s, towar))
                    {
                    sklep=s;
                    }
                }
            }
        }
    }
    if(sklep!=nullptr)
    {
        auto it = (sklep->dajtowary()).find(towar);
        string temp1 = it->first;
        int temp2 = (it->second).first - 1;
        double temp3 = (it->second).second;
        MapType towary=sklep->dajtowary();
        budzet = budzet + (marza*(it->second).second);
        sklep->ustawbudzet(sklep->dajbudzet() + (it->second).second);
        towary.erase(it->first);
        towary.insert(std::make_pair(temp1, std::make_pair(temp2, temp3)));
        sklep->ustaw_towarSklepu(towary);
    }
    return sklep;
}

string Siec::dajnazwe() const
{
    return nazwa;
}

ostream& Siec::wypisz(ostream& os) const
{
    os << "Siec(" << dajbudzet() << "@" << dajnazwe() << "@" << dajmarze() << ")";
    return os;
}

//Sklep

Sklep::Sklep(double _budzet, string _nazwa, Pozycja _p, bool _w_sieci, Siec* _jaka_siec) :
    ObiektHandlowy(_budzet), nazwa(_nazwa), p(_p), w_sieci(_w_sieci), jaka_siec(_jaka_siec) {};

Sklep& Sklep::dodaj_towar(Towar* t, int n, int liczba, double cena){
    towarSklepu.insert(std::make_pair(t->daj_towar(n), std::make_pair(liczba, cena)));
    return *this;
}

void Sklep::ustaw_w_sieci(bool w_sieci){
    this->w_sieci = w_sieci;
}

void Sklep::ustaw_jaka_siec(Siec* s){
    jaka_siec = s;
}

bool Sklep::daj_w_sieci() const
{
    return w_sieci;
}

Sklep& Sklep::opusc_siec(){
    if(w_sieci)
    {
        auto it = find((jaka_siec->dajsklepy()).begin(), (jaka_siec->dajsklepy()).end(), this);
        if (it != (jaka_siec->dajsklepy()).end()) {
            swap(*it, (jaka_siec->dajsklepy()).back());
            (jaka_siec->dajsklepy()).pop_back();
        }
        w_sieci = false;
        jaka_siec = nullptr;
    }
    else
    {
        cout<<"Ten sklep nie jest w sieci"<<endl;
    }
    return *this;
}

MapType Sklep::dajtowary() const
{
    return towarSklepu;
}

bool Sklep::czy_stac(string towar, double tempbudzet)
{
    auto it = towarSklepu.find(towar);
    return ((it->second).second<=tempbudzet);
}

bool Sklep::czy_jest(string towar)
{
    auto it = towarSklepu.find(towar);
    return ((it->second).first!=0);
}

bool Sklep::sprzedaj_towar(string towar, double tempbudzet)
{
    if(czy_stac(towar, tempbudzet) && czy_jest(towar))
    {
        auto it = towarSklepu.find(towar);
        string temp1 = it->first;
        int temp2 = (it->second).first - 1;
        double temp3 = (it->second).second;
        towarSklepu.erase(it->first);
        towarSklepu.insert(std::make_pair(temp1, std::make_pair(temp2, temp3)));
        budzet+=(it->second).second;
        return true;
    }
    return false;
}

Siec* Sklep::daj_jaka_siec() const
{
    return jaka_siec;
}

void Sklep::ustaw_towarSklepu(MapType towarSklepu)
{
    this->towarSklepu = towarSklepu;
}

Pozycja Sklep::dajpozycje() const {
    return p;
};

void Sklep::ustawpozycje(Pozycja p) {
    this->p = p;
}

string Sklep::dajnazwe() const
{
    return nazwa;
}

ostream& Sklep::wypisz(ostream& os) const
{
    string temp;
    if(daj_jaka_siec()!=nullptr) temp = daj_jaka_siec()->dajnazwe();
    else temp = " ";
    os << "Sklep(" << dajbudzet() << "@" << dajnazwe() << "@" << dajpozycje() << "@" << daj_w_sieci() << "@" << temp << ")";
    return os;
}

//Towar

void Towar::dodaj_towar(string nazwa)
{
    towary.push_back(nazwa);
}

string Towar::daj_towar(int n) const
{
    return towary.at(n);
}

int main()
{
    Miasto m;

    Sklep* sk1 = new Sklep(500, "MiniMarket", Pozycja(0,0));
    Sklep* sk2 = new Sklep(7, "Tesko na Lwowskiej", Pozycja(0,5));
    Sklep* sk3 = new Sklep(423.50, "Tesko na Kazanowie", Pozycja(13,0));
    Sklep* sk4 = new Sklep(151900, "Tesko kolo piatki", Pozycja(3,4));
    Sklep* sk5 = new Sklep(0.1, "Pychotka", Pozycja(5,7));
    Sklep* sk6 = new Sklep(423.50, "Zabka kolo Jowity", Pozycja(10,10));
    Sklep* sk7 = new Sklep(423.50, "Zabka pod szmatami na Kazimierzowskiej", Pozycja(5,90));
    Sklep* sk8 = new Sklep(0, "Gabonski osiedlowy kolo garazow", Pozycja(4,3));

    m += sk1;
    m += sk2;
    m += sk3;
    m += sk4;
    m += sk5;
    m += sk6;
    m += sk7;
    m += sk8;

    Towar t;

    t.dodaj_towar("ser");
    t.dodaj_towar("chleb");
    t.dodaj_towar("koperek");
    t.dodaj_towar("piwo");
    t.dodaj_towar("beczkowe mocne");
    t.dodaj_towar("tatra");
    t.dodaj_towar("ocet");
    t.dodaj_towar("kwas cytrynowy");
    t.dodaj_towar("olej rzepakowy");
    t.dodaj_towar("somerek");
    t.dodaj_towar("kawa");
    t.dodaj_towar("chesterfieldy niebieskie");
    t.dodaj_towar("cebularz");

    sk1->dodaj_towar(&t, 3, 10, 3.99);
    sk1->dodaj_towar(&t, 1, 1, 3);
    sk2->dodaj_towar(&t, 5, 100, 2.99);
    sk2->dodaj_towar(&t, 6, 5, 12);
    sk3->dodaj_towar(&t, 7, 5, 10);
    sk3->dodaj_towar(&t, 8, 5, 9);
    sk4->dodaj_towar(&t, 9, 5, 5);
    sk4->dodaj_towar(&t, 10, 5, 23.50);
    sk5->dodaj_towar(&t, 11, 5, 14.50);
    sk5->dodaj_towar(&t, 12, 5, 2.19);
    sk6->dodaj_towar(&t, 0, 5, 15.99);
    sk6->dodaj_towar(&t, 1, 5, 3.99);
    sk7->dodaj_towar(&t, 2, 5, 2);
    sk7->dodaj_towar(&t, 3, 5, 3.49);
    sk8->dodaj_towar(&t, 4, 5, 3.59);
    sk8->dodaj_towar(&t, 3, 5, 3.69);
    sk8->dodaj_towar(&t, 1, 5, 3.79);

    Siec* si1 = new Siec(1000, "Tesko", 0.05);
    Siec* si2 = new Siec(513, "Zabka", 0.1);

    m += si1;
    m += si2;

    si1->dodaj_sklep(sk2);
    si1->dodaj_sklep(sk3);
    si1->dodaj_sklep(sk4);
    si2->dodaj_sklep(sk6);
    si2->dodaj_sklep(sk7);

    si1->przejmij_siec(si2, &m);

    Klient* k1 = new Oszczedny(100, "Krzesia", Pozycja(1,1), "ser");
    Klient* k2 = new Tradycjonalista(200, "Fac", Pozycja(0,1), "chleb");
    Klient* k3 = new Tradycjonalista(2, "Dziumak", Pozycja(2,2), "koperek");
    Klient* k4 = new Losowy(300, "Katarzyna Harasimowicz-Gaska", Pozycja(3,3), sk1);
    Klient* k5 = new Minimalista(400, "Kisiel", Pozycja(4,4), sk5);
    Klient* k6 = new Maksymalista(500, "Brud", Pozycja(5,5), sk1);
    Klient* k7 = new Minimalista(4, "Koperski", Pozycja(1,1), sk8);

    m += k1;
    m += k2;
    m += k3;
    m += k4;
    m += k5;
    m += k6;
    m += k7;

    cout << m << endl;

    m.kup_prezenty();

    cout << m << endl;

    return 0;
}
