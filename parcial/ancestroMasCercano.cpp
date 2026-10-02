#include <iostream>
#include <queue>
#include <stack> 
using namespace std;

class Node {
public:
	int v;
	Node* left;
	Node* right;
	Node(int _v) {
		v = _v;
		left = nullptr;
		right = nullptr;
	}
};

class BinaryTree {
	Node* root;
	bool lado_reemp;
public:
	BinaryTree() {
		root = nullptr;
		lado_reemp = 0;
	}
	~BinaryTree() {
		if (root == nullptr) return;

		Node* p = root;
		queue<Node*>q;
		q.push(p);
		while (!q.empty()) {
			Node* c = q.front();
			q.pop();
			if (c->left) {
				q.push(c->left);
			}
			if (c->right) {
				q.push(c->right);
			}
			cout << "borrando nodo:" << c->v << endl;
			delete c;
			c = nullptr;
		}
		root = nullptr;
		cout << "desutrctor god" << endl;
	}

	bool insrt(int x) {
		Node** p = nullptr;
		if (find(x, p)) {
			return false;
		}
		*p = new Node(x);
		return true;
	}

	Node** fnd_reemp(Node** p) {
		Node** q = p;
		if (lado_reemp) {
			q = &((*q)->right);
			while ((*q)->left) {
				q = &((*q)->left);
			}
		}
		else {
			q = &((*q)->left);
			while ((*q)->right) {
				q = &((*q)->right);
			}
		}
		return q;
	}

	bool remv(int x) {
		Node** p = nullptr;
		if (!find(x, p)) {
			return false;
		}

		//caso 2 hijos, 1 hijo, 0 hijos
		if ((*p)->left && (*p)->right) {
			Node** q = fnd_reemp(p);
			(*p)->v = (*q)->v;
			p = q;

		}
		if (
			((*p)->left && (*p)->right == nullptr) ||
			((*p)->left == nullptr && (*p)->right)
			) {

			if ((*p)->left) {
				Node* t = *p;
				*p = (*p)->left;
				delete t;
			}
			else {
				Node* t = *p;
				*p = (*p)->right;
				delete t;
			}


			return true;
		}

		if ((*p)->left == nullptr && (*p)->right == nullptr) {
			delete* p;
			*p = nullptr;
			return true;
		}

	}

	bool find(int x, Node**& p) {
		p = &root;
		while (*p && (*p)->v != x) {
			if (x < (*p)->v) {
				p = &((*p)->left);
			}
			else {
				p = &((*p)->right);
			}
		}

		return *p;
	}

	void print();
	void inorder(Node* n) {
		if (n == nullptr)
			return;
		if (n->left)
			inorder(n->left);
		cout << n->v << " ";
		if (n->right)
			inorder(n->right);
	}

	void inorderST() {
		Node* c = root;
		stack<Node*>s;
		s.push(c);
		while (c || !s.empty()) {
			while (c) {
				s.push(c->left);
				c = c->left;
			}
			c = s.top();
			s.pop();
			cout << c->v << " ";
			c = c->right;
		}
	}
	void Levels(Node* p);
	void PrintLevels();
	int alturaMax();
	void altr_maxI(Node* p, int cont, int& max);
	int altr_maxR(Node* p);
	void clear(Node* p);
	Node* get_root() { return root; }

	int findLCA(int a, int b);
};

//Ejercicio 2: El Ancestro Común más Cercano(LCA con poda)Dados dos valores A y B 
//que existen en el Árbol Binario de Búsqueda(BST), encuentra el valor de su ancestro 
//común más bajo(el nodo más profundo que tiene a A y B como descendientes).
//Restricción : No debes recorrer todo el árbol(nada de $O(N)$).
//Debes usar la propiedad del BST para encontrarlo en tiempo $O(h)$(donde $h$ es la altura),
//bajando por una sola rama geométrica.Reto mental : 
//¿Qué condición matemática te dice que te has "pasado" del ancestro y que
//A y B se han separado en ramas distintas ? Firma esperada : int findLCA(int a, int b);

int BinaryTree::findLCA(int a, int b) {
	Node* p = root;
	while (p) {
		if (a > p->v && b > p->v)
			p = p->right;
		else if (a < p->v && b < p->v)
			p = p->left;
		else
			return p->v;
	}
	

	return -1; // Por si el árbol está vacío
}


int main() {
	BinaryTree t;
	// Reconstruimos el árbol del ejemplo anterior
	t.insrt(60); t.insrt(30); t.insrt(70);
	t.insrt(20); t.insrt(40); t.insrt(65);
	t.insrt(80); t.insrt(15); t.insrt(25);
	t.insrt(35); t.insrt(45); t.insrt(62);
	t.insrt(68); t.insrt(75); t.insrt(85);

	/* Árbol visual:
							  60
							/    \
						  30      70
						/    \   /   \
					  20     40 65   80
					 /  \   / \ / \  / \
					15  25 35 45 ... ...
	*/

	cout << "--- TEST CASES LCA ---" << endl;

	// Caso 1: Ambos están en la rama izquierda
	cout << "LCA(15, 45): " << t.findLCA(15, 45) << " | Esperado: 30" << endl;

	// Caso 2: Ambos están en la rama derecha
	cout << "LCA(62, 68): " << t.findLCA(62, 68) << " | Esperado: 65" << endl;

	// Caso 3: Caminos separados desde la raíz
	cout << "LCA(25, 85): " << t.findLCA(25, 85) << " | Esperado: 60" << endl;

	// Caso 4: (EL CASO TRAMPA) Uno de los nodos es ancestro directo del otro
	cout << "LCA(40, 45): " << t.findLCA(40, 45) << " | Esperado: 40" << endl;
	cout << "LCA(70, 85): " << t.findLCA(70, 85) << " | Esperado: 70" << endl;

	return 0;
}