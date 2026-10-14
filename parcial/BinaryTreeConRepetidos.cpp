#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Modificar el arbol segun las indicaciones
//
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
private:
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(CBinNode* n);
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
    // ?
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
    if (Find(x, p)) {
        while (*p) {
            if ((*p)->value <= x)
                p = &((*p)->nodes[1]);
            else
                p = &((*p)->nodes[0]);
        }
    }

    *p = new CBinNode(x);
    return 0;
}
bool CBinTree::Remove(int x)
{
    CBinNode** p;
    if (!Find(x, p))
        return 0;

    while (Find(x, p)==true) {
        if ((*p)->nodes[0] && (*p)->nodes[1])
        {
            CBinNode** q = Rep(p);
            (*p)->value = (*q)->value;
            p = q;
        }
        CBinNode* t = *p;

        if ((*p)->nodes[0] == nullptr) *p = (*p)->nodes[1];
        else *p = (*p)->nodes[0];

        delete t;
    }

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

void CBinTree::InOrder(CBinNode* n)
{
    if (!n) return;
    InOrder(n->nodes[0]);
    cout << n->value << " ";
    InOrder(n->nodes[1]);
}

void CBinTree::Print()
{
    InOrder(m_root);
    cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    CBinTree t;

    // 1. Armamos un árbol normal
    t.Insert(20); // Raíz
    t.Insert(10); // Izquierda
    t.Insert(40); // Derecha
    t.Insert(30); // Izquierda del 40
    t.Insert(50); // Derecha del 40

    cout << "Arbol normal: ";
    t.Print(); // Deberia imprimir: 10 20 30 40 50

    // 2. AHORA insertamos el duplicado (aquí ocurre el bug)
    t.Insert(20);

    cout << "Arbol despues del duplicado: ";
    t.Print();

    return 0;
}