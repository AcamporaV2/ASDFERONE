#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include <queue>

using namespace std;

const int INF = numeric_limits<int>::max();

template<typename T>
class Node{

    public:
        T key;
        int distance;
        Node<T>* parent;

        Node(T k) : key(k), distance(INF), parent(nullptr) {}
};

template <typename T>
class Grafo {

    private:
        unordered_map<T, Node<T>*> Nodi;
        unordered_map<T, vector<pair<T,int>>> adiacenti;

    public:

        Grafo(const string &filename)
        {
            ifstream in(filename);
            T from, to;
            int peso;

            while (in >> from >> to >> peso)
            {
                if(!Nodi.count(from)) Nodi[from] = new Node<T>(from);
                if(!Nodi.count(to)) Nodi[to] = new Node<T>(to);
                adiacenti[from].emplace_back(to, peso);
            }
            in.close();
        }

        void dijkstra(const T& fonte, const string& outfile)
        {
            for(auto &[_,archi]: adiacenti)
            {
                for(auto &[_,w]: archi)
                {
                    if(w<0)
                    {
                        cerr << "Pesi negativi";
                    }
                }
            }

            Nodi[fonte]->distance = 0;

           using P = pair<int, T>;

            priority_queue<P,vector<P>, greater<>> prio_q;
            prio_q.push({0, fonte});

            while(!prio_q.empty())
            {
                auto[dist,u] = prio_q.top(); prio_q.pop();
                if(dist > Nodi[u]->distance)
                    continue;
                
                for(auto& [v, peso]: adiacenti[u])
                {
                    if(Nodi[v]->distance > peso + Nodi[u]->distance)
                    {
                        Nodi[v]->distance = peso + Nodi[u]->distance;
                        Nodi[v]->parent = Nodi[u];
                        prio_q.push({Nodi[v]->distance, v});
                    }
                }
            }

            scrivi_distanza(outfile);
        }

        void scrivi_distanza(const string & filename)
        {
            ofstream out(filename);
            for(auto &[chiave, nodo]: Nodi)
            {
                out << "Nodo: "<<chiave<< "\tDistanza: ";
                if(nodo->distance == INF)
                {
                    out << "INF";
                }
                else 
                    out << nodo->distance;
                out << endl;
            }
            out.close();
        }

};


int main()
{
    try
    {
        Grafo<string> dijkstra("input_dijkstra.txt");

        dijkstra.dijkstra("A","output_dijkstra.txt");

    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    
}