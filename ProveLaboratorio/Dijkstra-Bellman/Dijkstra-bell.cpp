#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <limits>


using namespace std;

const int INF = numeric_limits<int>::max();

template <class T>
class Node{
    public:
        T key;
        int distance;
        Node* parent;

        Node(T k) : key(k), distance(INF), parent(nullptr) {}

};


template <class T>
class Graph {

    private:
        unordered_map<T, Node<T>*> nodes;
        unordered_map<T, vector<pair<T, int>>> adj;

    public:

        Graph(const string& filename){
            ifstream in(filename);
            T from, to;
            int weight;
            while(in >> from >> to >> weight){
                if(!nodes.count(from)) 
                    nodes[from] = new Node<T>(from);
                if(!nodes.count(to))
                    nodes[to] = new Node<T>(to);

                adj[from].emplace_back(to, weight);
            }
            in.close();
        }

        void reset(){
            for(auto& [_, node]: nodes){
                node->distance = INF;
                node->parent = nullptr;
            }
        }

        void dijkstra(const T& source, const string& outfile){
            for(auto& [_, edges] : adj)
                for(auto&[_,w] : edges)
                    if(w < 0)
                        throw runtime_error("No pesi negativi qui");


            reset();
            nodes[source]->distance = 0;

            using P = pair<int, T>;
            priority_queue<P, vector<P>, greater<>> pq;
            pq.push({0, source});

            while(!pq.empty()){
                auto [dist,u] = pq.top(); pq.pop();
                if(dist > nodes[u]->distance)
                    continue;
                for(auto &[v,weight]: adj[u])
                    {
                        if(nodes[v]->distance > nodes[u]->distance + weight)
                        {
                            nodes[v]->distance = nodes[u]->distance + weight;
                            nodes[v]->parent = nodes[u];
                            pq.push({nodes[v]->distance, v});
                        }
                    }
            }
            write_dist(outfile);
        }

        void bellman_ford(const T& source, const string& outfile){
            reset();
            nodes[source]->distance = 0;

            int V = nodes.size();
            for(int i = 0; i < V -1; ++i){
                for(auto&[u,edges]:adj){
                    for(auto&[v,w]: edges){
                        if(nodes[u]->distance != INF && nodes[v]->distance > nodes[u]->distance + w){
                            nodes[v]->distance = nodes[u]->distance + w;
                            nodes[v]->parent = nodes[u];
                        }
                    }
                }
            }

            for (auto& [u, edges] : adj) {
                        for (auto& [v, w] : edges) {
                            if (nodes[u]->distance != INF && nodes[v]->distance > nodes[u]->distance + w) {
                                throw runtime_error("Ciclo negativo rilevato.");
                            }
                        }
                    }
            
            write_dist(outfile);
        }

        void write_dist(const string& filename){
            ofstream out(filename);
            for(auto& [key,node] : nodes){
                out << "Nodo: "<< key << "\tDistanza: ";
                if(node->distance == INF)
                    out << "INF";
                else 
                    out << node->distance;
                out << endl;
            }
            out.close();
        }
};

int main()
{
     try {
        // Test Bellman-Ford
        Graph<string> g_bf("input_bell.txt");
        g_bf.bellman_ford("A", "output_bell.txt");

        // Test Dijkstra
        Graph<string> g_dj("input_dij.txt");
        g_dj.dijkstra("A", "output_dij.txt");

        cout << "Algoritmi eseguiti. Controlla i file di output.\n";
    } catch (const exception& e) {
        cerr << "Errore: " << e.what() << endl;
        return 1;
    }



    return 0;
}