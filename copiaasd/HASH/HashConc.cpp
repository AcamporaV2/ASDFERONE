#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>

using namespace std;

template <typename K, typename V>
class Hash{
    public:
        int m;
        vector<list<pair<K,V>>> table;

        Hash(int size) : m(size), table(size) {}


        int hash(K key)
        {
            return key % m;
        }

        void insert(K key, V val)
        {
            int idx = hash(key);
            int start = idx;

            for(auto& item : table[idx])
            {
                //chiave trovata si aggiorna
                if(item.first == key)
                {
                    item.second = val;
                    return;
                }
            }

            table[idx].push_back({key,val});
        }

        void print(ostream&out)
        {
            for(int i = 0; i <m; ++i)
            {
                for(auto & item:table[i])
                {
                    out << item.first << "->" << item.second << "\n";

                }
            }
        }

        bool contains(K key)
        {
            int idx = hash(key);

            for(auto & item:table[idx])
                if(item.first == key)
                    return true;
            
            return false;
        }

        V* find (K key)
        {
            int idx = hash(key);

            for(auto & item:table[idx])
            {
                if(item.first == key)
                    return &(item.second);
            }
            return nullptr;
        }
};

bool disjoint(Hash<int,string>&A, Hash<int,string> & B)
{
    for(int i = 0; i< A.m; ++i)
    {
        for(auto& row: A.table[i])
        {
            if(B.contains(row.first))
                return false;
        }
    }
    return true;
}

void leggiFile(Hash<int,string>&H, string file)
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


int main()
{
    ofstream out("OUT.txt");
    int M= 999;

    Hash<int,string> H1(M);
    Hash<int,string> H2(M);

    leggiFile(H1, "input1.txt");
    leggiFile(H2, "input2.txt");

    out << (disjoint(H1,H2) ? "Disgiunte\n" : "Non disgiunte\n");

    out << "tabella 1: \n";
    H1.print(out);

    
    out << "tabella 2: \n";
 
    H2.print(out);


    return 0;
}