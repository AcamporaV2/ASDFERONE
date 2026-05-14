#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

enum Color { white, grey, black};

template<typename T>
class Node{
    public:
        T valore;
        Color colore = white;
        Node<T>* padre = nullptr;

    Node(T val): valore(val) {}

};


template<typename T>
class Arco{
    public:
        int peso;
        Node<T>* from;
        Node<T>* to;


        Arco(int w, Node<T>* f, Node<T>* t): peso(w), from(f), to(t) {}


};


template<typename T>
class Grafo{
    private:

    unordered_map<T,Node<T>*> Nodi;
    unordered_map<T,vector<T>> adiacenti;

    bool ciclo_hamiltoniano(T curr, vector<T>&path, unordered_map<T,bool>&visitati)
    {
        if(path.size() == Nodi.size())
        {
            for(T vicini: adiacenti[curr])
            {
                if(vicini == path[0])
                {
                    path.push_back(path[0]);
                    return true;
                }
        
            }
            return false;
        }

        for (T vicini: adiacenti[curr])
        {
            if(!visitati[vicini])
            {
                visitati[vicini] = true;
                path.push_back(vicini);

                if(ciclo_hamiltoniano(vicini, path, visitati))
                {
                    return true;
                }
                visitati[vicini] = false;
                path.pop_back();
            }
        }
        return false;

    }

    public:
        vector<Arco<T>*> archi;

        Node<T>* agg_nodo(T val)
        {
            if(!Nodi.count(val))
            {
                Nodi[val] = new Node<T>(val);
            }
            return Nodi[val];
        }


        void agg_arco(T from, T to, int peso)
        {
            Node<T>* source = agg_nodo(from);
            Node<T>* destinazione = agg_nodo(to);
            archi.push_back(new Arco<T>(peso, source, destinazione));
            adiacenti[from].push_back(to);
        }

        void print_adjacency_list(ostream& out) const {
        for (const auto& [node, neighbors] : adiacenti) {
            out << node << " -> ";
            for (const auto& dest : neighbors) {
                out << dest << " ";
            }
            out << "\n";
            }
        }


        void trova_ciclo_hamil(T inizio, ofstream & out)
        {
            vector<T> Path;
            unordered_map<T,bool> visitati;

            for(auto&[key,_]: Nodi)
            {
                visitati[key] = false;
            }

            visitati[inizio] = true;
            Path.push_back(inizio);

            if(ciclo_hamiltoniano(inizio, Path ,visitati))
            {
                out << "Ciclo trovato \n";
                for(auto&v : Path)
                {
                    out << v << " ";
                }
                out <<"\n";
                
            } else 
            {
                out<< "no ciclo trovato\n";
            }
        }

};


int main()
{
    ifstream in("input.txt");
    ofstream out("output_diretto.txt");

    int n,m;
    in >> n >> m;

    Grafo<int> g;

    for(int i = 0; i < m; ++i)
    {
        int u,v,w;
        in >> u >> v>> w;
        g.agg_arco(u,v,w);
    }

    out << "Lista di adiacenza (grafo orientato):\n";
    g.print_adjacency_list(out);

    out<< "\nRicerca ciclo hamiltoniano dal nodo 0\n";
    g.trova_ciclo_hamil(0, out);

    return 0;

}