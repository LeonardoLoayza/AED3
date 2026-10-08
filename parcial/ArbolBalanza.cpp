#include <iostream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int v, Node* l = nullptr, Node* r = nullptr) : data(v), left(l), right(r) {}
};

class BinaryTree {
    Node* root;

    // Retorna la SUMA TOTAL de todo el subárbol que inicia en 'node'
    int printBalanzas(Node* node) { 
        if (node == nullptr) return 0;
        
        int leftsum = printBalanzas(node->left);
        int rightsum= printBalanzas(node->right);
        int suma = leftsum + rightsum;
        if (leftsum == rightsum)
            cout << node->data << " ";

        return node->data+suma; 
    }

public:
    BinaryTree(Node* r) { root = r; }

    void printBalanzas() {
        printBalanzas(root);
        cout << endl;
    }
};

void runTest(int id, Node* root, const string& expected) {
    BinaryTree tree(root);
    cout << "===== TEST " << id << " =====" << endl;
    cout << "Salida:   ";
    tree.printBalanzas();
    cout << "Esperado: " << expected << endl;
    cout << endl;
}

int main() {

    // Se dice que un nodo es una "Balanza Perfecta" si el peso total de TODA su 
    // rama izquierda es exactamente igual al peso total de TODA su rama derecha. 
    // El peso de una rama es la suma de los valores de todos los nodos que la componen.
    // Si un nodo no tiene un hijo (apunta a nullptr), ese lado pesa 0.
    // Por regla general, todas las hojas son Balanzas Perfectas (porque ambos lados pesan 0).
    
    /*
       TEST 1: El árbol del dibujo.
       Las hojas (9, 0, 6) se imprimen primero porque calculamos de abajo hacia arriba.
       Luego la raíz (10) se imprime porque 14 == 14.
    */
    Node* t0 = new Node(5, new Node(2), new Node(10));
    runTest(1, t0, "5");

    Node* t1 = new Node(10,
        new Node(5,
            new Node(9),
            new Node(0)
        ),
        new Node(8,
            new Node(6),
            nullptr
        )
    );
    runTest(1, t1, "9 0 6 10");

    /*
       TEST 2: Árbol perfectamente simétrico.
       Todos los nodos están balanceados.
              1
            /   \
           2     2
          / \   / \
         3   3 3   3
    */
    Node* t2 = new Node(1,
        new Node(2, new Node(3), new Node(3)),
        new Node(2, new Node(3), new Node(3))
    );
    runTest(2, t2, "3 3 2 3 3 2 1");

    /*
       TEST 3: Línea recta hacia la derecha (El peor caso para balanzas)
       Solo la hoja final está balanceada, el resto de nodos tiene 0 en la izq
       y mucho peso en la der.
         100
           \
            50
              \
               10
    */
    Node* t3 = new Node(100, nullptr,
        new Node(50, nullptr,
            new Node(10)
        )
    );
    runTest(3, t3, "10");

    return 0;
}