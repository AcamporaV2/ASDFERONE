#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

const int WHITE = 0;
const int GREY  = 1;
const int BLACK = 2;


template <typename T>
class Nodo {
    public:
        T val;
        int color = WHITE;
        int scoperta = 0;
        int finale = 0;
        Nodo<T>* parent = nullptr;

        Nodo(T valore): val(valore) {}
};

template <typename T>
class Grafo{
    private:
        int time = 0;
        unordered_map<T, Nodo<T>*> node_map;
        unordered_map<T, vector<T>> adj;

        void dfs_visit(Nodo<T>*u, stack<Nodo<T>*>& st){
            u->color = GREY;
            u->scoperta = ++time;

            for(T v_val : adj[u->val]){
                Nodo<T>* v = node_map[v_val];
                if(v->color == WHITE){
                    v->parent = u;
                    dfs_visit(v,st);
                }
            }

            u->color = BLACK;
            u->finale = ++time;
            st.push(u);
        }

    public:

        void add_edge(T from, T to){
            
            if(!node_map.count(from)) 
                node_map[from] = new Nodo<T>(from);
            
            if(!node_map.count(to))
                node_map[to] = new Nodo<T>(to);

            adj[from].push_back(to);
        }

        void ordinamento_topologico(ofstream &out){
            stack<Nodo<T>*> st;
            for(auto& [_,node]: node_map){
                node->color = WHITE;
                node->parent = nullptr;

            }
            time = 0;
            for (auto&[_,node]: node_map){
                if(node->color == WHITE) 
                    dfs_visit(node,st);
            }

            while(!st.empty()){
                out << "Nodo in ordine topologico: " << st.top()->val << "\n";
                st.pop();
            }
        }

};

int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");

    int n,m;
    in >> n >> m;

    Grafo<int> g;
    for(int i = 0; i <m; ++i)
    {
        int weight, from, to;
        in >> weight >> from >> to;
        g.add_edge(from,to);
    }

    g.ordinamento_topologico(out);

    cout << "file creato\n";

    return 0;
}