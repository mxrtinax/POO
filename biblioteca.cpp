#include <iostream>
#include <fstream>
#include <cstdlib>
#include <typeinfo>
#include <vector>
#include <cstring>
using namespace std;
int cote[99999];//salveaza toate cotele articolelor din biblioteca

class Articol{ //clasa de baza
protected:
  int cota; //cota e unica
  int nrExemplare;
  string nume;
  static int nrTotalArticole;
public:
  Articol(const int cot,int nrE,const string num);
  ~Articol();

  void set_cota(int);
  void set_nrExemplare(int);
  int get_cota();
  int get_nrExemplare();
  void set_nume(const string&);
  const string& get_nume();

  virtual void afisare(ostream&) const;
  virtual void citire(istream&);

  friend istream& operator>>(istream& in, Articol & Art);
  friend ostream& operator<<(ostream& out, const Articol & Art);
  Articol& operator<(Articol& a);
  Articol & operator = (Articol & Art);

  virtual void foo(){}; // ca sa poti folosi dynamic_cast, ai nev in baza de o functie virtuala
  static void cresteNrTotalArticole(int nr){nrTotalArticole+=nr;}
  static void scadeNrTotalArticole(int nr){nrTotalArticole-=nr;}
  static int get_nrTotalArticole(){return nrTotalArticole;}
};

int Articol::nrTotalArticole = 0;

Articol::Articol(const int cot = 0, int nrE = 0,const string num=""):cota(cot),nrExemplare(nrE),nume(num){
}

Articol::~Articol(){
  this->cota = 0;
  this->nrExemplare = 0;
  this->nume = "";
}

void Articol::set_cota(int nr=0){
  this->cota = nr;
}

void Articol::set_nrExemplare(int nr=0){
  this->nrExemplare = nr;
}

int Articol::get_cota(){
  return this->cota;
}

int Articol::get_nrExemplare(){
  return this->nrExemplare;
}

void Articol::set_nume(const string& x){
  this->nume = x;
}

const string& Articol::get_nume(){
  return this->nume;
}

void Articol::afisare(ostream &out)const {
  cout<<"\nNume articol: "<<nume<<"\ncota: "<<cota<<"\nNr exemplare: "<<nrExemplare<<"\n";
}

void Articol::citire(istream &in){
  try{
  cout<<"nume: ";
  getline(in,nume);
  cout<<"cota: ";
  in>>cota;
  /*for(int i=1;i<=this->get_nrTotalArticole();i++)
    if(cota==cote[i]) throw(cota);*/
  cout<<"nrExemplare: ";  //initial voiam sa fac exit la o cota deja existenta
  in>>nrExemplare;        //dupa m am gandit ca mai bine sa verifc daca exista cota cu acelasi nume
}
catch (int x)
    {
        cout<<"Cota exista deja.\n";
        exit(EXIT_FAILURE);
    }
  cote[this->get_nrTotalArticole()+1] = cota;
}

istream& operator>>(istream & in, Articol &Art){
  Art.citire(in);
  return in;
}

ostream& operator<<(ostream& out,const Articol& Art){
  Art.afisare(out);
  return out;
}

Articol& Articol::operator = (Articol& Art){
  this->cota = Art.cota;
  this->nrExemplare = Art.nrExemplare;
  this->nume = Art.nume;
  return *this;
}

Articol& Articol::operator<(Articol& a){
  if(this->get_nrExemplare()<a.get_nrExemplare())
    return *this;
  return a;
}

bool compare(Articol& a1, Articol& a2){
  return a1.get_nrExemplare() < a2.get_nrExemplare();
}

//-----------------------------------------------------------------------------

class Carte:public Articol{
protected:
  string editura;
public:
  Carte(const int cot, int nrE, const string &num, const string &ed);
  virtual ~Carte(); // nu era nevoie
  Carte &operator=(const Carte& crt);
  const string& get_der(){return editura;}
  void set_der(string& ed){editura=ed;}
  void citire(istream&);
  void afisare(ostream&);
  friend istream& operator>>(istream& in, Carte& crt);
  friend ostream& operator<<(ostream& out, Carte&crt);
  Carte & operator = (Carte &crt);
};

Carte::Carte(const int cot = 0, int nrE = 0, const string &num="", const string &ed=""):Articol(cot, nrE, num), editura(ed){}

Carte::~Carte(){
  editura = "";
}
void Carte::citire(istream& in){
  cout<<"Editura: ";
  cin.get();
  getline(in,editura);
  Articol::citire(in);
}

void Carte::afisare(ostream& out){
  Articol::afisare(out);
  out<<"Editura: "<<editura;
}

istream& operator>>(istream& in, Carte& crt){
  crt.citire(in);
  return in;
}

ostream& operator<<(ostream& out, Carte& crt){
  crt.afisare(out);
  return out;
}

  Carte& Carte::operator=(Carte& crt){
    Articol::operator=(crt);
    this->editura = crt.editura;
  }

class CD:public Articol{
  string tip;
public:
  CD(const int cot=0, int nrE=0, const string &num="",const string &tip=""):Articol(cot,nrE,num),tip(tip){};
  ~CD();
  void get_der(){cout<<tip<<"\n";}
  void citire(istream& in);
  void afisare(ostream& out);
  friend istream& operator>>(istream& in, CD& cd);
  friend ostream& operator<<(ostream& out, CD& cd);
  CD & operator = (CD & cd);
};

CD::~CD(){
  tip="";
}

void CD::citire(istream& in){
  try{
    cout<<"Tip (CD/DVD): ";
    in>>tip;
    cin.get();
    if(tip!="CD" && tip!= "DVD") throw(tip);
    Articol::citire(in);
  }

  catch(string x){
    cout<<"insertie nevalida!\n";
    exit(EXIT_FAILURE);
  }
}

void CD::afisare(ostream& out){
  Articol::afisare(out);
  out<<"Tip: "<<tip;
}

istream& operator>>(istream& in, CD& cd){
  cd.citire(in);
  return in;
}

ostream& operator<<(ostream& out, CD& cd){
  cd.afisare(out);
  return out;
}

CD& CD::operator=(CD&cd){
  Articol::operator=(cd);
  this->tip = cd.tip;
}

class Revista: public Articol{
protected:
  int lunaAparitie;
public:
  Revista(const int cot = 0, int nrE = 0, const string &num="", int lA=0):Articol(cot,nrE,num), lunaAparitie(lA){}
  ~Revista();
  void get_der(){cout<<lunaAparitie<<"\n";}
  void citire(istream& in);
  void afisare(ostream& out);
  friend istream& operator>>(istream& in, Revista& rev);
  friend ostream& operator<<(ostream& out, Revista& rev);
  Revista & operator = (Revista & rev);
};

Revista::~Revista(){
  lunaAparitie = 0;
}
void Revista::citire(istream& in){
  try{
    cin.get();
    Articol::citire(in);
    cout<<"Luna aparitie (1/2/../12): ";
    in>>lunaAparitie;
    if(lunaAparitie<1 || lunaAparitie>12) throw(lunaAparitie);
  }
  catch(int x){
    cout<<"insertie nevalida!\n";
    exit(EXIT_FAILURE);
  }
}

void Revista::afisare(ostream& out){
  Articol::afisare(out);
  out<<"Luna aparitie: "<<lunaAparitie<<"\n";
}

istream& operator>>(istream& in, Revista& rev){
  rev.citire(in);
  return in;
}

ostream& operator<<(ostream& out, Revista& rev){
  rev.afisare(out);
  return out;
}

Revista& Revista::operator=(Revista &rev){
  Articol::operator=(rev);
  this->lunaAparitie=rev.lunaAparitie;
}

class Biblioteca{
protected:
  vector <Articol*> articole;  //salvam intr un vector pointeri la articole - upcast
  char nume[200];
public:
  Biblioteca();
  ~Biblioteca();
  const void get_nume(){cout<<nume;}
  void citire(istream &in);
  void addArticol(Articol*&x);
  void imprumutaArticol(int);
  void restituieArticol(int);
  void printArticole();
  void add_n_articole();
  void tipuri_articole();
  friend istream& operator>>(istream&in, Biblioteca& bib);
};

Biblioteca::Biblioteca(){
  nume[0]='\0';
}

Biblioteca::~Biblioteca(){
  for(int i=0;i<articole.size();i++)
    delete articole[i];
  articole.clear();
  nume[0]='\0';
}

void Biblioteca::citire(istream& in){
  cout<<"Nume Biblioteca: ";
  cin.get(nume,200);
}

istream& operator>>(istream&in, Biblioteca &bib){
  bib.citire(in);
  return in;
}

void Biblioteca:: addArticol(Articol*&art){
  int i, ok=0;
  for(i=0;i<articole.size() && ok==0;i++)  // verificam daca cota si numele exista deja in biblioteca
    if(articole[i]->get_cota()==art->get_cota()) // daca da, adaugam exemplare la acelasi articol pentru a evita dublicatele
      if(articole[i]->get_nume()==art->get_nume()){
        articole[i]->set_nrExemplare(articole[i]->get_nrExemplare()+art->get_nrExemplare());
        ok=1;
      }
      else{cout<<"Cota este deja folosita\n";
            ok=1;
          art->scadeNrTotalArticole(art->get_nrExemplare());} //daca cota e folosita deja la alt articol, trebuie scazut din nr total de articole, nr de exemplare introduse acum


  if(ok==0) // daca cota nu exista, adaugam articol in vector
    articole.push_back(art);
}

void Biblioteca::add_n_articole(){
  int n;
  string tip;
  cout<<"Cate articole introduceti? ";
  cin>>n;
  for(int i=1;i<=n;i++)
    {
      cout<<"Tipul articolului "<<i<<" (carte/cd/revista): ";
      cin>>tip;
      try{//upcasting
      if(tip=="carte"){
        Articol*c = new Carte;
        cin>>*c;
        c->cresteNrTotalArticole(c->get_nrExemplare());
        this->addArticol(c);
       }

      if(tip=="cd"){
       Articol*cd = new CD;
       cin>>*cd;
       cd->cresteNrTotalArticole(cd->get_nrExemplare());
      this->addArticol(cd);
      }
      if(tip=="revista"){
        Articol*r = new Revista;
        cin>>*r;
        r->cresteNrTotalArticole(r->get_nrExemplare());
        this->addArticol(r);
       }
       if(tip!="carte" && tip!="cd" && tip!="revista") throw(tip);
     }
     catch(string x){
       cout<<"insertie nevalida!\n";
       exit(EXIT_FAILURE);
     }
  }
}

void Biblioteca::printArticole(){
  //sort(articole.begin(), articole.end());
  for(int i=0;i<articole.size();i++){        //downcast
    if(typeid(*articole[i])==typeid(Carte)){
      cout<<i+1<<"\nTip articol: Carte";
      Carte *c;
      c=static_cast<Carte*>(articole[i]);
      cout<<*c<<"\n";
    cout<<"-------------------------\n";
    }
    if(typeid(*articole[i])==typeid(CD)){
      cout<<i+1<<"\nTip articol: CD";
      CD *cd;
      cd=static_cast<CD*>(articole[i]);
      cout<<*cd<<"\n";
    cout<<"-------------------------\n";
    }
    if(typeid(*articole[i])==typeid(Revista)){
      cout<<i+1<<"\nTip articol: Revista";
      Revista *r;;
      r=static_cast<Revista*>(articole[i]);
      cout<<*r<<"\n";
    cout<<"-------------------------\n";
    }
  }
}

void Biblioteca::imprumutaArticol(int cod){
  int i;
  for(i=0;i<articole.size();i++){
    if(articole[i]->get_cota()==cod)
      if(articole[i]->get_nrExemplare()>0)
        {articole[i]->set_nrExemplare(articole[i]->get_nrExemplare()-1);
          cout<<"carte extrasa!\n";
        break;}
        else{cout<<"momentan articolul este idisponibil!\n"; break;}
  }
  if(i==articole.size())cout<<"cod nevalid!\n";
}

void Biblioteca::restituieArticol(int cod){
  int i, r;
  for(i=0;i<articole.size();i++){
    if(articole[i]->get_cota()==cod){
      cout<<"doriti sa restituiti "<<articole[i]->get_nume()<<"? (1/0) ";
      cin>>r;
      if(r==1){
          articole[i]->set_nrExemplare(articole[i]->get_nrExemplare()+1);
          cout<<"carte restituita!\n";
          break;
        }
        else {cout<<"anulat\n"; break;}
      }
  }
  if(i==articole.size())cout<<"cod nevalid!\n";
}

void Biblioteca::tipuri_articole(){
  int nr_carti=0, nr_cduri=0,nr_reviste=0;
  int n = articole.size();
  if(n>0){
    for(int i=0;i<n;i++){
      Carte *a1 = dynamic_cast<Carte*>(articole[i]);
      CD *a2 = dynamic_cast<CD*>(articole[i]);
      Revista *a3 = dynamic_cast<Revista*>(articole[i]);
      if(a1)
        nr_carti+=a1->get_nrExemplare();
      if(a2)
        nr_cduri+=a2->get_nrExemplare();
      if(a3)
        nr_reviste+=a3->get_nrExemplare(); //downcast
  }
  cout<<"Numar total carti: "<<nr_carti<<"\n";
  cout<<"Numar total cd-uri: "<<nr_cduri<<"\n";
  cout<<"Numar total reviste: "<<nr_reviste<<"\n";
}
else cout<<"Nu s-au citit articole. Introduceti prima data articole in biblioteca.\n";
}


menu(){
  int raspuns;
  string tip;
  Articol gol;
  cout<<"Creare biblioteca\n";
  Biblioteca B;
  cin>>B;
  cout<<"0. Inchide program\n";
  cout<<"1. Adaugati articole in biblioteca\n";
  cout<<"2. Afisare situatie Biblioteca\n";
  cout<<"3. Imprumuta articol\n";
  cout<<"4. Restituie articol\n";
  cout<<"5. Tipuri articole\n";
  cout<<"Nr. actiune: ";
  cin>>raspuns;
  while(raspuns!=0){

    if(raspuns==1){
      B.add_n_articole();
    }

    if(raspuns==2){
      cout<<"     Biblioteca ";
      B.get_nume();
      cout<<"\n========================================\n";
      cout<<"Un total de "<<gol.get_nrTotalArticole()<<" articole.\n";
      B.printArticole();
    }

    if(raspuns==3){
      int cod;
      cout<<"introduceti codul articolului de imprumutat: ";
      cin>>cod;
      B.imprumutaArticol(cod);
    }

    if(raspuns==4){
      int cod;
      cout<<"introduceti codul articolului de restituit: ";
      cin>>cod;
      B.restituieArticol(cod);
    }
    if(raspuns==5){
      B.tipuri_articole();
    }
    if(raspuns==6){
    }

    system("pause");
    system("cls");
    cout<<"0. Inchide program\n";
    cout<<"1. Adaugati articole in biblioteca\n";
    cout<<"2. Afisare situatie Biblioteca\n";
    cout<<"3. Imprumuta articol\n";
    cout<<"4. Restituie articol\n";
    cout<<"5. Tipuri articole\n";
    cout<<"Nr. actiune: ";
    cin>>raspuns;
  }
}

int main(){
  menu();
  return 0;
}
