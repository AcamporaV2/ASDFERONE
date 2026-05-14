/*

Utilizzando il paradigma della programmazione ad oggetti ed il linguaggio C++ 11, progettare ed implementare, 
come classe, una struttura dati hashtable con indirizzamento aperto che consente di memorizzare le coppie < int, string > contenute nel file IN.txt. 
Dotare la classe di un metodo PRINT per scrivere nel file OUT.txt il contenuto della hash table. (pt 18)

Implementare il metodo FIND(int) che restituisce in output la stringa associata alla chiave passata come argomento. (pt. 6)

Implementare il metodo DELETE(int) che consente di eliminare la coppia < int, string > associata alla chiave passata come argomento (dopo la cancellazione visualizzare a video il contenuto della hash table).
*/



#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum Status { EMPTY, ACTIVE, DELETED };

template <typename T, typename V>
struct Oggetto{

    int chiave;
    string valore;
    bool stato;


    Oggetto() : stato(false) {}

    Oggetto(T key, V value): chiave(key), valore(value), stato(true) {}

};


template<typename T, typename V>
struct Hash{
    public:
        int m;
        Oggetto<T,V>* tabella;

        Hash(int size): m(size)
        {
            tabella= new Oggetto<T,V>[m];
        }
        
        int hash(T chiave)
        {
            return chiave % m;
        }

        void insert(T chiave, V valore)
        {
            int idx = hash(chiave);
            int start = idx;

            while(tabella[idx].stato)
            {
                if(tabella[idx].chiave == chiave)
                {
                    tabella[idx].valore = valore;
                    return;
                }
                idx = (idx + 1) %m;

                if(idx == start)
                {
                    cerr << "Pieno\n";
                    return;
                }
            }
            tabella[idx] = Oggetto<T,V>(chiave, valore);
        }

        void stampa(ofstream & out)
        {
            for(int i = 0; i < m; i++)
            {
                if(tabella[i].stato)
                {
                    out << tabella[i].chiave << "->" << tabella[i].valore << "\n";
                }
            }
        }

        void leggifile(const string& file)
        {
            ifstream in(file);
            int k;
            string v;
            char c;

            while(in >> c && c == '<' && in >> k >> c && c == ',')
            {
                getline(in,v,'>');
                insert(k,v);
            }
            
        }

    //PARTE 2 DA 6 PUNTI 
    //-------------------------------------------------------------------------------------------
        V* find (T chiave)
        {
            int idx = hash(chiave);
            int start = idx;

            while(tabella[idx].stato)
            {
                if(tabella[idx].chiave == chiave)
                {
                    return &(tabella[idx].valore);
                }
                idx = (idx + 1) %m;

                if(idx == start)
                    break;
            }
            return nullptr;
        }
    //PARTE 3 DA 6 PUNTI
    //------------------------------------------------------------------------------------------
        bool remove(T chiave)
        {
            int idx = hash(chiave);
            int start = idx;

            while(tabella[idx].stato)
            {
                if(tabella[idx].chiave == chiave)
                {
                    tabella[idx].stato = false;
                    return true;
                }
                idx = (idx+1) %m;
                if (idx == start)
                    break;
            }
            return false;
        }
};



int main()
{
    int M = 999;
    Hash<int,string>Hash1(M);

    Hash1.leggifile("IN.txt");

    ofstream out("OUT.txt");

    out << "Tabella 1\n";
    Hash1.stampa(out);

    int chiaveRicerca;
    cout << "Inserisci la chiave da ricercare: ";
    cin >> chiaveRicerca;

    string* valoreTrovato = Hash1.find(chiaveRicerca);

    if(valoreTrovato)
        cout << "Trovata la chiave" << chiaveRicerca <<" valore: " << *valoreTrovato<< "\n";
    else 
        cout <<"Non ho trovato la chiave\n";


    int chiaveElimnare;
    cout<< "Inserisci la chiave da rimuovere";
    cin >> chiaveElimnare;

    if(Hash1.remove(chiaveElimnare))
        cout <<"chiave eliminata\n";
    else 
        cout << "chiave non trovata\n";


    out << "\ntabella 2\n";
    Hash1.stampa(out);
}