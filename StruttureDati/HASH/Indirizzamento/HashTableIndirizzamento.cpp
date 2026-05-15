/*
Utilizzando il paradigma della programmazione ad oggetti ed il linguaggio C++ 11,
progettare ed implementare, come classe, una struttura dati hashtable con
indirizzamento aperto che consente di memorizzare le coppie < int, string >
contenute nel file IN.txt. Dotare la classe di un metodo PRINT per scrivere nel file
OUT.txt il contenuto della hash table

. Implementare il metodo FIND(int) che restituisce in output la stringa associata
alla chiave passata come argomento.(pt. 6)

. Implementare il metodo DELETE(int) che consente di eliminare la coppia < int,
string > associata alla chiave passata come argomento (dopo la cancellazione
visualizzare a video il contenuto della hash table)

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum Status {EMPTY, ACTIVE, DELETED};

template <typename K, typename V>
struct Item{
    K key;
    V value;
    Status stato = EMPTY;
    Item() {}
    Item(K k, V v) : key(k), value(v), stato(ACTIVE) {}
};



template<typename K, typename V>
class HashAperta{
    public:

        int m;
        vector<Item<K,V>> table;

        HashAperta(int size): m(size), table(size) {}

        int hash(K key)
        {
            return key %m;
        }

        void insert(K key, V val){
            int idx = hash(key);
            int start = idx;

            while(table[idx].stato != EMPTY && table[idx].stato != DELETED)
            {
                if(table[idx].key == key && table[idx].stato == ACTIVE)
                {
                    table[idx].value = val;
                    return;
                }
                idx = (idx +1 ) % m;
                if (idx == start)
                {
                    cerr << "Tabella piena \n";
                }
                
            }
            table[idx] = Item<K,V>(key,val);
        }

        void print(ostream&out)
        {
            for(int i = 0; i < m; ++i)
            {
                if(table[i].stato == ACTIVE)
                {
                    out << table[i].key << "->" << table[i].value << "\n";
                }
            }
        }

    //--------------------------------------------------------------------
        V* find (K key){
            int idx = hash(key);
            int start = idx;


            while(table[idx].stato != EMPTY){
                if(table[idx].stato == ACTIVE && table[idx].key == key)
                {
                    return &(table[idx].value);
                }
                idx = (idx +1 ) % m;
                if (idx == start)
                    break;
            }
            return nullptr;
        }

    //--------------------------------------------------------------------------
        bool remove(K key){
            int idx = hash(key);
            int start = idx;

            while(table[idx].stato != EMPTY)
            {
                if(table[idx].stato == ACTIVE && table[idx].key == key){
                    table[idx].stato = DELETED;
                    return true;
                }
                idx = (idx+1) %m;
                if (idx == start)
                    break;
            }
            return false;
        }
};


void leggiFile(HashAperta<int, string>&H, string file){

    ifstream in(file);
    int k;
    string v;
    char c;

    while(in >> c && c == '<'&& in >> k >> c && c == ','){
        getline(in,v,'>');
        H.insert(k,v);
    }
}


int main(){
    int M = 999;
    HashAperta<int, string>H1(M);
    
    leggiFile(H1, "input.txt");

    ofstream out("OUT.txt");
    out << "Tabella indirizzamento Aperto:\n";
    H1.print(out);

    cout << "chiave da cercare: ";
    int k;
    if (cin>>k){
        string*val = H1.find(k);
        if(val)
            cout <<"Trovato: "<< *val << "\n";
        else 
            cout <<"Non trovato \n";
    }

    cout << "chiave da eliminare: ";
    if(cin >> k){
        if(H1.remove(k))
            cout << "Eliminato con successo \n";
        else 
            cout << "Non trovata";

        if (H1.find(k)) cout << "ERRORE: La chiave e' ancora presente.\n";
        else cout << "OK: La chiave non si trova piu' con find().\n";
    }

    return 0;   
}