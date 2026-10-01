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
			cout<<"borrando nodo:"<<c->v<<endl;
			delete c; 
			c = nullptr; 
		}
		root = nullptr;
		cout << "desutrctor god" << endl;
	}
	
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

	void inorderST() {
		Node* c = root;
		stack<Node*>s;
		s.push(c);
		while(c || !s.empty()) {
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
};
int main() {
	cout << "--- TEST 1: Arbol con nodos ---" << endl;
	{
		BinaryTree t;
		/*
			   10
			  /  \
			 5    15
			/ \
		   2   7
		*/
		t.insrt(10);
		t.insrt(5);
		t.insrt(15);
		t.insrt(2);
		t.insrt(7);

		cout << "Saliendo del bloque 1..." << endl;
	} // Aqui se llama al destructor automaticamente


	cout << "\n--- TEST 2: Arbol vacio ---" << endl;
	{
		BinaryTree t2;
		// No insertamos nada
		cout << "Saliendo del bloque 2..." << endl;
	} // Aqui se llama al destructor automaticamente

	return 0;
}