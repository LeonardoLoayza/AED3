#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void F1(int* ar, int n, int* s)
{
    for (int i = 0; i < n; i++)
    {
        *s += ar[i];
    }
}

void Fmax(int *ar,int n,int *maxlocal){
    *maxlocal=0;
    for(int i=0; i<n;i++){
        if (ar[i]>*maxlocal){
            *maxlocal=ar[i]; 
        }
    }
}

int main()
{
    int ar[16] = { 12, 45, 3, 89, 7, 23, 99, 14, 5, 67, 8, 31, 90, 11, 4, 15 };
    int xmax[]={0,0,0,0};
    int i = 0, nt = 4;

    vector<thread> ts(nt); 
    for(int i=0;i<nt;i++){
        ts[i]= thread(Fmax, &ar[i*4], 4, &xmax[i]);
    }
    for (int i = 0;i < nt;i++) {
        ts[i].join(); 
    }
    int m=0;
    for(int i=0;i<4;i++){
        if (xmax[i]>m){
            m=xmax[i]; 
        }
    }
    cout << m; 




    return 0;
}
