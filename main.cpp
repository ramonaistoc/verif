#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
ifstream f("fisier.txt");
class AFN
{
    int ok, sa;
    int nr_stari, nr_fin, nr_litere, nr_tranzitii;
    char *alfa;
    int *st_finale;

    struct tranz
    {
        int stare1, stare2;
        char litera;
    }*tr;

public:

  AFN()
    {
    int i;

    //cout<<"Nr literelor din alfabet este: ";
    f>>nr_litere;

    alfa=new char[nr_litere];
    //cout<<"Literele sunt: ";
    for(i=0;i<nr_litere;i++)
        f>>alfa[i];

    //cout<<"Numarul total de stari este: ";
    f>>nr_stari;

    //cout<<"Numarul starilor finale este: ";
    f>>nr_fin;

    st_finale=new int[nr_fin];
    //cout<<"Starile finale sunt: ";
    for(i=0;i<nr_fin;i++)
        f>>st_finale[i];

    //cout<<"Nr de tranzitii este: ";
    f>>nr_tranzitii;
    tr=new tranz[nr_tranzitii];

    for(i=0;i<nr_tranzitii;i++)
    {
        //cout<<"Introduceti starea1, litera si starea2: ";
        f>>tr[i].stare1>>tr[i].litera>>tr[i].stare2;
    }
    ok=0, sa=0;
}

    bool verificare(char *cuv, int poz, int sa);
};

bool AFN::verificare(char *cuv, int poz, int sa)
    { int n=strlen(cuv);
        int i;

       if( poz==n)        //daca am ajuns la sfarsitul cuv si starea actuala e finala
           {
            for(i=0;i<nr_fin;i++)                           //cunvantul e acceptat
              if(st_finale[i]==sa)
                {
                  ok=1;
                  return true;
                }
           }
      else
      {
          for(i=0;i<nr_tranzitii;i++)
            {

            if(ok==1)                       // verific din nou ok pt ca sunt 2 cond in if si una poate fi adev
             return true;

          if((tr[i].stare1==sa) && (tr[i].litera==cuv[poz]))    //verific daca starea actuala si litera se gasesc in vreun triplet
            verificare(cuv,poz+1,tr[i].stare2);                // in caz afirmativ, apleles functia pentru litera urmatoare
            }
      return false;
      }

    }

int main()
{
    AFN automat;

    if(automat.verificare("abbbac", 0, 0)==true)
        cout<<"da";
    else cout<<"nu";

    return 0;
}
