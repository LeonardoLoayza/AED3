#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

// -------------------------------------------------------------
// 1. NODO
// -------------------------------------------------------------
struct Node {
    int v;
    Node* left;
    Node* right;
    float x, y;
    int marca;
    float scale;
    float rotation;

    Node(int _v) {
        v = _v;
        left = right = nullptr;
        x = y = 0.0f;
        marca = 0;
        scale = 1.0f;
        rotation = 0.0f;
    }
};

// -------------------------------------------------------------
// 2. SISTEMAS BÉLICOS Y CAOS
// -------------------------------------------------------------
struct Particle {
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Color color;
    float lifetime;
    float maxLifetime;
    float size;

    Particle() {
        pos = { 0.0f, 0.0f };
        vel = { 0.0f, 0.0f };
        color = sf::Color::White;
        lifetime = 0.0f;
        maxLifetime = 1.0f;
        size = 2.0f;
    }

    void update(float dt) {
        pos += vel * dt;
        vel.y += 150.0f * dt;
        if (pos.y > 780.0f) {
            pos.y = 780.0f;
            vel.y = -vel.y * 0.7f;
        }
        lifetime -= dt;
    }
};

struct FloatingText {
    string text;
    sf::Vector2f pos;
    sf::Color color;
    float lifetime;
    float maxLifetime;
    float velY;
    unsigned int size;
};

struct Shockwave {
    sf::Vector2f pos;
    float radius;
    float maxRadius;
    float lifetime;
    float maxLifetime;
    sf::Color color;

    void update(float dt) {
        float progress = 1.0f - (lifetime / maxLifetime);
        radius = progress * maxRadius;
        lifetime -= dt;
    }
};

struct Missile {
    sf::Vector2f pos;
    sf::Vector2f target;
    float speed;
    bool active;
    Node* targetNode1;
    Node* targetNode2;
    string msg;
    int type; // 0: Misil, 1: Rayo Kaiju, 2: OVNI Laser

    void update(float dt) {
        sf::Vector2f dir = target - pos;
        float dist = sqrt(dir.x * dir.x + dir.y * dir.y);
        if (dist < 25.0f) {
            active = false;
        } else {
            dir /= dist;
            pos += dir * speed * dt;
        }
    }
};

// -------------------------------------------------------------
// 3. CLASE ÁRBOL DE CARAMELOS
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

    ~CandyTree() { clear(root); }

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
        calculatePositions(p->left, x - offset_x, y + 120.0f, offset_x / 2.0f);
        calculatePositions(p->right, x + offset_x, y + 120.0f, offset_x / 2.0f);
    }

    bool recorrido(Node* p, int max_cambio, Node*& n1, Node*& n2, string& transferType) {
        if (!p) return false;

        auto transfer = [&](Node* child) {
            if (child->v > 1 && child->v >= p->v) {
                child->v--;
                p->v++;
                p->marca = child->marca = max_cambio;
                n1 = p; n2 = child;
                transferType = "-1 CARAMELO ANIQUILADO!";
                return true;
            }
            else if (child->v == 0 && p->v >= 1) {
                child->v++;
                p->v--;
                p->marca = child->marca = max_cambio;
                n1 = p; n2 = child;
                transferType = "¡ROBO INTERGALÁCTICO!";
                return true;
            }
            return false;
        };

        if (p->left && p->marca != max_cambio && p->left->marca != max_cambio) {
            if (transfer(p->left)) return true;
        }
        if (p->right && p->marca != max_cambio && p->right->marca != max_cambio) {
            if (transfer(p->right)) return true;
        }

        if (recorrido(p->left, max_cambio, n1, n2, transferType)) return true;
        if (recorrido(p->right, max_cambio, n1, n2, transferType)) return true;

        return false;
    }

    bool paso(Node*& n1, Node*& n2, string& msgType) {
        if (terminado) return false;
        if (recorrido(root, vueltas + 1, n1, n2, msgType)) {
            vueltas++;
            return true;
        }
        else {
            terminado = true;
            return false;
        }
    }
};

// -------------------------------------------------------------
// 4. DIBUJO DE COMBATE DE FONDO (T-REX VS ROBOT MECH)
// -------------------------------------------------------------
void drawBackgroundFight(sf::RenderWindow& window, float animTime, bool attackTriggered) {
    // ---------------- DINOSAURIO T-REX (IZQUIERDA) ----------------
    float trexX = 120.0f + sin(animTime * 3.0f) * 15.0f;
    float trexY = 520.0f + cos(animTime * 4.0f) * 10.0f;

    // Cuerpo T-Rex
    sf::ConvexShape trexBody;
    trexBody.setPointCount(5);
    trexBody.setPoint(0, sf::Vector2f(trexX - 80.0f, trexY + 100.0f)); // Cola
    trexBody.setPoint(1, sf::Vector2f(trexX, trexY));                 // Espalda
    trexBody.setPoint(2, sf::Vector2f(trexX + 70.0f, trexY - 30.0f)); // Cuello
    trexBody.setPoint(3, sf::Vector2f(trexX + 50.0f, trexY + 80.0f)); // Pecho
    trexBody.setPoint(4, sf::Vector2f(trexX - 40.0f, trexY + 120.0f));
    trexBody.setFillColor(sf::Color(30, 100, 40, 180));
    window.draw(trexBody);

    // Cabeza T-Rex
    sf::RectangleShape trexHead(sf::Vector2f(70.0f, 40.0f));
    trexHead.setPosition(trexX + 60.0f, trexY - 50.0f);
    trexHead.setFillColor(sf::Color(40, 130, 50, 180));
    trexHead.setRotation(attackTriggered ? -15.0f : 0.0f);
    window.draw(trexHead);

    // Ojo T-Rex
    sf::CircleShape trexEye(5.0f);
    trexEye.setPosition(trexX + 110.0f, trexY - 45.0f);
    trexEye.setFillColor(sf::Color::Red);
    window.draw(trexEye);

    // ---------------- ROBOT MECH DE COMBATE (DERECHA) ----------------
    float mechX = 1080.0f - sin(animTime * 3.0f) * 15.0f;
    float mechY = 520.0f + cos(animTime * 2.0f) * 10.0f;

    // Cuerpo Mech
    sf::RectangleShape mechTorso(sf::Vector2f(90.0f, 110.0f));
    mechTorso.setOrigin(45.0f, 55.0f);
    mechTorso.setPosition(mechX, mechY + 20.0f);
    mechTorso.setFillColor(sf::Color(70, 80, 110, 180));
    mechTorso.setOutlineThickness(3.0f);
    mechTorso.setOutlineColor(sf::Color::Cyan);
    window.draw(mechTorso);

    // Cabeza Mech
    sf::RectangleShape mechHead(sf::Vector2f(45.0f, 30.0f));
    mechHead.setOrigin(22.5f, 15.0f);
    mechHead.setPosition(mechX, mechY - 45.0f);
    mechHead.setFillColor(sf::Color(100, 120, 160, 180));
    window.draw(mechHead);

    // Visor Mech
    sf::RectangleShape mechVisor(sf::Vector2f(35.0f, 8.0f));
    mechVisor.setOrigin(17.5f, 4.0f);
    mechVisor.setPosition(mechX - 5.0f, mechY - 45.0f);
    mechVisor.setFillColor(sf::Color::Cyan);
    window.draw(mechVisor);

    // Cañón del Mech
    sf::RectangleShape mechGun(sf::Vector2f(80.0f, 16.0f));
    mechGun.setPosition(mechX - 70.0f, mechY + 10.0f);
    mechGun.setFillColor(sf::Color(40, 40, 50, 200));
    window.draw(mechGun);

    // ---------------- COLISIÓN DE ATAQUES AL ATACAR ----------------
    if (attackTriggered) {
        // Rayo de Aliento del T-Rex (Verde)
        sf::Vertex trexBeam[] = {
            sf::Vertex(sf::Vector2f(trexX + 120.0f, trexY - 35.0f), sf::Color::Green),
            sf::Vertex(sf::Vector2f(600.0f, 500.0f), sf::Color::Yellow)
        };
        window.draw(trexBeam, 2, sf::Lines);

        // Cañón Láser del Mech (Azul Plasma)
        sf::Vertex mechBeam[] = {
            sf::Vertex(sf::Vector2f(mechX - 70.0f, mechY + 18.0f), sf::Color::Cyan),
            sf::Vertex(sf::Vector2f(600.0f, 500.0f), sf::Color::White)
        };
        window.draw(mechBeam, 2, sf::Lines);

        // Explosión de choque al centro
        sf::CircleShape clash(45.0f);
        clash.setOrigin(45.0f, 45.0f);
        clash.setPosition(600.0f, 500.0f);
        clash.setFillColor(sf::Color(255, 255, 255, 200));
        clash.setOutlineThickness(10.0f);
        clash.setOutlineColor(sf::Color::Yellow);
        window.draw(clash);
    }
}

// -------------------------------------------------------------
// 5. GENERADORES DE DESTRUCCIÓN
// -------------------------------------------------------------
void spawnMegaExplosion(vector<Particle>& particles, vector<Shockwave>& shockwaves, float x, float y, sf::Color primaryColor, int count = 400) {
    for (int i = 0; i < count; ++i) {
        Particle p;
        p.pos = { x, y };
        float angle = (rand() % 360) * 3.14159f / 180.0f;
        float speed = 200.0f + (rand() % 1200);
        p.vel = { cos(angle) * speed, sin(angle) * speed };
        
        int r = rand() % 4;
        if (r == 0) p.color = primaryColor;
        else if (r == 1) p.color = sf::Color::Magenta;
        else if (r == 2) p.color = sf::Color::Yellow;
        else p.color = sf::Color::White;

        p.lifetime = p.maxLifetime = 0.5f + (rand() % 90) / 100.0f;
        p.size = 4.0f + (rand() % 12);
        particles.push_back(p);
    }

    Shockwave sw;
    sw.pos = { x, y };
    sw.radius = 0.0f;
    sw.maxRadius = 350.0f;
    sw.lifetime = sw.maxLifetime = 0.5f;
    sw.color = primaryColor;
    shockwaves.push_back(sw);
}

void updateNodesScale(Node* root, float dt) {
    if (!root) return;
    if (root->scale > 1.0f) {
        root->scale -= dt * 4.0f;
        if (root->scale < 1.0f) root->scale = 1.0f;
    }
    root->rotation += 180.0f * dt;
    updateNodesScale(root->left, dt);
    updateNodesScale(root->right, dt);
}

// -------------------------------------------------------------
// 6. DIBUJO DE ÁRBOL
// -------------------------------------------------------------
void drawTreeEdges(sf::RenderWindow& window, Node* root) {
    if (!root) return;
    if (root->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(root->x, root->y), sf::Color::Cyan),
            sf::Vertex(sf::Vector2f(root->left->x, root->left->y), sf::Color::Magenta)
        };
        window.draw(line, 2, sf::Lines);
        drawTreeEdges(window, root->left);
    }
    if (root->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(root->x, root->y), sf::Color::Cyan),
            sf::Vertex(sf::Vector2f(root->right->x, root->right->y), sf::Color::Magenta)
        };
        window.draw(line, 2, sf::Lines);
        drawTreeEdges(window, root->right);
    }
}

void drawTreeNodes(sf::RenderWindow& window, Node* root, sf::Font& font, int vueltas, bool terminado) {
    if (!root) return;

    float radius = 25.0f * root->scale;
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(root->x, root->y);

    bool cambio = (!terminado && vueltas > 0 && root->marca == vueltas);
    if (cambio) {
        circle.setFillColor(sf::Color::Red);
        circle.setOutlineThickness(8.0f);
        circle.setOutlineColor(sf::Color::Yellow);
    } else {
        circle.setFillColor(sf::Color(255, 255, 255));
        circle.setOutlineThickness(3.0f);
        circle.setOutlineColor(sf::Color::Cyan);
    }

    window.draw(circle);

    sf::Text text;
    text.setFont(font);
    text.setString(to_string(root->v));
    text.setCharacterSize((unsigned int)(22 * root->scale));
    text.setStyle(sf::Text::Bold);
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
// 7. MAIN CATASTRÓFICO
// -------------------------------------------------------------
int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "ARBOL DE CARAMELOS: T-REX VS MECH ROBOT");
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

    vector<Particle> particles;
    vector<FloatingText> floatingTexts;
    vector<Shockwave> shockwaves;
    vector<Missile> projectiles;

    sf::Clock dtClock;
    float animTime = 0.0f;
    float shakeTimer = 0.0f;
    float shakeIntensity = 0.0f;
    float flashTimer = 0.0f;
    float clashTimer = 0.0f;
    sf::Color flashColor = sf::Color::White;
    float timeSpeed = 1.0f;
    float ufoAngle = 0.0f;

    sf::View defaultView = window.getDefaultView();

    while (window.isOpen()) {
        float rawDt = dtClock.restart().asSeconds();
        float dt = rawDt * timeSpeed;

        animTime += dt;
        ufoAngle += dt * 2.0f;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    Node *n1 = nullptr, *n2 = nullptr;
                    string transferMsg = "";
                    
                    if (tree.paso(n1, n2, transferMsg)) {
                        clashTimer = 0.4f; // Activa choque de rayo T-Rex vs Mech

                        int megaSurprise = rand() % 4;

                        if (megaSurprise == 0) {
                            Missile m;
                            m.pos = { 600.0f, 850.0f };
                            m.target = { n1->x, n1->y };
                            m.speed = 2200.0f;
                            m.active = true;
                            m.targetNode1 = n1; m.targetNode2 = n2;
                            m.msg = transferMsg;
                            m.type = 1;
                            projectiles.push_back(m);

                            floatingTexts.push_back({ "¡T-REX RUGE DINO-RAYO!", { 300.0f, 250.0f }, sf::Color::Green, 1.5f, 1.5f, -30.0f, 45 });
                        }
                        else if (megaSurprise == 1) {
                            float ufoX = 600.0f + cos(ufoAngle) * 400.0f;
                            float ufoY = 120.0f + sin(ufoAngle) * 40.0f;

                            Missile m;
                            m.pos = { ufoX, ufoY };
                            m.target = { n1->x, n1->y };
                            m.speed = 1800.0f;
                            m.active = true;
                            m.targetNode1 = n1; m.targetNode2 = n2;
                            m.msg = transferMsg;
                            m.type = 2;
                            projectiles.push_back(m);

                            floatingTexts.push_back({ "¡CAÑÓN PLASMA DEL MECH!", { 320.0f, 250.0f }, sf::Color::Cyan, 1.5f, 1.5f, -30.0f, 45 });
                        }
                        else if (megaSurprise == 2) {
                            for (int k = 0; k < 5; ++k) {
                                Missile m;
                                m.pos = { (float)(100 + rand() % 1000), -50.0f - (k * 80) };
                                m.target = { (k % 2 == 0) ? n1->x : n2->x, (k % 2 == 0) ? n1->y : n2->y };
                                m.speed = 1400.0f + (rand() % 500);
                                m.active = true;
                                m.targetNode1 = n1; m.targetNode2 = n2;
                                m.msg = transferMsg;
                                m.type = 0;
                                projectiles.push_back(m);
                            }
                            floatingTexts.push_back({ "¡BOMBARDEO ORBITAL!", { 350.0f, 250.0f }, sf::Color::Yellow, 1.5f, 1.5f, -30.0f, 45 });
                        }
                        else {
                            spawnMegaExplosion(particles, shockwaves, n1->x, n1->y, sf::Color::Magenta, 500);
                            spawnMegaExplosion(particles, shockwaves, n2->x, n2->y, sf::Color::Cyan, 500);
                            n1->scale = 3.5f; n2->scale = 3.5f;
                            shakeTimer = 0.6f; shakeIntensity = 35.0f;
                            flashTimer = 0.2f; flashColor = sf::Color::Magenta;

                            floatingTexts.push_back({ "¡EXPLOSIÓN APOCALÍPTICA!", { 250.0f, 250.0f }, sf::Color::Magenta, 1.5f, 1.5f, -30.0f, 45 });
                            floatingTexts.push_back({ transferMsg, {n1->x - 60.0f, n1->y - 40.0f}, sf::Color::Yellow, 1.2f, 1.2f, -80.0f, 22 });
                        }
                    }
                }
                else if (event.key.code == sf::Keyboard::C) {
                    timeSpeed = (timeSpeed == 1.0f) ? 0.2f : 1.0f;
                }
                else if (event.key.code == sf::Keyboard::F) {
                    spawnMegaExplosion(particles, shockwaves, (float)(rand() % 1200), (float)(rand() % 600), sf::Color::Yellow, 200);
                }
            }
        }

        if (clashTimer > 0) clashTimer -= dt;

        // Actualizar Proyectiles
        for (size_t i = 0; i < projectiles.size();) {
            projectiles[i].update(dt);
            
            Particle trail;
            trail.pos = projectiles[i].pos;
            trail.vel = { ((rand() % 100) / 100.0f - 0.5f) * 60.0f, 50.0f };
            if (projectiles[i].type == 1) trail.color = sf::Color::Green;
            else if (projectiles[i].type == 2) trail.color = sf::Color::Cyan;
            else trail.color = sf::Color(255, 120, 0);

            trail.lifetime = trail.maxLifetime = 0.35f;
            trail.size = 6.0f;
            particles.push_back(trail);

            if (!projectiles[i].active) {
                float x1 = projectiles[i].targetNode1->x;
                float y1 = projectiles[i].targetNode1->y;
                float x2 = projectiles[i].targetNode2->x;
                float y2 = projectiles[i].targetNode2->y;

                sf::Color explosionColor = (projectiles[i].type == 1) ? sf::Color::Green : ((projectiles[i].type == 2) ? sf::Color::Cyan : sf::Color::Yellow);
                spawnMegaExplosion(particles, shockwaves, x1, y1, explosionColor);
                spawnMegaExplosion(particles, shockwaves, x2, y2, explosionColor);

                projectiles[i].targetNode1->scale = 3.0f;
                projectiles[i].targetNode2->scale = 3.0f;

                floatingTexts.push_back({ projectiles[i].msg, {x1 - 60.0f, y1 - 40.0f}, sf::Color::Yellow, 1.2f, 1.2f, -90.0f, 24 });
                
                shakeTimer = 0.5f;
                shakeIntensity = 30.0f;
                flashTimer = 0.12f;
                flashColor = explosionColor;

                projectiles[i] = projectiles.back();
                projectiles.pop_back();
            } else {
                ++i;
            }
        }

        if (tree.get_root()) {
            tree.calculatePositions(tree.get_root(), 600.0f, 140.0f, 270.0f);
        }

        updateNodesScale(tree.get_root(), dt);

        // Actualizar partículas
        for (size_t i = 0; i < particles.size();) {
            particles[i].update(dt);
            if (particles[i].lifetime <= 0) {
                particles[i] = particles.back();
                particles.pop_back();
            } else {
                ++i;
            }
        }

        // Actualizar Shockwaves
        for (size_t i = 0; i < shockwaves.size();) {
            shockwaves[i].update(dt);
            if (shockwaves[i].lifetime <= 0) {
                shockwaves[i] = shockwaves.back();
                shockwaves.pop_back();
            } else {
                ++i;
            }
        }

        // Actualizar textos flotantes
        for (size_t i = 0; i < floatingTexts.size();) {
            floatingTexts[i].pos.y += floatingTexts[i].velY * dt;
            floatingTexts[i].lifetime -= dt;
            if (floatingTexts[i].lifetime <= 0) {
                floatingTexts[i] = floatingTexts.back();
                floatingTexts.pop_back();
            } else {
                ++i;
            }
        }

        // Temblor de pantalla
        sf::View currentView = defaultView;
        if (shakeTimer > 0) {
            shakeTimer -= dt;
            float offsetX = ((rand() % 100) / 100.0f - 0.5f) * shakeIntensity * 2.0f;
            float offsetY = ((rand() % 100) / 100.0f - 0.5f) * shakeIntensity * 2.0f;
            currentView.move(offsetX, offsetY);
        }
        window.setView(currentView);

        // Renderizado
        window.clear(sf::Color(8, 5, 15));

        // --- DIBUJAR COMBATE EN EL FONDO (T-REX VS MECH) ---
        drawBackgroundFight(window, animTime, clashTimer > 0.0f);

        // OVNI VOLANDO
        float ufoX = 600.0f + cos(ufoAngle) * 400.0f;
        float ufoY = 120.0f + sin(ufoAngle) * 40.0f;
        
        sf::ConvexShape beam;
        beam.setPointCount(3);
        beam.setPoint(0, sf::Vector2f(ufoX, ufoY));
        beam.setPoint(1, sf::Vector2f(ufoX - 50.0f, ufoY + 200.0f));
        beam.setPoint(2, sf::Vector2f(ufoX + 50.0f, ufoY + 200.0f));
        beam.setFillColor(sf::Color(0, 255, 100, 30));
        window.draw(beam);

        sf::CircleShape ufo(25.0f);
        ufo.setScale(2.2f, 0.6f);
        ufo.setOrigin(25.0f, 25.0f);
        ufo.setPosition(ufoX, ufoY);
        ufo.setFillColor(sf::Color::Green);
        ufo.setOutlineThickness(3.0f);
        ufo.setOutlineColor(sf::Color::Yellow);
        window.draw(ufo);

        // DIBUJAR ÁRBOL Y PROYECTILES
        drawTreeEdges(window, tree.get_root());
        drawTreeNodes(window, tree.get_root(), font, tree.get_vueltas(), tree.get_terminado());

        for (const auto& m : projectiles) {
            sf::CircleShape projShape(12.0f);
            projShape.setOrigin(12.0f, 12.0f);
            projShape.setPosition(m.pos);
            projShape.setFillColor((m.type == 1) ? sf::Color::Green : ((m.type == 2) ? sf::Color::Cyan : sf::Color::Yellow));
            projShape.setOutlineThickness(4.0f);
            projShape.setOutlineColor(sf::Color::White);
            window.draw(projShape);
        }

        // Shockwaves
        for (const auto& sw : shockwaves) {
            sf::CircleShape circle(sw.radius);
            circle.setOrigin(sw.radius, sw.radius);
            circle.setPosition(sw.pos);
            circle.setFillColor(sf::Color::Transparent);
            
            sf::Color c = sw.color;
            c.a = (sf::Uint8)(255 * (sw.lifetime / sw.maxLifetime));
            circle.setOutlineColor(c);
            circle.setOutlineThickness(10.0f * (sw.lifetime / sw.maxLifetime));
            
            window.draw(circle);
        }

        // Partículas
        for (const auto& p : particles) {
            sf::CircleShape particleShape(p.size * (p.lifetime / p.maxLifetime));
            particleShape.setPosition(p.pos);
            particleShape.setFillColor(p.color);
            window.draw(particleShape);
        }

        // Textos flotantes
        for (const auto& ft : floatingTexts) {
            sf::Text txt(ft.text, font, ft.size);
            txt.setStyle(sf::Text::Bold);
            txt.setPosition(ft.pos);
            
            sf::Color c = ft.color;
            c.a = (sf::Uint8)(255 * (ft.lifetime / ft.maxLifetime));
            txt.setFillColor(c);
            
            window.draw(txt);
        }

        // Destellos
        if (flashTimer > 0) {
            flashTimer -= dt;
            sf::RectangleShape flash(sf::Vector2f(1200, 800));
            flash.setFillColor(flashColor);
            window.draw(flash);
        }

        // HUD / Interfaz
        string msg = "Paso: " + to_string(tree.get_vueltas());
        if (tree.get_terminado()) msg += " (¡BATALLA FINAL ALCANZADA!)";
        msg += "\n[ESPACIO]: DISPARAR GUERRA  |  [C]: SLOW-MOTION  |  [F]: FUEGOS ARTIFICIALES";

        sf::Text info(msg, font, 18);
        info.setStyle(sf::Text::Bold);
        info.setFillColor(sf::Color::Yellow);
        info.setOutlineThickness(2.0f);
        info.setOutlineColor(sf::Color::Red);
        info.setPosition(15.0f, 15.0f);
        window.draw(info);

        window.display();
    }

    return 0;
}