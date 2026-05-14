#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <functional>

using namespace std;


enum class Color {White, Grey, Black};

const int INF = 1e9;

template<typename T>
class Node{
    public:
        T value;                 // Valore del nodo
        Color color = Color::White; // Stato del nodo durante l'algoritmo
        int distance = INF;      // Distanza minima trovata finora
        Node<T>* parent = nullptr; // Padre nel MST
    

    Node(T val) : value(val) {}
};


template<typename T>
class Arco{

    public:
    int weight;       // Peso dell'arco
    Node<T>* from;    // Nodo di partenza
    Node<T>* to;      // Nodo di arrivo

     Arco(int w, Node<T>*f, Node<T>*t) : weight(w), from(f), to(t) {}
};


template<typename T>
class GrafoNondiretto{
    
    unordered_map<T, Node<T>*> nodes;
    unordered_map<T, vector<pair<T,int>>> adj;

    public:
        vector<Arco<T>*> edges; // Lista di tutti gli archi

        Node<T>* add_node(T val){
            // Crea il nodo solo se non esiste già
            if(!nodes.count(val)){
                nodes[val] = new Node<T>(val);
            }
            return nodes[val];
        }


        void add_edge(T from, T to, int weight){
            // Aggiunge l'arco e lo salva in entrambe le direzioni
            Node<T>*src = add_node(from);
            Node<T>*dest = add_node(to);
            edges.push_back(new Arco<T>(weight, src, dest));
            adj[from].emplace_back(to, weight);
            adj[to].emplace_back(from, weight); //Non orientato
        }

        void stampa(ostream& out){
            // Stampa la lista di adiacenza
            for (const auto& [node, neighbors] : adj){
                out << node << " -> ";
                for (const auto& [dest,w]: neighbors){
                    out << "(" << dest << ", peso: "<< w << ") ";
                }
                out << "\n";
            }
        }


        void prim(T start, ofstream& out){

            // Inizializza tutti i nodi prima di iniziare Prim
            for(auto&[_,node]: nodes){
                node->distance = INF;
                node->parent = nullptr;
                node->color = Color::White;
            }

            // Controlla che il nodo iniziale esista
            if(!nodes.count(start)){
                out << "nodo iniziale non trovato\n";
                return;
            }
            // Crea la priority queue: il nodo con distanza minore esce per primo
            auto cmp = [](Node<T>* a, Node<T>* b) { return a->distance > b->distance; };
            priority_queue<Node<T>*, vector<Node<T>*>, decltype(cmp)> pq(cmp);

            // Prende il nodo di partenza e gli assegna distanza 0
            Node<T>*src = nodes[start];
            src->distance = 0;
            // Inserisce il nodo iniziale nella coda
            pq.push(src);

            int total_weight = 0;

            // Finché ci sono nodi da visitare
            while(!pq.empty()){
                // Estrae il nodo con distanza minore
                Node<T>* u = pq.top();
                pq.pop();

                // Se è già stato chiuso, lo salta
                if(u->color == Color::Black) continue;

                // Marca il nodo come scelto nell'MST
                u->color = Color::Black;
                total_weight += u->distance;

                // Stampa l'arco scelto per arrivare a questo nodo
                if(u->parent != nullptr){
                    out << "Arco: (" << u->parent->value << " - " << u->value << ") peso: " << u->distance << "\n";
                } else {
                    // Il primo nodo è quello iniziale
                    out << "Nodo iniziale: " << u->value << "\n";
                }

                // Controlla tutti i vicini del nodo corrente
                for (auto &[v,w]: adj[u->value]){
                    Node<T>* neighbor = nodes[v];
                    // Se trova un arco più leggero, aggiorna il vicino
                    if(neighbor->color != Color::Black && w < neighbor->distance){
                        neighbor->distance = w;
                        neighbor->parent = u;
                        // Reinserisce il vicino con il nuovo peso migliore
                        pq.push(neighbor);
                    }
                }
            }
            // Stampa il peso totale dell'albero di copertura minimo
            out<< "\nPeso totale MST: "<< total_weight << "\n";

        }
};


int main()
{
    // Legge il grafo dal file e scrive il risultato su output.txt
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n,m;
    in >> n >> m;

    // Crea un grafo non diretto con interi
    GrafoNondiretto<int> g;

    // Legge tutti gli archi
    for(int i = 0; i < m; ++i){
        int u,v,w;
        in >> u >> v >> w;
        g.add_edge(u,v,w);
    }

    // Mostra il grafo e avvia Prim dal nodo 0
    out<< "Lista adiacenza\n";
    g.stampa(out);
    out <<"Albero Prim:\n";
    g.prim(0, out);

    // Fine esecuzione
    cout<< "finito";
    return 0;
}