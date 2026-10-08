#include <iostream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void push_back(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = tail = newNode;
            return;
        }

        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    void print() const {
        Node* current = head;

        while (current != nullptr) {
            cout << current->data;

            if (current->next != nullptr)
                cout << " <-> ";

            current = current->next;
        }

        cout << endl;
    }

    void printBackward() const {
        Node* current = tail;

        while (current != nullptr) {
            cout << current->data;

            if (current->prev != nullptr)
                cout << " <-> ";

            current = current->prev;
        }

        cout << endl;
    }

    void reverseInGroups(int k) {
        // =====================================================
        // COMPLETE EL CODIGO AQUI
        // =====================================================
        if (k <= 1 || head==nullptr)
            return;

        Node* current = head;
        Node* prevGroup = nullptr;

        while (current) {
            int count = 1;
            Node* first = current;
            Node* last = current;
            
            while (count < k && last->next) {
                last = last->next;
                count++; 
            }

            if (count < k) // no hay suficinete elementos
                break; 

            Node* before = first->prev;
            Node* after = last->next;

            current = first; 

            // invertir hasta llegar a last 
            while (current != after) {
                Node* temp = current->next;
                current->next = current->prev;
                current->prev = temp;
                current = temp;
            }

            //reconecta before 
            if (before) {
                before->next = last;
            }
            else {
                head = last;
            }
            last->prev = before;

            //conectar after 

            first->next = after;
            if (after)
                after->prev = first;

            // pasamos al siguiente bloque 
            current = after;
        }

        // encontrar el nuevo tail 
        tail = head; 
        while (tail && tail->next)
            tail = tail->next;
    }

};

void runTest(int id, int n, int k, const string& expected) {
    DoublyLinkedList list;

    for (int i = 1; i <= n; i++)
        list.push_back(i);

    cout << "===== TEST " << id << " (n = " << n << ", K = " << k << ") =====" << endl;

    cout << "Original:    ";
    list.print();

    list.reverseInGroups(k);

    cout << "Resultado:   ";
    list.print();

    cout << "Esperado:    " << expected << endl;

    cout << "Hacia atras: ";
    list.printBackward();

    cout << endl;
}

int main() {

    runTest(1, 8, 3, "3 <-> 2 <-> 1 <-> 6 <-> 5 <-> 4 <-> 7 <-> 8");
    runTest(2, 6, 2, "2 <-> 1 <-> 4 <-> 3 <-> 6 <-> 5");
    runTest(3, 5, 3, "3 <-> 2 <-> 1 <-> 4 <-> 5");
    runTest(4, 5, 10, "1 <-> 2 <-> 3 <-> 4 <-> 5");
    runTest(5, 5, 1, "1 <-> 2 <-> 3 <-> 4 <-> 5");
    runTest(6, 6, 6, "6 <-> 5 <-> 4 <-> 3 <-> 2 <-> 1");

    return 0;
}