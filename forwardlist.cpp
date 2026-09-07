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


};

int main(){

}