#include <iostream>
#include <initializer_list>
#include <vector>
#include <deque>
#include <queue>
using namespace std;
struct Node
{
	int value;
	Node* nodes[2];
	Node(int v) { value = v; nodes[0] = nodes[1] = nullptr; }
};

class CBinTree
{
public:
	CBinTree();
	~CBinTree();
	bool find(int x, Node**& p);
	bool ins(int x);
	void ins(std::initializer_list<int> values);
	void print();
	void inorder(Node* n);

	void l(Node* n, deque<int> &d) {
		if (!n) return;
		if (n->nodes[0]->nodes[0])
			l(n->nodes[0], d);
		d.push_front(n->value);
	}
	void r(Node* n, deque<int>& d2) {
		if (!n) return;
		if (n->nodes[1]->nodes[1])
			r(n->nodes[1], d2);
		d2.push_back(n->value);
	}

	void perimeter()
	{
		// Implementar
		// Imprimir en orden antihorario los nodos del perimetro del arbol,
		// comenzando por la raiz.
		// El perimetro esta compuesto por:
		// - Borde izquierdo: camino desde la raiz hasta el nodo mas a la izquierda
		// - Borde inferior: nodos con al menos un hijo nullptr (de izq a der)
		// - Borde derecho: camino desde el nodo mas a la derecha hasta la raiz
		//   (sin incluir la raiz ni repetir nodos ya impresos)

		if (!root) return; 
		vector<Node*> left_b;
		vector<Node*> right_b; 
		vector<Node*> bottom_b;

		Node* curr = root; 
		while (curr) {
			left_b.push_back(curr);
			curr = curr->nodes[0];
		}

		curr = root->nodes[1];
		while (curr) {
			right_b.push_back(curr);
			curr = curr->nodes[1];
		}

		vector<Node*>s;
		curr = root; 
		while (curr != nullptr || s.empty() == false) {
			while (curr) {
				s.push_back(curr);
				curr = curr->nodes[0];
			}
			curr = s.back(); 
			s.pop_back(); 
			if (!curr->nodes[0] || !curr->nodes[1]) {
				bool repetido = false; 

				for (Node* x : left_b) 
					if (curr == x) repetido = true; 
				for (Node* x : right_b)
					if (curr == x) repetido = true;

				if (repetido==false)
					bottom_b.push_back(curr);
			}
			curr = curr->nodes[1];
		}

		for (Node* x : left_b)
			cout << x->value << " ";
		for (Node* x : bottom_b)
			cout << x->value << " ";
		// rbegin es reverse begin 
		for (auto iterator = right_b.rbegin(); iterator != right_b.rend();iterator++) {
			cout << (*iterator)->value << " ";
		}
		

	}


private:
	Node* root;
};

CBinTree::CBinTree()
{
	root = nullptr;
}

CBinTree::~CBinTree()
{
}

bool CBinTree::find(int x, Node**& p)
{
	for (p = &root; *p && (*p)->value != x;
		p = &((*p)->nodes[x > (*p)->value]));
	return *p && (*p)->value == x;
}

bool CBinTree::ins(int x)
{
	Node** p;
	if (find(x, p)) return 0;
	*p = new Node(x);
	return 1;
}

void CBinTree::ins(std::initializer_list<int> values)
{
	for (int x : values) ins(x);
}

void CBinTree::print()
{
	std::cout << "inorder: ";
	inorder(root);
	std::cout << "\n";
}



void CBinTree::inorder(Node* n)
{
	if (!n) return;
	inorder(n->nodes[0]);
	std::cout << n->value << " ";
	inorder(n->nodes[1]);
}

int main()
{
	// Caso 1: arbol completo
	std::cout << "Caso 1: arbol completo" << std::endl;
	CBinTree t1;
	t1.ins({ 50,
		30, 70,
		20, 40, 60, 80,
		15, 25, 35, 45, 55, 65, 75, 90,
		12, 17, 22, 28, 32, 38, 42, 48, 52, 58, 62, 68, 72, 78, 85, 95 });
	t1.print();
	std::cout << "esperado:  50 30 20 15 12 17 22 28 32 38 42 48 52 58 62 68 72 78 85 95 90 80 70\n";
	std::cout << "perimeter: ";
	t1.perimeter();
	std::cout << "\n" << std::endl;

	// Caso 2: arbol con ultimo nivel incompleto
	std::cout << "Caso 2: arbol con ultimo nivel incompleto" << std::endl;
	CBinTree t2;
	t2.ins({ 50,
		30, 70,
		20, 40, 60, 80,
		15, 25, 35, 45, 55, 65, 75, 90,
		12, 22, 28, 38, 42, 48, 52, 62, 68, 78, 85, 95 });
	t2.print();
	std::cout << "esperado:  50 30 20 15 12 22 28 35 38 42 48 52 55 62 68 75 78 85 95 90 80 70\n";
	std::cout << "perimeter: ";
	t2.perimeter();
	std::cout << "\n" << std::endl;

	return 0;
}