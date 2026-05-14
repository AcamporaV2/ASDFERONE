#include <iostream>
#include <fstream>
#include <vector>
#include <queue>



using namespace std;



enum Color {white, grey, black};


template<class T>
class Nodo{
    public:
        T val;
        vector<Nodo<T>*> adj;
        Color color;
        int dist; //bfs

        Nodo(T val): val(val), color(white), dist(-1) {}

        void add_edge(Nodo<T>*v){
            adj.push_back(v);
            v->adj.push_back(this);
        }
};


template<class T>
class Grafo{
    public:
        vector<Nodo<T>*> nodes;

        void add_node(T val){
            nodes.push_back(new Nodo<T>(val));
        }

        void add_edge(T u, T v){
            Nodo<T>* node_u = nullptr;
            Nodo<T>* node_v = nullptr;

            for(auto node: nodes){
                if(node->val == u)
                    node_u=node;
                if(node->val == v)
                    node_v= node;
            }

            if(node_u && node_v)
            {
                node_u->add_edge(node_v);
            }
        }

        void reset() {
        for (auto node : nodes) {
            node->color = white;
            node->dist = -1;
            }
        }

        void bfs(T start_val, ostream&out){
            Nodo<T>* start_node = nullptr;
            for(auto node:nodes){
                if(node->val == start_val){
                    start_node = node;
                    break;
                }
            }
            if(!start_node) return;
            reset();
            queue<Nodo<T>*>q;
            start_node->color = grey;
            start_node->dist = 0;
            q.push(start_node);

            while(!q.empty()){
                Nodo<T>* u = q.front();
                q.pop();
                out << u->val << " ";

                for(Nodo<T>*v : u->adj)
                {
                    if(v->color == white)
                    {
                        v->color == grey;
                        v->dist = u->dist +1;
                        q.push(v);
                    }
                }
                u->color = black;
            }
        }

        void print(ostream& out) {
            for (auto node : nodes) {
                out << node->val << " -> ";
                for (auto neighbor : node->adj) {
                    out << neighbor->val << " ";
                }
                out << "\n";
                }
        }

        
};


int main()
{
    ifstream in("inputNonPesato.txt");
    int n,m;

    in >> n >> m;

    Grafo<int> g;

    for(int i = 0; i < m; ++i)
    {
        int u,v;

        if(in >> u >> v)
            g.add_edge(u,v);
    }


    ofstream out("output.txt");
    out << "lista adiacenza:\n";
    g.print(out);

    out<<"\nBFS dal nodo 0:\n";
    g.bfs(0, out);

    cout<< "finito";
    return 0;
}