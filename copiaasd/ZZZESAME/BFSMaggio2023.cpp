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
#include <queue>
#include <vector>

using namespace std;

enum Color {white, grey, black};

template<typename T>
class Nodo{
    public:
    T value;
    vector<pair<Node<T>*,int>> adj;
    Color color;
    int dist;


    Nodo(T val): value(val), color(white), dist(-1)  {}


    void add_adge(Nodo<T>*v, int weight)
    {
        adj.push_back({v,weight});
        v->adj.push_back({this, weight});
    }
};


template <typename T>
class Grafo {

    public:
        vector<Nodo<T>*> nodes;


        void add_node(T val)
        {
            nodes.push_back(new Node<T>(val));
        }

        void add_edge(T u, T v, int weight)
        {
            Nodo<T>* node_u = nullptr;
            Nodo<T>* node_v = nullptr;

            for(auto node: nodes)
            {
                if(node->value == u)
                    node_u = node;
                if(node->value == v)
                    node_v = node;
            }

            if(node_u && node_v)
            {
                node_u->add_adge(node_v, weight);
            }
        }


        void reset()
        {
            for(auto node:nodes)
            {
                node->color = white;
                node->value = -1;
            }
        }


        void bfs(T start, ostream &out)
        {
            Nodo<T>* start_node = nullptr;
            for(auto node:nodes)
            {
                if(node->val == start)
                {
                    start_node = node;
                    break;
                }
            }

            if(!start_node) return;

            reset();
            queue<Nodo<T>*> q;

            start_node->color = grey;
            start_node->dist = -1;
            q.push(start_node);

            while(!q.empty())
            {
                Nodo<T>* u = q.front();
                q.pop();
                out << u->value << " ";

                
                for(auto edge : u->adj)
                {
                    Nodo<T>*v = edge.first;
                    if(v->color == white)
                    {
                        v->color = grey;
                        v->dist = u->dist +1;
                        q.push(v);
                    }
                }

                u->color = black;
            }
        }

        void print(ostream & out)
        {
            for(auto node:nodes)
            {
                out << node->val << " ";
                for(auto edge: node-> adj)
                {
                    out << "(" << edge.fist->value << ", W: " << edge.second << ") ";
                }
                out << "\n";
            }
        }

};


int main()
{
    ifstream in ("input.txt");
    ofstream out("output.txt");
    int n,m;
    in >> n >> m;

    Grafo<int> g;
    for(int i = 0; i < m; ++i)
    {
        g.add_node(i);
    }

    for(int i = 0; i < m; ++i)
    {
        int u,v,w;
        in >> u >> v >> w;
        g.add_edge(u,v,w);
    }

    out << "lista di adiacenza:\n";
    g.print(out);

    out << "BFS dal nodo iniziale start: \n";
    g.bfs(1, out);

    cout << "finito";
    return 0;
}
