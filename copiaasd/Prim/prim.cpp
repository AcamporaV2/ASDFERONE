#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

enum class Color {white, grey, black};

const int INF = 1e9;

template <typename T>
class Nodo{
    public:

    T value;
    Color color = Color::white;
    int distance = INF;
    Nodo<T>*parent = nullptr;


    Nodo(T val) : value(val) {}
};


template <typename T>
class Arco{

    public:
        int weight;
        Nodo<T>* from;
        Nodo<T>* to;

        Arco(int w, Nodo<T>*f, Nodo<T>*t) : weight(w), from(f), to(t) {}
};


template<typename T>
class GrafoNonDiretto{

    private:
        unordered_map<T, Nodo<T>*> nodes;
        unordered_map<T, vector<pair<T, int >>> adj;

    public:
        vector<Arco<T>*> edges;

        Nodo<T>* add_nodo(T val)
        {
            if(!nodes.count(val))
            {
                nodes[val] = new Nodo<T>(val);
            }

            return nodes[val];
        }

        void add_edge(T from, T to, int weight)
        {
            Nodo<T>*src = add_nodo(from);
            Nodo<T>* dest = add_nodo(to);
            edges.push_back(new Arco<T>(weight, src, dest));
            adj[from].emplace_back(to, weight);
            adj[to].emplace_back(from, weight);
        }

        void stampa(ostream & out)
        {
            for(const auto&[node, neighbors]: adj)
            {
                out << node << " -> ";
                for(const auto&[dest,w]: neighbors)
                {
                    out << "( "<<  dest << ", peso: " << w << ")";
                }
                out << "\n";
            }
        }

        void prim(T start, ofstream & out)
        {
            for(auto & [_,node]: nodes)
            {
                node->distance = INF;
                node->color = Color::white;
                node->parent = nullptr;
            }

            if(!nodes.count(start))
            {
                out << "nodo iniziale non trovato";
                return;
            }

            auto cmp = [](Nodo<T>*a, Nodo<T>* b) { return a->distance > b->distance; };
            priority_queue<Nodo<T>*, vector<Nodo<T>*>, decltype(cmp)> pq(cmp);

            Nodo<T>* src = nodes[start];
            src->distance = 0;
            pq.push(src);

            int tot_weight = 0;

            while(!pq.empty())
            {
                Nodo<T>* u = pq.top();
                pq.pop();

                if(u->color == Color::black) continue;

                u->color = Color::black;
                tot_weight = tot_weight + u->distance;

                if(u->parent != nullptr)
                {
                    out << "Arco (" << u->parent->value << " - " << u->value << ") peso:" << u->distance << "\n";
                } else 
                {
                    out << "Nodo iniziale: " << u->value << "\n";
                }

                for(auto & [v,w]: adj[u->value])
                {
                    Nodo<T>* neighbor = nodes[v];

                    if(neighbor->color != Color::black && w < neighbor->distance)
                    {
                        neighbor->parent = u;
                        neighbor->distance = w;

                        pq.push(neighbor);
                    }
                }
            }

            out << "Peso totale MST: " << tot_weight << "\n";
        }
};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    GrafoNonDiretto<int> G;
    int n,m;
    in >> n >> m;

    for(int i = 0; i < m; ++i)
    {
        int u,v,w;
        in >> u >> v >> w;
        G.add_edge(u,v,w);
    }

    out << "Lista di adiacenza: \n";
    G.stampa(out);

    out << "Prim a partitre dal nodo 0 :\n";
    G.prim(0,out);

    cout << "miao miao";
    return 0;
}