/*
Usando il paradigma della programmazione ad oggetti ed linguaggio C++ 11
progettare ed implementare una classe grafo che consenta di caricare dati di un
grafo non orientato pesato G contenuti nel file GRP.txt II file testo contiene nel
primo rigo due interi separati da uno spazio che indicano, rispettivamente, il
numero di nodi ed il numero di archi.
I successivi righi contengono ciascuno tre numeri, separati da uno spazio, per
indicare il nodo sorgente, nodo destinazione ed il peso di ogni arco. Dotare la
classe di un metodo BFS(s) che scrive nel file OUT.txt, per ogni nodo, la distanza
dal nodo s ed il proprio predecessore


*/


#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

enum color  {white, gray, black};

template<typename T>
class Node {

    public:
        T valore;
        color colore = white;
        int distanza = INF;
      //  int scoperta = 0;
       // int fine = 0;
        Node<T>* padre = nullptr;


        Node(T valore): valore(valore) {}
};


template<typename T>
class Arco {

    public:
        int peso;
        Node<T>* from;
        Node<T>* to;

        Arco(int w, Node<T>* f, Node<T>* t) : peso(w), from(f), to(t) {}
};


template <typename T>
class Grafo{
    private:
       int  time = 0;
    
    public:
        unordered_map<T,Node<T>*> nodi;
        unordered_map<T, vector<pair<T,int>>> adiacenti;
        vector<Arco<T>*> archi;
    

        ~Grafo()
        {
            for(auto& p : nodi) delete p.second;
            for(Arco<T>* e: archi) delete e;
        }

        Node<T>* aggiungi_nodo(T val)
        {
            if(!nodi.count(val))
            {
                nodi[val] = new Node<T>(val);
            }
            return nodi[val];
        }


        void aggiungi_arco(T from, T to, int peso, bool orientato = false)
        {
            Node<T>* fonte = aggiungi_nodo(from);
            Node<T>* destinazione = aggiungi_nodo(to);
            archi.push_back(new Arco<T>(peso, fonte, destinazione));
            adiacenti[from].emplace_back(to, peso);
            if(orientato)
            {
                adiacenti[to].emplace_back(from, peso);
            }
        }

        void stampa_lista_adiacenza(ofstream & out)
        {
            for(const auto& [node, vicini]: adiacenti)
            {
                out << node << ": ";
                for(const auto&[vicini, peso]: vicini)
                {
                    out << "(" << vicini << ", peso "<< peso << ") ";
                }
                out << "\n";
            }
        }

       void BFS(T start)
        {
            for(auto &[_,nodo]: nodi)
            {
                nodo->colore = white;
                nodo->distanza = INF;
                nodo->padre = nullptr;
            }

            Node<T>* source = nodi[start];
            source->colore = gray;
            source->distanza = 0;
            source->padre = nullptr;

            queue<Node<T>*> q;
            q.push(source);

            while(!q.empty())
            {
                Node<T>* u = q.front();
                q.pop();

                for(auto&[v_val,_]: adiacenti[u->valore])
                {
                    Node<T>*v = nodi[v_val];
                    if(v->colore == white)
                    {
                        v->colore = gray;
                        v->distanza = u->distanza + 1;
                        v->padre = u;
                        q.push(v);
                    }
                }
                u->colore= black;
            }
        }

};



int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n,m;
    in >> n>> m;

    Grafo<int> g;

    for (int i = 0; i < m; i++)
    {
        int u,v,w;
        in >> u>> v>> w;
        g.aggiungi_arco(u,v,w);
    }

    out<< "lista adiacenza:\n";
    g.stampa_lista_adiacenza(out);


    out << "\nDistanze dal nodo " << g.nodi.begin()->first << " (BFS):\n";
    g.BFS(1); // oppure qualsiasi nodo di partenza
    out << "\nRisultati BFS:\n";
    for (auto& [key, node] : g.nodi) {
        out << "Nodo " << key << ", distanza: " << node->distanza << "\n";
    }
}


