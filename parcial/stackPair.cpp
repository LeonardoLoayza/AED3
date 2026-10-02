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
		if (!root) return; 
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

	void inorderStack2() {
		stack<pair<Node*, int>> st;
		st.push({ root,0 });

		while (!st.empty()) {
			Node* nodo = st.top().first;
			int estado = st.top().second;

			if (estado == 0) {
				st.top().second = 1;
				if (nodo->left)
					st.push({ nodo->left,0 });
			}
			else if (estado == 1) {
				st.top().second = 2;
				cout << nodo->v;
			}
			else {
				st.pop();
				if (nodo->right != nullptr)
					st.push({ nodo->right, 0 });
			}
		}
	}

	bool removeSubtree(int x) {
		Node** p = nullptr;
		if (!find(x, p))
			return false;

		Node* c = *p;
		queue<Node*> q;
		q.push(c);
		while (!q.empty()) {
			c = q.front();
			if (c->left) q.push(c->left);
			if (c->right) q.push(c->right);
			q.pop();
			delete c;
			c = nullptr;


		}
		*p = nullptr;
		return true;

	}
};

int main() {
	int main() {
		BinaryTree t;

		// =========================
		// TEST 1: Árbol vacío
		// =========================
		cout << "===== TEST 1: ARBOL VACIO =====" << endl;
		cout << "Buscar 10: " << t.find(10, *(new Node**)) << endl;
		cout << endl;


		// =========================
		// TEST 2: Inserciones
		// =========================
		cout << "===== TEST 2: INSERCIONES =====" << endl;

		cout << "Insertar 50: " << t.insrt(50) << endl;
		cout << "Insertar 30: " << t.insrt(30) << endl;
		cout << "Insertar 70: " << t.insrt(70) << endl;
		cout << "Insertar 20: " << t.insrt(20) << endl;
		cout << "Insertar 40: " << t.insrt(40) << endl;
		cout << "Insertar 60: " << t.insrt(60) << endl;
		cout << "Insertar 80: " << t.insrt(80) << endl;

		// Árbol:
		//
		//           50
		//         /    \
	    //       30      70
		//      /  \    /  \
	    //    20   40  60   80


		// =========================
		// TEST 3: Insertar duplicados
		// =========================
		cout << "\n===== TEST 3: DUPLICADOS =====" << endl;

		cout << "Insertar 50 otra vez: " << t.insrt(50) << endl;
		cout << "Insertar 30 otra vez: " << t.insrt(30) << endl;
		cout << "Insertar 80 otra vez: " << t.insrt(80) << endl;


		// =========================
		// TEST 4: Buscar
		// =========================
		cout << "\n===== TEST 4: BUSQUEDA =====" << endl;

		Node** p = nullptr;

		cout << "Buscar 40: " << t.find(40, p) << endl;
		cout << "Buscar 100: " << t.find(100, p) << endl;


		// =========================
		// TEST 5: Inorder recursivo
		// =========================
		cout << "\n===== TEST 5: INORDER =====" << endl;

		t.inorder(t.get_root());
		cout << endl;

		// Esperado:
		// 20 30 40 50 60 70 80


		// =========================
		// TEST 6: Inorder iterativo
		// =========================
		cout << "\n===== TEST 6: INORDER STACK =====" << endl;

		t.inorderST();
		cout << endl;


		// =========================
		// TEST 7: Eliminar hoja
		// =========================
		cout << "\n===== TEST 7: ELIMINAR HOJA =====" << endl;

		cout << "Eliminar 20: " << t.remv(20) << endl;

		t.inorder(t.get_root());
		cout << endl;

		// Esperado:
		// 30 40 50 60 70 80


		// =========================
		// TEST 8: Eliminar nodo con un hijo
		// =========================
		cout << "\n===== TEST 8: UN HIJO =====" << endl;

		// Creamos un hijo para 40
		cout << "Insertar 35: " << t.insrt(35) << endl;

		// Ahora 40 tiene un hijo izquierdo: 35
		cout << "Eliminar 40: " << t.remv(40) << endl;

		t.inorder(t.get_root());
		cout << endl;

		// Esperado:
		// 30 35 50 60 70 80


		// =========================
		// TEST 9: Eliminar nodo con dos hijos
		// =========================
		cout << "\n===== TEST 9: DOS HIJOS =====" << endl;

		cout << "Eliminar 70: " << t.remv(70) << endl;

		t.inorder(t.get_root());
		cout << endl;


		// =========================
		// TEST 10: Eliminar raíz
		// =========================
		cout << "\n===== TEST 10: ELIMINAR RAIZ =====" << endl;

		cout << "Eliminar 50: " << t.remv(50) << endl;

		t.inorder(t.get_root());
		cout << endl;


		// =========================
		// TEST 11: Eliminar elemento inexistente
		// =========================
		cout << "\n===== TEST 11: ELEMENTO INEXISTENTE =====" << endl;

		cout << "Eliminar 999: " << t.remv(999) << endl;


		// =========================
		// TEST 12: removeSubtree
		// =========================
		cout << "\n===== TEST 12: REMOVE SUBTREE =====" << endl;

		BinaryTree t2;

		t2.insrt(50);
		t2.insrt(30);
		t2.insrt(70);
		t2.insrt(20);
		t2.insrt(40);
		t2.insrt(60);
		t2.insrt(80);

		cout << "Antes:" << endl;
		t2.inorder(t2.get_root());
		cout << endl;

		cout << "Eliminar subarbol 30: "
			<< t2.removeSubtree(30) << endl;

		cout << "Despues:" << endl;
		t2.inorder(t2.get_root());
		cout << endl;

		// Esperado:
		// 50 60 70 80


		// =========================
		// TEST 13: removeSubtree de raíz
		// =========================
		cout << "\n===== TEST 13: REMOVE SUBTREE RAIZ =====" << endl;

		cout << "Eliminar todo el arbol: "
			<< t2.removeSubtree(50) << endl;

		cout << "Raiz: " << t2.get_root() << endl;


		// =========================
		// TEST 14: Árbol de un solo nodo
		// =========================
		cout << "\n===== TEST 14: UN SOLO NODO =====" << endl;

		BinaryTree t3;

		t3.insrt(10);

		cout << "Antes: ";
		t3.inorder(t3.get_root());
		cout << endl;

		cout << "Eliminar 10: " << t3.remv(10) << endl;

		cout << "Raiz despues: "
			<< t3.get_root() << endl;


		return 0;
	}

}
