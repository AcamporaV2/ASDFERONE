#include <iostream>
#include <fstream>
#include <string>



using namespace std;

template<typename T, typename S>
struct Oggetto{

    T chiave;
    S valore;
    bool occupato;

    Oggetto() : occupato(false) {}
    Oggetto(T k, S v) : chiave(k), valore(v), occupato(true) {}

};


template<typename T, typename S>
class hashtable
{
    public: 
    int m;
    Oggetto<T,S>* tabella;

    hashtable(int size): m(size)
    {
        tabella = new Oggetto<T,S>[m];
    }

    int hash (T chiave)
    {
        return static_cast<unsigned char>(chiave) % m;
    }


    void inserisci(T chiave, S valore)
    {
        int idx = hash(chiave);
        int start = idx;

        while(tabella[idx].occupato == true)
        {
            if(tabella[idx].chiave == chiave)
            {
                tabella[idx].valore = valore;
                return;
            }
            idx = (idx +1) %m;

            if(idx == start)
            {
                cerr<< "pieno\n";
                return;
            }
        }
        tabella[idx] = Oggetto<T,S>(chiave, valore);
    }

    void stampa(ofstream &out)
        {
            for( int i = 0; i < m; i++)
                if(tabella[i].occupato)
                    out << tabella[i].chiave << "->" << tabella[i].valore << "\n";
        }

        // Legge coppie nel formato <chiave,valore> e le inserisce nella hash table.
        void leggiFile(const string& file)
        {
            ifstream in(file);
            char k;
            int  v;
            char c;
            while (in >> c && c == '<' && in >> k >> c && c == ',' && in >> v >> c && c == '>')
            {   
                inserisci(k,v);
            }
        }
};


int main()
{
    int M = 999;
    hashtable<char, int> Tabella1(M);

    Tabella1.leggiFile("IN.txt");
    ofstream out ("OUT.txt");

    out<< "tabella 1 \n";
    Tabella1.stampa(out);
}