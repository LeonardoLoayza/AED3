#include <iostream>
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
    }
    T getY() {
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
        for (int i = 0;i < dimx;++i)
            ejeX[i] = nullptr;
        for (int i = 0;i < dimy;++i)
            ejeY[i] = nullptr;
    }

    bool findx(int x, int y, T value, Node<T>**& p);
    bool findy(int x, int y, T value, Node<T>**& q);
    void ins(int x, int y, T value); // lo hizo edgard, osea esta mal 
    void rem(int x, int y, T value);
    void set(int x, int y, T value); // 
    T get(int x, int y);
    void print();

private:
    Node<T>** ejeX;
    Node<T>** ejeY;
    int dimx;
    int dimy;
};
template<class T, T NE>
bool CMatrix<T, NE>::findx(int x, int y, T value, Node<T>**& p) {
    if (*(ejeX + x) != nullptr) {
        p = (ejeX + x);
        for (;*p && (*p)->getY() < y; p = &((*p)->abajo));
    }
    return *p && (*p) && (*p)->getY == y;
}

template<class T, T NE>
bool CMatrix<T, NE>::findy(int x, int y, T value, Node<T>**& q) {
    if (*(ejeY + y) != nullptr) {
        q = ejeY + y;
        for (; *q && (*q)->x < x; q = &((*q)->derecha));
    }

    return *q && (*q) && (*q)->x == x;
}


//void ins(int x, int y,T value);
template<class T, T NE>
void CMatrix<T, NE>::ins(int x, int y, T value) {
    Node<T>** p = nullptr;
    Node<T>** q = nullptr;
    bool x_vector = *(ejeX + x);
    bool y_vector = *(ejeY + y);

    if (dimx > x || dimy > y) return;

    bool f_x = findx(x, y, value, p);
    bool f_x = findy(x, y, value, q);
    
    //Existe el nodo x,y 
    if (f_x) {
        (*p)->val=value;
        return; 
    }

    //En caso no existe
    Node<T>* tmp = new Node<T>(x, y, value);

    if (!x_vector) {
        
    }
}



int main()
{
    std::cout << "Hello World";
    CMatrix<int, 0> m(5, 5);
    return 0;
}
