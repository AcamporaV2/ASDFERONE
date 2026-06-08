/*
    Utilizzando il paradigma della programmazione ad oggetti ed il linguaggio C++ 11, progettare ed implementare, come classe, 
    una struttura dati hash table con concatenamento che consenta di memorizzare le coppie < int, string > contenute nei file IN1.txt ed IN2.txt 
    (una istanza di hash table per ogni file). Dotare la classe di un metodo PRINT per scrivere nel file OUT.txt 
    il contenuto delle hash table (in ogni riga del file scrivere il contenuto di una cella delle hash table). (pt. 18)

Dotare la classe del metodo HASH_M che implementi la funzione di hash con il metodo della moltiplicazione 
e del metodo HASH_U che implementi la funzione di hash con il metodo del hashing universale. (pt. 6)

Dotare la classe di un metodo DISJOINT(HT) che riceva in input un'istanza di hash table e 
restituisca TRUE se l'istanza di hash table su cui è richiamato il metodo e l'istanza passata come argomento rappresentano due insiemi disgiunti,
 FALSE altrimenti. (pt. 6)

*/



#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>

using namespace std;


template<typename K, typename V>
class Hash{
    public:
        int m;
        vector<list<pair<K,V>>> table;

        Hash(int size): m(size), table(size) {}

        int hash(K key)
        {
            return key % m;
        }

        void insert(K key, V val){
            int idx = hash(key);

            for(auto & item:table[idx])
            {
                //duplicato
                if(item.first == key)
                    item.second = val;
                    return;
            }


            table[idx].push_back({key,val});
        }

        void print(ostream& out)
        {
            for(int i = 0; i < m; ++i)
            {
                for(auto& item:table[i])
                    out << item.first << "->" << item.second << "\n";
            }
        }


};

void read_file(Hash<int,string>&H, string file){
    ifstream in(file);
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

    Hash<int,string> H1(M),H2(M);

    read_file(H1, "input1.txt");
    read_file(H2, "input2.txt");

    ofstream out("output.txt");

    out << "Tabella 1: \n";
    H1.print(out);

    out << "Tabella 2: \n";
    H2.print(out);


    return 0;
}