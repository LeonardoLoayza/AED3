
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

template <class T>
class Node {
public:
    int x, y;
    T val;
    Node<T>* abajo;
    Node<T>* derecha;

    Node(int _x, int _y, T _val) {
        x = _x;
        y = _y;
        val = _val;
        abajo = nullptr;
        derecha = nullptr;
    }

    T getY() const {
        return y;
    }
};

template <class T, T NE>
class CMatrix {
public:
    CMatrix(int _dimx, int _dimy) {
        dimx = _dimx;
        dimy = _dimy;

        ejeX = new Node<T>*[dimx];
        ejeY = new Node<T>*[dimy];

        for (int i = 0; i < dimx; ++i)
            ejeX[i] = nullptr;

        for (int i = 0; i < dimy; ++i)
            ejeY[i] = nullptr;
    }

    ~CMatrix() {
        for (int i = 0; i < dimx; ++i) {
            Node<T>* actual = ejeX[i];

            while (actual != nullptr) {
                Node<T>* d = actual;
                actual = actual->abajo;
                delete d;
            }
        }

        delete[] ejeX;
        delete[] ejeY;

        ejeX = nullptr;
        ejeY = nullptr;
    }

    bool findx(int x, int y, T value, Node<T>**& p);
    bool findy(int x, int y, T value, Node<T>**& q);

    void ins(int x, int y, T value);
    void rem(int x, int y, T value);
    void set(int x, int y, T value);
    T get(int x, int y);
    void print();

    bool puedePonerMina(int x, int y);
    bool ponerMina(int x, int y);

    bool colocarMinasRandom(int cantidad);

private:
    Node<T>** ejeX;
    Node<T>** ejeY;

    int dimx;
    int dimy;
};

// BUSCAR POR COLUMNA
template<class T, T NE>
bool CMatrix<T, NE>::findx(
    int x, int y, T value, Node<T>**& p
) {
    p = ejeX + x;

    for (; *p && (*p)->getY() < y; p = &((*p)->abajo));

    return *p && (*p)->getY() == y;
}

// BUSCAR POR FILA
template<class T, T NE>
bool CMatrix<T, NE>::findy(
    int x, int y, T value, Node<T>**& q
) {
    q = ejeY + y;

    for (; *q && (*q)->x < x; q = &((*q)->derecha));

    return *q && (*q)->x == x;
}

// INSERTAR
template<class T, T NE>
void CMatrix<T, NE>::ins(int x, int y, T value) {
    if (x < 0 || y < 0 || x >= dimx || y >= dimy)
        return;

    Node<T>** p = nullptr;
    Node<T>** q = nullptr;

    bool existe = findx(x, y, value, p);

    if (value == NE) {
        if (existe)
            rem(x, y, value);

        return;
    }

    if (existe) {
        (*p)->val = value;
        return;
    }

    findy(x, y, value, q);

    Node<T>* tmp = new Node<T>(x, y, value);

    tmp->abajo = *p;
    *p = tmp;

    tmp->derecha = *q;
    *q = tmp;
}

// ELIMINAR
template <class T, T NE>
void CMatrix<T, NE>::rem(int x, int y, T value) {
    if (x < 0 || y < 0 || x >= dimx || y >= dimy)
        return;

    Node<T>** p = nullptr;
    Node<T>** q = nullptr;

    bool existe = findx(x, y, value, p);

    if (!existe)
        return;

    findy(x, y, value, q);

    Node<T>* d = *p;

    *p = d->abajo;
    *q = d->derecha;

    delete d;
}

// OBTENER VALOR
template<class T, T NE>
T CMatrix<T, NE>::get(int x, int y) {
    if (x < 0 || y < 0 || x >= dimx || y >= dimy)
        return NE;

    Node<T>** p = nullptr;

    if (findx(x, y, NE, p))
        return (*p)->val;

    return NE;
}

// MODIFICAR
template<class T, T NE>
void CMatrix<T, NE>::set(int x, int y, T value) {
    ins(x, y, value);
}

// IMPRIMIR TABLERO
template<class T, T NE>
void CMatrix<T, NE>::print() {
    std::cout << "\n   ";

    for (int x = 0; x < dimx; ++x)
        std::cout << x << " ";

    std::cout << "\n  +" << std::string(dimx * 2, '-') << "\n";

    for (int y = 0; y < dimy; ++y) {
        std::cout << y << " | ";

        for (int x = 0; x < dimx; ++x) {
            T val = get(x, y);

            if (val == NE)
                std::cout << ". ";
            else
                std::cout << "1 ";
        }

        std::cout << "\n";
    }

    std::cout << "\n";
}

// VALIDAR POSICION DE MINA
template<class T, T NE>
bool CMatrix<T, NE>::puedePonerMina(int x, int y) {
    if (x < 0 || y < 0 || x >= dimx || y >= dimy)
        return false;

    // No repetir fila ni columna
    if (ejeX[x] != nullptr)
        return false;

    if (ejeY[y] != nullptr)
        return false;

    // Verificar que no existan minas alrededor
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {

            if (dx == 0 && dy == 0)
                continue;

            if (get(x + dx, y + dy) != NE)
                return false;
        }
    }

    return true;
}

// COLOCAR UNA MINA
template<class T, T NE>
bool CMatrix<T, NE>::ponerMina(int x, int y) {
    if (!puedePonerMina(x, y))
        return false;

    ins(x, y, 1);

    return true;
}

// COLOCAR MINAS ALEATORIAMENTE
template<class T, T NE>
bool CMatrix<T, NE>::colocarMinasRandom(int cantidad) {

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<std::pair<int, int>> posiciones;

    // Generar todas las coordenadas posibles
    for (int y = 0; y < dimy; ++y) {
        for (int x = 0; x < dimx; ++x) {
            posiciones.push_back({x, y});
        }
    }

    // Mezclar coordenadas
    std::shuffle(posiciones.begin(), posiciones.end(), gen);

    int colocadas = 0;

    for (const auto& pos : posiciones) {

        int x = pos.first;
        int y = pos.second;

        if (ponerMina(x, y)) {

            colocadas++;

            if (colocadas == cantidad)
                return true;
        }
    }

    return false;
}

// MAIN
int main() {

    int n = 0;

    std::cout << "Ingrese la dimension del tablero (N x N): ";

    if (!(std::cin >> n) || n <= 0)
        return 0;

    CMatrix<int, 0> tablero(n, n);

    std::cout << "\nTablero inicial:\n";
    tablero.print();

    int minas = n;

    std::cout << "Colocando " << minas
              << " minas aleatoriamente...\n";

    if (tablero.colocarMinasRandom(minas)) {

        std::cout << "\nTablero completado exitosamente.\n";
        std::cout << "Se colocaron " << minas << " minas.\n";

    } else {

        std::cout << "\nNo fue posible colocar todas las minas.\n";
    }

    std::cout << "\nTABLERO FINAL:\n";
    tablero.print();

    return 0;
}
