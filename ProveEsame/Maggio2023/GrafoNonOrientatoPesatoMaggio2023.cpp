/*

.Usando il paradigma della programmazione ad oggetti ed linguaggio C++ 11
progettare ed implementare una classe grafo che consenta di caricare dati di un
grafo non orientato pesato G contenuti nel file GRP.txt II file testo contiene nel
primo rigo due interi separati da uno spazio che indicano, rispettivamente, il
numero di nodi ed il numero di archi.
I successivi righi contengono ciascuno tre numeri, separati da uno spazio, per
indicare il nodo sorgente, nodo destinazione ed il peso di ogni arco. Dotare la
classe di un metodo BFS(s) che scrive nel file OUT.txt, per ogni nodo, la distanza
dal nodo s ed il proprio predecessore

Dotare la classe dei metodi PRIM() e PRINT_MST() per calcolare e stampare a video
il minimum spanning tree. (pt. 6)

.Dotare la classe del metodo IS_BINARY(MST) che restituisca TRUE se MST è un
albero binario e FALSE altrimenti. (pt. 6)

*/

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

enum Color {white, grey, black};

template <class T>
class Node{
    public:
        T val;
        vector<pair<Node<T>*, int>> adj;
        Color color;
        int dist;

        Node(T val): val(val), color(white), dist(-1) {}

        void add_edge(Node<T>*v, int weight){
            adj.push_back({v,weight});
            v->adj.push_back({this,weight});
        }  
};


template <class T>
class Grafo{
    public:
        vector<Node<T>*> nodes;


        void add_node(T val){
            nodes.push_back(new Node<T>(val));
        }


        void add_edge(T u, T v, int weight){
            Node<T>* node_u = nullptr;
            Node<T>* node_v = nullptr;

            for(auto node: nodes){
                if(node->val == u)
                    node_u = node;
                if(node->val == v)
                    node_v = node;
            
            }

            if(node_u && node_v)
            {
                node_u->add_edge(node_v,weight);
            }
        }

        void reset() {
            for (auto node : nodes) {
                node->color = white;
                node->dist = -1;
            }
        }

        void bfs(T start_val, ostream&out){
            Node<T>* start_node = nullptr;
            for(auto node: nodes)
            {
                if(node->val == start_val)
                {
                    start_node = node;
                    break;
                }
            }

            if(!start_node) return;

            reset();
            queue<Node<T>*> q;
            start_node->color = grey;
            start_node->dist = 0;
            q.push(start_node);

            while(!q.empty()){
                Node<T>*u = q.front();
                q.pop();
                out << u->val << " ";
                

                for(auto edge : u->adj){
                    Node<T>*v = edge.first;
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

        void print(ostream & out){
            for(auto node: nodes){
                out << node->val << "->";
                for(auto edge: node->adj){
                    out << "(" << edge.first->val << ", W: " << edge.second << ") ";
                }
                out << "\n";
            }
        }

};


int main()
{
    ifstream in("GrafoMaggio2023_input.txt");
    ofstream out("GrafoMaggio2023_output.txt");
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
        if(in >> u >> v >> w)
            g.add_edge(u,v,w);
    }

    out << "\nBFS dal nodo 0\n";
    g.bfs(1,out);

    cout << "finito";
    return 0;
}