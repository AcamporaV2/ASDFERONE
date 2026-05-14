#include <iostream>
#include <fstream>
#include <map>
#include <vector>



using namespace std;


enum Color {white, grey, black};


template <class T>
class Node{
    public:
        T val;
        vector<pair<Node<T>*, int>> adj;
        Color color;

        Node(T val): val(val), color(white) {}

        void add_edge(Node<T>*v, int weight){
            adj.push_back({v,weight});
        }
};

template<class T>
class Grafo{
    public:

        vector<Node<T>*> nodes;

        void add_node(T val){
            nodes.push_back(new Node<T>(val));
        }

        void add_edge(T u, T v, int weight){
            Node<T>* node_u = nullptr;
            Node<T>* node_v = nullptr;

            for(auto node : nodes){
                if(node->val == u ) 
                    node_u = node;

                if(node->val == v )
                    node_v = node;
            }

            if(node_u && node_v){
                node_u->add_edge(node_v,weight);
            }
        }

        void reset(){
            for(auto node : nodes){
                node->color = white;
            }
        }

        void dfs(T start, ostream& out){
            Node<T>* nodo_start = nullptr;
            for(auto node: nodes){
                if(node->val == start)
                {
                    nodo_start = node;
                    break;
                }
            }

            if(!nodo_start) return;

            reset();
            dfs_visit(nodo_start, out);
        }

        void dfs_visit(Node<T>*u, ostream&out){
            u->color = grey;
            out << u->val << " ";

            for(auto edge: u->adj){
                Node<T>* v = edge.first;
                if(v->color == white)
                {
                    dfs_visit(v, out);
                }
            }
            u->color = black;
        }

        void print(ostream& out)
        {
            for(auto node: nodes)
            {
                out<< node->val << "->";
                for(auto edge: node->adj)
                {
                    out << "(" << edge.first->val << ",w :"<<edge.second<<") ";
                }
                out <<"\n";
            }

        }
};

int main(){
    ifstream in("inputOrientato.txt");
    int n,m;
    
    if(!(in >> n >> m)){
        n = 5, m = 4;
    }

    Grafo<int> g;
    for(int i = 0; i < m; ++i)
    {
        g.add_node(i);
    }

    for(int i = 0; i < m; ++i)
    {
        int u,v,w;

        if(in >> u >> v >> w)
            g.add_edge(u,v,w);
        else if (i==0) { 
            g.add_edge(0,1,10); g.add_edge(1,2,5); 
            break; 
        }

    }

    ofstream out("outputOrientato.txt");
    out << "Lista di adiacenza (orientata):\n";
    g.print(out);

    out << "\nDFS ricorsiva su 0\n";
    g.dfs(0,out);

    cout<< "finito";
    return 0;
}