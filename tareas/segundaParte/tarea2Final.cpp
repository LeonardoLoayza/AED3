#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

// -------------------------------------------------------------
// NODO
// -------------------------------------------------------------
struct Node {
    int v;
    Node* left;
    Node* right;
    float x, y;
    int marca;

    Node(int _v) {
        v = _v;
        left = right = nullptr;
        x = y = 0.0f;
        marca = 0;
    }
};

// -------------------------------------------------------------
// CLASE ARBOL DE CARAMELOS
// -------------------------------------------------------------
class CandyTree {
    Node* root;
    int vueltas;
    bool terminado;

public:
    CandyTree() {
        root = nullptr;
        vueltas = 0;
        terminado = false;
    }

    ~CandyTree() {
        clear(root);
    }

    Node* get_root() { return root; }
    int get_vueltas() { return vueltas; }
    bool get_terminado() { return terminado; }

    void clear(Node* p) {
        if (!p) return;
        clear(p->left);
        clear(p->right);
        delete p;
    }

    void crear_arbol(int v) {
        clear(root);
        root = new Node(v);
        vueltas = 0;
        terminado = false;
    }

    void insertar_nodo(string rut, int k) {
        Node** p = &root;
        for (char c : rut) {
            if (!*p) return;
            if (c == 'L') p = &(*p)->left;
            else if (c == 'R') p = &(*p)->right;
        }
        *p = new Node(k);
    }

    void calculatePositions(Node* p, float x, float y, float offset_x) {
        if (!p) return;
        p->x = x;
        p->y = y;
        calculatePositions(p->left, x - offset_x, y + 90.0f, offset_x / 2.0f);
        calculatePositions(p->right, x + offset_x, y + 90.0f, offset_x / 2.0f);
    }

    // Permite SOLO UN traspaso de caramelo por paso/iteración
    bool recorrido(Node* p, int max_cambio) {
        if (!p) return false;

        // Evaluar hijo izquierdo
        if (p->left && p->marca != max_cambio && p->left->marca != max_cambio) {
            Node* h = p->left;
            if (h->v > 1 && h->v >= p->v) {
                h->v--;
                p->v++;
                p->marca = h->marca = max_cambio;
                return true;
            }
            else if (h->v == 0 && p->v >= 1) {
                h->v++;
                p->v--;
                p->marca = h->marca = max_cambio;
                return true;
            }
        }

        // Evaluar hijo derecho
        if (p->right && p->marca != max_cambio && p->right->marca != max_cambio) {
            Node* h = p->right;
            if (h->v > 1 && h->v >= p->v) {
                h->v--;
                p->v++;
                p->marca = h->marca = max_cambio;
                return true;
            }
            else if (h->v == 0 && p->v >= 1) {
                h->v++;
                p->v--;
                p->marca = h->marca = max_cambio;
                return true;
            }
        }

        if (recorrido(p->left, max_cambio)) return true;
        if (recorrido(p->right, max_cambio)) return true;

        return false;
    }

    void paso() {
        if (terminado) return;
        if (recorrido(root, vueltas + 1))
            vueltas++;
        else
            terminado = true;
    }
};

// -------------------------------------------------------------
// FUNCIONES DE DIBUJO
// -------------------------------------------------------------
void drawTreeEdges(sf::RenderWindow& window, Node* root) {
    if (!root) return;
    if (root->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(root->x, root->y), sf::Color::White),
            sf::Vertex(sf::Vector2f(root->left->x, root->left->y), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        drawTreeEdges(window, root->left);
    }
    if (root->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(root->x, root->y), sf::Color::White),
            sf::Vertex(sf::Vector2f(root->right->x, root->right->y), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        drawTreeEdges(window, root->right);
    }
}

void drawTreeNodes(sf::RenderWindow& window, Node* root, sf::Font& font, int vueltas, bool terminado) {
    if (!root) return;

    float radius = 18.0f;
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(root->x, root->y);

    bool cambio = (!terminado && vueltas > 0 && root->marca == vueltas);
    circle.setFillColor(cambio ? sf::Color::Green : sf::Color::White);

    window.draw(circle);

    sf::Text text;
    text.setFont(font);
    text.setString(to_string(root->v));
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Black);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    text.setPosition(root->x, root->y);

    window.draw(text);

    drawTreeNodes(window, root->left, font, vueltas, terminado);
    drawTreeNodes(window, root->right, font, vueltas, terminado);
}

// -------------------------------------------------------------
// MAIN
// -------------------------------------------------------------
int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Arbol de Caramelos");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        cout << "Error cargando fuente" << endl;
    }

    CandyTree tree;
    tree.crear_arbol(3);
    tree.insertar_nodo("L", 0);
    tree.insertar_nodo("R", 0);
    tree.insertar_nodo("RL", 2);
    tree.insertar_nodo("RR", 0);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    tree.paso();
                }
            }
        }

        if (tree.get_root()) {
            tree.calculatePositions(tree.get_root(), 600.0f, 100.0f, 250.0f);
        }

        window.clear(sf::Color(30, 30, 30));

        drawTreeEdges(window, tree.get_root());
        drawTreeNodes(window, tree.get_root(), font, tree.get_vueltas(), tree.get_terminado());

        // Texto informativo simplificado
        string msg = "Paso: " + to_string(tree.get_vueltas());
        if (tree.get_terminado()) msg += " (Terminado)";
        msg += "  |  ESPACIO: Avanzar paso";

        sf::Text info(msg, font, 18);
        info.setFillColor(sf::Color::White);
        info.setPosition(15.0f, 15.0f);
        window.draw(info);

        window.display();
    }

    return 0;
}