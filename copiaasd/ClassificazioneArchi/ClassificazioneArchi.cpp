#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <fstream>


using namespace std;

enum class Color {White, Grey, Black};



template <typename T>
class Node{

    public:

        T value;
      
        int tempo_scoperta = 0;
        int tempo_fine = 0;
        Color color = Color::White;
        Node<T>* padre = nullptr;

        Node(T val): value(val) {}
};


template <typename T>
class Arco{
    public:

        int peso;
        Node<T>* from;
        Node<T>* to;

        Arco(int w, Node<T>*f, Node<T>*t) : peso(w), from(f), to(t) {}
};


template <typename T>
class GrafoDiretto{

    private:
        unordered_map<T,Node<T>*> nodes;
        unordered_map<T, vector<pair<T,int>>> adj;
        int time = 0;

        void DFS_VISIT(Node<T>*node, ostream& out){

            time++;
            node->tempo_scoperta = time;
            node->color = Color::Grey;

            for(auto &[neighbor_key, _]: adj[node->value]){
                Node<T>* neighbor = nodes[neighbor_key];

                if(neighbor->color == Color::White){
                    out << "Arco d'albero: (" << node->value << "->"<< neighbor->value << ")\n";
                    neighbor->padre = node;
                    DFS_VISIT(neighbor,out);
                } else if(neighbor->color == Color::Grey){
                    out << "Arco all'indietro" << node->value << "->" <<neighbor->value;
                } else if(neighbor->color == Color::Black){
                    if(node->tempo_scoperta < neighbor->tempo_fine){
                        out << "Arco in avanti: " << node->value << "->" << neighbor->value << ")\n";
                    } else {
                        out << "Arco trasversale: (" << node->value << "->" << neighbor->value << ")\n";
                    }
                }
            }

            node->color = Color::Black;
            time++;
            node->tempo_fine = time;
        }

    public:
        vector<Arco<T>*> edges;

        Node<T>* add_node(T val){
            if(!nodes.count(val))
            {
                nodes[val] = new Node<T>(val);
            }
            return nodes[val];
        }

        void add_arco(T from, T to, int weight){
            Node<T>* src = add_node(from);
            Node<T>* dest = add_node(to);
            edges.push_back(new Arco<T>(weight, src, dest));
            adj[from].emplace_back(to, weight);
        }

        void DFS(T start, ofstream &out){
            for(auto[_,node]: nodes){
                node->color = Color::White;
                node->padre = nullptr;
                node->tempo_scoperta = 0;
                node->tempo_fine = 0;
            }
            time = 0;

            if(nodes.count(start))
            {
                DFS_VISIT(nodes[start], out);
            }
        }

        void stamp(ofstream &out){
            for(const auto&[node,neighbors]:adj){
                out << node << "->";
                for(const auto &[dest,w] : neighbors){
                    out << "(" << dest << ", peso: " << w << ")";
                }
                out << "\n";
            }
        }

};


int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n,m;
    in >> n >> m;

    GrafoDiretto<int> g;
    for(int i = 0; i < m; ++i)
    {
        int u,v,w;
        in >> u>> v >> w;
        g.add_arco(u,v,w);
    }

    out << "Lista adiacenza \n";
    g.stamp(out);

    out << "DFS\n";
    g.DFS(0, out);

    cout << "miao";
    return 0;

}