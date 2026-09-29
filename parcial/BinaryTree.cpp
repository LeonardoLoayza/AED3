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
	void inorder(Node* p);
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
	Node** p = nullptr;

	cout << "--- TEST 1: Insercion (insrt) y Busqueda (find) ---" << endl;
	cout << "Insertar 5: " << t.insrt(5) << " (Esperado: 1 - true)" << endl;
	cout << "Insertar 3: " << t.insrt(3) << " (Esperado: 1 - true)" << endl;
	cout << "Insertar 8: " << t.insrt(8) << " (Esperado: 1 - true)" << endl;

	// Caso de prueba: Insertar un duplicado
	cout << "Insertar 5 (duplicado): " << t.insrt(5) << " (Esperado: 0 - false)" << endl;

	// Caso de prueba: Buscar un elemento que existe y uno que no
	cout << "Buscar 8: " << t.find(8, p) << " (Esperado: 1 - true)" << endl;
	cout << "Buscar 10: " << t.find(10, p) << " (Esperado: 0 - false)" << endl;
	cout << endl;

	cout << "--- TEST 2: Eliminacion (remv) - Caso 0 hijos (Nodos Hoja) ---" << endl;
	t.insrt(10); // 8 -> derecho -> 10
	// 10 no tiene hijos.
	cout << "Remover 10 (0 hijos): " << t.remv(10) << " (Esperado: 1 - true)" << endl;
	cout << "Buscar 10 despues de remover: " << t.find(10, p) << " (Esperado: 0 - false)" << endl;
	cout << endl;

	cout << "--- TEST 3: Eliminacion (remv) - Caso 1 hijo ---" << endl;
	// Estructura actual: 5 (root), 3 (izq), 8 (der). 
	t.insrt(9); // Hacemos que 8 tenga un hijo derecho (9)
	cout << "Remover 8 (1 hijo, el 9): " << t.remv(8) << " (Esperado: 1 - true)" << endl;
	// El 9 debió subir a la posicion del 8
	cout << "Buscar 9 despues de remover 8: " << t.find(9, p) << " (Esperado: 1 - true)" << endl;
	cout << endl;

	cout << "--- TEST 4: Eliminacion (remv) - Caso 2 hijos ---" << endl;
	// Estructura actual: root es 5. Hijos: 3 (izq), 9 (der).
	t.insrt(2); // hijo izq de 3
	t.insrt(4); // hijo der de 3
	// Ahora 3 tiene dos hijos (2 y 4).
	cout << "Remover 3 (2 hijos, el 2 y 4): " << t.remv(3) << " (Esperado: 1 - true)" << endl;
	// Dependiendo de tu 'lado_reemp' (0 = izquierda), el reemplazo debería ser el mayor de los menores (2).
	cout << endl;

	cout << "--- TEST 5: Eliminacion de un nodo que no existe ---" << endl;
	cout << "Remover 99: " << t.remv(99) << " (Esperado: 0 - false)" << endl;

	return 0;
}