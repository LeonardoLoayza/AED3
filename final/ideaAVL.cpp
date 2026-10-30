// ============================================================
// Arbol AVL fusionado:
//  - Estilo limpio, recursivo y generico (template)  [File 2]
//  - Destructor sin fugas, PrintLevels con altura y
//    balance, recorrido inorden iterativo, alturaMax  [File 1]
// ============================================================
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// ---------------- Nodo ----------------
template <typename T>
struct AVLNode {
    T key;
    AVLNode* left;
    AVLNode* right;
    int height; // Altura del subarbol con raiz en este nodo

    explicit AVLNode(const T& k)
        : key(k), left(nullptr), right(nullptr), height(1) {}
};

// ---------------- Arbol AVL ----------------
template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    // --- Utilidades de altura y balance ---
    static int height(const AVLNode<T>* n) { return n ? n->height : 0; }

    static void updateHeight(AVLNode<T>* n) {
        n->height = 1 + max(height(n->left), height(n->right));
    }

    // Factor de balance = altura(izquierda) - altura(derecha)
    static int balanceFactor(const AVLNode<T>* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    // --- Rotaciones ---
    // Rotacion simple a la derecha (caso LL)
    static AVLNode<T>* rotateRight(AVLNode<T>* y) {
        AVLNode<T>* x  = y->left;
        AVLNode<T>* T2 = x->right;

        x->right = y;
        y->left  = T2;

        updateHeight(y); // y ahora es hijo: actualizar primero
        updateHeight(x); // x ahora es la nueva raiz del subarbol
        return x;
    }

    // Rotacion simple a la izquierda (caso RR)
    static AVLNode<T>* rotateLeft(AVLNode<T>* x) {
        AVLNode<T>* y  = x->right;
        AVLNode<T>* T2 = y->left;

        y->left  = x;
        x->right = T2;

        updateHeight(x); // x ahora es hijo: actualizar primero
        updateHeight(y); // y ahora es la nueva raiz del subarbol
        return y;
    }

    // Rebalancea un nodo segun su factor de balance y devuelve
    // la nueva raiz del subarbol.
    static AVLNode<T>* rebalance(AVLNode<T>* n) {
        updateHeight(n);
        int bf = balanceFactor(n);

        if (bf > 1) {                       // Pesado a la izquierda
            if (balanceFactor(n->left) < 0) // Caso LR
                n->left = rotateLeft(n->left);
            return rotateRight(n);          // Caso LL
        }
        if (bf < -1) {                       // Pesado a la derecha
            if (balanceFactor(n->right) > 0) // Caso RL
                n->right = rotateRight(n->right);
            return rotateLeft(n);            // Caso RR
        }
        return n; // Ya esta balanceado
    }

    // --- Insercion recursiva ---
    static AVLNode<T>* insert(AVLNode<T>* n, const T& key, bool& inserted) {
        if (!n) {
            inserted = true;
            return new AVLNode<T>(key);
        }
        if (key < n->key)
            n->left = insert(n->left, key, inserted);
        else if (key > n->key)
            n->right = insert(n->right, key, inserted);
        else
            return n; // Duplicado: no se inserta

        return rebalance(n);
    }

    // Nodo con la clave minima (sucesor inorden)
    static AVLNode<T>* minValueNode(AVLNode<T>* n) {
        while (n->left) n = n->left;
        return n;
    }

    // --- Eliminacion recursiva ---
    static AVLNode<T>* remove(AVLNode<T>* n, const T& key, bool& removed) {
        if (!n) return nullptr;

        if (key < n->key) {
            n->left = remove(n->left, key, removed);
        } else if (key > n->key) {
            n->right = remove(n->right, key, removed);
        } else {
            removed = true;
            // Caso 0 o 1 hijo
            if (!n->left || !n->right) {
                AVLNode<T>* child = n->left ? n->left : n->right;
                delete n;
                return child; // Puede ser nullptr: lo maneja el llamador
            }
            // Caso 2 hijos: copiar el sucesor y eliminarlo
            AVLNode<T>* succ = minValueNode(n->right);
            n->key = succ->key;
            bool dummy;
            n->right = remove(n->right, succ->key, dummy);
        }
        return n ? rebalance(n) : nullptr;
    }

    // --- Recorridos y utilidades ---
    static void inorder(const AVLNode<T>* n) {
        if (!n) return;
        inorder(n->left);
        cout << n->key << ' ';
        inorder(n->right);
    }

    static void destroy(AVLNode<T>* n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroy(root); } // Sin fugas, sin mensajes

    // Regla de cinco: arbol no copiable (evita doble delete)
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    // Inserta la clave. Devuelve false si ya existia.
    bool insert(const T& key) {
        bool inserted = false;
        root = insert(root, key, inserted);
        return inserted;
    }

    // Elimina la clave. Devuelve false si no existia.
    bool remove(const T& key) {
        bool removed = false;
        root = remove(root, key, removed);
        return removed;
    }

    bool search(const T& key) const {
        AVLNode<T>* n = root;
        while (n) {
            if (key < n->key) n = n->left;
            else if (key > n->key) n = n->right;
            else return true;
        }
        return false;
    }

    void clear() {
        destroy(root);
        root = nullptr;
    }

    // La altura maxima es trivial: se lee de la raiz
    int alturaMax() const { return height(root); }

    // Recorrido inorden (recursivo)
    void printInorder() const {
        inorder(root);
        cout << '\n';
    }

    // Recorrido inorden iterativo (con pila explicita)
    void printInorderIterativo() const {
        stack<const AVLNode<T>*> pila;
        const AVLNode<T>* actual = root;
        cout << "In-Orden con Stack: ";
        while (actual || !pila.empty()) {
            while (actual) {
                pila.push(actual);
                actual = actual->left;
            }
            actual = pila.top();
            pila.pop();
            cout << actual->key << ' ';
            actual = actual->right;
        }
        cout << '\n';
    }

    // Recorrido por niveles mostrando valor, altura y balance
    void printLevels() const {
        cout << "Por Niveles (valor, h=altura, b=balance): ";
        if (!root) { cout << "(vacio)\n"; return; }
        queue<const AVLNode<T>*> q;
        q.push(root);
        while (!q.empty()) {
            const AVLNode<T>* c = q.front();
            q.pop();
            cout << c->key << "(h=" << c->height
                 << ", b=" << balanceFactor(c) << ") ";
            if (c->left)  q.push(c->left);
            if (c->right) q.push(c->right);
        }
        cout << '\n';
    }
};

// ---------------- Demo ----------------
int main() {
    AVLTree<int> t;

    cout << "Insertando: 60, 30, 70, 20, 40, 65, 80, 75\n";
    for (int x : {60, 30, 70, 20, 40, 65, 80, 75})
        t.insert(x);
    t.printInorder();
    t.printLevels();

    cout << "\nInsertando 50 (causa rotacion LR en 30)\n";
    t.insert(50);
    t.printLevels();

    cout << "\nInsertando 10 (causa rotacion LL en 20)\n";
    t.insert(10);
    t.printLevels();

    cout << "\nEliminando 80 (causa rebalanceo)\n";
    t.remove(80);
    t.printLevels();

    cout << "\nEliminando 65\n";
    t.remove(65);
    t.printInorder();
    t.printInorderIterativo();
    t.printLevels();

    cout << "\nAltura maxima del arbol: " << t.alturaMax() << '\n';
    cout << "Buscar 50: " << (t.search(50) ? "Si" : "No") << '\n';
    cout << "Buscar 65: " << (t.search(65) ? "Si" : "No") << '\n';

    // Tambien funciona con otros tipos gracias al template:
    AVLTree<char> letras;
    for (char c : string("MERGEFACIL")) letras.insert(c);
    cout << "\nAVLTree<char> inorden: ";
    letras.printInorder();

    return 0;
}
