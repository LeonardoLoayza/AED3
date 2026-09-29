#include <iostream>
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
	//~BinaryTree();
	
	bool insrt(int x) {
		Node** p=nullptr;
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
			while ( (*q)->left ) {
				q = &((*q)->left);
			}
		}
		else {
			q = &((*q)->left);
			while ( (*q)->right ) {
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

	void inorderST();
	void Levels(Node* p);
	void PrintLevels();
	int alturaMax();
	void altr_maxI(Node* p, int cont, int& max);
	int altr_maxR(Node* p);
	void clear(Node* p);
	Node* get_root() { return root; }
};

int main() {
	BinaryTree t;

	/*
			  50
			/    \
		  30      70
		 /  \    /  \
	   20   40  60   80
	*/

	t.insrt(50);
	t.insrt(30);
	t.insrt(70);
	t.insrt(20);
	t.insrt(40);
	t.insrt(60);
	t.insrt(80);

	cout << "--- TEST 1: Inorder de un arbol completo ---" << endl;
	cout << "Esperado: 20 30 40 50 60 70 80 " << endl;
	cout << "Obtenido: ";
	// Pasamos la raiz usando tu funcion get_root()
	t.inorder(t.get_root());
	cout << endl << endl;


	cout << "--- TEST 2: Inorder despues de eliminar una hoja (20) ---" << endl;
	t.remv(20);
	cout << "Esperado: 30 40 50 60 70 80 " << endl;
	cout << "Obtenido: ";
	t.inorder(t.get_root());
	cout << endl << endl;


	cout << "--- TEST 3: Inorder despues de eliminar un nodo con 2 hijos (50 - la raiz) ---" << endl;
	t.remv(50);
	cout << "Esperado: 30 40 60 70 80 " << endl; // El arbol se reestructura pero sigue ordenado
	cout << "Obtenido: ";
	t.inorder(t.get_root());
	cout << endl;

}