/*

Utilizzando il paradigma della programmazione ad oggetti ed il linguaggio
C++ 11, progettare ed implementare, come classe, una struttura dati albero binario
di ricerca che consenta di caricare le coppie chiave carattere contenute nel file
ABR.txt secondo l'ordine anticipato (preorder). Dotare la classe di un metodo per
scrivere nel file OUT.txt l'output della visita preorder dell'albero precedentemente
creato.


*/



#include <iostream>
#include <fstream>


using namespace std;

template<typename T, typename S>
class Node{

    public:
        T chiave;
        S valore;
        Node* left;
        Node* right;
        Node* parent;

        Node(T k, S v): chiave(k), valore(v), left(nullptr), right(nullptr), parent(nullptr) {}
};


template<typename T, typename S>
class ABR{
    public:

    Node<T,S>* radice;

    ABR() : radice(nullptr) {}

    void insert(T key, S val)
    {
        Node<T,S>* NodoIn = new Node<T,S>(key,val);
        Node<T,S>* ParenteNodo = nullptr;
        Node<T,S>* NodoCorrente = radice;

        while(NodoCorrente!= nullptr)
        {
            ParenteNodo = NodoCorrente;
            if(key < NodoCorrente->chiave)
            {
                NodoCorrente = NodoCorrente->left;
            } 
            else if (key > NodoCorrente->chiave)
            {
                NodoCorrente = NodoCorrente->right;
            }
            else 
            {
                NodoCorrente->valore = val;
                delete NodoIn;
                return;
            }
        }
        NodoIn->parent = ParenteNodo;
        if (ParenteNodo == nullptr) radice = NodoIn;
        else if (key < ParenteNodo->chiave) ParenteNodo->left = NodoIn;
        else ParenteNodo->right = NodoIn;
    }


    void preorder(Node<T,S>* nodo, ofstream& out)
    {
        if(!nodo) return;
        out << "chiave: "<< nodo->chiave << ", valore: " << nodo->valore << "\n";
        preorder(nodo->left, out);
        preorder(nodo->right, out);
    }

    void postorder(Node<T,S>* nodo, ofstream& out)
    {
        if(!nodo) return;
        postorder(nodo->left, out);
        postorder(nodo->right,out);            
        out << "chiave: " << nodo->chiave << ", valore: " << nodo->valore << "\n";

    }

};


int main()
{
    ifstream in("input.txt");
    ofstream out ("output.txt");

    ABR < int, char > albero;
    int chiave;
    char valore;

    while(in >> chiave >> valore)
    {
        albero.insert(chiave,valore);
    }

    out << "Preorder: \n";
    albero.preorder(albero.radice, out);

    out << "\nPostorder: \n";
    albero.postorder(albero.radice, out);
}