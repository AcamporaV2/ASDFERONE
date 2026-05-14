#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>


using namespace std;

class Node{

    public:
        char c;
        int freq;
        Node* left;
        Node* right;

        Node(char c, int freq, Node* left = nullptr, Node* right= nullptr) 
            : c(c), freq(freq), left(left), right(right) {}
};

struct Compare{

    bool operator() (Node* a, Node* b)
    {
        return a->freq,b->freq;
    }
};

class Huffman {
    private:

        Node* radice = nullptr;
        unordered_map<char, string> codici;

        void genera_codici(Node* nodo, const string& codice_corrente)
        {
            if(!nodo) return;

            if(!nodo->left && !nodo->right)
            {
                codici[nodo->c] = codice_corrente;
            }

            genera_codici(nodo->left, codice_corrente + "0");
            genera_codici(nodo->right, codice_corrente + "1");
        }
    
    public:
        
        ~Huffman() {
            destroy_tree(radice);
        }

        void destroy_tree (Node* nodo)
        {
            if(!nodo) return;

            destroy_tree(nodo->left);
            destroy_tree(nodo->right);
            delete nodo;
        }

        void costruisci(const vector<pair<char, int>> & data)
        {
            priority_queue<Node*, vector<Node*>, Compare> coda_prio;

            for (auto &[c, freq]: data)
            {
                coda_prio.push(new Node(c, freq));
            }

            while(coda_prio.size() > 1)
            {
                Node* left = coda_prio.top(); coda_prio.pop();
                Node* right = coda_prio.top(); coda_prio.pop();
                Node* merge = new Node ('\0', left->freq + right->freq, left, right);
                coda_prio.push(merge);
            }

            radice = coda_prio.top();
            genera_codici(radice, "");
            
        }

        void stampa_codici(ofstream &out)
        {
            out << "Codici di huffman:\n";
            for(const auto&[c,codice]: codici)
            {
                out << c << ": " << codice << "\n";
            }
        }

        string decode(const string& encoded_str) const {
            string decoded = "";
            Node* current = radice;
            for (char bit : encoded_str) {
                if (!current) break;
                if (bit == '0') {
                    current = current->left;
                } else if (bit == '1') {
                    current = current->right;
                } else {
                    // Ignora caratteri non binari
                    continue;
                }

                // Se siamo in una foglia, aggiungiamo il carattere decodificato
                if (current && !current->left && !current->right) {
                    decoded += current->c;
                    current = radice;
                }
            }
            return decoded;
        }

        void print_codes(ostream& out) const {
        out << "Codici di Huffman:\n";
        for (const auto& [ch, code] : codici) {
            out << ch << ": " << code << "\n";
        }
    }

};


int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    vector<pair<char,int>> data;
    char c;
    int freq;

    while(in >> c >> freq)
    {
        data.emplace_back(c,freq);
    }

    Huffman albero;

    albero.costruisci(data);
    albero.stampa_codici(out);

    string stringa_codifica;
    cout << "Inserisci la stringa codificata da decodificare: ";
    cin >> stringa_codifica;

    string decodata = albero.decode(stringa_codifica);
    out << "\nDecodifica della stringa " << stringa_codifica << ": " << decodata << "\n";

    cout<< "decodifica della stringa codificata: " << decodata << endl;

    return 0;
}