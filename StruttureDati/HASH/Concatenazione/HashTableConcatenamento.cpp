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

template<typename K, typename V>
class HashConc{
    public:
        int m;
        vector<list<pair<K,V>>> table;

        HashConc(int size): m(size), table(size) {}

        int hash(K key)
        {
            return key % m;
        }

        void insert(K key, V val){
            int idx = hash(key);
            for(auto& item:table[idx]){
                if(item.first ==key){
                    item.second = val;
                    return;
                }
            }
            table[idx].push_back({key,val});
        }

        void print(ostream&out){
            for(int i = 0; i < m; ++i)
                for(auto& item:table[i])
                    out << item.first << "-> " << item.second << "\n";
        }
        
        bool contains(K key){
            int idx = hash(key);
            for(auto& item: table[idx])
                if(item.first == key) return true;
            return false;
        }

        V* find(K key){
            int idx = hash(key);
            for(auto& item:table[idx]){
                if(item.first == key) return &(item.second);
            }
            return nullptr;
        }

        
};

bool disjoint(HashConc<int,string>&A,HashConc<int,string>&B){
    for(int i = 0; i < A.m; i++)
        for(auto& row:A.table[i])
            if(B.contains(row.first)) return false;
    return true;
}

void readFile(HashConc<int, string>&H, string file){
    ifstream in(file);
    int k;
    string v;
    char c;

    while(in >> c && c == '<' && in >> k >> c && c == ','){
        getline(in,v,'>');
        H.insert(k,v);
    }
}





int main()
{
    int M = 999;
    HashConc<int,string>H1(M), H2(M);
    readFile(H1, "input1.txt");
    readFile(H2,"input2.txt");
    ofstream out("output.txt");

    out << (disjoint(H1,H2) ? "Disgiunte\n": "Non Disgiunte\n");
    out << "Tabella 1: \n"; 
    H1.print(out);
    out << "Tabella 2: \n";
    H2.print(out);

    return 0;
}