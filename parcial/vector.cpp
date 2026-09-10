// std, implementar 

#include <iostream>
#include <cassert>
using namespace std; 

// vector, linked list, list 
// forward list, double linked list, deque, queue 

// pushback, pushfront, pop back, pop front, operator, expand, collapse
// front, back, constrcut, destruct

struct CVector {
    int nelem;
    int maxe;
    int* v;
    CVector(int n) {
        maxe = n;
        nelem = 0;
        v = new int[maxe];
    }

    ~CVector() {
        delete [] v;
        v = 0;
    }


    void pushback(int x) {
        if (nelem >= maxe) { // expand
            expand(); 
            return; 
        }
        v[nelem] = x; 
        nelem++;
    }

    void popback() {
        if (nelem > 0) return;
        nelem--;
    }
    void popfront() {
        if (nelem > 0) return;
        for (int i = 0;i < nelem-1;i++) {
            v[i] = v[i + 1];
        }
        nelem--;
    }

    int operator[](int x) {
        assert(x < nelem && x>0);
        return v[x];
    }

    void pushfront(int x) {
        for (int i = nelem; i > 0; i--) {
            v[i] = v[i - 1];
        }
        v[0] = x;
        nelem++;
    }

    void expand() {
        int * nv = new int[maxe * 2];
        maxe = maxe * 2;
        for (int i = 0;i < nelem;i++) {
            nv[i] = v[i];
        }
        delete []v;
        v = nv;

        return; 
    }

    void collapse() {
        if (nelem < maxe / 2) {
            int newmaxe = maxe / 2;
            
            if (newmaxe < 1) {
                newmaxe = 1;
            }

            int* nv = new int[newmaxe];

            for (int i = 0;i < nelem;i++) {
                nv[i] = v[i];
            }
            delete[] v;
            v = nv;
            maxe = newmaxe;
        }
    }

    void print() {
        for (int i = 0;i < nelem;i++) {
            cout << v[i] << " ";
        }
        cout << endl;
    }
};
int main()
{
    CVector c(5); 
    c.pushback(7);c.pushback(4);c.pushback(5);
    c.print();
    c.popback();
    c.print();
}
