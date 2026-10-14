// =====================================================================
// PREGUNTA 1 (6 pts) - Lista simple: reorder()
// =====================================================================
// Considere el siguiente programa de base. Se pide implementar el metodo
// reorder() que reordena la lista intercalando los nodos de los extremos:
//
//        L0 -> Ln -> L1 -> Ln-1 -> L2 -> Ln-2 -> ...
//
// Ejemplos:   1 2 3 4 5 6   queda   1 6 2 5 3 4
//             1 2 3 4 5     queda   1 5 2 4 3
//
// Restricciones:
//  - NO crear nodos nuevos (el test verifica Node::creados).
//  - NO modificar los valores (value): solo se reenlazan los next.
//  - NO usar arreglos ni contenedores de la STL (vector, deque, stack...).
//  - Debe funcionar con lista vacia, 1, 2 y 3 nodos, cantidad par e impar
//    y valores repetidos.
//  - Complejidad O(n) en tiempo y O(1) en memoria adicional.
// =====================================================================
#include <iostream>
#include <initializer_list>

struct Node
{
    int value;
    Node* next;
    static int creados;
    Node(int v) { value = v; next = nullptr; creados++; }
};
int Node::creados = 0;

class CList
{
public:
    CList();
    ~CList();
    void push_back(int x);
    void push_back(std::initializer_list<int> values);
    void print();
    void reorder();

private:
    Node* head;
};

CList::CList()
{
    head = nullptr;
}

CList::~CList()
{
    while (head) {
        Node* t = head;
        head = head->next;
        delete t;
    }
}

void CList::push_back(int x)
{
    Node** p = &head;
    while (*p)
        p = &(*p)->next;
    *p = new Node(x);
}

void CList::push_back(std::initializer_list<int> values)
{
    for (int x : values) push_back(x);
}

void CList::print()
{
    int n = 0;
    for (Node* p = head; p; p = p->next) {
        std::cout << p->value << " ";
        if (++n > 100) { std::cout << "... (posible ciclo)"; break; }
    }
    std::cout << "\n";
}

void CList::reorder()
{

    Node** p = &head;
    Node** q = &head;
    if (!*p)
        return;
    while (*p && *q){

        // hallar el nodo final 
        while ( (*q)->next ) {
            q = &((*q)->next);
        }
        // caso 1 nodo 

        if (*p == *q) 
            break; 

        if ((*p)->next == *q) {
            break; 
        }

        Node* tmp = (*p)->next;
        (*p)->next = *q; 
        (*q)->next = tmp; 
        *q = nullptr; 
        q = &head; 
        p = &((*p)->next); 
        p = &((*p)->next);
    }

}

int main()
{
    int antes;

    std::cout << "Caso 1: lista vacia" << std::endl;
    CList l1;
    antes = Node::creados;
    l1.reorder();
    std::cout << "esperado:  (nada)\n";
    std::cout << "reorder:   "; l1.print();
    std::cout << "nodos nuevos: " << Node::creados - antes << "   esperado: 0\n\n";

    std::cout << "Caso 2: un nodo" << std::endl;
    CList l2;
    l2.push_back({ 7 });
    antes = Node::creados;
    l2.reorder();
    std::cout << "esperado:  7\n";
    std::cout << "reorder:   "; l2.print();
    std::cout << "nodos nuevos: " << Node::creados - antes << "   esperado: 0\n\n";

    std::cout << "Caso 3: dos nodos" << std::endl;
    CList l3;
    l3.push_back({ 1, 2 });
    antes = Node::creados;
    l3.reorder();
    std::cout << "esperado:  1 2\n";
    std::cout << "reorder:   "; l3.print();
    std::cout << "nodos nuevos: " << Node::creados - antes << "   esperado: 0\n\n";

    std::cout << "Caso 4: tres nodos" << std::endl;
    CList l4;
    l4.push_back({ 1, 2, 3 });
    antes = Node::creados;
    l4.reorder();
    std::cout << "esperado:  1 3 2\n";
    std::cout << "reorder:   "; l4.print();
    std::cout << "nodos nuevos: " << Node::creados - antes << "   esperado: 0\n\n";

    std::cout << "Caso 5: cantidad par" << std::endl;
    CList l5;
    l5.push_back({ 1, 2, 3, 4, 5, 6 });
    antes = Node::creados;
    l5.reorder();
    std::cout << "esperado:  1 6 2 5 3 4\n";
    std::cout << "reorder:   "; l5.print();
    std::cout << "nodos nuevos: " << Node::creados - antes << "   esperado: 0\n\n";

    std::cout << "Caso 6: cantidad impar" << std::endl;
    CList l6;
    l6.push_back({ 10, 20, 30, 40, 50, 60, 70 });
    antes = Node::creados;
    l6.reorder();
    std::cout << "esperado:  10 70 20 60 30 50 40\n";
    std::cout << "reorder:   "; l6.print();
    std::cout << "nodos nuevos: " << Node::creados - antes << "   esperado: 0\n\n";

    std::cout << "Caso 7: valores repetidos" << std::endl;
    CList l7;
    l7.push_back({ 4, 4, 7, 7, 1, 1, 9, 9, 2 });
    antes = Node::creados;
    l7.reorder();
    std::cout << "esperado:  4 2 4 9 7 9 7 1 1\n";
    std::cout << "reorder:   "; l7.print();
    std::cout << "nodos nuevos: " << Node::creados - antes << "   esperado: 0\n\n";

    std::cout << "Caso 8: se aplica dos veces (la 2da debe dar otro orden)" << std::endl;
    CList l8;
    l8.push_back({ 1, 2, 3, 4, 5, 6 });
    l8.reorder();
    l8.reorder();
    std::cout << "esperado:  1 4 6 3 2 5\n";
    std::cout << "reorder:   "; l8.print();
    std::cout << "\n";

    return 0;
}