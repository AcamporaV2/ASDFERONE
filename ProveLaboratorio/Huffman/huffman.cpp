// Librerie standard usate per I/O, strutture dati e stringhe
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;


// Nodo dell'albero di Huffman (foglia o interno)
class Node{
    public:

    char ch;      // carattere (solo per foglie)
    int freq;     // frequenza del carattere
    Node* left;   // figlio sinistro
    Node* right;  // figlio destro

    Node(char ch, int freq, Node* left = nullptr, Node* right = nullptr)
        : ch(ch), freq(freq), left(left), right(right) {}
};

// Comparatore per la coda di priorità (min-heap sulla freq)
struct Compare{

    bool operator() (Node* a, Node* b)
    {
        return a->freq > b->freq;
    }
};


// Classe che costruisce e gestisce la codifica/decodifica Huffman
class Huffman{
    private:
        Node* root = nullptr;                    // radice dell'albero
        unordered_map<char, string> codes;       // tabella carattere -> codice

        // Genera ricorsivamente i codici a partire dalla radice
        void genera_codici(Node* node, const string& current_code){
            if(!node) return;

            if(!node->left && !node->right){
                codes[node->ch] = current_code; // assegnazione codice alla foglia
            }

            genera_codici(node->left, current_code + "0");
            genera_codici(node->right, current_code + "1");
        }

    public:

        // Costruisce l'albero di Huffman dai dati (char, freq)
        void build(const vector<pair<char,int>>& data)
        {
            if(data.empty()) return;

            priority_queue<Node*, vector<Node*>, Compare> pq;
            for(auto & [ch, freq]: data)
            {
                pq.push(new Node(ch,freq)); // crea una foglia per ogni coppia
            }

            // Unisce i nodi a coppie fino a ottenere una sola radice
            while(pq.size() > 1)
            {
                Node* left = pq.top(); pq.pop();
                Node* right = pq.top(); pq.pop();
                Node* merged = new Node('\0', left->freq + right->freq, left, right);
                pq.push(merged);
            }

            root = pq.top();
            genera_codici(root, ""); // popola la tabella dei codici
        }

        // Stampa i codici su uno stream di output
        void print_codes(ostream & out){
            out << "codici di huffman:\n";

            for(const auto&[ch,code]: codes){
                out << ch << ": " << code << "\n";
            }
        }

        // Decodifica una stringa di bit usando l'albero
        string decode(const string & encoded_str) 
        {
            string decoded= "";
            Node* current = root;

            for(char bit: encoded_str)
            {
                if(!current) break;
                if(bit == '0'){
                    current = current->left;   // scendi a sinistra
                } else if(bit == '1'){
                    current = current->right;  // scendi a destra
                } else {
                    continue; // ignora caratteri non validi
                }


                if(current && !current->left && !current->right){
                    decoded += current->ch; // raggiunta una foglia -> carattere
                    current = root;         // ritorna alla radice
                }
            }
            return decoded;
        }
};


// Programma principale: legge coppie (char freq), costruisce Huffman e decodifica
int main()
{
    ifstream in("input.txt");        // file di input con coppie char freq
    ofstream out("output.txt");      // file di output per i codici

    vector<pair<char,int>> data;
    char ch;
    int freq;

    // Legge fino a EOF: coppia char freq per riga/stream
    while(in >> ch >> freq)
    {
        data.emplace_back(ch,freq);
    }

    Huffman h;
    h.build(data);          // costruisce l'albero e i codici
    h.print_codes(out);     // salva i codici su output.txt


    // Esempio: decodifica di una stringa codificata (da inserire o leggere)
    // Qui come esempio stringa codificata codici concatenati, ad esempio "010011..."
    string encoded_string;
    cout << "Inserisci la stringa codificata da decodificare (es. 010011...): ";
    cin >> encoded_string;

    string decoded = h.decode(encoded_string);
    out << "\nDecodifica della stringa '" << encoded_string << "': " << decoded << "\n";

    cout << "Codici Huffman generati e salvati in output.txt\n";
    cout << "Decodifica della stringa codificata: " << decoded << endl;


    return 0;
}