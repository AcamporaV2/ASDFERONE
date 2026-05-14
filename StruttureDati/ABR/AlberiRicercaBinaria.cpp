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
        Node<K,V>* root = nullptr;


        void insert(K key, V val){
            Node<K,V>* n = new Node<K,V>(key,val);
            Node<K,V>* p = nullptr;
            Node<K,V>* curr = root;

            while(curr){
                p = curr;
                if(key< curr->key)
                    curr = curr->left;
                else if(key > curr->key)
                    curr = curr->right;
                else {
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
        void preorder(Node<K,V>*n, ostream&out){
            if(!n) return;
            out << n->key << ":" << n->value << " ";
            preorder(n->left,out);
            preorder(n->right,out);
        }

        void postorder(Node<K,V>*n, ostream&out){
            if(!n) return;
            postorder(n->left,out);
            postorder(n->right, out);
            out << n->key << ": "<< n->value << " ";
        }
        
        Node<K,V>* search(K key){
            Node<K,V>* curr = root;
            while(curr && curr->key != key){
                if(key < curr->key) curr = curr->left;
                else curr = curr->right;
            }
            return curr;
        }

        Node<K,V>* minimum(Node<K,V>*n ){
            while(n && n->left) n = n->left;
            return n;
        }

        void transplant(Node<K,V>*u, Node<K,V>*v){
            if(!u->parent) root = v;
            else if(u == u->parent->left) u->parent->left = v;
            else u->parent->right = v;
            if(v) v->parent = u->parent;
        }


        void remove(K key){
            Node<K,V>* z = search(key);

            if(!z) return;

            if(!z->left) transplant(z,z->right);
            else if (!z->right) transplant(z,z->left);
            else {
                Node<K,V>* y = minimum(z->right);
                if(y->parent !=z){
                    transplant(y,y->right);
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


int main(){
    ifstream in("inputStringa.txt");
    ofstream out("output.txt");
    ABR<int,char> tree;
    int k; char v;

    while( in >> k >> v)
        tree.insert(k,v);

    out << "Preorder: ";
    tree.preorder(tree.root, out);
    out << "\n";

    out << "Postorder: ";
    tree.postorder(tree.root, out);
    out << "\n";

    cout << "Chiave da cercare: ";
    if(cin >> k){
        Node<int,char>* found = tree.search(k);
        if(found) 
            cout << "Trovato " << found->value << "\n";
        else cout << "non trovato\n";
    }


    return 0;
}