#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

// =====================================
// NODO
// =====================================
struct Node {
    int v;
    Node* left;
    Node* right;
    float x, y;
    bool activo;   // participo en la ultima ronda

    Node(int _v) {
        v = _v;
        left = right = nullptr;
        x = y = 0;
        activo = false;
    }
};

// =====================================
// ARBOL (completo, por niveles)
// =====================================
class BinaryTree {
public:
    Node* root = nullptr;
    vector<Node*> nodos;
    vector<int> inicial;

    ~BinaryTree() { limpiar(); }

    void limpiar() {
        for (Node* p : nodos) delete p;
        nodos.clear();
        root = nullptr;
    }

    void construir(const vector<int>& vals) {
        limpiar();
        inicial = vals;

        for (int v : vals) nodos.push_back(new Node(v));

        int n = nodos.size();
        for (int i = 0; i < n; i++) {
            if (2 * i + 1 < n) nodos[i]->left  = nodos[2 * i + 1];
            if (2 * i + 2 < n) nodos[i]->right = nodos[2 * i + 2];
        }
        root = nodos.empty() ? nullptr : nodos[0];
    }

    void restaurar() {
        for (size_t i = 0; i < nodos.size(); i++) {
            nodos[i]->v = inicial[i];
            nodos[i]->activo = false;
        }
    }

    // x por recorrido inorden, y por profundidad
    float calcularPosiciones(float ancho, float yInicial, float dy) {
        int n = nodos.size();
        float spacing = min(70.f, (ancho - 100.f) / max(1, n));
        float total = spacing * (n - 1);
        float startX = ancho / 2 - total / 2;

        int contador = 0;
        function<void(Node*, int)> rec = [&](Node* p, int depth) {
            if (!p) return;
            rec(p->left, depth + 1);
            p->x = startX + contador * spacing;
            p->y = yInicial + depth * dy;
            contador++;
            rec(p->right, depth + 1);
        };
        rec(root, 0);
        return spacing;
    }
};

// =====================================
// VERSION CLASICA (minimo sin restriccion de rondas)
// =====================================
long long calcularBalance(Node* p, long long& movimientos) {
    if (!p) return 0;

    long long izq = calcularBalance(p->left, movimientos);
    long long der = calcularBalance(p->right, movimientos);

    movimientos += abs(izq) + abs(der);

    return p->v - 1 + izq + der;
}

// =====================================
// TRANSFERENCIAS (flujo por cada arista)
// =====================================
struct Transferencia {
    Node* origen;
    Node* destino;
    long long restantes;
};

long long calcularFlujo(Node* p, vector<Transferencia>& mov) {
    if (!p) return 0;

    long long izq = calcularFlujo(p->left, mov);
    long long der = calcularFlujo(p->right, mov);

    if (p->left && izq != 0) {
        if (izq > 0) mov.push_back({p->left, p, izq});    // hijo -> padre
        else         mov.push_back({p, p->left, -izq});   // padre -> hijo
    }

    if (p->right && der != 0) {
        if (der > 0) mov.push_back({p->right, p, der});
        else         mov.push_back({p, p->right, -der});
    }

    return p->v - 1 + izq + der;
}

// =====================================
// UNA RONDA
// Regla: cada nodo participa en a lo sumo UN movimiento
// (ya sea enviando o recibiendo) por ronda.
// =====================================
int ejecutarRonda(BinaryTree& t, vector<Transferencia>& transferencias) {
    for (Node* p : t.nodos) p->activo = false;

    int realizados = 0;

    for (auto& m : transferencias) {
        if (m.restantes <= 0) continue;
        if (m.origen->activo || m.destino->activo) continue;
        if (m.origen->v <= 0) continue;          // no tiene caramelo para dar

        m.origen->v--;
        m.destino->v++;
        m.restantes--;

        m.origen->activo = true;
        m.destino->activo = true;
        realizados++;
    }
    return realizados;
}

bool hayPendientes(const vector<Transferencia>& tr) {
    for (auto& m : tr)
        if (m.restantes > 0) return true;
    return false;
}

// =====================================
// VERIFICAR OBJETIVO
// =====================================
bool verificar(BinaryTree& t) {
    for (Node* p : t.nodos)
        if (p->v != 1) return false;
    return true;
}

// =====================================
// DIBUJO
// =====================================
void drawEdges(sf::RenderWindow& window, BinaryTree& t) {
    for (Node* p : t.nodos) {
        for (Node* h : {p->left, p->right}) {
            if (!h) continue;
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(p->x, p->y), sf::Color(150, 150, 150)),
                sf::Vertex(sf::Vector2f(h->x, h->y), sf::Color(150, 150, 150))
            };
            window.draw(line, 2, sf::Lines);
        }
    }
}

void drawNodes(sf::RenderWindow& window, BinaryTree& t,
               sf::Font& font, float radius) {
    for (Node* p : t.nodos) {
        sf::CircleShape circle(radius);
        circle.setOrigin(radius, radius);
        circle.setPosition(p->x, p->y);

        if (p->v == 1)      circle.setFillColor(sf::Color(40, 190, 100));   // ok
        else if (p->v == 0) circle.setFillColor(sf::Color(220, 80, 80));    // vacio
        else                circle.setFillColor(sf::Color(240, 200, 60));   // sobra

        if (p->activo) {
            circle.setOutlineThickness(4);
            circle.setOutlineColor(sf::Color(80, 160, 255));
        }
        window.draw(circle);

        sf::Text text;
        text.setFont(font);
        text.setString(to_string(p->v));
        text.setCharacterSize((unsigned)max(10.f, radius * 0.8f));
        text.setFillColor(sf::Color::Black);

        sf::FloatRect r = text.getLocalBounds();
        text.setOrigin(r.left + r.width / 2, r.top + r.height / 2);
        text.setPosition(p->x, p->y);
        window.draw(text);
    }
}

// =====================================
// MAIN
// =====================================
int main() {

    // ---- Entrada ----
    int N;
    cout << "N (numero de nodos): ";
    cin >> N;

    if (N <= 0) {
        cout << "N debe ser mayor que 0\n";
        return 1;
    }

    vector<int> vals(N);
    long long suma = 0;

    cout << "Caramelos de cada nodo (por niveles, " << N << " valores):\n";
    for (int i = 0; i < N; i++) {
        cin >> vals[i];
        if (vals[i] < 0) {
            cout << "Los valores no pueden ser negativos\n";
            return 1;
        }
        suma += vals[i];
    }

    if (suma != N) {
        cout << "La suma de los valores (" << suma
             << ") debe ser igual a N (" << N << ")\n";
        return 1;
    }

    // ---- Arbol ----
    BinaryTree t;
    t.construir(vals);

    long long minimo = 0;
    calcularBalance(t.root, minimo);
    cout << "\nMovimientos minimos (sin limite por ronda): " << minimo << endl;

    vector<Transferencia> transferencias;
    calcularFlujo(t.root, transferencias);

    // ---- Ventana ----
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Distribucion de caramelos");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        cout << "Error cargando fuente\n";
        return 1;
    }

    float spacing = t.calcularPosiciones(1200, 150, 100);
    float radius = max(8.f, min(23.f, spacing * 0.45f));

    int ronda = 0;
    long long total = 0;
    bool terminado = !hayPendientes(transferencias);
    string mensaje = terminado ? "Ya estaba distribuido" : "Presiona ESPACIO para avanzar";

    cout << "\nControles:\n";
    cout << "ESPACIO: ejecutar siguiente ronda\n";
    cout << "R: reiniciar\n";

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::Space && !terminado) {

                    int realizados = ejecutarRonda(t, transferencias);

                    if (realizados > 0) {
                        ronda++;
                        total += realizados;
                        cout << "Ronda " << ronda << ": "
                             << realizados << " movimientos\n";
                    }

                    if (!hayPendientes(transferencias)) {
                        terminado = true;
                        mensaje = "Distribucion completada";
                        cout << "Total movimientos: " << total << endl;
                        cout << "Objetivo cumplido: "
                             << (verificar(t) ? "SI" : "NO") << endl;
                    }
                    else if (realizados == 0) {
                        terminado = true;
                        mensaje = "Bloqueado: ningun movimiento posible";
                        cout << mensaje << endl;
                    }
                }

                if (event.key.code == sf::Keyboard::R) {
                    t.restaurar();
                    transferencias.clear();
                    calcularFlujo(t.root, transferencias);
                    ronda = 0;
                    total = 0;
                    terminado = !hayPendientes(transferencias);
                    mensaje = "Presiona ESPACIO para avanzar";
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));

        drawEdges(window, t);
        drawNodes(window, t, font, radius);

        sf::Text info;
        info.setFont(font);
        info.setCharacterSize(20);
        info.setFillColor(sf::Color::White);
        info.setString(
            "N: " + to_string(N) +
            "\nRonda: " + to_string(ronda) +
            "\nMovimientos: " + to_string(total) + " / " + to_string(minimo) +
            "\n" + mensaje
        );
        info.setPosition(20, 20);
        window.draw(info);

        window.display();
    }

    return 0;   // BinaryTree libera sus nodos en el destructor
}