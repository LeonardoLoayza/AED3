#include <iostream>
#include <vector>
using namespace std;

class CHeap {
public:
    vector <int> v;
    int nelem; 
    CHeap() {
        nelem = 0; 
    }
    void push(int x) {
        v.push_back(x);
        nelem++;
        heapifyUp(nelem - 1); 
    }

    void pop() {
        v[0] = v[nelem - 1]; 
        nelem--;
        heapifyDown();
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2; 
            if (v[index] > v[parent]) {
                swap(v[index], v[parent]);
            }
            index = parent; 
        }
    }
    void heapifyDown() {}
    void popTop() {}
    void print() {
        for (int a : v) {
            cout << a << " "; 
        }
        cout << endl; 
    }

};
int main() {
    CHeap h;

    // Caso 1: Pop de un heap con varios elementos
    h.push(10);
    h.push(20);
    h.push(30);
    h.push(40);
    h.print();

    h.pop();
    h.print();

    // Caso 2: Pop de un heap con un solo elemento
    CHeap h2;
    h2.push(5);
    h2.pop();
    h2.print();

    // Caso 3: Pop de un heap con elementos repetidos
    CHeap h3;
    h3.push(10);
    h3.push(10);
    h3.push(20);
    h3.push(20);
    h3.pop();
    h3.print();

    // Caso 4: Pop de un heap con valores negativos
    CHeap h4;
    h4.push(-5);
    h4.push(-2);
    h4.push(-10);
    h4.pop();
    h4.print();

    // Caso 5: Pop de un heap vacío
    CHeap h5;
    h5.pop();
    h5.print();

    return 0;
}
