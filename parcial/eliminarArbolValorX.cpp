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
	bool removeSubtree(int x){
	    Node**p=nullptr; 
	    if(!find(x,p)) 
	        return false; 
	    
	    Node*c=*p; 
	    queue<Node*> q;
	    q.push(c);
	    while(!q.empty()){
	        c=q.front(); 
	        if(c->left) q.push(c->left); 
	        if(c->right) q.push(c->right); 
	        q.pop();
	        delete c; 
	        c=nullptr;
	        
	       
	    }
	    *p=nullptr; 
	    return true; 
	    
	}
};

int main() {

    // ============================================================
    // TEST 1: Eliminar un subárbol interno
    // ============================================================
    cout << "\n========== TEST 1 ==========\n";

    {
        BinaryTree t;

        /*
                  10
                 /  \
                5    15
               / \
              2   7
                 / \
                6   8
        */

        t.insrt(10);
        t.insrt(5);
        t.insrt(15);
        t.insrt(2);
        t.insrt(7);
        t.insrt(6);
        t.insrt(8);

        cout << "Antes: ";
        t.inorder(t.get_root());
        cout << endl;

        bool r = t.removeSubtree(5);

        cout << "Se elimino: " << r << endl;

        cout << "Despues: ";
        t.inorder(t.get_root());
        cout << endl;

        // Esperado:
        // 10 15
    }


    // ============================================================
    // TEST 2: Eliminar una hoja
    // ============================================================
    cout << "\n========== TEST 2 ==========\n";

    {
        BinaryTree t;

        /*
                  10
                 /  \
                5    15
               / \
              2   7
                 / \
                6   8
        */

        t.insrt(10);
        t.insrt(5);
        t.insrt(15);
        t.insrt(2);
        t.insrt(7);
        t.insrt(6);
        t.insrt(8);

        cout << "Antes: ";
        t.inorder(t.get_root());
        cout << endl;

        bool r = t.removeSubtree(6);

        cout << "Se elimino: " << r << endl;

        cout << "Despues: ";
        t.inorder(t.get_root());
        cout << endl;

        // Esperado:
        // 2 5 7 8 10 15
    }


    // ============================================================
    // TEST 3: Eliminar hijo derecho completo
    // ============================================================
    cout << "\n========== TEST 3 ==========\n";

    {
        BinaryTree t;

        /*
                  10
                 /  \
                5    15
                    /  \
                   12   20
        */

        t.insrt(10);
        t.insrt(5);
        t.insrt(15);
        t.insrt(12);
        t.insrt(20);

        cout << "Antes: ";
        t.inorder(t.get_root());
        cout << endl;

        bool r = t.removeSubtree(15);

        cout << "Se elimino: " << r << endl;

        cout << "Despues: ";
        t.inorder(t.get_root());
        cout << endl;

        // Esperado:
        // 5 10
    }


    // ============================================================
    // TEST 4: Eliminar la RAIZ
    // ============================================================
    cout << "\n========== TEST 4 ==========\n";

    {
        BinaryTree t;

        /*
                  10
                 /  \
                5    15
               / \   / \
              2   7 12 20
        */

        t.insrt(10);
        t.insrt(5);
        t.insrt(15);
        t.insrt(2);
        t.insrt(7);
        t.insrt(12);
        t.insrt(20);

        cout << "Antes: ";
        t.inorder(t.get_root());
        cout << endl;

        bool r = t.removeSubtree(10);

        cout << "Se elimino: " << r << endl;

        cout << "Despues: ";
        t.inorder(t.get_root());
        cout << endl;

        // Esperado:
        // árbol vacío
    }


    // ============================================================
    // TEST 5: El valor NO existe
    // ============================================================
    cout << "\n========== TEST 5 ==========\n";

    {
        BinaryTree t;

        t.insrt(10);
        t.insrt(5);
        t.insrt(15);
        t.insrt(2);
        t.insrt(7);

        cout << "Antes: ";
        t.inorder(t.get_root());
        cout << endl;

        bool r = t.removeSubtree(100);

        cout << "Se elimino: " << r << endl;

        cout << "Despues: ";
        t.inorder(t.get_root());
        cout << endl;

        // Esperado:
        // r = false
        // 2 5 7 10 15
    }


    // ============================================================
    // TEST 6: Árbol con un solo nodo
    // ============================================================
    cout << "\n========== TEST 6 ==========\n";

    {
        BinaryTree t;

        t.insrt(10);

        cout << "Antes: ";
        t.inorder(t.get_root());
        cout << endl;

        bool r = t.removeSubtree(10);

        cout << "Se elimino: " << r << endl;

        cout << "Despues: ";
        t.inorder(t.get_root());
        cout << endl;

        // Esperado:
        // árbol vacío
    }


    // ============================================================
    // TEST 7: Subárbol grande
    // ============================================================
    cout << "\n========== TEST 7 ==========\n";

    {
        BinaryTree t;

        /*
                        50
                      /    \
                    30      80
                   /  \    /  \
                  20   40 70   90
                 / \      / \
                10 25    60 75
        */

        t.insrt(50);
        t.insrt(30);
        t.insrt(80);
        t.insrt(20);
        t.insrt(40);
        t.insrt(70);
        t.insrt(90);
        t.insrt(10);
        t.insrt(25);
        t.insrt(60);
        t.insrt(75);

        cout << "Antes: ";
        t.inorder(t.get_root());
        cout << endl;

        bool r = t.removeSubtree(30);

        cout << "Se elimino: " << r << endl;

        cout << "Despues: ";
        t.inorder(t.get_root());
        cout << endl;

        // Esperado:
        // 50 60 70 75 80 90
    }


    return 0;
}

