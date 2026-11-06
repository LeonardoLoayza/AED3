#include <iostream>
#include <assert.h>
using namespace std;
struct CNode
{
    CNode(int v)
    {
        value = v; next = 0;
    }
    int value;
    CNode* next;
};

class CForward_list
{
public:
    CForward_list();
    ~CForward_list();
    void push_front(int x);
    void pop_front();
    void push_back(int x);
    void pop_back();
    int& operator[](int i);
    int& front();
    int& back();
    void print();

    /*void merge(CForward_list& l2) {
        CNode* a = this->head; 
        CNode* b = l2.head;
        CNode* c = nullptr;
        CNode* d = nullptr; 
        while (a != nullptr) {
            if (a->value < b->value) {
                d = a->next;
                a->next = b;
                a = d;
            }
            else if (a->value > b->value) {
                c = b->next;
                b->next = a;
                a = b;
                b = c;
                a = a->next;
            }
        }
    }*/

    void merge(CForward_list& l2) {
        CNode* a = this->head;
        CNode* b = l2.head;
        CNode* nc = nullptr;
        CNode** p = &nc; 

        while (a!=nullptr && b!=nullptr) {
            if (a->value < b->value) {
                *p = a;
                a = a->next;
            }
            else{
                *p = b;
                b = b->next;
            }
            p = &((*p)->next);
        }

        if (!b) {
            *p = a;
        }
        else if (!a) {
            *p = b;
        }

        head = nc;
        this->nelem += l2.nelem;

        l2.head = nullptr; 
        l2.nelem = 0;
    }

private:
    CNode* head;
    int nelem;
};

CForward_list::CForward_list()
{
    head = 0;
    nelem = 0;
}

CForward_list::~CForward_list()
{
    // borrar elementos
}


void CForward_list::push_front(int x)
{
    CNode* t = new CNode(x);
    t->next = head;
    head = t;
    nelem++;
}

void CForward_list::pop_front()
{
    assert(nelem > 0);
    CNode* t = head;
    head = t->next;
    delete t;
    nelem--;
}

void CForward_list::push_back(int x)
{
    CNode** p;
    for (p = &head; *p != 0; p = &((*p)->next));
    *p = new CNode(x);
    nelem++;
}

void CForward_list::pop_back()
{
    assert(nelem > 0);
    CNode** p;
    for (p = &head; (*p)->next != 0; p = &((*p)->next));
    delete* p;
    *p = 0;
    nelem--;
}

int& CForward_list::operator[](int i)
{
    assert(i < nelem);
    CNode* q = head;
    for (int k = 0; k < i;++k, q = q->next);
    return q->value;
}

int& CForward_list::front()
{
    assert(nelem > 0);
    return head->value;
}

int& CForward_list::back()
{
    CNode* q = head;
    for (int k = 0; k < nelem - 1; ++k, q = q->next);
    return q->value;
}

void CForward_list::print()
{
    for (CNode* q = head; q; q = q->next)
        std::cout << q->value << " ";
    std::cout << "\n";
}

int main()
{
    CForward_list v;
    v.push_back(3);
    v.push_back(7);
    v.push_back(6);
    v.push_front(1);
    v.push_front(9);
    v.push_front(2);
    v.print();
    v.pop_back();
    v.pop_front();
    v.print();

    v[3] = 4;
    v.print();

    v.front() = 1;
    v.back() = 1;
    v.print();

    std::cout << "\n";
    cout << endl;
    CForward_list l1;
    l1.push_back(1);
    l1.push_back(3);

    CForward_list l2;
    l2.push_back(2);
    l2.push_back(4);

    l1.merge(l2);

    l1.print(); // Resultado esperado: 1 2 3 4

    return 0;
    
}

