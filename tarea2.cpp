#include <iostream>
using namespace std;
template<class O>
struct util {
    O o;

    void print(int * ini, int * fin) {
        for (int* it = ini; it <= fin; it++) {
            cout << *it << " ";
        }
        cout << endl;
    }

    void split(int* ini, int* fin) {
        int* q = ini; 
        int* p = fin; 
        while (p <= q) {
            if (o(*p)) {
                p++;
            }
            else if (!o(*q)) {
                q--;
            }
            else { // p cumple, q no cumple
                swap(*p, *q);
                p++;
                q--; 
            }
            print(ini, fin);
        }

    }
    void merge(int* ini, int* mid, int* fin) {
        int* p = ini; 
        int* q = mid + 1;

        while (p <= mid && q <= fin) {
            if (*p <= *q ) { // caso 1
                p++; 
            }
            else {
                int* r = p; 
                while (r != q) {
                    swap(*r, *q);
                    r++; 
                }
                p++; 
                mid++;
                q++;
            }
            print(ini, fin);
        }
    }

};
// no sabemos cuantos elem tiene el array, usar (fin - ini) + 1 
// ini = p , q = mid , fin 
// se hace un swap, tengo un int * r, que se hace swap con q, se incrementa 
// hasta que r llegue a q, ahi se incrementa q

// solo usar un array 
struct div3 {
    bool operator()(int a) {
        return !(a % 3);
    }
};

int main()
{
    /*util<div3> u;
    int arr[] = { 3, 2, 1, 5, 9, 7, 11, 8, 33, 25, 4 };
    int n = sizeof(arr) / sizeof(arr[0]);

    u.split(arr, arr + n - 1);

    for (int x : arr) 
        std::cout << x << " ";
    std::cout << std::endl;*/

    util<div3> u;
    int arr[] = { 3, 2, 1, 5, 9, 7, 11, 8, 33, 25, 4 };
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "=== SPLIT ===" << std::endl;
    u.split(arr, arr + n - 1);

    std::cout << std::endl << "=== MERGE ===" << std::endl;
    int arr2[] = { 1, 3, 5, 2, 4, 6 };
    u.merge(arr2, arr2 + 2, arr2 + 5);
}
