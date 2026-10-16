#include <iostream>
#include <stack>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v; nodes[0] = nodes[1] = 0;
    }
    int value;
    CBinNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool Insert(int x);
    bool Remove(int x);
    void Print();
    void PrintStackInOrder();
private:
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(CBinNode* n);
    void StackInOrder(CBinNode* n);
    CBinNode* m_root;
    bool m_b;
};

CBinTree::CBinTree()
{
    m_root = 0;
    m_b = 0;
}

CBinTree::~CBinTree()
{
}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for (p = &m_root;
        *p && (*p)->value != x;
        p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if (Find(x, p)) return 0;
    *p = new CBinNode(x);
    return 0;
}
bool CBinTree::Remove(int x)
{
    CBinNode** p;
    if (!Find(x, p)) return 0;
    if ((*p)->nodes[0] && (*p)->nodes[1])
    {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CBinNode* t = *p;
    *p = (*p)->nodes[(*p)->nodes[0] == 0];
    delete t;
    return 1;
}

CBinNode** CBinTree::Rep(CBinNode** q)
{
    m_b = !m_b;
    q = &((*q)->nodes[!m_b]);
    while ((*q)->nodes[m_b])
        q = &((*q)->nodes[m_b]);
    return q;
}

void CBinTree::Print()
{
    cout << "\nInOrder con recursividad\n";
    InOrder(m_root);
    cout << endl;
}

void CBinTree::InOrder(CBinNode* n)
{
    if (!n) return;
    InOrder(n->nodes[0]);
    cout << n->value << " ";
    InOrder(n->nodes[1]);
}

void CBinTree::PrintStackInOrder()
{
    cout << "\nInOrder con Stack\n";
    StackInOrder(m_root);
    cout << endl;
}
// Soluciones aqui!
//
void CBinTree::StackInOrder(CBinNode* n)
{
    if (!n) return; 
    stack<CBinNode*> s;
    CBinNode* c = m_root; 
    while (s.empty() == false || c != nullptr) {
        while (c != nullptr) { 
            s.push(c); 
            c = c->nodes[0];
        }
        c = s.top(); 
        s.pop();
        cout << c->value << " "; 
        c = c->nodes[1]; 
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    CBinTree t;
    t.Insert(50); t.Insert(30); t.Insert(60);
    t.Insert(80); t.Insert(55); t.Insert(11);
    t.Insert(33); t.Insert(5); t.Insert(14);
    t.Insert(31); t.Insert(48);
    t.Print();
    t.PrintStackInOrder();
}
