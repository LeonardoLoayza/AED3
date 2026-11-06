/*
ARBOL DE CARAMELOS - paso a paso

Arbol de ejemplo (por niveles):
		3
	  0   0
	-  -  2  0

Controles:
  ESPACIO : avanzar un paso (una ronda de recorrido)
  A       : activar / desactivar modo automatico (1 paso por segundo)
  R       : reiniciar el arbol

Colores:
  verde  = nodos que participaron en el ultimo paso
  blanco = nodos sin cambio en el ultimo paso
*/

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class node {
public:
	int value;
	node* left;
	node* right;
	int x, y;
	int marca;

	node(int v) {
		value = v;
		left = nullptr;
		right = nullptr;
		x = 0;
		y = 0;
		marca = 0;
	}
};

class Ctree {
private:
	node* root;
	int vueltas;      // numero de pasos realizados
	bool terminado;   // true cuando ya no hay mas cambios

public:
	Ctree() {
		root = nullptr;
		vueltas = 0;
		terminado = false;
	}

	~Ctree() {
		clear(this->root);
	}

	void clear(node* n) {
		if (!n)
			return;
		clear(n->left);
		clear(n->right);
		delete n;
	}

	node*& get_root() {
		return root;
	}

	void setPosxy(node* n, int level, int& col) {
		if (!n)
			return;
		setPosxy(n->left, level + 1, col);
		n->x = col * 80 + 100;
		n->y = level * 90 + 100;
		col++;
		setPosxy(n->right, level + 1, col);
	}

	void drawNode(sf::RenderWindow& pantalla, node* n, sf::Font& font) {
		float radius = 16.0f;

		sf::CircleShape c(radius);
		bool cambio = (!terminado && vueltas > 0 && n->marca == vueltas);
		c.setFillColor(cambio ? sf::Color::Green : sf::Color::White);
		c.setOrigin(radius, radius);
		c.setPosition((float)n->x, (float)n->y);
		pantalla.draw(c);

		sf::Text tex;
		tex.setFont(font);
		tex.setString(std::to_string(n->value));
		tex.setCharacterSize(16);
		tex.setFillColor(sf::Color::Black);

		sf::FloatRect b = tex.getLocalBounds();
		tex.setOrigin(b.left + b.width / 2.0f,
			b.top + b.height / 2.0f);
		tex.setPosition((float)n->x, (float)n->y);
		pantalla.draw(tex);
	}

	void drawNodes(sf::RenderWindow& pantalla, node* n, sf::Font& font) {
		if (!n)
			return;
		drawNodes(pantalla, n->left, font);
		drawNode(pantalla, n, font);
		drawNodes(pantalla, n->right, font);
	}

	void drawLine(sf::RenderWindow& pantalla, node* node_a, node* node_b) {
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f((float)node_a->x, (float)node_a->y), sf::Color::White),
			sf::Vertex(sf::Vector2f((float)node_b->x, (float)node_b->y), sf::Color::White)
		};
		pantalla.draw(line, 2, sf::Lines);
	}

	void drawLines(sf::RenderWindow& pantalla, node* n) {
		if (!n)
			return;
		if (n->left) {
			drawLine(pantalla, n, n->left);
			drawLines(pantalla, n->left);
		}
		if (n->right) {
			drawLine(pantalla, n, n->right);
			drawLines(pantalla, n->right);
		}
	}

	// ************************* EJERCICIO *********************************

	void crear_arbol(int v) {
		clear(root);
		root = new node(v);
		vueltas = 0;
		terminado = false;
	}

	void insertar_nodo(std::string rut, int k) {
		node** p = &root;
		for (char c : rut) {
			if ((!*p))
				return;
			if (c == 'L')
				p = &(*p)->left;
			else if (c == 'R')
				p = &(*p)->right;
			else
				continue;
		}
		(*p) = new node(k);
	}

	bool recorrido(node* p, int max_cambio) {
		if (!p)
			return false;

		bool cambio = false;

		if (p->left && p->marca != max_cambio && p->left->marca != max_cambio) {
			node* h = p->left;
			if (h->value > 1 && h->value >= p->value) {
				h->value--;
				p->value++;
				cambio = true;
			}
			else if (h->value == 0 && p->value >= 1) {
				h->value++;
				p->value--;
				cambio = true;
			}
			if (cambio)
				p->marca = h->marca = max_cambio;
		}

		if (p->right && p->marca != max_cambio && p->right->marca != max_cambio) {
			node* h = p->right;
			if (h->value > 1 && h->value >= p->value) {
				h->value--;
				p->value++;
				cambio = true;
			}
			else if (h->value == 0 && p->value >= 1) {
				h->value++;
				p->value--;
				cambio = true;
			}
			if (cambio)
				p->marca = h->marca = max_cambio;
		}

		bool a = recorrido(p->left, max_cambio);
		bool b = recorrido(p->right, max_cambio);

		return cambio || a || b;
	}

	// Un solo paso = una ronda de recorrido
	void paso() {
		if (terminado)
			return;
		if (recorrido(root, vueltas + 1))
			vueltas++;
		else
			terminado = true;
	}

	int get_vueltas() { return vueltas; }
	bool get_terminado() { return terminado; }

	void draw() {
		sf::Font font;
		if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
			std::cout << "error de fuente" << std::endl;
			return;
		}

		int col = 1;
		setPosxy(root, 0, col);

		sf::RenderWindow pantalla(sf::VideoMode(1200, 800), "Armar_suma");
		pantalla.setFramerateLimit(60);

		bool automatico = false;
		sf::Clock reloj;

		while (pantalla.isOpen()) {
			sf::Event ev;
			while (pantalla.pollEvent(ev)) {
				if (ev.type == sf::Event::Closed)
					pantalla.close();

				if (ev.type == sf::Event::KeyPressed) {
					if (ev.key.code == sf::Keyboard::Space)
						paso();
					else if (ev.key.code == sf::Keyboard::A) {
						automatico = !automatico;
						reloj.restart();
					}
					else if (ev.key.code == sf::Keyboard::R) {
						crear_arbol(3);
						insertar_nodo("L", 0);
						insertar_nodo("R", 0);
						insertar_nodo("RL", 2);
						insertar_nodo("RR", 0);
						col = 1;
						setPosxy(root, 0, col);
					}
				}
			}

			if (automatico && reloj.getElapsedTime().asSeconds() >= 1.0f) {
				paso();
				reloj.restart();
			}

			pantalla.clear(sf::Color(30, 30, 30));
			drawLines(pantalla, root);
			drawNodes(pantalla, root, font);

			std::string msg = "Paso: " + std::to_string(vueltas);
			if (terminado)
				msg += "  (terminado)";
			msg += "   |   ESPACIO: paso   A: auto (" + std::string(automatico ? "ON" : "OFF") + ")   R: reiniciar";

			sf::Text info(msg, font, 20);
			info.setFillColor(sf::Color::White);
			info.setPosition(10.f, 10.f);
			pantalla.draw(info);

			pantalla.display();
		}
	}
};

int main() {
	Ctree c1;

	// Arbol:      3
	//           /   \
	//          0     0
	//               / \
	//              2   0
	c1.crear_arbol(3);
	c1.insertar_nodo("L", 0);
	c1.insertar_nodo("R", 0);
	c1.insertar_nodo("RL", 2);
	c1.insertar_nodo("RR", 0);

	c1.draw();

	return 0;
}
