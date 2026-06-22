#include <iostream>
#include <fstream>


using namespace std;

template<typename K, typename V>
struct Node{
    public:
        K key;
        V val;
        Node* left = nullptr;
        Node*right = nullptr;
        Node* parent = nullptr;


        Node(K k, V v): key(k), val(v) {}
};


template <typename K, typename V>
class ABR{

    public:
        Node<K,V>* root;

        ABR() : root(nullptr) {}

        void insert(K key, V val)
        {
            Node<K,V>* nuovo = new Node<K,V>(key,val);
            Node<K,V>* padre = nullptr;
            Node<K,V>* curr = root;

            while(curr)
            {
                padre = curr;
                if(key < curr->key)
                {
                    curr = curr->left;
                }
                else if (key > curr->key)
                {
                    curr = curr->right;}

                else
                { 
                    curr->val = val;
                    delete nuovo;
                    return;
                }
            }

            nuovo->parent = padre;

            if(padre == nullptr)
                root = nuovo;
            else if(key < padre->key)
                padre->left = nuovo;
            else 
                padre->right = nuovo;
        }

        void preorder(Node<K,V>* nodo, ostream & out)
        {
            if(!nodo) return;
            out << nodo->key << ": " << nodo->val << " ";
            preorder(nodo->left, out);
            preorder(nodo->right, out);
        }

        void postorder(Node<K,V>* nodo, ostream & out)
        {
            if(!nodo) return;
            postorder(nodo->left,out);
            postorder(nodo->right,out);
            out << nodo->key << ": " << nodo->val << " ";
        }

        //ROBA CHE NON E' USCITA VEDENDO MA COMUNQUE POTREBBE IMMAGINANDO IL TUTTO 
        Node<K,V>* search(K key)
        {
            Node<K,V>* curr = root;
            while(curr && curr->key != key)
            {
                if (key < curr->key)
                    curr = curr->left;
                else 
                    curr = curr->right;
            }
            return curr;
        }

        Node<K,V>* minimum(Node<K,V>* nodo)
        {
            while(nodo && nodo->left)
                nodo = nodo->left;
            
            return nodo;
        }

        void transplant(Node<K,V>*u, Node<K,V>* v)
        {
            if(!u->parent)
                root = v;
            else if (u == u->parent->left)
                u->parent->left = v;
            else 
                u->parent->right = v;
            
            if(v)
                v->parent = u->parent;
        }

        void remove(K key)
        {
            Node<K,V>*z = search(key);
            if(!z) return;

            if(!z->left) 
                transplant(z, z->right); //no figlio SX, CASO 1
            else if(!z->right)
                transplant(z, z->left); //NO FIGLIO DX, CASO 2
            else 
            {
                //CASO 3 DUE FIGLI, TROVA IL SUCCESSORE
                Node<K,V>* y = minimum(z->right);
                
                if(y->parent != z)
                {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                transplant(z,y);
                y->left = z->left;
                y->left->parent = y;

            }
            delete z;
        }
};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    ABR<int,char> albero;
    int k; char v;

    while(in >> k >> v) 
        albero.insert(k,v);
    
    out << "preorder\n";
    albero.preorder(albero.root,out);
    
    out << "\npost order\n";
    albero.postorder(albero.root, out);

    cout << "finito";

    return 0;
}