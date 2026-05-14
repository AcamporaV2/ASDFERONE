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
        int scoperta = 0;
        int fine = 0;
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


template<typename T>
class Grafo {

    
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

        void DFS()
        {
            for (auto&[_,nodo]: nodi)
            {
                nodo->colore = white;
                nodo->padre = nullptr;
            }

            time = 0;

            for (auto&[_,nodo]: nodi)
            {
                if (nodo->colore == white)
                {
                    DFS_VISIT(nodo);
                }
            }
        }

        void DFS_VISIT(Node<T>* u)
        {
            u->colore = gray;
            u->scoperta = ++time;

            for(auto& [v_val,_]: adiacenti[u->valore])
            {
                Node<T>* v = nodi[v_val];
                if(v->colore == white)
                {
                    v->padre = u;
                    DFS_VISIT(v);
                }
            }

            u->colore = black;
            u->fine = ++time;
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

    g.DFS();

    out << "\nTempi di scoperta/fine (DFS):\n";
    for (unordered_map<int, Node<int>*>::iterator it = g.nodi.begin(); it != g.nodi.end(); ++it) {
        out << "Nodo " << it->first << ": discovery=" << it->second->scoperta
            << ", finish=" << it->second->fine << "\n";
    }


    out<< "lista adiacenza:\n";
    g.stampa_lista_adiacenza(out);
}