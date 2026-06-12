#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;


enum class Color {White, Grey, Black};

const int INF = 1e9;

template <typename T>
class Node{
    public:
        T value;
        Color color = Color::White;
        int distanza = INF;
        int tempo_scoperta = 0;
        int tempo_finale = 0;
        Node<T>* parent = nullptr;


        Node(T val): value(val){}
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

        unordered_map<T, Node<T>*> nodes;
        unordered_map<T, vector<pair<T,int>>> adj;
        int time = 0;

        void DFS_VISIT(Node<T>*node, ofstream& out){
            time++;
            node->tempo_scoperta = time;
            node->color = Color::Grey;

            for(auto& [neighbor_key,_]: adj[node->value]){
                Node<T>* neighbor = nodes[neighbor_key];

                if (neighbor->color == Color::White){
                    out << "Arco di Albero: (" << node->value << "->" << neighbor->value << ")\n";
                    neighbor->parent = node;
                    DFS_VISIT(neighbor,out);
                } else if(neighbor->color == Color::Grey){
                    out << "Arco all'indietro: (" << node->value << "->" << neighbor->value << ")\n";
                } else if(neighbor->color == Color::Black){
                    if(node->tempo_scoperta < neighbor->tempo_finale){
                        out << "Arco in Avanti : (" << node->value << "->" << neighbor->value << ")\n";
                    } else {
                        out << "Arco Trasversale: (" << node->value << "->" << neighbor->value << ")\n";
                    }
                }
            }

            node->color = Color::Black;
            time++;
            node->tempo_finale = time;
        }

    public: 
        vector<Arco<T>*> edges;

        Node<T>* add_node(T val){
            if (!nodes.count(val)){
                nodes[val] = new Node<T>(val);
            }
            return nodes[val];
        }

        void add_edge (T from, T to, int weight){
            Node<T>* src = add_node(from);
            Node<T>* dest = add_node(to);
            edges.push_back(new Arco<T>(weight, src, dest));
            adj[from].emplace_back(to,weight);
        }

        void DFS(T start, ofstream &out){
            for(auto[_, node]: nodes){
                node->color = Color::White;
                node->parent = nullptr;
                node->tempo_scoperta = 0;
                node->tempo_finale = 0;
            }
            time = 0;
            if(nodes.count(start)){
                DFS_VISIT(nodes[start], out);
            }
        }

        void stampa_lista(ofstream &out){
            for (const auto&[node, neighbors]: adj){
                out << node << "-> ";
                for (const auto&[dest,w]: neighbors){
                    out << "(" << dest << ", peso: " << w << ") ";
                }
                out << "\n";
            }
        }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n,m;
    in >> n >> m;

    GrafoDiretto<int> g;

    for(int i = 0; i< m; ++i){
        int u,v,w;
        in >> u >> v >> w;
        g.add_edge(u,v,w);
    }

    out << "Lista adiacenza (Grafo orientato): \n";
    g.stampa_lista(out);
    out << "\n Classificazione archi dopo DFS:\n";
    g.DFS(0, out);

    cout<< "tutto svolto";
    return 0;
}


