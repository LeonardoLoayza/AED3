#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int v, Node* l = nullptr, Node* r = nullptr) : data(v), left(l), right(r) {}
    Node() {};
};

class BinaryTree {
    Node* root;

    //printZigZag(root, true, 0);
    void printZigZag(Node* node, bool esZigZag, int direccionAnterior) {
        if (!node) return; 
        if (esZigZag) cout << node->data << " ";
        printZigZag(node->left, esZigZag && (direccionAnterior!=1), 1);
        printZigZag(node->right,esZigZag && (direccionAnterior!=2), 2);
    }
public:
    BinaryTree(Node* r) { root = r; }

    void printZigZag() {
        printZigZag(root, true, 0);
        cout << endl;
    }
};
    void runTest(int id, Node* root, const string& expected) {
        BinaryTree tree(root);
        cout << "===== TEST " << id << " =====" << endl;
        cout << "Salida:   ";
        tree.printZigZag();
        cout << "Esperado: " << expected << endl;
        cout << endl;
    }

int main() {
    /*
       TEST 1: El árbol del dibujo.
       Rompemos en el 3 (Izq->Izq) y en el 6 (Der->Der).
       El 8 se pierde porque desciende del 3.

                           1
                         /   \
                        /     \
                       /       \
                      2         5
                    /   \        \
                   /     \        \
                  3       4        6
                   \     /
                    \   /
                     8  7
    */
    Node* t1 = new Node(1,
        new Node(2,
            new Node(3, nullptr, new Node(8)),
            new Node(4, new Node(7), nullptr)
        ),
        new Node(5, nullptr, new Node(6))
    );
    runTest(1, t1, "1 2 4 7 5");


    /*
       TEST 2: Solo hijos izquierdos.
       El 10 es raíz. El 20 es su hijo izquierdo (válido).
       El 30 rompe la regla (Izq->Izq).

                    10
                   /
                 20
                /
              30
             /
           40
    */
    Node* t2 = new Node(10,
        new Node(20,
            new Node(30,
                new Node(40)
            )
        )
    );
    runTest(2, t2, "10 20");


    /*
       TEST 3: Zig-Zag perfecto de un solo camino.
       Todos alternan estrictamente.

                    100
                      \
                      90
                      /
                    80
                      \
                      70
    */
    Node* t3 = new Node(100, nullptr,
        new Node(90,
            new Node(80, nullptr, new Node(70))
        )
    );
    runTest(3, t3, "100 90 80 70");


    /*
       TEST 4: Un solo nodo (Raíz).
    */
    Node* t4 = new Node(42);
    runTest(4, t4, "42");


    /*
       TEST 5: Árbol vacío.
    */
    runTest(5, nullptr, "");

    return 0;
}