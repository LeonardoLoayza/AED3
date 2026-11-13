//Tarea 3: Paso a paso insertar nodos y construir el AVL, ir rebalanceando, luego seleccionar un nodo y pintar los nodos que sean primos. 


#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// -------------------------------------------------------------
// NODO AVL
// -------------------------------------------------------------
struct Node {
    int v;
    Node* left;
    Node* right;
    int height;
    float x, y;

    Node(int _v) {
        v = _v;
        left = right = nullptr;
        height = 1;
        x = y = 0.0f;
    }
};

// -------------------------------------------------------------
// CLASE ARBOL AVL
// -------------------------------------------------------------
class AVLTree {
    Node* root;

    int getHeight(Node* n) {
        return n ? n->height : 0;
    }

    int getBalance(Node* n) {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    void updateHeight(Node* n) {
        if (n) {
            n->height = 1 + max(getHeight(n->left), getHeight(n->right));
        }
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->v)
            node->left = insert(node->left, key);
        else if (key > node->v)
            node->right = insert(node->right, key);
        else
            return node;

        updateHeight(node);
        int balance = getBalance(node);

        // Caso Izquierda-Izquierda (LL)
        if (balance > 1 && key < node->left->v)
            return rotateRight(node);

        // Caso Derecha-Derecha (RR)
        if (balance < -1 && key > node->right->v)
            return rotateLeft(node);

        // Caso Izquierda-Derecha (LR)
        if (balance > 1 && key > node->left->v) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Caso Derecha-Izquierda (RL)
        if (balance < -1 && key < node->right->v) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

public:
    AVLTree() { root = nullptr; }
    ~AVLTree() { clear(root); }

    Node* get_root() { return root; }

    void clear(Node* p) {
        if (!p) return;
        clear(p->left);
        clear(p->right);
        delete p;
    }

    void insertKey(int key) {
        root = insert(root, key);
    }

    void calculatePositions(Node* p, float x, float y, float offset_x) {
        if (!p) return;
        p->x = x;
        p->y = y;
        calculatePositions(p->left, x - offset_x, y + 80.0f, offset_x / 2.0f);
        calculatePositions(p->right, x + offset_x, y + 80.0f, offset_x / 2.0f);
    }

    // Busca un nodo dentro del árbol por su valor
    Node* findNode(Node* p, int val) {
        if (!p) return nullptr;
        if (p->v == val) return p;
        if (val < p->v) return findNode(p->left, val);
        return findNode(p->right, val);
    }

    // Busca al padre de un nodo objetivo
    Node* getParent(Node* curr, Node* target) {
        if (!curr || curr == target) return nullptr;
        if (curr->left == target || curr->right == target) return curr;
        if (target->v < curr->v) return getParent(curr->left, target);
        return getParent(curr->right, target);
    }

    // Obtiene los primos del nodo objetivo (hijos del hermano del padre)
    vector<Node*> getCousins(Node* target) {
        vector<Node*> cousins;
        if (!root || !target) return cousins;

        Node* parent = getParent(root, target);
        if (!parent) return cousins;

        Node* grandParent = getParent(root, parent);
        if (!grandParent) return cousins;

        // El hermano del padre es el tío del nodo objetivo
        Node* uncle = (grandParent->left == parent) ? grandParent->right : grandParent->left;

        if (uncle) {
            if (uncle->left) cousins.push_back(uncle->left);
            if (uncle->right) cousins.push_back(uncle->right);
        }

        return cousins;
    }

    // Detecta clic en algún nodo dado su radio
    Node* getNodeAtPosition(Node* p, float mx, float my, float radius) {
        if (!p) return nullptr;
        float dx = p->x - mx;
        float dy = p->y - my;
        if (sqrt(dx * dx + dy * dy) <= radius) return p;

        Node* resLeft = getNodeAtPosition(p->left, mx, my, radius);
        if (resLeft) return resLeft;
        return getNodeAtPosition(p->right, mx, my, radius);
    }
};

// -------------------------------------------------------------
// DIBUJO
// -------------------------------------------------------------
void drawEdges(sf::RenderWindow& window, Node* root) {
    if (!root) return;
    if (root->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(root->x, root->y), sf::Color::White),
            sf::Vertex(sf::Vector2f(root->left->x, root->left->y), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        drawEdges(window, root->left);
    }
    if (root->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(root->x, root->y), sf::Color::White),
            sf::Vertex(sf::Vector2f(root->right->x, root->right->y), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        drawEdges(window, root->right);
    }
}

void drawNodes(sf::RenderWindow& window, Node* root, sf::Font& font, Node* selected, const vector<Node*>& cousins) {
    if (!root) return;

    float radius = 20.0f;
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(root->x, root->y);

    // Color según estado: Seleccionado (Amarillo), Primo (Verde), Normal (Blanco)
    if (root == selected) {
        circle.setFillColor(sf::Color::Yellow);
    } else {
        bool esPrimo = false;
        for (Node* c : cousins) {
            if (c == root) {
                esPrimo = true;
                break;
            }
        }
        circle.setFillColor(esPrimo ? sf::Color::Green : sf::Color::White);
    }

    window.draw(circle);

    sf::Text text;
    text.setFont(font);
    text.setString(to_string(root->v));
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Black);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(root->x, root->y);

    window.draw(text);

    drawNodes(window, root->left, font, selected, cousins);
    drawNodes(window, root->right, font, selected, cousins);
}

// -------------------------------------------------------------
// MAIN
// -------------------------------------------------------------
int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Construccion AVL y Primos");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        cout << "Error cargando fuente" << endl;
    }

    AVLTree tree;
    vector<int> datos = { 10, 20, 30, 40, 50, 25, 5, 15, 27 };
    size_t indiceInsercion = 0;

    Node* selectedNode = nullptr;
    vector<Node*> cousins;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Insertar nodo siguiente con ESPACIO
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    if (indiceInsercion < datos.size()) {
                        tree.insertKey(datos[indiceInsercion]);
                        indiceInsercion++;
                        // Al rebalancear el árbol, refrescamos la lista de primos
                        if (selectedNode) {
                            selectedNode = tree.findNode(tree.get_root(), selectedNode->v);
                            cousins = tree.getCousins(selectedNode);
                        }
                    }
                }
            }

            // Seleccionar nodo con Clic Izquierdo
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    float mx = (float)event.mouseButton.x;
                    float my = (float)event.mouseButton.y;
                    Node* clicked = tree.getNodeAtPosition(tree.get_root(), mx, my, 20.0f);
                    if (clicked) {
                        selectedNode = clicked;
                        cousins = tree.getCousins(selectedNode);
                    }
                }
            }
        }

        if (tree.get_root()) {
            tree.calculatePositions(tree.get_root(), 600.0f, 100.0f, 250.0f);
        }

        window.clear(sf::Color(30, 30, 30));

        drawEdges(window, tree.get_root());
        drawNodes(window, tree.get_root(), font, selectedNode, cousins);

        // Leyenda
        string msg = "ESPACIO: Insertar nodo (" + to_string(indiceInsercion) + "/" + to_string(datos.size()) + ")";
        if (indiceInsercion < datos.size()) {
            msg += " [Siguiente: " + to_string(datos[indiceInsercion]) + "]";
        } else {
            msg += " (Construccion Finalizada)";
        }
        msg += "\nClic Izquierdo en un nodo para ver sus primos (Verde)";

        sf::Text info(msg, font, 18);
        info.setFillColor(sf::Color::White);
        info.setPosition(15.0f, 15.0f);
        window.draw(info);

        window.display();
    }

    return 0;
}