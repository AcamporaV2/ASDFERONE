/*
Utilizzando il paradigma della programmazione ad oggetti ed il linguaggio C++ 11, progettare ed implementare, come classe, 
una struttura dati hash table con concatenamento che consenta di memorizzare le coppie < int, string > contenute nei file IN1.txt ed IN2.txt (una istanza di hash table per ogni file). 
Dotare la classe di un metodo PRINT per scrivere nel file OUT.txt 
il contenuto delle hash table (in ogni riga del file scrivere il contenuto di una cella delle hash table). (pt. 18


*/


#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>

using namespace std;

// Classe template per una hash table con concatenamento.
// K = tipo chiave, V = tipo valore.
template<typename K, typename V>
class HashConc{
    public:
        int m; // numero di celle (bucket)
        vector<list<pair<K,V>>> table; // ogni cella contiene una lista di coppie <chiave, valore>

        // Costruttore: crea una tabella di dimensione "size".
        HashConc(int size): m(size), table(size) {}

        // Funzione hash base: usa il resto della divisione per m.
        int hash(K key)
        {
            return key % m;
        }

        // Inserisce una coppia <key, val> nella tabella.
        // Se la chiave esiste gia, aggiorna il valore.
        void insert(K key, V val){
            int idx = hash(key); // calcola la cella dove inserire

            // Cerca la chiave nella lista della cella.
            for(auto& item:table[idx]){
                if(item.first ==key){
                    item.second = val; // chiave trovata: aggiorna il valore
                    return; // termina
                }
            }

            // Chiave non trovata: aggiunge una nuova coppia in fondo alla lista.
            table[idx].push_back({key,val});
        }

        // Stampa tutti gli elementi della tabella su uno stream (es. file).
        void print(ostream&out){
            // Scorre tutte le celle.
            for(int i = 0; i < m; ++i)
                // Stampa ogni coppia presente nella lista della cella i.
                for(auto& item:table[i])
                    out << item.first << "-> " << item.second << "\n";
        }
        
        // Controlla se una chiave e presente nella tabella.
        bool contains(K key){
            int idx = hash(key); // calcola la cella

            // Cerca la chiave nella lista della cella.
            for(auto& item: table[idx])
                if(item.first == key) return true;
            return false;
        }

        // Restituisce il puntatore al valore associato alla chiave.
        // Se non esiste, restituisce nullptr.
        V* find(K key){
            int idx = hash(key); // calcola la cella

            // Cerca la chiave nella lista della cella.
            for(auto& item:table[idx]){
                if(item.first == key) return &(item.second);
            }
            return nullptr;
        }

        
};

// Verifica se due hash table sono disgiunte rispetto alle chiavi.
// Ritorna true se non hanno nessuna chiave in comune.
bool disjoint(HashConc<int,string>&A,HashConc<int,string>&B){
    // Scorre tutte le celle della tabella A.
    for(int i = 0; i < A.m; i++)
        // Scorre tutte le coppie nella cella i.
        for(auto& row:A.table[i])
            // Se B contiene la stessa chiave, non sono disgiunte.
            if(B.contains(row.first)) return false;
    return true;
}

// Legge da file coppie nel formato <chiave,valore> e le inserisce nella hash table.
void readFile(HashConc<int, string>&H, string file){
    ifstream in(file); // apre il file di input
    int k; // chiave intera
    string v; // valore stringa
    char c; // carattere di supporto per leggere < , >

    // Legge finche trova coppie nel formato previsto.
    while(in >> c && c == '<' && in >> k >> c && c == ','){
        getline(in,v,'>'); // legge il valore fino al carattere '>'
        H.insert(k,v); // inserisce la coppia nella hash table
    }
}





int main()
{
    int M = 999; // dimensione della tabella hash

    // Crea due hash table: una per input1 e una per input2.
    HashConc<int,string>H1(M), H2(M);

    // Carica i dati dai due file di input.
    readFile(H1, "input1.txt");
    readFile(H2,"input2.txt");

    // Apre il file di output.
    ofstream out("output.txt");

    // Scrive se le due tabelle sono disgiunte oppure no.
    out << (disjoint(H1,H2) ? "Disgiunte\n": "Non Disgiunte\n");

    // Stampa il contenuto della prima tabella.
    out << "Tabella 1: \n"; 
    H1.print(out);

    // Stampa il contenuto della seconda tabella.
    out << "Tabella 2: \n";
    H2.print(out);

    // Fine programma.
    return 0;
}