#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

enum Status {EMPTY, ACTIVE, DELETED};

template <typename K, typename V>
struct Item
{
    K key;
    V value;
    Status stato = EMPTY;

    Item(){}
    Item(K k, V v): key(k), value(v), stato(ACTIVE) {}
};



template <typename K, typename V>
class HashAperta{

    public:
        int m;
        vector<Item<K,V>> table;

        HashAperta(int size) : m(size), table(size) {}


        int hash(K key)
        {
            return key % m;
        }

        void insert(K key, V val)
        {
            int idx = hash(key);
            int start = idx;
            
            while(table[idx].stato!= EMPTY && table[idx].stato != DELETED)
            {
                if(table[idx].key == key && table[idx].stato == ACTIVE)
                {
                    table[idx].value = val;
                    return;
                }
                idx = (idx + 1) % m;
                if(idx == start)
                {
                    cerr << "tabella piena\n";
                }
            }

            table[idx] = Item<K,V>(key,val);
        }


        void print(ostream & out)
        {
            for(int i = 0; i < m; ++i)
            {
                if(table[i].stato == ACTIVE)
                {
                    out << table[i].key << "->" << table[i].value << "\n";
                }
            }
        }
        
        void leggiFile(const string& file)
        {
            ifstream in(file);
            //i due tipi che ci servono
            char k;
            int v;

            char c;

            while(in >> c && c == '<' && in >> k >> c && c == ',' && in >> v >> c && c == '>')
            {
                H.insert(k,v);
            }
        }

};




int main()
{
    int M = 999;
    HashAperta<char, int> Hash(M);


    Hash.leggiFile("IN.txt");
    ofstream out("output.txt");

    out << "tabella \n";
    Hash.print(out);

    return 0;

}