#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_map>


using namespace std;

const int INF = 1e9;

enum Color {white, gray, black};

template<typename T>
class Nodo{
    public:

    T val;
    Color colore = white;
    int distance = INF;
    Nodo<T>*parent = nullptr;

    Nodo(T val): val(val) {}
};


template <typename T>
class Arco{
    public:

        int peso;
        Nodo<T>* from;
        Nodo<T>* to;

        Arco(int w, Nodo<T>* f, Nodo<T>* t) : peso(w), from(f), to(t) {}
};


template<typename T>
class Grafo{
    public:
        unordered_map<T, Nodo<T>*> nodes;
        unordered_map<T, vector<pair<T,int>>> adj;
        vector<Arco<T>*> archi;


        Nodo<T>* agg_nodo(T val)
        {
            if(!nodes.count(val))
            {
                nodes[val] = new Nodo<T>(val);

            }
            return nodes[val];
        }

        void agg_arco(T from, T to, int peso, bool orientato = false)
        {
            Nodo<T>* src = agg_nodo(from);
            Nodo<T>* dest = agg_nodo(to);

            archi.push_back(new Arco<T>(peso, src, dest));
            adj[from].emplace_back(to, peso);
            if(orientato)
            {
                adj[to].emplace_back(from, peso);
            }
        }

        void print(ofstream & out)
        {
            for (const auto &  [node, neighbor]: adj)
            {
                out << node << " ";
                for(const auto &[neighbor, w]:neighbor)
                {
                    out << "(" << neighbor << ", peso "<< w << ")";
                }
                out << "\n";
            }

        }

        void BFS(T start)
        {
            for(auto&[_,nodo]: nodes)
            {
                nodo->colore = white;
                nodo->distance = INF;
                nodo->parent = nullptr;
            }

            Nodo<T>* source = nodes[start];
            source->colore = gray;
            source->distance = 0;
            source->parent = nullptr;

            queue<Nodo<T>*> q;
            q.push(source);

            while(!q.empty())
            {
                Nodo<T>* u = q.front();
                q.pop();
                for(auto &[v_val,_]: adj[u->val])
                {
                    Nodo<T>*v = nodes[v_val];
                    if(v->colore == white)
                    {
                        v->colore = gray;
                        v->parent = u;
                        v->distance = u->distance +1;
                        q.push(v);
                    }
                }
                u->colore = black;
            }
        }
};

int main()
{
    ifstream in("input.txt");
    ofstream out ("output.txt");

    Grafo<int> g;

    int n,m;

    in >> n >> m;

    for(int i = 0; i < m; ++i)
    {
        int u,v,w;
        in >> u >> v >> w;
        g.agg_arco(u,v,w);
    }

    out << "lista adiacenza: \n";
    g.print(out);

    out << "Dist dal nodo iniziale BFS\n";
    g.BFS(1);
    
    for(auto &[key, node]: g.nodes)
    {
        out << "nodo: "<< key << ", distanza:" << node->distance << "\n";
    }

    return 0;
}