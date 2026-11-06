#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct Node {
    int v;
    Node* left;
    Node* right;
    float x, y;
    bool is_perimeter;

    Node(int _v) {
        left = right = nullptr;
        v = _v;
        x = y = 0.0f;
        is_perimeter = false;
    }
};

class BinaryTree {
    Node* root;
    bool lado_reemp;

public:
    BinaryTree();
    ~BinaryTree();
    bool insrt(int x);
    bool remv(int x);
    Node** fnd_reemp(Node** p);
    bool find(int x, Node**& p);
    void clear(Node* p);
    Node* get_root() { return root; }

    void calculatePositions(Node* p, float x, float y, float offset_x);
    void resetPerimeter(Node* p);
    void findPerimeter();

    void getLeftBoundary(Node* p);
    void getRightBoundary(Node* p);
    void getLeaves(Node* p);
    void construir(int v[], int n);
};

BinaryTree::BinaryTree() {
    root = nullptr;
    lado_reemp = false;
}

BinaryTree::~BinaryTree() {
    this->clear(root);
    root = nullptr;
}

bool BinaryTree::insrt(int x) {
    Node** p = &root;
    if (find(x, p)) return false;
    *p = new Node(x);
    return true;
}

bool BinaryTree::remv(int x) {
    Node** p = &root;
    if (!find(x, p)) return false;
    if ((*p)->left && (*p)->right) {
        Node** q = fnd_reemp(p);
        (*p)->v = (*q)->v;
        p = q;
    }
    Node* t = *p;
    if ((*p)->left)
        *p = (*p)->left;
    else
        *p = (*p)->right;
    delete t;
    return true;
}

Node** BinaryTree::fnd_reemp(Node** p) {
    Node** q = p;
    if (lado_reemp) {
        q = &((*q)->left);
        while ((*q)->right)
            q = &((*q)->right);
    }
    else {
        q = &((*q)->right);
        while ((*q)->left)
            q = &((*q)->left);
    }
    lado_reemp = !lado_reemp;
    return q;
}

bool BinaryTree::find(int x, Node**& p) {
    while (*p && (*p)->v != x) {
        if (x < (*p)->v)
            p = &((*p)->left);
        else
            p = &((*p)->right);
    }
    return *p != nullptr;
}

void BinaryTree::clear(Node* p) {
    if (!p) return;
    clear(p->left);
    clear(p->right);
    delete p;
}

void BinaryTree::calculatePositions(Node* p, float x, float y, float offset_x) {
    if (!p) return;
    p->x = x;
    p->y = y;
    calculatePositions(p->left, x - offset_x, y + 80.0f, offset_x / 2.0f);
    calculatePositions(p->right, x + offset_x, y + 80.0f, offset_x / 2.0f);
}

void BinaryTree::resetPerimeter(Node* p) {
    if (!p) return;
    p->is_perimeter = false;
    resetPerimeter(p->left);
    resetPerimeter(p->right);
}

void BinaryTree::getLeftBoundary(Node* p) {
    if (!p) return;
    if (p->left) {
        p->is_perimeter = true;
        getLeftBoundary(p->left);
    }
    else if (p->right) {
        p->is_perimeter = true;
        getLeftBoundary(p->right);
    }
}

void BinaryTree::getRightBoundary(Node* p) {
    if (!p) return;
    if (p->right) {
        p->is_perimeter = true;
        getRightBoundary(p->right);
    }
    else if (p->left) {
        p->is_perimeter = true;
        getRightBoundary(p->left);
    }
}

void BinaryTree::getLeaves(Node* p) {
    if (!p) return;
    getLeaves(p->left);
    if (!p->left && !p->right) {
        p->is_perimeter = true;
    }
    getLeaves(p->right);
}

void BinaryTree::findPerimeter() {
    if (!root) return;
    resetPerimeter(root);

    root->is_perimeter = true;

    if (root->left) {
        getLeftBoundary(root->left);
    }
    if (root->right) {
        getRightBoundary(root->right);
    }

    getLeaves(root);
}


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

void drawTreeNodes(sf::RenderWindow& window, Node* root, sf::Font& font) {
    if (!root) return;

    float radius = 16.0f;
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(root->x, root->y);

    if (root->is_perimeter) {
        circle.setFillColor(sf::Color::Green);
    }
    else {
        circle.setFillColor(sf::Color::White);
    }

    window.draw(circle);

    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(root->v));
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Black);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    text.setPosition(root->x, root->y);

    window.draw(text);

    drawTreeNodes(window, root->left, font);
    drawTreeNodes(window, root->right, font);
}


void BinaryTree::construir(int v[], int n) {

    queue<Node*> q;

    // Crear nodos del ultimo nivel
    for (int i = 0; i < n; i++) {
        q.push(new Node(v[i]));
    }

    while (q.size() > 1) {

        queue<Node*> aux;

        while (!q.empty()) {

            Node* a = q.front();
            q.pop();

            Node* b = q.front();
            q.pop();

            Node* padre = new Node(a->v + b->v);

            padre->left = a;
            padre->right = b;

            aux.push(padre);
        }

        q = aux;
    }

    root = q.front();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Perimetro");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Error cargando la fuente de Windows" << std::endl;
    }

    BinaryTree t;

    int v[] = { 1, 2, 3, 4 };

    t.construir(v, 4);


    t.findPerimeter();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (t.get_root()) {
            t.calculatePositions(t.get_root(), 600.0f, 50.0f, 300.0f);
        }

        window.clear(sf::Color(30, 30, 30));

        drawTreeEdges(window, t.get_root());
        drawTreeNodes(window, t.get_root(), font);

        window.display();
    }

    return 0;
}


