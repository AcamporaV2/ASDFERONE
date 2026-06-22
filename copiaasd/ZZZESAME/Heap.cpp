
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

template <typename T>
class MinHeap {
    private:
        vector<T> data;
        inline int left(int i) {return 2*i+1;}
        inline int right(int i) {return 2*i +1;}
        inline int parent(int i){return (i-1)/2;}


        void heapify(int i, int size)
        {
            int l = left(i);
            int r = right(i);
            int smallest = i;

            if(l < size && data[l] < data[smallest])
                smallest = l;
            if(r < size && data[r] < data[smallest])
                smallest = r;
            
            if(smallest != i)
            {
                swap(data[i], data[smallest]);
                heapify(smallest, size);
            }
        }

    public: 
        
        MinHeap(const vector<T>&vec) : data(vec) {
            for(int i = data.size()/2 -1; i>= 0; --i)
                heapify(i, data.size());
        }

        void decrease_key(int i, T key)
        {
            if(key >data[i])
                return;
            data[i] = key;
            while(i > 0 && data[parent(i)] > data[i])
                swap(data[i], data[parent(i)]);
                i = parent(i);
        }
        void heapsort()
        {
            int n = data.size();
            for(int i = n-1; i>=1; --i)
            {
                swap(data[0], data[i]);
                heapify(0,i);
            }
        }

        void print(ostream& out)
        {
            for(auto v: data)
            {
                out << v << " ";
            }
            out << "\n";
        }
};