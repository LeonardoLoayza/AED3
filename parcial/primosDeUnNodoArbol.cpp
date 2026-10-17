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
		lado_reemp = 1;
	}
	~BinaryTree() {
		if (root == nullptr) return; 
		queue<Node*>q; 
		q.push(root);
		Node* current = nullptr; 
		
		while (!q.empty()) {
			current = q.front(); 
			q.pop(); 

			if (current->left != nullptr) 
				q.push(current->left);
			
			if (current->right !=nullptr )
				q.push(current->right); 

			delete current;
		}
		cout << "deleted";
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
		if (lado_reemp) {
			p = &((*p)->right);
			while ((*p)->left) {
				p = &((*p)->left);
			}
		}
		else {
			p = &((*p)->left);
			while ((*p)->right) {
				p = &((*p)->right);
			}
		}
		return p; 
	}

	bool remv(int x) {
		Node** p = nullptr;
		if (!find(x, p)) {
			return false; 
		}

		if ((*p)->left && (*p)->right) {
			Node** q = nullptr; 
			q=fnd_reemp(p);
			(*p)->v = (*q)->v;
			p = q;
		}

		if ((*p)->right) {
			Node* tmp = *p; 
			*p = (*p)->right; 

			delete tmp; 
			tmp = nullptr;
		}
		else {
			Node* tmp = *p;
			*p = (*p)->left;

			delete tmp;
			tmp = nullptr;
		}

		return true; 
	}

	bool find(int x, Node**& p) {
		p = &root; 
		while (*p && (*p)->v != x) {
			if ((*p)->v < x) {
				p = &((*p)->right); 
			}
			else {
				p = &((*p)->left);
			}
		}
		return *p && (*p)->v == x;
	}

	void print();
	void inorder(Node* n) {
	}


	void inorderST() {

	}
	void Levels(Node* p);
	void PrintLevels();
	int alturaMax();
	void altr_maxI(Node* p, int cont, int& max);
	int altr_maxR(Node* p);
	void clear(Node* p);
	Node* get_root() { return root; }
	void printCousins(int x) {
		if (!root || root->v == x) return; 
		queue<Node*> q; 
		Node* current = root;
		q.push(current); 
		bool found = false;

		while (!q.empty() && found == false) {
			int size = q.size(); 
			while (size > 0 ) {
				current = q.front(); 
				q.pop(); 

				bool esPadre = false; 
				if (current->left && current->left->v == x)
					esPadre = true; 
				if (current->right && current->right->v == x)
					esPadre = true;

				if (esPadre) {
					found = true;
				}
				else {
					if (current->left) q.push(current->left);
					if (current->right) q.push(current->right);
				}
				size--; 
			}
		}
		
		if (found) {
			while (q.empty() == false) {
				cout << q.front()->v << " ";
				q.pop(); 
			}
		}

	}
};
int main() {
	BinaryTree t;

	/*
	   Vamos a construir el siguiente Árbol Binario de Búsqueda (BST):

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

	cout << "--- PRUEBA DE NODOS PRIMOS ---" << endl;

	// Caso 1: Primos de un nodo hoja (20). 
	// Su padre es 30. Los nodos en su nivel con distinto padre son 60 y 80.
	t.printCousins(20); // Esperado: 60 80

	// Caso 2: Primos de otro nodo hoja (60).
	// Su padre es 70. Los nodos en su nivel con distinto padre son 20 y 40.
	t.printCousins(60); // Esperado: 20 40

	// Caso 3: Primos de un nodo en el nivel 1 (30).
	// Solo tiene a su hermano (70), no tiene primos.
	t.printCousins(30); // Esperado: El nodo no tiene primos.

	// Caso 4: Primos de la raíz (50).
	// La raíz nunca tiene primos.
	t.printCousins(50); // Esperado: El nodo no tiene primos.

	// Caso 5: Nodo que no existe en el árbol (100).
	t.printCousins(100); // Esperado: El nodo 100 no existe en el arbol.

	cout << "\nTerminando programa..." << endl;
	return 0;
}