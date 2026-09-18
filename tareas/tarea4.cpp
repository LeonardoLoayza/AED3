#include <iostream>
#include <assert.h>
#include <string>
using namespace std; 

template <class T> 
class CVector
{
public:
    CVector(int s);
    ~CVector();
    void push_front(T x);
    void pop_front();
    void push_back(T x);
    void pop_back();
    void expand();
    void collapse();
    T& operator[](int i);
    T& front();
    T& back();
    void print();
    int sumavector(){
        int s=0;
        for(int i=0;i<nelem;i++){
            s+=vec[i];
        }
        return s; 
    }
    
private:
    int* vec;
    int nelem, size;
};
template <class T> 
CVector<T>::CVector(int s)
{
    size = s;
    vec = new T[size];
    nelem = 0;
}

template <class T> 
CVector<T>::~CVector()
{    delete vec;    }

template <class T> 
void CVector<T>::expand()
{
    int *q = new int [size*2];
    for (int i = 0; i < size; ++i )
        q[i] = vec[i];
    delete vec;
    vec = q;
    size *= 2;
}

template <class T> 
void CVector<T>::collapse()
{}

template <class T> 
void CVector<T>::push_front(T x)
{
    if ( nelem == size )
        expand();
    for ( int i = nelem; i > 0; i-- )
        vec[i] = vec[i-1];
    vec[0] = x;
    nelem++;
}

template <class T> 
void CVector<T>::pop_front()
{
    // criterio collpase
    for ( int i = 0; i < nelem; ++i )
        vec[i] = vec[i+1];
    nelem--;
}

template <class T> 
void CVector<T>::push_back(T x)
{
    if ( nelem == size )
        expand();
    vec[nelem] = x;
    nelem++;
}

template <class T> 
void CVector<T>::pop_back()
{
    // criterio collpase
    nelem--;
}

template <class T> 
T& CVector<T>::operator[](int i)
{
    assert(i < size);
    return *(vec+i); //vec[i];
}

template <class T> 
T& CVector<T>::front()
{
    return *vec;
}

template <class T> 
T& CVector<T>::back()
{
    return *(vec+nelem-1); //vec[nelem-1]
}

template <class T> 
void CVector<T>::print()
{
    for ( int i = 0; i < nelem; ++i )
        std::cout<<vec[i]<<" ";
}

int main()
{
    CVector<int> v(5);
    string s="13";
    int m9=9;

    for(int i=0; i<s.length();i++){
        int digito=s[i]-'0';
        v.push_back(digito); 
    }

    int suma= v.sumavector(); 

    while(m9<suma){
        m9+=9;
    }

    int respuesta = m9-suma; 
    if (respuesta == 0 || respuesta == 9) {
        respuesta = 9; 
    }
    
    cout << respuesta; 

    // convierto a string y meto los numeros a vector
    // recorro vector y sumo todo 
    // agarro el multiplo de 9 que sea mayor que la suma 
    // resta y doy el resultado 

}