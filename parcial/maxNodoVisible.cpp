#include <iostream>
#include <string>
#include <algorithm> // Para usar max(a, b)
#include <limits>    // Para el valor mínimo inicial

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int v, Node* l = nullptr, Node* r = nullptr) : data(v), left(l), right(r) {}
};

class BinaryTree {
    Node* root;

    // max_camino: el valor más grande que hemos visto desde la raíz hasta aquí
    void printVisibleNodes(Node* node, int max_camino) {
        if (!node) return;
        if (node->data >= max_camino)
            cout << node->data << " ";
        
        if (node->data >= max_camino) {
            max_camino = node->data;
        }
        printVisibleNodes(node->left, max_camino);

        printVisibleNodes(node->right, max_camino);
    }

public:
    BinaryTree(Node* r) { root = r; }

    void printVisibleNodes() {
        int infinito_negativo = numeric_limits<int>::min();
        printVisibleNodes(root, infinito_negativo);
        cout << endl;
    }
};

void runTest(int id, Node* root, const string& expected) {
    BinaryTree tree(root);
    cout << "===== TEST " << id << " =====" << endl;
    cout << "Salida:   ";
    tree.printVisibleNodes();
    cout << "Esperado: " << expected << endl;
    cout << endl;
}

int main() {
    /*
       TEST 1: El árbol del dibujo.
       10 es visible.
       5 está tapado por 10.
       3 está tapado por 10.
       12 es visible (12 >= 10).
       15 es visible (15 >= 10).
       9 está tapado por 15 (el máximo en su camino es 15).
       20 es visible (20 >= 15).
    */
    Node* t1 = new Node(10,
        new Node(5,
            new Node(3),
            new Node(12)
        ),
        new Node(15,
            new Node(9),
            new Node(20)
        )
    );
    runTest(1, t1, "10 12 15 20");


    /*
       TEST 2: Árbol estrictamente decreciente.
       Solo la raíz es visible porque todos los demás son más pequeños
       que el primer valor (100).
    */
    Node* t2 = new Node(100,
        new Node(50,
            new Node(20),
            nullptr
        ),
        new Node(80)
    );
    runTest(2, t2, "100");


    /*
       TEST 3: Árbol estrictamente creciente.
       TODOS son visibles porque cada hijo es mayor que su padre.
    */
    Node* t3 = new Node(1,
        nullptr,
        new Node(2,
            nullptr,
            new Node(3,
                nullptr,
                new Node(4)
            )
        )
    );
    runTest(3, t3, "1 2 3 4");


    /* TEST 4: Árbol con valores iguales (mayor o igual cuenta como visible) */
    Node* t4 = new Node(5,
        new Node(5,
            new Node(5),
            nullptr
        ),
        nullptr
    );
    runTest(4, t4, "5 5 5");

    return 0;
}