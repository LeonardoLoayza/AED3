#include <iostream>
#include <vector>
#include <queue>
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
    void Print();
    void kneighbors(int x, int k);
private:
    bool Find(int x, CBinNode**& p);
    void InOrder(CBinNode* n);
    int absolute(int num) {
        if (num < 0)
            return num * -1;
        return num; 
    }
    void p(CBinNode* n, vector<int> &v) {
        if (!n)
            return; 
        p(n->nodes[0], v);
        v.push_back(n->value);
        p(n->nodes[1], v);
    }
    CBinNode* m_root;
};

CBinTree::CBinTree()
{
    m_root = 0;
}

CBinTree::~CBinTree()
{
}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for (p = &m_root; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if (Find(x, p)) return 0;
    *p = new CBinNode(x);
    return 0;
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
// Soluciones aqui!


void CBinTree::kneighbors(int x, int k)
{
    std::cout << "\n(" << x << "," << k << ") => ";
    vector<int> v; 
    p(m_root, v);

    bool x_existe; 
    int numeroaimprimir; 

    for (int i = 0;i < v.size();i++) {
        if (v[i] == x) {
            x_existe = true;
        }
    }
    if (x_existe) numeroaimprimir = k;
    else numeroaimprimir = k;

    int izq = 0; 
    int der = v.size() - 1;

    while (der + izq - 1 > numeroaimprimir) {
        if (abs(v[izq] - x) > abs(v[der]-x)) 
            izq++;
        if (abs(v[izq] - x) < abs(v[der] - x)) 
            der--;
    }

    for (int i = izq; i < der-1; i++) {
        cout << v[i] << " "; 
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    CBinTree t;
    t.Insert(55); t.Insert(41); t.Insert(77);
    t.Insert(33); t.Insert(47); t.Insert(61);
    t.Insert(88); t.Insert(20); t.Insert(36);
    t.Insert(44); t.Insert(51); t.Insert(57);
    t.Insert(65); t.Insert(80); t.Insert(99);
    t.Print();

    // (33, 4) = > 33 36 41 44
    // (88, 3) = > 77 80 88 99
    // (76, 2) = > 77 80

    t.kneighbors(33, 4);
    t.kneighbors(88, 3);
    t.kneighbors(76, 2);
    t.kneighbors(47, 5);
    t.kneighbors(61, 4);
    t.kneighbors(50, 3);
    t.kneighbors(81, 5);
    t.kneighbors(20, 7);
}