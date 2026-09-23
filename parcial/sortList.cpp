
#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() {
        head = nullptr;
    }

    ~SinglyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_front(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    void print() {
        Node* current = head;
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << " -> ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void sort() {
        // Implementar
        // Restricciones:
        // - No usar arreglos ni contenedores STL adicionales
        // - No se pueden modificar los valores (data) de los nodos
        // - Solo se pueden usar punteros adicionales como variables auxiliares
        // - El ordenamiento debe hacerse reenlazando los punteros next de los nodos
        // 7-2-9-1-8-3-5

        Node* nc = nullptr;
        Node* c = head;
        Node* tmp = c->next;
        while (c != nullptr) {
            tmp = c->next;
            Node* s = nc;
            if (nc == nullptr) {
                c->next = nullptr;
                nc = c;
                c =tmp;
                continue; 
            }
            else if (c->data < nc->data) { // en caso c sea menor que nc  
                c->next = nc;
                nc = c;
                c = tmp;
                continue;
            }
            // c es mayor que nc, entonces buscamos su lugar en nc usando s y iterando 
            else if (s->next && s->next->data <= c->data) {
                while (s->next && s->next->data <= c->data) {
                    s = s->next;
                }
                c->next = s->next; 
                s->next = c;
                c = tmp;
                continue;
            }
        }
        head = nc;
    }
};

int main() {
    // Prueba 1: Lista desordenada general
    std::cout << "Prueba 1: Lista desordenada general" << std::endl;
    SinglyLinkedList lista1;
    lista1.push_front(5);    lista1.push_front(3);
    lista1.push_front(8);    lista1.push_front(1);
    lista1.push_front(9);    lista1.push_front(2);
    lista1.push_front(7);
    std::cout << "Antes: ";   lista1.print();
    lista1.sort();
    std::cout << "Despues: "; lista1.print();
    std::cout << std::endl;

    // Prueba 2: Lista en orden inverso (peor caso)
    std::cout << "Prueba 2: Lista en orden inverso" << std::endl;
    SinglyLinkedList lista2;
    lista2.push_front(1);    lista2.push_front(2);
    lista2.push_front(3);    lista2.push_front(4);
    lista2.push_front(5);    lista2.push_front(6);
    std::cout << "Antes: ";   lista2.print();
    lista2.sort();
    std::cout << "Despues: "; lista2.print();
    std::cout << std::endl;

    // Prueba 3: Lista ya ordenada
    std::cout << "Prueba 3: Lista ya ordenada" << std::endl;
    SinglyLinkedList lista3;
    lista3.push_front(5);    lista3.push_front(4);
    lista3.push_front(3);    lista3.push_front(2);
    lista3.push_front(1);
    std::cout << "Antes: ";   lista3.print();
    lista3.sort();
    std::cout << "Despues: "; lista3.print();
    std::cout << std::endl;

    // Prueba 4: Lista con un solo elemento
    std::cout << "Prueba 4: Lista con un solo elemento" << std::endl;
    SinglyLinkedList lista4;
    lista4.push_front(42);
    std::cout << "Antes: ";   lista4.print();
    lista4.sort();
    std::cout << "Despues: "; lista4.print();
    std::cout << std::endl;

    // Prueba 5: Lista con elementos repetidos
    std::cout << "Prueba 5: Lista con elementos repetidos" << std::endl;
    SinglyLinkedList lista5;
    lista5.push_front(4);    lista5.push_front(2);
    lista5.push_front(4);    lista5.push_front(1);
    lista5.push_front(2);    lista5.push_front(3);
    std::cout << "Antes: ";   lista5.print();
    lista5.sort();
    std::cout << "Despues: "; lista5.print();
    std::cout << std::endl;

    return 0;
}
