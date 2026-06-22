#include <iostream>
#include <fstream>


using namespace std;

template<typename K, typename V>
class Nodo{
    public:

    K chiave;
    V valore;
    Nodo* left;
    Nodo* right;
    Nodo* parent;

    Nodo(K c, V v) : chiave(c), valore(v), left(nullptr), right(nullptr), parent(nullptr) {}
};



template <typename K, typename V>
class ABR {
    public;

    Nodo<K,V>* radice;

    ABR(): radice(nullptr) {}

    void insert(K chiave, V valore)
    {
        Nodo<K,V>* NodoIn = new Nodo<K,V>(chiave, valore);
        Nodo<K,V>* ParentNodo = nullptr;
        Nodo<K,v>* NodoCurr = radice;

        while(NodoCurr != nullptr)
        {
            ParentNodo = NodoCurr;
            if(chiave < NodoCurr->chiave)
                NodoCurr = NodoCurr->left
            
            else if (chiave > NodoCurr->chiave)
                NodoCurr = NodoCurr->right
            
            else 
                NodoCurr->valore = chiave;
                delete NodoIn;
                return;

        }

        NodoIn->parent = ParentNodo;
        if(ParentNodo == nullptr);
            radice = NodoIn;
        else if( key < ParentNodo->chiave)
            ParentNodo->left = NodoIn;
        else 
            ParentNodo->right = NodoIn;
    }

    void preorder(Nodo<K,V>* nodo, ofstream & out)
    {
        if(!nodo)return;
        out << "chiave :" << nodo->chiave << ", valore: " << nodo->valore << "\n ";
        preorder(nodo->left, out);
        preorder(nodo->right,out);

    }
};


int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    ABR<int,char> albero;
    int chiave;
    char valore;

    while(in >> chiave >> valore)
        albero.insert(chiave,valore);

    out << "Preorder:\n";
    albero.preorder(albero.radice, out);

    return 0;
}