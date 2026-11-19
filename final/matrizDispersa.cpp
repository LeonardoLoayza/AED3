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
        abajo=nullptr; 
        derecha=nullptr; 
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
    p = (ejeX + x);
    for (;*p && (*p)->getY() < y; p = &((*p)->abajo));
    
    return *p && (*p)->getY() == y;
}

template<class T, T NE>
bool CMatrix<T, NE>::findy(int x, int y, T value, Node<T>**& q) {
    q = ejeY + y;
    for (; *q && (*q)->x < x; q = &((*q)->derecha));

    return *q && (*q)->x == x;
}

//void ins(int x, int y,T value);
template<class T, T NE>
void CMatrix<T, NE>::ins(int x, int y, T value) {
    // check boundaries 
    if(x<0 || y<0 || x>=dimx || y>=dimy) return; 
    
    Node<T>**p=nullptr;
    Node<T>**q=nullptr; 
    
    bool existe = findx(x,y,value,p); 
    
    // Por si pasan un 0, borramos o simplemente retornamos
    if(value==NE){
        if(existe){
            rem(x,y,value);
        }
        return; 
    }
    
    // existe el nodo, solo actualiza 
    if(existe){
        (*p)->val=value;
        return; 
    }
    
    // posiciona el pointer q
    findy(x,y,value,q); 
    
    // Crea nodo y reconecta 
    Node<T> * tmp = new Node<T>(x,y,value); 
    
    tmp->abajo=*p;
    *p=tmp; 
    
    tmp->derecha=*q; 
    *q=tmp;
    
    return ;
}

template <class T, T NE>
void CMatrix<T,NE>::rem(int x, int y, T value){
    // boudnaries
    if(x<0 || y<0 || x>=dimx || y>=dimy) 
        return; 
        
    Node<T>**p=nullptr; 
    Node<T>**q=nullptr; 
    
    bool existe = findx(x,y,value, p); 
    
    // no existe 
    if(!existe) 
        return; 
    
    // borra y reconecta, y limpia memoria 
    findy(x,y,value,q); 
    
    Node<T>*d=*p; 
    
    *p = d->abajo; 
    *q = d->derecha; 
    
    delete d; 
    return;     
}


int main()
{
    std::cout << "Hello World";
    CMatrix<int, 0> m(5, 5);
    return 0;
}
