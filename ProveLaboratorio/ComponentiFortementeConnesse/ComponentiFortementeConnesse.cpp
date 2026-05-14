#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

enum Color {WHITE, GREY, BLACK};


template<typename T>
class Node{

    public:
        T value;
        Color color = WHITE;
        Node<T>* parent = nullptr;

    Node(T val) : value(val){}

};


template<typename T>
class Edge{

    public:
        Node<T>* from;
        Node<T>* to;
        int weight;
    
    Edge(Node<T>*f, Node<T>*t, int w = 1) : from(f), to(t), weight(w) {}
};


template<typename T>
class GrafoDiretto{

    private:
        map<T, Node<T>*> nodes;
        map<T, vector<Edge<T>*>> adj;
        map<T, vector<Edge<T>*>> adj_transposed;
        map<T, int> finish_time;
        int time = 0;
        vector<Edge<T>*> all_edges;


    void dfs_visit(Node<T>* node)
    {
        node->color = GREY;
        for (const auto& edge : adj[node->value]){
            Node<T>* next = edge->to;
            if(next->color == WHITE){
                next->parent = node;
                dfs_visit(next);
            }
        }
        node->color = BLACK;
        finish_time[node->value] = ++time;
    }

    void dfs_visit_transposed(Node<T>* node, vector<T>& component){
        node->color = GREY;
        component.push_back(node->value);
        for(const auto& edge: adj_transposed[node->value]){
            Node<T>* next = edge->to;
            if(next->color == WHITE){
                dfs_visit_transposed(next, component);
            }
        }
        node->color = BLACK;
    }

    public:
    
    void add_edge(T u, T v, int weight = 1){
        if(nodes.count(u) == 0) nodes[u] = new Node<T>(u);
        if(nodes.count(v) == 0) nodes[v] = new Node<T>(v);

        Node<T>* from = nodes[u];
        Node<T>* to   = nodes[v];

        auto* edge = new Edge<T>(from, to, weight);
        auto* edge_rev = new Edge<T>(from, to, weight);

        adj[u].push_back(edge);
        adj_transposed[v].push_back(edge_rev);
        all_edges.push_back(edge);
        all_edges.push_back(edge_rev); //cleanup
    }
    
    vector<vector<T>> find_sccs(){

        //DFS normale, step 1
        for(auto & entry: nodes){
            entry.second->color = WHITE;
            entry.second->parent = nullptr;

        }
        time = 0;

        for(auto & entry: nodes){
            if(entry.second->color == WHITE){
                dfs_visit(entry.second);
            }
        }

        //Ordiniamo per tempo di fine decrescente
        vector<pair<int, T>> order;
        for (const auto& entry: finish_time){
            order.emplace_back(entry.second, entry.first);
        }
        sort(order.rbegin(), order.rend());

        //DFS sul trasposto
        for(auto& entry: nodes){
            entry.second->color = WHITE;
            entry.second->parent = nullptr;
        }

        vector<vector<T>> components;
        for(const auto& [_,node_val]: order){
            Node<T>* node = nodes[node_val];
            if(node->color == WHITE){
                vector<T> component;
                dfs_visit_transposed(node, component);
                components.push_back(component);
            }
        }
        return components;
    }

    ~GrafoDiretto() {
    for (auto& entry : nodes) delete entry.second;
    for (auto* edge : all_edges) delete edge;
}
};


int main() {
    ifstream in("input.txt");
    ofstream out ("output.txt");

    GrafoDiretto<int>g;
    int u,v;

    while(in >> u >> v){
        g.add_edge(u,v);
    }
    vector<vector<int>> sccs = g.find_sccs();

    out << "Componenti fortemente connesse:\n";
    for (const auto& comp: sccs){
        for (int node: comp){
            out << node << " ";
        }
        out << "\n";
    }

    cout << "Componenti fortemente connesse scritte in output.txt\n";
    return 0;
}
