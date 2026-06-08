/*
Utilizzando il paradigma della programmazione ad oggetti ed il linguaggio C++ 11,
progettare ed implementare, come classe, una struttura dati MIN HEAP che
consenta di caricare i numeri interi contenuti nel file HEAP.txt. Dotare la classe di
un metodo per scrivere nel file OUT.txt il contenuto del MIN HEAP.(pt. 18)

Dotare la classe MIN_HEAP del metodo DECREASE_KEY (i, key ) che decrementi a
key l'elemento i e lo riposizioni nel MIN HEAP. Mostrare a video il contenuto del
MIN HEAP dopo la chiamata DECREASE KEY(53,30). (pt. 6)

.Dotare la classe MIN HEAP del metodo HEAP SORT() che ordini in ordine
decrescente i numeri contenuti nel MIN HEAP. Mostrare a video il contenuto del
MIN HEAP dopo la chiamata HEAP SORT()(pt. 6)
*/



#include <iostream>
#include <vector>
#include <fstream>


using namespace std;


template<typename T>
class MinHeap{
    private:
        vector<T> data;
        inline int left(int i) {return 2*i+1; }
        inline int right(int i) {return 2*i +2; }
        inline int parent(int i) {return (i-1)/2; }

        void heapify(int i, int size){
            int l = left(i);
            int r = right(i);
            int smallest = i;

            if(l < size && data[l] < data[smallest]) 
                smallest = l;
            if(r < size && data[r] < data[smallest])
                smallest = r;
            
            if(smallest !=i){
                swap(data[i], data[smallest]);
                heapify(smallest, size);
            }
        }

    public: 
        //costruttore
        MinHeap(const vector<T>&vec) : data(vec) {
            for(int i = data.size()/2- 1; i >=0; --i)
                heapify(i, data.size());
        }

        void decrease_key(int i, T key){
            //Se il valore della chiamata Decrease(1,30), se il valore al posto 1 è maggiore non lo cambia manco morto
            if(key> data[i])
                return;
            data[i] = key;
            while(i > 0 && data[parent(i)] > data[i]){
                swap(data[i], data[parent(i)]);
                i = parent(i);
            }
        }

        void heapsort(){
            int n = data.size();
            for(int i = n-1; i >= 1; --i)
            {
                swap(data[0], data[i]);
                heapify(0,i);
            }
        }

        void print(ostream& out){
            for(auto v : data)
                out<< v << " ";
            out << "\n";
        }

};

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    vector<int> vals;

    if(in)
    {
        int v;
        while(in >> v)  
            vals.push_back(v);
    }

    MinHeap<int> H(vals);
    out<<"\nMin heap iniziale:\n";
    H.print(out);

    H.decrease_key(3,30);
    out << "\nMin Heap dopo decrease:\n";
    H.print(out);

    H.heapsort();
    out<< "\nHeap ordinato:\n";
    H.print(out);

    cout <<" finito";
    return 0;
}