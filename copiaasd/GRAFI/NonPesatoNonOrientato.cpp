#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

enum Color {White, Grey, Black};


template<typename T>
class Nodo{

    public:
    T val;
    vector<Nodo<T>*> adj;
    Color color;
    int dist;

    Nodo(T val): val(val), color(White), dist(-1) {}

    void add_edge(Nodo<T>*v)
    {
        adj.push_back(v);
        v->adj.push_back(this);
    }
};


template <typename T>
class Grafo {
    public:
        vector<Nodo<T>*> nodes;

        void add_node(T val)
        {
            nodes.push_back(new Nodo<T>(val));
        }

        void add_edge(T u, T v)
        {
            Nodo<T>* node_u = nullptr;
            Nodo<T>* node_v = nullptr;

            for(auto node: nodes)
            {
                if(node->val == u)
                    node_u = node;
                if(node->val == v)
                    node_v = node;
            }

            if(node_u && node_v)
            {
                node_u->add_edge(node_v);
            }
        }

        void reset() {
            for(auto node: nodes)
            {
                node->color = White;
                 node->dist = -1;
            }
        }

        void bfs(T start, ostream & out)
            {
                Nodo<T>* start_node = nullptr;
                for(auto node: nodes)
                {
                    if(node->val == start)
                    {
                        start_node = node;
                        break;
                    }
                }

                if(!start_node)
                    return;
                
                reset();
                queue<Nodo<T>*>q;
                start_node->color = Grey;
                start_node->dist = 0;
                q.push(start_node);

                while(!q.empty())
                {
                    Nodo<T>* u = q.front(); 
                    q.pop();
                    out << u->val << " ";
                    for(Nodo<T>* v : u->adj)
                    {
                        if(v->color == White)
                        {
                            v->color = Grey;
                            v->dist = u->dist + 1;
                            q.push(v);
                        }
                    }
                    u->color = Black;
                }
            }

            void print(ostream & out)
            {
                for(auto node:nodes)
                {
                    out << node->val << " -> ";
                    for(auto neighbor: node->adj)
                    {
                        out << neighbor->val << " ";
                    }
                    out << "\n";
                }
            }
};

int main()
{
    ifstream in("inputNonPesNonOr.txt");
    ofstream out("outputNonPesNonOr.txt");

    int n, m;

    in >> n >> m;
    Grafo<int> G;

    for (int i = 0; i < n; ++i) {
        G.add_node(i);
    }

    for (int i = 0; i < m; i++)
    {
        int u,v;

       if( in >> u >>v)
            G.add_edge(u,v);
    }

    out << "Lista adiacenza\n";
    G.print(out);

    out << "\nBFS dal nodo 0: \n";
    G.bfs(0, out);

    cout << "miao miao";
    return 0;
}