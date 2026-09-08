#include <iostream>
#include <vector>
using namespace std;


class CNode{
public: 
    int v;
    CNode * next; 
    CNode(int _v){
        v=_v;
        next=nullptr;
    }
};
    
class ForwardList{
public:     
    CNode * head;
    int nelem;
    ForwardList(){
        head=nullptr;
        nelem=0;
    }

    void pushback(int x){
        CNode**p=&head;
        while(*p){
            p=&((*p)->next);
        }
        *p=new CNode(x);
        nelem++;
        return; 
    }

    void pushfront(int x){
        CNode*n=new CNode(x);
        n->next=head;
        head=n; 
        nelem++;
        return;
    }

    void popback(){
        CNode**p=&head;
        while(*p&&(*p)->next){
            p=&((*p)->next);
        }
        delete *p;
        *p=nullptr;
        nelem--;
    }

    void popfront(){
        if(head==nullptr) return;
        CNode*n=head;
        head=head->next;
        delete n;
        n=0;
        nelem--;
    }

    int& operator[](int j){
        // assert j <= nelem
        CNode*p=head;
        for(int i=0;i<j;i++){
            p=p->next;
        }
        return p->v;
    }

    void print(){
        for(CNode *p = head; p != nullptr; p = p->next)
            cout << p->v << " ";
        cout << endl; 
    }

    // collapse 
    void collapse(){

    }

    void eraseAdyacentDuplicates(){
        CNode**p=&head;
        CNode*veci=nullptr;
        while(*p && (*p)->next){
            veci=(*p)->next;
            if ((*p)->v==veci->v){
                (*p)->next=veci->next;
                delete veci;
                nelem--;
            }
            else {
                p=&((*p)->next);
            }

        }
    }

};

int main(){
    ForwardList lista;
    // Insertamos: 1, 1, 1, 2, 3, 3, 4, 1
    lista.pushback(1);
    lista.pushback(1);
    lista.pushback(1);
    lista.pushback(2);
    lista.pushback(3);
    lista.pushback(3);
    lista.pushback(4);
    lista.pushback(1); // Este 1 se queda porque no es adyacente a los primeros
    cout << "Tamanio original: " << lista.nelem << endl;
    lista.eraseAdyacentDuplicates();
    cout << "Tamanio tras eraseDuplicates: " << lista.nelem << endl;
    // Imprimimos la lista
    cout << "Lista final: ";
    for(int i = 0; i < lista.nelem; i++){
        cout << lista[i] << " ";
    }
    cout << endl;

    return 0;


    // ForwardList f;
    // f.pushback(5); f.print(); 
    // f.pushback(5); f.print(); 
    // f.pushback(4); f.print(); 
    // f.pushfront(1); f.print(); 
    // f.popfront(); f.print(); 


}