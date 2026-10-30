#include <iostream>
#include <stack>
#include <queue>
#include <algorithm> // Para std::max
using namespace std;

// 1. El Nodo ahora incluye la altura
struct AVLNode {
	int v;
	AVLNode* left;
	AVLNode* right;
	int height; // Altura del subárbol con raíz en este nodo
	AVLNode(int _v) {
		left = right = 0;
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
		p->height = 1 + max(height(p->left), height(p->right); 
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

		y->right = x; 
		x->left = yr; 

		updateHeight(x); 
		updateHeight(y); 
		return y; 
	}


public:
	AVLTree() {
		root = 0;
		lado_reemp = 0;
	}
	~AVLTree() {
		cout << "Comienza liberacion" << endl;
		this->clear(root);
		root = 0;
		cout << "Termina liberacion" << endl;
	}

	bool insrt(int x) { 
	}

	bool remv(int x) {
	}

	AVLNode** fnd_reemp(AVLNode** p, stack<AVLNode**>& path) {
	}

	bool find(int x, AVLNode**& p) {
		
	}

	void print() {
		
	}

	void inorder(AVLNode* p) {
		
	}

	void inorderST() {
		
	}

	void Levels(AVLNode* p) {
		
	}

	void PrintLevels() {
		
	}

	int alturaMax() {
	}

	void clear(AVLNode* p) {
	}

	AVLNode* get_root() { return root; }
};

int main() {
	AVLTree t;
	cout << "Insertando: 60, 30, 70, 20, 40, 65, 80, 75" << endl;
	t.insrt(60);
	t.insrt(30);
	t.insrt(70);
	t.insrt(20);
	t.insrt(40);
	t.insrt(65);
	t.insrt(80);
	t.insrt(75);
	t.print();
	t.PrintLevels(); // Verás las alturas y factores de balance

	// Prueba de rotación (insertar 50 causará un desbalance LR en 60)
	cout << "\nInsertando 50 (causa rotacion LR en 30)" << endl;
	t.insrt(50);
	t.print();
	t.PrintLevels();

	// Prueba de rotación (insertar 10 causará un desbalance LL en 20)
	cout << "\nInsertando 10 (causa rotacion LL en 20)" << endl;
	t.insrt(10);
	t.print();
	t.PrintLevels();

	cout << "\nEliminando 80 (causa rebalanceo)" << endl;
	t.remv(80);
	t.print();
	t.PrintLevels();

	cout << "\nEliminando 65" << endl;
	t.remv(65);
	t.print();
	t.PrintLevels();

	cout << "\nAltura maxima del arbol: " << t.alturaMax() << endl;

	return 0;
}
