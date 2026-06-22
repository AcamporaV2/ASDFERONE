#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <stack>


using namespace std;

const int WHITE = 0;
const int GREY = 1;
const int BLACK = 2;

template <typename T>
class Nodo{
    public:
    T val;
    int color = WHITE;
    int scoperta = 0;
    int finale = 0;
    Nodo<T>* padre = nullptr;


    Nodo(T valore) : val(valore) {}
};


template <typename T>
class Grafo{
    private:
        int time = 0;
        unordered_map<T,Nodo<T>*> mappa_nodi;
        unordered_map<T, vector<T>> adj;

        void dfs_visit(Nodo<T>*u, stack<Nodo<T>*>& st)
        {
            u->color = GREY;
            u->scoperta = ++time;

            for(T v_val : adj[u->val])
            {
                Nodo<T>* v = mappa_nodi[v_val];
                if(v->color == WHITE)
                {
                    v->padre = u;
                    dfs_visit(v, st);
                }
            }

            u->color = BLACK;
            u->finale = ++time;
            st.push(u);
        }

    public:

        void add_edge(T from, T to)
        {
            if(!mappa_nodi.count(from))
                mappa_nodi[from] = new Nodo<T>(from);
            if(!mappa_nodi.count(to))
                mappa_nodi[to] = new Nodo<T>(to);
            
            adj[from].push_back(to);
        }

        void ordinamento_topo(ofstream &out)
        {
            stack<Nodo<T>*> st;
            for(auto &[_,nodo] : mappa_nodi)
            {
                nodo->color = WHITE;
                nodo->padre = nullptr;
            }
            time = 0;
            for(auto&[_,nodo]:mappa_nodi)
                if(nodo->color == WHITE)
                    dfs_visit(nodo,st);


            while(!st.empty()){
                out << "Nodi in ordine topologico: " << st.top()->val << "\n";
                st.pop();
            }
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
        int weight, from, to;

        in >> from >> to >> weight;
        g.add_edge(from,to);
    }
    g.ordinamento_topo(out);

    return 0;
}