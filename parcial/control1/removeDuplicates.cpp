#include <iostream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    void push_back(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* current = head;

        while (current->next != nullptr)
            current = current->next;

        current->next = newNode;
    }

    void print() const {
        Node* current = head;

        while (current != nullptr) {
            cout << current->data;

            if (current->next != nullptr)
                cout << " -> ";

            current = current->next;
        }

        cout << endl;
    }

    void removeDuplicates() {

        // =====================================================
        // COMPLETE EL CODIGO AQUI
        // =====================================================

        Node* p = head;
        while (p) {
            if (p->next && p->data == p->next->data) {
                Node* tmp = p->next; 
                p->next = p->next->next;
                delete tmp;
                tmp = nullptr;
            }
            else {
                p = p->next;
            }
        }



        // =====================================================
    }
};

void runTest(int id, const int* values, int n, const string& expected) {
    LinkedList list;

    for (int i = 0; i < n; i++)
        list.push_back(values[i]);

    cout << "===== TEST " << id << " =====" << endl;

    cout << "Original:  ";
    list.print();

    list.removeDuplicates();

    cout << "Resultado: ";
    list.print();

    cout << "Esperado:  " << expected << endl;
    cout << endl;
}

int main() {

    int a[] = { 1, 2, 2, 3, 3, 3, 5, 7, 7 };
    runTest(1, a, 9, "1 -> 2 -> 3 -> 5 -> 7");

    int b[] = { 1, 1, 1, 1, 1 };
    runTest(2, b, 5, "1");

    int c[] = { 1, 2, 3, 4, 5 };
    runTest(3, c, 5, "1 -> 2 -> 3 -> 4 -> 5");

    int d[] = { 1, 1, 2, 2, 2, 3, 4, 4 };
    runTest(4, d, 8, "1 -> 2 -> 3 -> 4");

    runTest(5, nullptr, 0, "(lista vacia)");

    int f[] = { 4, 4, 9 };
    runTest(6, f, 3, "4 -> 9");

    return 0;
}   