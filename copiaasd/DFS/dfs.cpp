#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

//const int INF = 1e9;

enum Color {white, gray, black};

template<typename T>
class Node{
    public:

        T val;
        Node<T>* parent = nullptr;
        Color color = white;
        int scoperta = 0;
        int fine = 0;
        //int distance = INF;
        
        Node(T val) : val(val) {}
};


template<typename T>
class Arco{
    public:

        int peso;
        Node<T>* from;
        Node<T>* to;

        Arco(int w, Node<T>*f, Node<T>*t) : peso(w), from(f), to(t) {}
};


template<typename T>
class Grafo
{

    private:
        int time = 0;
    public:
        unordered_map<T, Node<T>*> nodes;
        unordered_map<T, vector<pair<T,int>>> adj;
        vector<Arco<T>*> edges;


    Node<T>* agg_nodo(T val)
    {
        if(!nodes.count(val))
        {
            nodes[val]= new Node<T>(val);

        }
        return nodes[val];
    }

    void agg_arco(T from, T to, int peso, bool orientato = false)
    {
        Node<T>* src = agg_nodo(from);
        Node<T>* dest = agg_nodo(to);
        edges.push_back(new Arco<T>(peso, src, dest));
        adj[from].emplace_back(to, peso);
        if(orientato)
        {
            adj[to].emplace_back(from,peso);
        }
    }

    void print(ofstream & out)
    {
        for(const auto &[node, neighbor]:adj)
        {
            out << node << " ";
            for(const auto &[neighbor, w]: neighbor)
            {
                out << "(" << neighbor<< ", peso:" << w << ")";
            }
            out << "\n";
        }
    }

    void DFS()
    {
        for(auto &[_,nodo]:nodes)
        {
            nodo->color = white;
            nodo->parent = nullptr;
            
        }
        time = 0;
        for(auto &[_,nodo]:nodes)
        {
            if(nodo->color == white)
                DFS_VISIT(nodo);
        }
    }

    void DFS_VISIT(Node<T>*u)
    {
        u->color = gray;
        u->scoperta = ++time;

        for(auto &[v_val,_]: adj[u->val])
        {
            Node<T>* v = nodes[v_val];
            if(v->color == white)
            {
                v->parent = u;
                DFS_VISIT(v);
            }
        }
        u->color = black;
        u->fine = ++time;
    }
};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n,m;
    in >> n >> m;

    Grafo<int> g;

    for(int i = 0; i < m; ++i)
    {
        int u,v,w;
        in >> u >> v >> w;

        g.agg_arco(u,v,w);
    }

    g.DFS();

    out << "\nTempi di scoperta/fine (DFS):\n";
    for (const auto& [id, nodo] : g.nodes) {
    out << "Nodo " << id << ": discovery=" << nodo->scoperta << ", finish=" << nodo->fine << '\n';
    }


    out<< "lista adiacenza:\n";
    g.print(out);

    return 0;
}