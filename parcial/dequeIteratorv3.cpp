#include <iostream>
#include <assert.h>
#include <cassert>
struct CDeque_iterator
{
    int** chunk;
    int* offset;
};

class CDeque
{
public:
    CDeque(int cs, int ms);
    ~CDeque();
    void expand_map();
    void push_front(int x);
    void pop_front();
    void push_back(int x);
    void pop_back();
    int& operator[](int i);
    int& front();
    int& back();
    void print();

private:
    int** map;
    int chunk_size, map_size;
    int nelem;
    CDeque_iterator start, finish;
};

CDeque::CDeque(int cs, int ms)
{
    chunk_size = cs;
    map_size = ms;
    map = new int* [map_size];

    start.chunk = finish.chunk = map + map_size / 2;
    *start.chunk = new int[chunk_size];

    start.offset = finish.offset = *start.chunk + chunk_size / 2;

    nelem = 0;
}

CDeque::~CDeque()
{
    for (int** c = start.chunk; c <= finish.chunk; ++c)
        delete[] * c;
    delete[] map;
}

void CDeque::expand_map()
{
}

void CDeque::push_front(int x)//0,expand, edge, nroaml
{
    if (start.offset == finish.offset) {
        *start.offset = x;
        nelem++;
        finish.offset++; 
        return;
    }
    
    if (start.offset == *start.chunk) {
        start.chunk--;
        *start.chunk = new int[chunk_size];

        start.offset = *start.chunk + chunk_size - 1;
        *start.offset = x;
        nelem++; 
        return; 
    }

    start.offset--; 
    *start.offset = x;
    nelem++;
}

void CDeque::pop_front()// 0,1, edge, normal 
{
    if (nelem == 0)return; 
    if (nelem == 1) {
        start.offset++; 
        nelem--;
        return;
    }
    if (start.offset == *start.chunk + chunk_size - 1) {
        delete[] *start.chunk;
        start.chunk++; 
        start.offset = *start.chunk;
        nelem--;
        return; 
    }
    start.offset++;
    nelem--; 
    return; 
}

void CDeque::push_back(int x) // vacio, expand, edge, normal
{
    if (start.offset == finish.offset) { // 0 elem 
        *finish.offset = x;
        finish.offset++; 
        nelem++; 
        return; 
    }

    //edge 
    if (finish.offset == *finish.chunk + chunk_size - 1) {
        *finish.offset = x; 
        finish.chunk++; 
        *finish.chunk = new int[chunk_size];
        finish.offset = *finish.chunk; 
        nelem++; 
        return;
    }

    //normal
    *finish.offset = x;
    finish.offset++;
    nelem++;
    return;
}

void CDeque::pop_back()
{
    if (nelem == 0) return;
    if (nelem == 1) {
        finish.offset--;
        nelem--;
        return;
    }
    if (finish.offset == *finish.chunk) {
        delete[] *finish.chunk;
        finish.chunk--;
        finish.offset = *finish.chunk + chunk_size - 1;
        nelem--;
        return;
    }

    finish.offset--;
    nelem--;
    return;
}

int& CDeque::operator[](int i)
{
    int startchunk = start.chunk - map;
    int startoffset = start.offset - *start.chunk; 

    int pos = (startchunk * chunk_size) + startoffset + i;
    int chunk = pos/chunk_size;
    int offset = pos % chunk_size; 

    return map[chunk][offset];
}

int& CDeque::front()
{
    return *start.offset; 
}

int& CDeque::back()
{
    // finish.offset esta al inicio de un chunk 
    if (finish.offset == *finish.chunk) {
        return *(*(finish.chunk - 1) + chunk_size - 1);
    }

    return *(finish.offset-1); 
}

void CDeque::print()
{
    if (nelem == 0) return;
    int** i;
    i = start.chunk;
    for (;i <= finish.chunk;i++) {
        int* inicio; 
        int* fin;
        if (i == start.chunk) inicio = start.offset;
        else inicio = *i; 

        if (i == finish.chunk) fin = finish.offset;
        else fin=*i+chunk_size-1;
        
        for (int*j=inicio;j && j <= fin;j++) {
            if (j == finish.offset)
                break; 
            std::cout << *j << " "; 
        }
    }
}
int main() {
    // Tamaño de chunk = 3, Tamaño de mapa = 7
    // Un chunk pequeño fuerza a probar los saltos de memoria ("edges") rápidamente.
    CDeque v(3, 7);

    std::cout << "===== TEST 1: PUSH BASICOS =====" << std::endl;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_front(5);
    v.push_front(1); // Debería forzar un salto de chunk en start
    v.print(); // Esperado: 1 5 10 20 30
    std::cout << "\n";
    assert(v.front() == 1);
    assert(v.back() == 30);

    std::cout << "===== TEST 2: OPERATOR[] =====" << std::endl;
    // Comprobamos la lectura cruzando chunks
    assert(v[0] == 1);
    assert(v[1] == 5);
    assert(v[2] == 10);
    assert(v[3] == 20);
    assert(v[4] == 30);

    // Comprobamos la escritura
    v[2] = 99;
    assert(v[2] == 99);
    std::cout << "Operator[] funciona correctamente cruzando chunks.\n";

    std::cout << "===== TEST 3: POP_BACK (Normal y Edge) =====" << std::endl;
    v.pop_back(); // quita 30
    assert(v.back() == 20);
    v.pop_back(); // quita 20
    assert(v.back() == 99);
    std::cout << "Pop_back normal y con salto de chunk correcto.\n";

    std::cout << "===== TEST 4: POP_FRONT (Normal y Edge) =====" << std::endl;
    v.pop_front(); // quita 1
    assert(v.front() == 5);
    v.pop_front(); // quita 5
    assert(v.front() == 99);
    std::cout << "Pop_front normal y con salto de chunk correcto.\n";

    std::cout << "===== TEST 5: COLLAPSE (Vaciado Total) =====" << std::endl;
    // Queda un solo elemento (99)
    v.pop_front(); // Ahora el deque debe estar vacío (nelem == 0)

    // Evitamos crashes si hacemos pop cuando está vacío
    v.pop_back();
    v.pop_front();

    std::cout << "Vaciado exitoso. Insertando de nuevo tras colapso...\n";
    v.push_back(42);
    v.push_front(24);
    assert(v.front() == 24);
    assert(v.back() == 42);
    assert(v[0] == 24);
    assert(v[1] == 42);

    std::cout << "\nTODOS LOS TESTS PASARON CON EXITO." << std::endl;
    return 0;
}