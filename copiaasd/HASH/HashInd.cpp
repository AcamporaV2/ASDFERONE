#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;
enum Status {EMPTY, ACTIVE, DELETED};

template<typename K, typename V>
struct Item{

    K key;
    V value;
    Status stato = EMPTY;

    Item() {}
    Item(K k, V v) : key(k), value(v), stato(ACTIVE) {}

};


template<typename K, typename V>
class Hash{

    public:
        int m;
        vector<Item<K,V>> table;

        Hash(int size): m(size), table(size) {}

        int hash(K key)
        {
            return key%m;
        }

        void insert(K key, V val)
        {
            int idx = hash(key);
            int start = idx;

            while(table[idx].stato != EMPTY && table[idx].stato != DELETED)
            {
                if(table[idx].key == key && table[idx].stato == ACTIVE)
                {
                    table[idx].value = val;
                    return;
                }

                idx = (idx +1) % m;
                if(idx == start)
                {
                    cerr << "Tabella piena\n";
                }
            }
            table[idx]= Item<K,V>(key,val);
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

        V* find(K key)
        {
            int idx = hash(key);
            int start = idx;

            while(table[idx].stato != EMPTY)
            {
                if(table[idx].stato == ACTIVE && table[idx].key == key)
                {
                    return &(table[idx].value);
                }
                idx = (idx +1) %m;
                if (idx == start)
                    break;
                
            }
            return nullptr;
        }


        bool remove(K key)
        {
            int idx = hash(key);
            int start = idx;

            while(table[idx].stato != EMPTY)
            {
                if(table[idx].stato == ACTIVE and table[idx].key == key)
                {
                    table[idx].stato = DELETED;
                    return true;
                }
                idx = (idx +1 )%m;

                if(idx == start) 
                    break;
            }
            return false;
        }
};


void leggifile(Hash<int,string>&H, string file)
{
    ifstream in(file);
    //prime due sono il tipo di cosa che inseriamo nella hash table
    int k;
    string v;

    char c;

    while(in >> c && c == '<' && in >> k >> c && c == ',')
    {
        getline(in,v,'>');
        H.insert(k,v);
    }
}


int main(){
    int M = 999;
    Hash<int, string>H1(M);
    
    leggifile(H1, "input.txt");

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
            cout << "Non trovata\n";

        if (H1.find(k)) cout << "ERRORE: La chiave e' ancora presente.\n";
        else cout << "OK: La chiave non si trova piu' con find().\n";
    }

    return 0;   
}