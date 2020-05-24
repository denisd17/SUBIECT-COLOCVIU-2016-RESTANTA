#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

using namespace std;
/*
RUTA

ZBOR -> ZBOR SPECIAL -> ZBOR SARBATOARE
*/

class Zbor{
protected:
    static int cod;
    string data;
    int id;
    int discount;

public:
    Zbor();
    Zbor(string,int);
    Zbor(const Zbor&);
    virtual ~Zbor(){};

    friend ostream& operator<<(ostream&, const Zbor&);
    friend istream& operator>>(istream&, Zbor&);
    string get_data()const{return data;}
    int get_discount()const{return discount;}

    virtual void afisare(ostream&)const;
    virtual void citire(istream&);
};
int Zbor::cod;

Zbor::Zbor()
{
    cod+=1;
    id = cod;
    data="";
    discount = 0;
}

Zbor::Zbor(string da, int di)
{
    cod+=1;
    id = cod;
    data = da;
    discount = di;
}

Zbor::Zbor(const Zbor& z)
{
    cod+=1;
    id = cod;
    data = z.data;
    discount = z.discount;
}

ostream& operator<<(ostream& out, const Zbor& z)
{
    z.afisare(out);
    return out;
}
istream& operator>>(istream& in, Zbor& z)
{
    z.citire(in);
    return in;
}

void Zbor::afisare(ostream& out) const
{
    out<<"Id unic: W"<<id<<"\n";
    out<<"Data incepere: "<<data<<"\n";
    if(discount)
        out<<"Discount aplicat de "<<discount<<"%\n";
}

void Zbor::citire(istream& in)
{
    cout<<"Data incepere: ";
    getline(in, data);
    cout<<"Discount: ";
    in>>discount;
    in.get();
}

class Zbors : public Zbor{
protected:
    int perioada;
    string unitate; ///zile sau luni

public:
    Zbors();
    Zbors(string, int, int, string);
    Zbors(const Zbors&);
    ~Zbors(){};

    virtual void afisare(ostream&)const;
    virtual void citire(istream&);
};

Zbors::Zbors() : Zbor()
{
    perioada = 0;
    unitate = "zile";
}

Zbors::Zbors(string da, int di, int p, string u) : Zbor(da,di)
{
    perioada = p;
    unitate = u;
}

Zbors::Zbors(const Zbors& z) : Zbor(z)
{
    perioada = z.perioada;
    unitate = z.unitate;
}

void Zbors::afisare(ostream& out) const
{
    Zbor::afisare(out);
    out<<"Valabil pentru o perioada de "<<perioada<<" "<<unitate<<"\n";
}

void Zbors::citire(istream& in)
{
    Zbor::citire(in);
    int optiune;
    cout<<"Perioada de timp pe care va fi valabil zborul\n1.Zile\n2.Luni\n";
    in>>optiune;
    if(optiune == 1)
        unitate = "zile";
    else if(optiune == 2)
        unitate = "luni";
    cout<<"Numarul de "<<unitate<<" pe care va fi valabil zborul: ";
    in>>perioada;
    in.get();
}

class Zborsa : public Zbors{
private:
    string sarbatoare;

public:
    Zborsa();
    Zborsa(string, int, int, string, string);
    Zborsa(const Zborsa&);
    ~Zborsa(){};

    void afisare(ostream&)const;
    void citire(istream&);
};

Zborsa::Zborsa() : Zbors()
{
    sarbatoare="";
}

Zborsa::Zborsa(string da, int di, int pe, string u, string sa) : Zbors(da,di,pe,u)
{
    sarbatoare = sa;
}

Zborsa::Zborsa(const Zborsa& z) : Zbors(z)
{
    sarbatoare = z.sarbatoare;
}

void Zborsa::afisare(ostream& out)const
{
    Zbors::afisare(out);
    out<<"Zbor adaugat cu ocazia sarbatorii de "<<sarbatoare<<"\n";
}

void Zborsa::citire(istream& in)
{
    Zbors::citire(in);
    cout<<"Cu ocazia carei sarbatori a fost adaugat acest zbor\n1.Halloween\n2.Thanksgiving\n3.Craciun\n";
    int optiune;
    in>>optiune;

    if(optiune == 1)
        sarbatoare = "Halloween";
    else if(optiune == 2)
        sarbatoare = "Thanksgiving";
    else if(optiune == 3)
        sarbatoare = "Craciun";
}

class Ruta{
private:
    list<Zbor*> curse;
    string plecare;
    string destinatie;
    int pret;
    int durata;
    //string data;

public:
    Ruta();
    Ruta(list<Zbor*>,string, string, int, int);
    Ruta(const Ruta&);
    ~Ruta();

    list<Zbor*> get_curse()const{return curse;}
    void adauga_cursa();
    string get_plecare()const{return plecare;}
    string get_destinatie()const{return destinatie;}

    friend ostream& operator<<(ostream&, const Ruta&);
    friend istream& operator>>(istream&, Ruta&);
};

Ruta::Ruta()
{
    plecare = "";
    destinatie = "";
    pret = 0;
    durata = 0;
}

Ruta::Ruta(list<Zbor*> l, string plec, string dest, int pr, int dur)
{
    Zbor *p;
    list<Zbor*>::iterator i;
    for(i = l.begin();i!=l.end();++i)
    {
        Zborsa *p1 = dynamic_cast<Zborsa*>(*i);
        Zbors *p2 = dynamic_cast<Zbors*>(*i);
        Zbor *p3 = dynamic_cast<Zbor*>(*i);

        if(p1)
        {
            p = new Zborsa(*p1);
            curse.push_back(p);
        }
        else if(p2)
        {
            p = new Zbors(*p2);
            curse.push_back(p);
        }
        else if(p3)
        {
            cout<<"da";
            p = new Zbor(*p3);
            curse.push_back(p);
        }
    }
    plecare = plec;
    destinatie = dest;
    pret = pr;
    durata = dur;
}

Ruta::Ruta(const Ruta& z)
{
    Zbor *p;
    list<Zbor*>::const_iterator i;
    for(i = z.curse.begin();i!=z.curse.end();++i)
    {
        Zborsa *p1 = dynamic_cast<Zborsa*>(*i);
        Zbors *p2 = dynamic_cast<Zbors*>(*i);
        Zbor *p3 = dynamic_cast<Zbor*>(*i);

        if(p1)
        {
            p = new Zborsa(*p1);
            curse.push_back(p);
        }
        else if(p2)
        {
            p = new Zbors(*p2);
            curse.push_back(p);
        }
        else if(p3)
        {
            p = new Zbor(*p3);
            curse.push_back(p);
        }
    }
    plecare = z.plecare;
    destinatie = z.destinatie;
    pret = z.pret;
    durata = z.durata;
}

Ruta::~Ruta()
{
    cout<<"DELETE RUTA\n";
    list<Zbor*>::iterator i;
    for(i = curse.begin();i!=curse.end();++i)
    {
        delete *i;
    }
    curse.resize(0);

    plecare = "";
    destinatie = "";
    pret = 0;
    durata = 0;

}

ostream& operator<<(ostream& out, const Ruta& r)
{
    out<<"Ruta: "<<r.plecare<<" - "<<r.destinatie<<"\n";
    out<<"Pret bilet: "<<r.pret<<"lei\n";
    out<<"Cu durata de: "<<r.durata<<"ore\n";

    out<<"Curse inregistrare pe acesta ruta: \n";
    list<Zbor*>::const_iterator i;
    for(i=r.curse.begin();i!=r.curse.end();++i)
    {
        cout<<"------------------\n";
        cout<<(**i);
    }
    cout<<"------------------\n";

    return out;
}

void Ruta::adauga_cursa()
{
    cout<<"Alegeti tip cursa: \n";
    cout<<"1.Permanenta\n2.Zbor Temporar\n3.Zbor Temporar Sarbatoare\n";
    int optiune;
    Zbor *p;

    cin>>optiune;
    cin.get();

    if(optiune == 1)
    {
        p = new Zbor;
        cin>>(*p);
    }
    else if(optiune == 2)
    {
        p = new Zbors;
        cin>>(*p);
    }
    else if(optiune == 3)
    {
        p = new Zborsa;
        cin>>(*p);
    }
    curse.push_back(p);
}


istream& operator>>(istream& in, Ruta& r)
{
    cout<<"Plecare: ";
    getline(in, r.plecare);
    cout<<"Sosire: ";
    getline(in, r.destinatie);
    cout<<"Pret bilet: ";
    in>>r.pret;
    in.get();
    cout<<"Durata zbor: ";
    in>>r.durata;
    in.get();

    cout<<"Doriti sa adaugati curse pe aceasta ruta?(1/0)\n";
    bool optiune;
    in>>optiune;

    if(optiune)
    {
        cout<<"Cate curse doriti sa adaugati?\n";
        int nr;
        in>>nr;
        in.get();

        for(int i = 0;i<nr;i++)
            r.adauga_cursa();
    }


    return in;
}

bool data(string data1, string data2, string data3)
{
    bool d = false;
    ///verificam anul
    int d1 = atoi((data1.substr(6,4)).c_str());
    int d2 = atoi((data2.substr(6,4)).c_str());
    int d3 = atoi((data3.substr(6,4)).c_str());

    if(d1 <= d3 && d3 <= d2)
    {
        ///verificam luna
        d1 = atoi((data1.substr(3,2)).c_str());
        d2 = atoi((data2.substr(3,2)).c_str());
        d3 = atoi((data3.substr(3,2)).c_str());
        if(d1 <= d3 && d3 <= d2)
        {
            ///verificam ziua
            d1 = atoi((data1.substr(0,2)).c_str());
            d2 = atoi((data2.substr(0,2)).c_str());
            d3 = atoi((data3.substr(0,2)).c_str());
            if(d1 <= d3 && d3 <= d2)
                d = true;
        }
    }

    return d;
}

void meniu()
{
    cout<<"1.Adauga ruta\n";
    cout<<"2.Afiseaza rute\n";
    cout<<"3.Adauga cursa\n";
    cout<<"4.Curse intre doua date\n";
    cout<<"5.Curse active\n";
    cout<<"6.Rute fara discount\n";
    cout<<"7.EXIT\n";
}

void program()
{
    bool exit = false;
    int optiune;
    list<Ruta*> rute;
    Ruta *r;

    while(!exit)
    {
        meniu();
        cin>>optiune;
        cin.get();

        if(optiune == 1)
        {
            r = new Ruta;
            cin>>(*r);
            rute.push_back(r);
        }
        else if(optiune == 2)
        {
            if(rute.size() == 0)
            {
                cout<<"NU AU FOST CITITE RUTE\n";
            }
            else
            {
                list<Ruta*>::iterator i;
                for(i = rute.begin();i!=rute.end();++i)
                {
                    cout<<"-----------------------\n";
                    cout<<(**i);
                }
                cout<<"-----------------------\n";
            }

        }
        else if(optiune == 3)
        {
            cout<<"Rute disponibile: \n";
            list<Ruta*>::iterator i;
            int indice = 0;
            int optiune;
            for(i = rute.begin();i!=rute.end();++i)
            {
                cout<<"-----------------------\n";
                cout<<indice<<". "<<(**i).get_destinatie()<<" - "<<(**i).get_plecare()<<"\n";
                indice+=1;
            }
            cout<<"-----------------------\n";
            cout<<"Introduceti optiune: ";
            cin>>optiune;
            while(optiune < 0 || optiune > indice)
            {
                cout<<"Optiune invalida: ";
                cin>>optiune;
            }
            bool stop = false;
            indice = 0;
            for(i = rute.begin();i!=rute.end() && !stop;++i)
            {
                if(indice == optiune)
                {
                    (**i).adauga_cursa();
                    stop = true;
                }

                indice+=1;
            }

        }
        else if(optiune == 4)
        {
            string data1,data2,data3;
            cout<<"Introduceti data1: ";
            getline(cin,data1);

            cout<<"Introduceti data2: ";
            getline(cin,data2);

            list<Ruta*>::iterator i;
            for(i = rute.begin();i!=rute.end();++i)
            {
                list<Zbor*> c = (**i).get_curse();
                list<Zbor*>::iterator j;
                for(j = c.begin();j!=c.end();++j)
                {
                    data3 = (**j).get_data();
                    if(data(data1,data2,data3))
                        cout<<(**j);
                }
            }
            cout<<"-----------------------\n";


        }
        else if(optiune == 5)
        {
            ///to do
        }
        else if(optiune == 6)
        {
            list<Ruta*>::iterator i;
            for(i = rute.begin();i!=rute.end();++i)
            {
                int gasit = 0;
                list<Zbor*> c = (**i).get_curse();
                list<Zbor*>::iterator j;
                for(j = c.begin();j!=c.end() && gasit == 0;++j)
                {
                    if((**j).get_discount() != 0)
                        gasit = 1;
                }
                if(gasit == 0)
                {
                    for(j = c.begin();j!=c.end() && gasit == 0;++j)
                    {
                        cout<<"-------------------\n";
                        cout<<(**j);
                    }
                }
            }
            cout<<"-----------------------\n";
        }
        else if(optiune == 7)
        {
            exit = true;
            list<Ruta*>::iterator i;
            for(i = rute.begin();i!=rute.end();++i)
            {
                delete *i;
            }
        }
        else
        {
            cout<<"INPUT GRESIT\n";
        }
        system("pause");
        system("cls");
    }
}
int main()
{

    program();
    return 0;
}
