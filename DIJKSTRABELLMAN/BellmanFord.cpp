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
        Node* parent;

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

        void bellman_ford(const T& fonte, const string& outfile)
        {
            Nodi[fonte]->distance = 0;
            int V = Nodi.size();

            for(int i = 0; i < V - 1; ++i)
            {
                for(auto&[u,archi]: adiacenti)
                {
                    for(auto&[v,w]: archi)
                    {
                        if(Nodi[u]->distance != INF && Nodi[v]->distance > w + Nodi[u]->distance)
                        {
                            Nodi[v]->distance = Nodi[u]->distance + w;
                            Nodi[v]->parent = Nodi[u];
                        }
                    }
                }
            }


            for(auto&[u,archi]: adiacenti)
            {
                for(auto&[v,w]: archi)
                {
                    if(Nodi[u]->distance != INF && Nodi[v]->distance > w + Nodi[u]->distance)
                    {
                        throw runtime_error("Ciclo niggativo");
                    }
                }

            }

            scrivi_distanza(outfile);
        }

        void scrivi_distanza(const string & filename)
        {
            printf("ciao");
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
    try{
        Grafo<string> bellman("input_bf.txt");

        bellman.bellman_ford("A", "output_bf.txt");
    } catch (const exception&e)
    {
        cerr << "Errore" << e.what() << endl;
        return 1;
    }

    return 0;
}
