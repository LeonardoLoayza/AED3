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
		root = 0;
		lado_reemp = 0;
	}
	~AVLTree() {
		cout << "Comienza liberacion" << endl;
		this->clear(root);
		root = 0;
		cout << "Termina liberacion" << endl;
	}

	AVLNode* rebalance(AVLNode* p) {
		updateHeight(p);
		int bf = getBalanceFactor(p);

		if (bf > 1) {
			if (getBalanceFactor(p->left)< 0)
				p->left = rotateLeft(p->left);
			return rotateRight(p);
		}
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
				return false;
			if ((*p)->v < x) {
				p = &((*p)->right);
			}
			else {
				p = &((*p)->left);
			}
		}
		*p = new AVLNode(x);

		while (s.empty() == false) {
			AVLNode** a = s.top();
			s.pop();
			*a = rebalance(*a);
		}

		return true;
	}

	bool remv(int x) {
	    stack<AVLNode**> path; 
	    AVLNode**p=&root; 
	    
	    while (*p && (*p)->v!=x) {
	        path.push(p); 
	        if ( (*p)->v > x){
	            //p=&((*p)->right); 
	        } else {
	            //p=&((*p)->left); 
	        }
	    }
	    
	    // wasnt found, quit 
	    if (*p == nullptr) return; 
	    
	    // 2 children 
	    if ((*p)->left && (*p)->right){
	        // find reemp 
	        // aowfjiw newf
	    }
	    
	    
	    return false; 
	    
	}

	// AVLNode** fnd_reemp(AVLNode** p, stack<AVLNode**>& path) {}

	bool find(int x, AVLNode**& p) {
        return false; 
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
	    return 1; 
	}

	void clear(AVLNode* p) {
	}

	AVLNode* get_root() { return root; }
};
int main() {
	AVLTree t; 
}
