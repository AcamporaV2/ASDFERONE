#include <fstream>
#include <iostream>
#include <queue>
#include <vector>


using namespace std;

enum Color {White, Grey, Black};

template <typename T>
class Nodo{

    public:
        T val;
        vector<pair<Nodo<T>*, int>> adj;
        Color color;
        int dist;


        Nodo(T val) : val(val), color(White), dist(-1) {}
    
        void add_edge(Nodo<T>*v, int weight)
        {
            adj.push_back({v,weight});
            v->adj.push_back({this, weight});
        }
    };


template <typename T>
class Grafo{
    public:

    vector<Nodo<T>*> nodes;

    void add_node(T val)
    {
        nodes.push_back(new Nodo<T>(val));
    }

    void add_edge(T u, T v, int weight)
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
            node_u->add_edge(node_v, weight);
        }
    }

    void reset() {
            for (auto node : nodes) {
                node->color = White;
                node->dist = -1;
            }
    }

    void bfs(T start, ostream&out)
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

        if(!start_node) return;

        reset();
        queue<Nodo<T>*> q;
        start_node->color = Grey;
        start_node->dist = 0;
        q.push(start_node);

        while(!q.empty())
        {
            Nodo<T>* u = q.front();
            q.pop();
            out << u->val << " ";

            for(auto edge: u->adj)
            {
                Nodo<T>* v = edge.first;
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
        for(auto node: nodes)
        {
            out << node->val << "->";
            for(auto edge:node->adj)
            {
                out << "(" << edge.first->val << ", W." << edge.second << ")";
            }
            out <<"\n";
        }
    }
};


int main()
{
    ifstream in("inputPesatoNonOr.txt");
    ofstream out ("outputPesatoNonOr.txt");

    int n,m;
    in >> n >> m;
    Grafo<int> g;

    for(int i = 0; i <n; ++i)
    {
        g.add_node(i);
    }

    for(int i = 0; i < m; ++i)
    {
        int u,v,w;
        in >> u >> v >> w;
        g.add_edge(u,v,w); 
    }


    out << "lista adiacenza \n";
    g.print(out);

    out << "BFS pesata da 0: \n";
    g.bfs(1, out);

    cout << "miao miao";
    return 0;
}