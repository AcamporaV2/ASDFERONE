#include <iostream>
#include <fstream>
#include <map>
#include <vector>


using namespace std;

enum Color {white, grey, black};

template <class T>
class Node{
    public:
    T value;
    vector<pair<Node<T>*, int >> adj;
    Color color;

    Node(T val) : value(val), color(white) {}

    void add_edge(Node<T>*v, int weight)
    {
        adj.push_back({v,weight});
    }

};


template <class T>
class Grafo {

    public:
        vector<Node<T>*> nodes;

        void add_nodo(T val)
        {
            nodes.push_back(new Node<T>(val));
        }

        void add_edge(T u, T v, int weight)
        {
            Node<T>* node_u = nullptr;
            Node<T>* node_v = nullptr;

            for(auto node: nodes)
            {
                if(node->value == u)
                    node_u = node;
                if(node->value == v)
                    node_v = node;
                
            }

            if(node_u && node_v)
            {
                node_u->add_edge(node_v, weight);
            }

        }

        void reset()
        {
            for(auto node: nodes)
            {
                node->color = white;
            }
        }

        void dfs(T start, ostream & out)
        {
            Node<T>* nodo_start = nullptr;
            for(auto node: nodes)
            {
                if(node->value == start)
                {
                    nodo_start = node;
                    break;
                }
            }
            if(!nodo_start) return;

            reset();
            dfs_visit(nodo_start, out);

        }

        void dfs_visit(Node<T>*u , ostream& out)
        {
            u->color = grey;
            out << u->value << " ";

            for(auto edge: u->adj)
            {
                Node<T>* v = edge.first;
                if(v->color == white)
                {
                    dfs_visit(v,out);
                }
                
            }
            u->color = black;
        }

        void print(ostream &out)
        {
            for(auto node: nodes)
            {
                out << node->value << "->";
                for(auto edge: node->adj)
                {
                    out << "(" << edge.first->value << ", w: " << edge.second << ")";
                }
                out << "\n";
            }
        }
};

int main()
{
    ifstream in("inputOrientato.txt");
    ofstream out("outputOrientato.txt");

    int n,m;
    in >> n >> m;

    Grafo<int> g;
    for(int i = 0; i < n; ++i)
    {
        g.add_nodo(i);
    }

    for(int i = 0; i < m; ++i)
    {
        int u,v,w;
        
        in >> u >> v >> w;

        g.add_edge(u,v,w);
    }

    out << "lista di adiacenza: \n";
    g.print(out);

    out << "\nDFS dal nodo 0\n";
    g.dfs(1, out);

    cout << "miao miao";
    return 0;
}