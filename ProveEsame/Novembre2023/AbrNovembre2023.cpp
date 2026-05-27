/*

Utilizzando il paradigma della programmazione ad oggetti ed il linguaggio
C++ 11, progettare ed implementare, come classe, una struttura dati albero binario
di ricerca che consenta di caricare le coppie chiave carattere contenute nel file
ABR.txt secondo l'ordine anticipato (preorder). Dotare la classe di un metodo per
scrivere nel file OUT.txt l'output della visita preorder dell'albero precedentemente
creato. (pt. 18)

.Considerando l'albero come un albero di Huffman (in cui * equivale al carattere
nullo), implementare un metodo che riceva in input una stringa. di caratteri
maiuscoli e restituisca in output la stringa codificata con caratteri [0,1]. (pt. 6)

.Considerando l'albero come un albero di Huffman (in cui * equivale al carattere
nullo), implementare un metodo che riceva in input una stringa. codificata con
caratteri (0, 1) e restituisca in output la stringa decodificata.
(pt. 6)

*/


#include <iostream>
#include <fstream>

using namespace std;

template<typename K, typename V>
struct Node{
    K key;
    V value;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    Node(K k, V v): key(k), value(v) {}
};



template<typename K, typename V>
class ABR{

    public:
        Node<K,V>*root = nullptr;

        void insert(K key, V val){
            Node<K,V>*n = new Node<K,V>(key,val);
            Node<K,V>*p = nullptr;
            Node<K,V>* curr = root;

            while(curr){
                p = curr;

                if(key < curr->key)
                    curr = curr->left;
                else if(key > curr->key)
                    curr = curr->right;
                else  {
                    curr->value = val;
                    delete n;
                    return;
                }
            }

            n->parent = p;
            if(!p)
                root = n;
            else if(key < p->key)
                p->left = n;
            else 
                p->right = n;
        }

        void preorder(Node<K,V>*n, ostream & out)
        {
            if(!n) return;
            out << n->key << ": " << n->value << " ";
            preorder(n->left, out);
            preorder(n->right,out);
        }
};


int main()
{
    ifstream in("InputNovembre2023.txt");
    ofstream out("OutputNovembre2023.txt");

    ABR<int, char> tree;
    int k;
    char v;

    while(in >> k >> v)
        tree.insert(k,v);
    
    
    out<< "Preorder:";
    tree.preorder(tree.root, out);
    
    return 0;
}