#include <iostream>
#include <vector>
#include <cassert> 

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
        if (nelem == 0)
            return;
        v[0] = v[nelem - 1];
        nelem--;

        if(nelem>0)
            heapifyDown(0);
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (v[index] > v[parent]) {
                swap(v[index], v[parent]);
                index = parent; 
            } 
            else {
                break; 
            }
        }
    }

    void heapifyDown(int index) {
        while (true) {
            int leftchild = (index * 2)+1;
            int rightchild = (index * 2)+2;
            int elegido = index; 
            
            if (leftchild < nelem && v[leftchild] > v[elegido])
                elegido = leftchild;
            if (rightchild < nelem && v[rightchild] > v[elegido])
                elegido = rightchild; 
            if (index == elegido)
                break;

            swap(v[index], v[elegido]);
            index = elegido; 
        }
    }

    void popTop() {
        return;
    }
    void print() {
        for (int a : v) {
            cout << a << " ";
        }
        cout << endl;
    }
    int top() {
        if (nelem == 0) throw runtime_error("Heap vacio");
        return v[0];
    }

};
void runTests() {
    cout << "Iniciando bateria de pruebas..." << endl;

    // Caso 1: Push básico y estructura del Max-Heap
    {
        CHeap h;
        h.push(10);
        h.push(20);
        h.push(5);
        h.push(30);
        // Debería reorganizarse para que 30 esté en la cima
        assert(h.top() == 30);
        assert(h.nelem == 4);
        cout << "Caso 1 (Push y Max-Heap) -> PASO" << endl;
    }

    // Caso 2: Pop básico (Extracción del máximo)
    {
        CHeap h;
        h.push(10); h.push(20); h.push(30);
        h.pop(); // Saca el 30
        assert(h.top() == 20); // El nuevo máximo debe ser 20
        h.pop(); // Saca el 20
        assert(h.top() == 10);
        assert(h.nelem == 1);
        cout << "Caso 2 (Pop basico) -> PASO" << endl;
    }

    // Caso 3: Pop de un heap con un solo elemento
    {
        CHeap h;
        h.push(5);
        h.pop();
        assert(h.nelem == 0);
        cout << "Caso 3 (Pop unico elemento) -> PASO" << endl;
    }

    // Caso 4: Valores repetidos
    {
        CHeap h;
        h.push(15); h.push(15); h.push(15);
        assert(h.top() == 15);
        h.pop();
        assert(h.top() == 15);
        assert(h.nelem == 2);
        cout << "Caso 4 (Valores repetidos) -> PASO" << endl;
    }

    // Caso 5: Valores negativos
    {
        CHeap h;
        h.push(-5); h.push(-10); h.push(-2); h.push(-1);
        // El mayor valor (más cercano a 0) es -1
        assert(h.top() == -1);
        h.pop();
        assert(h.top() == -2);
        cout << "Caso 5 (Valores negativos) -> PASO" << endl;
    }

    // Caso 6: Pop en un heap vacío (Resiliencia)
    {
        CHeap h;
        h.pop(); // No debería crashear (ahora tiene validación)
        assert(h.nelem == 0);
        cout << "Caso 6 (Pop heap vacio) -> PASO" << endl;
    }

    // Caso 7: Ordenamiento implícito (Heap Sort test)
    {
        CHeap h;
        vector<int> input = { 3, 1, 4, 1, 5, 9, 2, 6, 5 };
        for (int num : input) h.push(num);

        vector<int> output;
        while (h.nelem > 0) {
            output.push_back(h.top());
            h.pop();
        }

        // Debería salir ordenado de mayor a menor
        vector<int> expected = { 9, 6, 5, 5, 4, 3, 2, 1, 1 };
        assert(output == expected);
        cout << "Caso 7 (Extraccion completa / Ordenamiento) -> PASO" << endl;
    }

    cout << "¡Todos los tests pasaron exitosamente!" << endl;
}

int main() {
    runTests();
    return 0;
}