#include <iostream>
using namespace std;
class Nod
    {
        int info;
        Nod *next;
    public:
        //constructori si destructori
        Nod ()
        {
            next = NULL;
        }
        Nod (int intreg)
        {
            info = intreg;
            next = NULL;
        }
        Nod (const Nod &nod)
        {
            info = nod.info;
            next = nod.next;
        }
        virtual ~Nod ()
        {
            /*info = 0;
            delete next;*/
        }
        //operatori
        Nod operator= (Nod nod)
        {
            info = nod.info;
            delete next;
            next = nod.next;
            return *this;
        }
        friend istream& operator>> (istream &in, Nod &nod)
        {
            in>>nod.info;
            nod.next = NULL;
            return in;
        }
        friend ostream& operator<< (ostream &out, Nod &nod)
        {
            out<<nod.info;
            return out;
        }
        //getteri setteri
        int Getinfo(){return info;}
        virtual Nod *Getnext(){return next;}
        void Setinfo(int aux){info = aux;}
        void Setnext (Nod *aux){next = aux;}
        //fuctii
    };

class Nod_dublu: public Nod
    {
        Nod *ante;
    public:
        //constructori si destructori
        Nod_dublu(): Nod()
        {
            ante = NULL;
        }
        Nod_dublu(int intreg): Nod(intreg)
        {
            ante = NULL;
        }
        Nod_dublu(const Nod_dublu &nod): Nod(nod)
        {
            ante = NULL;
        }
        ~Nod_dublu()
        {
            /*delete ante;
            this -> Setinfo(0);
            delete this -> Getnext();*/
        }
        //operatori
        Nod_dublu operator= (Nod_dublu nod)
        {
            delete ante;
            delete this -> Getnext();
            this -> Setinfo(nod.Getinfo());
            ante = NULL;
            this -> Setnext(NULL);
            return *this;
        }

        friend istream& operator>>(istream &in, Nod_dublu &nod)
        {

            nod.ante = NULL;
            nod.Setnext(NULL);
            int intreg;
            in >> intreg;
            nod.Setinfo(intreg);
            return in;
        }

        friend ostream& operator<<(ostream &out, Nod_dublu &nod)
        {
            out<<nod.Getinfo();
            return out;
        }
        bool operator> (Nod_dublu nod)
        {
            if(this -> Getinfo() > nod.Getinfo())
                return 1;
            else
                return 0;
        }
        bool operator< (Nod_dublu nod)
        {
            if(this -> Getinfo() < nod.Getinfo())
                return 1;
            else
                return 0;
        }
        int operator- (Nod_dublu nod)
        {
            return this -> Getinfo() - nod.Getinfo();
        }
        //get/set
        Nod *Getante(){return ante;}
        void Setante(Nod *aux) {ante = aux;}
        // functii
    };

class Comparator
{
public:
    virtual int compare (Nod_dublu x, Nod_dublu y) = 0;
    virtual void Gettype() = 0;
};
class Crescator: public Comparator
{
public:
    int compare(Nod_dublu x, Nod_dublu y)
    {
        return x - y;
    }
    void Gettype() {cout<<"C";}
};
class Descrescator: public Comparator
{
public:
    int compare(Nod_dublu x, Nod_dublu y)
    {
        return y - x;
    }
    void Gettype(){cout<<"D";}
};

    class Lista
    {
        Nod_dublu *u;
        Nod_dublu *p;
        int n;
    public:
        //constructori si destructor
        Lista ()
        {
            n = 0;
            p = new Nod_dublu;
            u = p;
        }
        Lista (int intreg)
        {
            n = 1;
            p = new Nod_dublu; // cred ca nu e nevoie sa initializez si next si ante cu null
            // ma gandesc ca se apeleaza si constructorul din Nod_dublu, nu?
            p -> Setinfo(intreg);
            u = p;
        }
        Lista (const Lista &li)
        {
            n = li.n;
            Nod_dublu *i,*aux;
            p = new Nod_dublu(li.p -> Getinfo());
            u = p;
            i = li.p;
            i = dynamic_cast<Nod_dublu *>(i -> Getnext());
            while(i != NULL)
            {
                aux = new Nod_dublu;
                u -> Setnext(aux);
                aux = u;
                u = dynamic_cast<Nod_dublu *>(u -> Getnext());
                u -> Setinfo(i -> Getinfo());
                u -> Setante(aux);
                i = dynamic_cast<Nod_dublu *>(i -> Getnext());
            }
        }
        virtual ~Lista()
        {
            //cout<<"Lista\n ";
            Nod_dublu *i;
            i = p;
            while(i != NULL && n != 0) //sa incerci sa il verifici cu u
            {
                --n;
                Nod_dublu *j = i;
                i = dynamic_cast<Nod_dublu *>(i -> Getnext());
                delete j;
            }

        }
        //operatori
        Lista &operator= (Lista &li)
        {
            //stergem lista deja existenta
            n = 0;
            Nod_dublu *i,*j;
            i = p;
            j = i;
            i = dynamic_cast<Nod_dublu *>(i -> Getnext());
            delete j;
            while(i != NULL)
            {
                j = i;
                i = dynamic_cast<Nod_dublu *>(i -> Getnext());
                delete j;
            }
            //acum facem atribuirea
            n = li.n;
            p = new Nod_dublu(li.p -> Getinfo());
            u = p;
            i = li.p;
            i = dynamic_cast<Nod_dublu *>(i -> Getnext());
            while(i != NULL)
            {
                this -> adauga(i -> Getinfo());
                i = dynamic_cast<Nod_dublu *>(i -> Getnext());
            }
            return *this;
        }

        friend istream& operator>>(istream &in, Lista &li)
        {
            //stergem in caz ca exista ceva in lista li
            li.n = 0;
            Nod_dublu *i,*j;
            i = li.p;
            j = i;
            j = dynamic_cast<Nod_dublu *>(i -> Getnext());
            delete i;
            while(j != NULL)
            {
                i = j;
                j = dynamic_cast<Nod_dublu *>(i -> Getnext());
                delete i;
            }

            int intreg, h;
            in >> li.n;
            in >> intreg;
            li.p = new Nod_dublu(intreg);
            li.u = li.p;
           for(h=1;h<li.n;++h)
            {
                in >> intreg;
                li.adauga(intreg);
            }
            return in;
        }
        friend ostream& operator<<(ostream &out, Lista &li)
        {
            Nod_dublu *i;
            i = li.p;
            while(i != NULL)
            {
                out << i -> Getinfo() << " ";
                i = dynamic_cast<Nod_dublu *>(i -> Getnext());
            }
            return out;
        }
        //functii
        virtual void adauga(int intreg, bool creste_n = false)
        {
            Nod_dublu *aux;
            aux = new Nod_dublu;
            if(n == 0)
            {
                p = aux;
            }
            u -> Setnext(aux);
            aux = u;
            u = dynamic_cast<Nod_dublu *>(u -> Getnext());
            u -> Setinfo(intreg);
            u -> Setante(aux);
            u -> Setnext(NULL);
            if (creste_n)
                ++n;
        }
        virtual void sortare(bool ok)
        {
            Comparator *aux;
            if(ok)
                aux = new Crescator;
            else
                aux = new Descrescator;
            //aux -> Gettype();
            Nod_dublu *i,*j;
            int s;
            i = p;
            while(i != u)
            {
                j = dynamic_cast<Nod_dublu *>(i -> Getnext());
                while(j != p)
                {
                    if(aux -> compare(i -> Getinfo(), j -> Getinfo()) > 0)
                    {
                        s = i -> Getinfo();
                        i -> Setinfo(j -> Getinfo());
                        j -> Setinfo(s);
                    }
                    j = dynamic_cast<Nod_dublu *>(j -> Getnext());
                }
                i = dynamic_cast<Nod_dublu *>(i -> Getnext());
            }
        }
        //getteri setteri
        int Getn(){return n;}
        void Setn(int intreg){n = intreg;}
        Nod_dublu *Getu(){return u;}
        Nod_dublu *Getp(){return p;}
        void Setp(Nod_dublu *aux){p = aux;}
        void Setu(Nod_dublu *aux){ u = aux;}
    };

class Lista_circulara: public Lista
{
    static Nod_dublu *maxim;
    static int ma;
public:
    Lista_circulara():Lista(){}
    Lista_circulara(int intreg):Lista(intreg)
    {
        Getu() -> Setnext(Getp());
        Getu() -> Setante(Getp());
        //cout<<"CI L_C \n";
        if(Getn() > ma)
        {
            ma = Getn();
            maxim = Getp();
        }
    }
    Lista_circulara(Lista_circulara &lic)
    {
        Setn(lic.Getn());
        Nod_dublu *i,*aux;
        Setp(new Nod_dublu(lic.Getp() -> Getinfo()));
        Setu(Getp());
        Getu() -> Setnext(Getp());
        Getu() -> Setante(Getp());
        i = lic.Getp();
        i = dynamic_cast<Nod_dublu *>(i -> Getnext());
        while(i != lic.Getp())
        {
            aux = new Nod_dublu;
            Getu() -> Setnext(aux);
            aux = Getu();
            Setu(dynamic_cast<Nod_dublu *>(Getu() -> Getnext()));
            Getu() -> Setinfo(i -> Getinfo());
            Getu() -> Setante(aux);
            Getu() -> Setnext(Getp());
            i = dynamic_cast<Nod_dublu *>(i -> Getnext());
        }
    }
    ~Lista_circulara() //s ar putea sa fie ceva gresit aici
    {
        /*Setn(0);
            Nod_dublu *i,*j;
            i = Getp();
            j = i;
            j = dynamic_cast<Nod_dublu *>(i -> Getnext());
            delete i;
            while(j != NULL)
            {
                i = j;
                j = dynamic_cast<Nod_dublu *>(i -> Getnext());
                delete i;
            }*/
            //cout<<"Lista_circulara ";
    }
    //operatori
    Lista_circulara &operator= (Lista_circulara &lic)
    {
        //stergem ce se afla in lista initiala
        Setn(0);
            Nod_dublu *i,*j;
            i = Getp();
            j = i;
            j = dynamic_cast<Nod_dublu *>(i -> Getnext());
            delete i;
            while(j != NULL)
            {
                i = j;
                j = dynamic_cast<Nod_dublu *>(i -> Getnext());
                delete i;
            }

        Setn(lic.Getn());
        Nod_dublu *aux;
        Setp(new Nod_dublu(lic.Getp() -> Getinfo()));
        Setu(Getp());
        Getu() -> Setnext(Getp());
        Getu() -> Setante(Getp());
        i = lic.Getp();
        i = dynamic_cast<Nod_dublu *>(i -> Getnext());
        while(i != lic.Getp())
        {
            aux = new Nod_dublu;
            Getu() -> Setnext(aux);
            aux = Getu();
            Setu(dynamic_cast<Nod_dublu *>(Getu() -> Getnext()));
            Getu() -> Setinfo(i -> Getinfo());
            Getu() -> Setante(aux);
            Getu() -> Setnext(Getp());
            i = dynamic_cast<Nod_dublu *>(i -> Getnext());
        }
    }
    friend istream &operator>>(istream &in, Lista_circulara &lic)
    {
        //stergem in caz ca exista ceva in lic
        lic.Setn(0);
        Nod_dublu *i,*j;
        i = lic.Getp();
        j = i;
        j = dynamic_cast<Nod_dublu *>(i -> Getnext());
        delete i;
        while(j != NULL)
        {
            i = j;
            j = dynamic_cast<Nod_dublu *>(i -> Getnext());
            delete i;
        }

        int intreg, h;
        in >> intreg;
        lic.Setn(intreg);
        in >> intreg;
        lic.Setp(new Nod_dublu(intreg));
        lic.Setu(lic.Getp());
        lic.Getu() -> Setnext(lic.Getp());
        lic.Getu() -> Setante(lic.Getp());
        for(h=1;h<lic.Getn();++h)
        {
            in >> intreg;
            lic.adauga(intreg);
        }
        if(lic.Getn() > ma)
        {
            ma = lic.Getn();
            maxim = lic.Getp();
        }
            return in;
    }
    friend ostream &operator<<(ostream &out, Lista_circulara &lic)
    {
        Nod_dublu *i;
        i = lic.Getp();
        out << i -> Getinfo() << " ";
        i = dynamic_cast<Nod_dublu *>(i -> Getnext());
        while(i != lic.Getp())
        {
            out << i -> Getinfo() << " ";
            i = dynamic_cast<Nod_dublu *>(i -> Getnext());
        }
        out << '\n';
        return out;
    }
    int operator[] (int intreg)
    {
        int j;
        Nod_dublu *i;
        i = Getp();
        for(j = 1; j < intreg; ++j)
            i = dynamic_cast<Nod_dublu *>(i -> Getnext());
        return i -> Getinfo();
    }
    //functii
    void adauga(int intreg, bool creste_n = false)
    {
        Lista::adauga(intreg, creste_n);
        Nod_dublu *i,*j;
        i = Getp();
        j = Getu();
        j -> Setnext(i);
        i -> Setante(j);
        if(creste_n && Getn() > ma)
        {
            ma = Getn();
            maxim = Getp();
        }
    }
    void sortare(bool ok)
    {
        Lista::sortare(ok);
    }
    static int Getma() {return ma;}
    static Nod_dublu *Getmaxim() {return maxim;}
};

int Lista_circulara :: ma = 0;
Nod_dublu *Lista_circulara :: maxim = NULL;


int indicele_listei(int numar)
{
    int intreg;
    cout<<"Alege indicele listei dorite: ";
    cin >> intreg;
    while(intreg > numar)
    {
        cout<<"Indice invalid!";
        cout<<"\nIntroduceti alt indice: ";
        cin>>intreg;
    }
    return intreg;
}
int main()
{
    Lista_circulara v[101];
    int numar, i, comanda, nr, j;
    cin >> numar;
    for(i = 1; i <= numar; ++i)
        cin>>v[i];
    for(i=1;i<=numar;++i)
        cout<<v[i];

    cout<<"Meniu: \n"<<"0. Exit\n"<<"1. Indicele numarul aflat pe indicele castigator conform problemei lui Josephus \n";
    cout<<"2. Adauga un element unei liste \n"<<"3. Afiseaza cea mai lunga lista circulara\n"<<"4. Afiseaza o lista la alegere\n";
    cout<<"5. Sorteaza o lista la alegere\n";
    cout<<"Alege actiunea dorita: ";
    while(cin>>comanda)
    {
    if(comanda == 0)
    {
        return 0;
    }
    else if(comanda == 1)
    {
        i = indicele_listei(numar);
        nr = v[i].Getn();
        j = 1;
        while(j <= nr)
            j = j * 2;
        nr = (nr - j/2) * 2 + 1;
        cout<<"Raspunsul este: "<<v[i][nr]<<'\n';
    }
    else if(comanda == 2)
    {
        i = indicele_listei(numar);
        cout<<"Scrie valoarea pe care vrei sa o adaugi: ";
        cin>>nr;
        v[i].adauga(nr,true);
        cout<<"Acum lista a "<<i<<"-a este: "<<v[i]<<'\n';
    }
    else if(comanda == 3)
    {
        Nod_dublu *auxi1, *auxi2;
        auxi1 = v[1].Getmaxim();
        cout<<"Cea mai lunga lista are: "<<v[1].Getma()<<" elemente, iar acestea sunt: "<< auxi1 -> Getinfo()<< " ";
        auxi2 = dynamic_cast <Nod_dublu *>(auxi1 -> Getnext());
        while(auxi2 != auxi1)
        {
            cout<<auxi2 -> Getinfo()<<" ";
            auxi2 = dynamic_cast <Nod_dublu *>(auxi2 -> Getnext());
        }
        cout<<'\n';
    }
    else if (comanda == 4)
    {
        i = indicele_listei(numar);
        cout<<"Lista aleasa are elementele: ";
        cout<<v[i]<<'\n';
    }
    else if (comanda == 5)
    {
        i = indicele_listei(numar);
        cout<<"Pentru sortare crescatoare introduceti codul: 1\n";
        cout<<"Pentru sortare descrescatoare introduceti codul: 0\n";
        cout<<"Introduceti codul dorit: ";
        bool ok;
        cin>>ok;
        v[i].sortare(ok);
        cout<<"Ati sortat lista "<<i<<", care acum este: ";
        cout<<v[i];
    }
    else
    {
        cout<<"Alegere invalida!\n";
    }
    cout<<"Alege actiunea dorita: ";
    }

    return 0;
}
