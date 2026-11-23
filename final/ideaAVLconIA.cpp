#include <iostream>
#include <stack>
#include <queue>
#include <algorithm> // Para std::max

using namespace std;

// 1. El Nodo incluye la altura
struct AVLNode {
	int v;
	AVLNode* left;
	AVLNode* right;
	int height; // Altura del subárbol con raíz en este nodo

	AVLNode(int _v) {
		left = right = nullptr;
		v = _v;
		height = 1; // Un nodo hoja siempre tiene altura 1
	}
};

class AVLTree {
	AVLNode* root;
	bool lado_reemp;

	int height(AVLNode* p) {
		if (!p) return 0;
		return p->height;
	}

	void updateHeight(AVLNode* p) {
		p->height = 1 + max(height(p->left), height(p->right));
	}

	int getBalanceFactor(AVLNode* p) {
		if (!p) return 0;
		return height(p->left) - height(p->right);
	}

	AVLNode* rotateLeft(AVLNode* x) {
		AVLNode* y = x->right;
		AVLNode* yl = y->left;

		x->right = yl;
		y->left = x;

		updateHeight(x);
		updateHeight(y);
		return y;
	}

	AVLNode* rotateRight(AVLNode* x) {
		AVLNode* y = x->left;
		AVLNode* yr = y->right;

		x->left = yr;
		y->right = x;

		updateHeight(x);
		updateHeight(y);
		return y;
	}

public:
	AVLTree() {
		root = nullptr;
		lado_reemp = false;
	}

	~AVLTree() {
		cout << "Comienza liberacion" << endl;
		clear(root);
		root = nullptr;
		cout << "Termina liberacion" << endl;
	}

	AVLNode* rebalance(AVLNode* p) {
		if (!p) return nullptr;

		updateHeight(p);
		int bf = getBalanceFactor(p);

		// Caso Izquierda-Izquierda o Izquierda-Derecha
		if (bf > 1) {
			if (getBalanceFactor(p->left) < 0)
				p->left = rotateLeft(p->left);
			return rotateRight(p);
		}
		// Caso Derecha-Derecha o Derecha-Izquierda
		else if (bf < -1) {
			if (getBalanceFactor(p->right) > 0)
				p->right = rotateRight(p->right);
			return rotateLeft(p);
		}

		return p;
	}

	bool insrt(int x) {
		stack<AVLNode**> s;
		AVLNode** p = &root;

		while (*p) {
			s.push(p);
			if ((*p)->v == x)
				return false; // Valor duplicado
			if (x < (*p)->v) {
				p = &((*p)->left);
			}
			else {
				p = &((*p)->right);
			}
		}

		*p = new AVLNode(x);

		// Rebalancear hacia arriba mediante la pila
		while (!s.empty()) {
			AVLNode** a = s.top();
			s.pop();
			*a = rebalance(*a);
		}

		return true;
	}

	// Busca el sustituto para el caso de 2 hijos y acumula el camino en la pila
	AVLNode** fnd_reemp(AVLNode** p, stack<AVLNode**>& path) {
		AVLNode** q = p;
		if (lado_reemp) { // Sucesor (más a la izquierda del subárbol derecho)
			q = &((*q)->right);
			while ((*q)->left) {
				path.push(q);
				q = &((*q)->left);
			}
		}
		else { // Predecesor (más a la derecha del subárbol izquierdo)
			q = &((*q)->left);
			while ((*q)->right) {
				path.push(q);
				q = &((*q)->right);
			}
		}
		return q;
	}

	bool remv(int x) {
		stack<AVLNode**> path;
		AVLNode** p = &root;

		// 1. Buscar el nodo guardando la ruta de punteros
		while (*p && (*p)->v != x) {
			path.push(p);
			if (x < (*p)->v) {
				p = &((*p)->left);
			}
			else {
				p = &((*p)->right);
			}
		}

		// Si no se encontró, salir
		if (*p == nullptr) return false;

		path.push(p); // Guardar la posición del propio nodo a eliminar

		// Caso: 2 Hijos
		if ((*p)->left && (*p)->right) {
			AVLNode** q = fnd_reemp(p, path);
			(*p)->v = (*q)->v; // Copiar valor del reemplazo
			p = q;             // Redireccionar p hacia el nodo a borrar físicamente
			lado_reemp = !lado_reemp; // Alternar lado de reemplazo
		}

		// Caso: 1 o 0 Hijos
		AVLNode* t = *p;
		if ((*p)->left) {
			*p = (*p)->left;
		}
		else {
			*p = (*p)->right;
		}
		delete t;

		// 2. Rebalancear hacia arriba deshaciendo la pila
		while (!path.empty()) {
			AVLNode** a = path.top();
			path.pop();
			*a = rebalance(*a);
		}

		return true;
	}

	bool find(int x, AVLNode**& p) {
		p = &root;
		while (*p && (*p)->v != x) {
			if (x < (*p)->v)
				p = &((*p)->left);
			else
				p = &((*p)->right);
		}
		return (*p != nullptr);
	}

	void inorder(AVLNode* p) {
		if (!p) return;
		inorder(p->left);
		cout << p->v << " ";
		inorder(p->right);
	}

	void inorderST() {
		AVLNode* c = root;
		stack<AVLNode*> s;
		while (c || !s.empty()) {
			while (c) {
				s.push(c);
				c = c->left;
			}
			c = s.top();
			s.pop();
			cout << c->v << " ";
			c = c->right;
		}
		cout << endl;
	}

	void PrintLevels() {
		if (!root) return;
		queue<AVLNode*> q;
		q.push(root);

		while (!q.empty()) {
			int levelSize = q.size();
			while (levelSize--) {
				AVLNode* curr = q.front();
				q.pop();
				cout << curr->v << " ";
				if (curr->left) q.push(curr->left);
				if (curr->right) q.push(curr->right);
			}
			cout << endl;
		}
	}

	int alturaMax() {
		return height(root);
	}

	void clear(AVLNode* p) {
		if (!p) return;
		clear(p->left);
		clear(p->right);
		delete p;
	}

	AVLNode* get_root() { return root; }
};

int main() {
	AVLTree t;

	cout << "--- Insertando elementos ---" << endl;
	t.insrt(10);
	t.insrt(20);
	t.insrt(30);
	t.insrt(40);
	t.insrt(50);
	t.insrt(25);

	cout << "Recorrido Inorder: ";
	t.inorder(t.get_root());
	cout << endl;

	cout << "Impresion por Niveles (Estructura AVL):" << endl;
	t.PrintLevels();

	cout << "\n--- Eliminando elementos ---" << endl;
	t.remv(30);
	cout << "Despues de eliminar 30 (Inorder): ";
	t.inorderST();

	cout << "Niveles despues de rebalancear:" << endl;
	t.PrintLevels();

	return 0;
}
