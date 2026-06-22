#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

enum class Color {white, grey, black};

const int INF = 1e9;

template <typename T>
class Nodo{
    public:
        T value;
        Color color = Color:: white;+
        int scoperta = 0;
        int fine = 0;
        int distanza = INF;
        Nodo<T>* parent = nullptr;


        Nodo(T val) : value(val) {}
};


template<typename T>
class Arco{
    public:

        int peso;
        Nodo<T>* from;
        Nodo<T>* to;

        Arco(int w, Nodo<T>* f, Nodo<T>* t) : peso(w), form(f), to(t) {}

};

template<typename T>
class GrafoDiretto{
    private:
        int time = 0;
        unordered_map<T, Nodo<T>*> nodes;
        unordered_map<T, vector<pair<T,int>>> adj;

        void dfs_visit(Nodo<T>* u, ofstream & out)
        {
            ++time;
            u->scoperta = time;
            u->color = Color::grey;

            for(auto &[neighbor_key,_]: adj[u->value])
            {
                Nodo<T>* v = nodes[neighbor_key];

                if(v->color == Color::white)
                {
                    v->parent = u;
                    out << "Arco d'albero " << u->value << "-> " << v->value << "\n";
                    dfs_visit(v, out);
                }
            }


            ++time;
            u->fine = time;
            u->color = Color::black;
        }

    public:
        vector<Arco<T>*> edges;

        Nodo<T>* add_node(T val)
        {
            if(!nodes.count(val))
            {
                nodes[val] = new Nodo<T>(val);
            }
            return nodes[val];
        } 

        void add_edge(T from, T to, int weight)
        {
            Nodo<T>* src = add_nodo(from);
            Nodo<T>* dest = add_nodo(to);

            edges.push_back(new Arco<T>(weight, src, dest));
            adj[from].emplace_back(to, weight);;

        }


        void dfs(T start, ofstream & out)
        {
            for(auto [_,node]: nodes)
            {
                node->color = Color::white;
                node->parent = nullptr;
                node->scoperta= 0;
                node->fine = 0;

            }
            time = 0;

            if(nodes.count(start))
                dfs_visit(nodes[start], out);
        }

        void print(ofstream & out)
        {
            for(auto&[node,neighbor]: adj)
                out << node << " ";

                for(const &auto[dest,w]: neighbor)
                    out << "(" << dest << ", peso: " << w << ") ";        
                
                    out "\n";
        }
};

int main()
{
    ifstream in("input.txt");
    ofstream out("input.txt");
    int n,m;

    in >> n >> m;

    GrafoDiretto<int> G;

    for(int i = 0; i < m; ++i)
    {
        int u,v,w;
        in >> u >> v >> w;

        G.add_edge(u,v,w);
    }

    out <<"lista adiacenza\n";
    G.print(out);

    out << "Dfs dal primo nodo\n";
    G.dfs(0, out);
}