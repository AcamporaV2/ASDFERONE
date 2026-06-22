#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <unordered_set>


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
    int fine = 0;

    Nodo<T>* parent = nullptr;

    Nodo(T value) : val(value) {}
};


template <typename T>
class Grafo{
    private:
    int time = 0;
    unordered_map<T, Nodo<T>*> nodes;
    unordered_map<T, vector<T>> adj;

    
    void dfs_visit(Nodo<T>*u, stack<Nodo<T>*>& st)
    {
        u->color = GREY;
        u->scoperta = ++time;

        for(T v_val : adj[u->val])
        {
            Nodo<T>*v = nodes[v_val];
            if(v->color == WHITE)
            {
                v->parent = u;
                dfs_visit(v,st);
            }

            
        }
        u->color = BLACK;
        u->fine = ++time;
        st.push(u);
    }

    public:

        void add_edge(T from, T to)
        {
            if(!nodes.count(from))
                nodes[from] = new Nodo<T>(from);

            if(!nodes.count(to))
                nodes[to] = new Nodo<T> (to);

            adj[from].push_back(to);
         }


         void ordinamento_topo(ofstream &out)
         {
            stack<Nodo<T>*> st;

            for(auto & [_,node]: nodes)
            {
                node->color = WHITE;
                node->parent = nullptr;
            }

            time = 0;

            for(auto &[_,node]:nodes)
                if(node->color == WHITE)
                    dfs_visit(node,st);


            while(!st.empty())
            {
                out << "Nodi in ordine topologico: " << st.top->val << "\n";
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

    Grafo<int>g;

    for(int i = 0; i < m; ++i)
    {
        int u,v,w;
        in >> u >> v >> w;
        g.add_edge(u,v);

    }

    g.ordinamento_topo(out);
    
    cout << "finito\n";

    return 0;
}