#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

enum class Color {White, Grey, Black};

template <typename T>
class Nodo{
    public:

    T value;
    Color color = Color::White;
    Nodo<T>* parent = nullptr;

    Nodo(T val) : value(val) {}
};

template <typename T>
class Arco{

    public: 

        int weight;
        Nodo<T>* from;
        Nodo<T>* to;

        Arco(int w, Nodo<T>* f, Nodo<T>* t) : weight(w), from(f), to(t) {}
};

template <typename T>
class Grafo{
    private:
        unordered_map<T, Nodo<T>*> nodi;
        unordered_map<T, vector<T>> adj;


        bool ciclo_hamil_util(T curr, vector<T>&path, unordered_map<T,bool>& visitati){
            
            if(path.size() == nodi.size()){

                for (T neighbor : adj[curr]){
                    if(neighbor == path[0]){
                        path.push_back(path[0]);
                        return true;
                    }
                }
                return false;
            }

            for (T neighbor : adj[curr]){
                if(!visitati[neighbor]){
                    visitati[neighbor] = true;
                    path.push_back(neighbor);

                    if (ciclo_hamil_util(neighbor,path, visitati))
                    {
                        return true;
                    }
                    
                    visitati[neighbor] = false;
                    path.pop_back();
                    

                
                }
            }
            return false;
        }


        public:

            vector<Arco<T>*> edges;

            Nodo<T>* add_nodo(T val){
                if(!nodi.count(val)){
                    nodi[val] = new Nodo<T>(val);
                }
                return nodi[val];
            }

            void add_arco(T from, T to, int weight){
                Nodo<T>* src = add_nodo(from);
                Nodo<T>* dest = add_nodo(to);
                edges.push_back(new Arco<T>(weight, src, dest));
                adj[from].push_back(to);
            }

            void stampa(ostream& out){
                for(const auto&[node, neighbor]:adj){
                    out << node << "->";
                    for (const auto& dest: neighbor){
                        out << dest << " ";
                    }
                     out << "\n";
                }
               
            }

            void trova_ciclo_hamil(T start, ofstream&out){
                vector<T> path;
                unordered_map<T, bool> visitati;

                for (auto& [key,_]: nodi){
                    visitati[key] = false;
                }

                visitati[start] = true;
                path.push_back(start);

                if(ciclo_hamil_util(start,path,visitati)){
                    out << "ciclo trovato:\n";
                    for(auto& v: path)
                    {
                        out << v<< " ";
                    }
                    out << "\n";
                } else 
                {
                    out << "nessun ciclo trovato \n";
                }
            }


};

int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");

    int n,m;
    in >> n >> m;

    Grafo<int>g;

    for(int i = 0; i < m; ++i){
        int u,v,w;

        in>> u >> v >> w;
        g.add_arco(u,v,w);
    }

    out << "Lista adiacenza: \n";
    g.stampa(out);

    out << "\n ricerca ciclo hamiltoniano da 0:\n";
    g.trova_ciclo_hamil(0,out);

    cout << "finito tutto";
    return 0;
}