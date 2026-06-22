#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

enum class Color {White, Grey, Black};

template <typename T>
class Node{
    public:
        T value;
        Color color = Color::White;
        int distance = -1;
        Node<T>* parent = nullptr;

        Node(T val) : value(val) {}
};

template <typename T>
class Arco{
    public:
        int weight;
        Node<T>* from;
        Node<T>* to;

        Arco(int w, Node<T>*f, Node<T>*t): weight(w), from(f), to(t) {}
};

template <typename T>
class Grafo{
    private:
        unordered_map<T, Node<T>*> nodes;
        unordered_map<T, vector<pair<T,int>>> adj;

        bool DFS_cycle(T u, T parent, unordered_set<T>& visitati)
        {
            visitati.insert(u);
            for(auto &[v,_]: adj[u])
            {
                if(v == parent)
                    continue;
                if(visitati.count(v))
                    return true;
                if(DFS_cycle(v,u,visitati))
                    return true;

            }
            return false;
        }
    
    public:
        
        vector<Arco<T>*> edges;

        Node<T>* add_node(T val)
        {
            if(!nodes.count(val))
            {
                nodes[val] = new Node<T>(val);

            }
            return nodes[val];
        }


        void add_edge(T from, T to, int weight)
        {
            Node<T>*src = add_node(from);
            Node<T>* dest = add_node(to);
            edges.push_back(new Arco<T>(weight, src, dest));
            adj[from].emplace_back(to, weight);
            adj[to].emplace_back(from, weight);
        }

        void print_adj_list(ostream & out) const {
            for(const auto &[node, neighbors]: adj)
            {
                out << node << "->";
                for(const auto&[dest,w]: neighbors)
                {
                    out << "(" << dest << ", peso: " << w << ") ";
                }
                out << "\n";
            }
        }

        void bfs(T start, ofstream & out)
        {
            if(!nodes.count(start))
            {
                cerr << "Nodo non presente";
                return;
            }
            for(auto &[_,node]: nodes)
            {
                node->color = Color::White;
                node->distance = -1;
                node->parent = nullptr;
            }

            Node<T>* src = nodes[start];
            src->color = Color::Grey;
            src->parent = nullptr;

            queue<Node<T>*> q;
            q.push(src);

            out << "Visita bfs dal nodo " << start << "\n";
            while(!q.empty())
            {
                Node<T>* u = q.front();
                q.pop();
                out << u->value << " ";

                for(auto &[v,_]:adj[u->value])
                {
                    Node<T>* neighbor = nodes[v];
                    if(neighbor->color == Color::White)
                    {
                        neighbor->color = Color::Grey;
                        neighbor->distance = u->distance + 1;
                        neighbor->parent = u;
                        q.push(neighbor);
                    }
                }

                u->color = Color::Black;
            }
            out << "\n";
        }

        bool is_tree()
        {
            if(edges.size() != nodes.size() -1)
                return false;
            unordered_set<T> visited;
            if(nodes.empty())
                return false;
            T start = nodes.begin()->first;
            if(DFS_cycle(start, start, visited))
                return false;
            
                return visited.size() == nodes.size();
        }

        bool is_binary()
        {
            if(!is_tree())
                return false;
            for(auto &[node, neighbors]: adj)
            {
                if(neighbors.size() > 3)
                    return false;
            }
            return true;
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
        int u,v,w;
        in >> u >> v >> w;
        g.add_edge(u,v,w);
    }

    out << "lista adiacenza \n";
    g.print_adj_list(out);

    g.bfs(0,out);

    bool tree = g.is_tree();
    bool binary_tree = g.is_binary();

    out << "\n Il grafo è un albero? " << (tree ? "Sì" : "No") << "\n";
    out << "\n L'albero è binario? " << (binary_tree ? "Sì" : "No") << "\n";

    cout << "miao";
    
    return 0;
}