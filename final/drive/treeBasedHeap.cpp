#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <stdexcept>

using namespace std;

class Node {
public:
    int v;
    Node* left;
    Node* right;
    Node* parent;

    Node(int _v, Node* _parent = nullptr)
        : v(_v), left(nullptr), right(nullptr), parent(_parent) {}
};

class TreeHeapWithDeque {
private:
    Node* root;
    deque<Node*> open_nodes; // Nodos que aún pueden tener hijos
    deque<Node*> all_nodes;  // Guarda el orden de inserción exacta (último nodo siempre al final)

    void heapifyUp(Node* node) {
        while (node->parent && node->v > node->parent->v) {
            swap(node->v, node->parent->v);
            node = node->parent;
        }
    }

    void heapifyDown(Node* node) {
        while (true) {
            Node* maxNode = node;

            if (node->left && node->left->v > maxNode->v) {
                maxNode = node->left;
            }
            if (node->right && node->right->v > maxNode->v) {
                maxNode = node->right;
            }

            if (maxNode == node) break;

            swap(node->v, maxNode->v);
            node = maxNode;
        }
    }

    void clearTree(Node* n) {
        if (!n) return;
        clearTree(n->left);
        clearTree(n->right);
        delete n;
    }

public:
    TreeHeapWithDeque() : root(nullptr) {}

    ~TreeHeapWithDeque() {
        clearTree(root);
    }

    int top() const {
        if (!root) throw runtime_error("Heap vacio");
        return root->v;
    }

    void push(int x) {
        if (!root) {
            root = new Node(x);
            open_nodes.push_back(root);
            all_nodes.push_back(root);
            return;
        }

        // 1. Obtener el padre en O(1) usando el deque
        Node* parent = open_nodes.front();
        Node* newNode = new Node(x, parent);

        if (!parent->left) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
            open_nodes.pop_front(); // Ya se llenaron sus dos hijos
        }

        open_nodes.push_back(newNode);
        all_nodes.push_back(newNode);

        // 2. Reordenar el heap (O(log N))
        heapifyUp(newNode);
    }

    void pop() {
        if (!root) return;

        if (all_nodes.size() == 1) {
            delete root;
            root = nullptr;
            open_nodes.clear();
            all_nodes.clear();
            return;
        }

        // 1. Ubicar el último nodo en O(1) usando el deque
        Node* lastNode = all_nodes.back();
        all_nodes.pop_back();

        // Si el último nodo estaba en open_nodes, lo quitamos de ahí también
        if (!open_nodes.empty() && open_nodes.back() == lastNode) {
            open_nodes.pop_back();
        }

        // 2. Reemplazar el valor de la raíz
        root->v = lastNode->v;

        // 3. Desconectar el último nodo de su padre
        Node* parent = lastNode->parent;
        if (parent->right == lastNode) {
            parent->right = nullptr;
            // Al quitar el hijo derecho, el padre vuelve a tener espacio disponible
            open_nodes.push_front(parent);
        } else {
            parent->left = nullptr;
        }

        delete lastNode;

        // 4. Reordenar el heap (O(log N))
        heapifyDown(root);
    }

    int size() const {
        return all_nodes.size();
    }
};

int main() {
    TreeHeapWithDeque h;
    vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    for (int x : nums) h.push(x);

    cout << "Extrayendo elementos en orden descendente:" << endl;
    while (h.size() > 0) {
        cout << h.top() << " ";
        h.pop();
    }
    cout << endl;
    return 0;
}
