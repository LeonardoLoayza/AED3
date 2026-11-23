#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <stdexcept>

using namespace std;

class Node {
public:
	int v; 
	Node*left; 
	Node*right; 
	Node*parent; 
	Node(int v, Node*parent=nullptr){
		this->v=v; 
		left=nullptr; 
		right=nullptr; 
		parent=nullptr; 
	}
};

class TreeHeapWithDeque {
private:

	
	void heapifyUp(Node* n) {
		while(n->parent!=nullptr && n->v > n->parent->v){
			swap(n->v, n->parent->v);
		}
	}
	
	void heapifyDown(Node* n) {
		while(n!=nullptr){
			Node*maxNode=n; 
			
			if(n->left != nullptr && n->left->v > maxNode->v)
				maxNode=n->left; 
			if(n->right != nullptr && n->right->v > maxNode->v) 
				maxNode=n->right; 
			
			if(maxNode==n) // el nodo esta bien posicionado,zafo
				break; 
				
			swap(n->v, maxNode->v); // aplico cambiazo 
			n=maxNode; 
		}
		
		return;
	}
	
	void clearTree(Node* n) {
		if(!n)return;
		clearTree(n->left);
		clearTree(n->right);
		delete n; 
	}
	
public:
		Node*root; 
		deque<Node*>open_nodes;
		deque<Node*>all_nodes; 
		
		TreeHeapWithDeque(){
			root=nullptr; 
		}
		
		~TreeHeapWithDeque() {
			clearTree(root); 
		}
		
		// TOOOP 
		int top() const {
			if (!root) throw runtime_error("Heap vacio");
			return root->v;
		}
		
		// PUSHHHHHHHH
		void push(int x) {
			// caso vacio
			if (!root){
				root=new Node(x);
				open_nodes.push_back(root);
				all_nodes.push_back(root);
				return;
			}
			
			Node*padre=open_nodes.front();
			Node*nuevo=new Node(x,padre);
			
			if(padre->left == nullptr){
				padre->left=nuevo;
			} 
			else {
				padre->right=nuevo;
				open_nodes.pop_front(); // ya no me sirve, porque esta lleno 
			}
			
			all_nodes.push_back(nuevo);
			open_nodes.push_back(nuevo); 
			
			heapifyUp(nuevo); 
			return; 
		}
		
		// POOOOOOOP 
		void pop() {
			// casovacio, caso 1 elem , caso normal 
			if(!root)
				return; 
			if(all_nodes.size()==1){
				delete root; 
				root=nullptr; 
				all_nodes.clear(); 
				open_nodes.clear(); 
				return; 
			}
			
			// caso normal
			// obten ultimo nodo 
			Node*ultimo=all_nodes.back(); 
			all_nodes.pop_back(); 
			
			if(open_nodes.back() == ultimo)
				open_nodes.pop_back();
			
			root->v=ultimo->v; 
			
			// desconectar ultimo nodo 
			Node*padreUltimo=ultimo->parent; 
			
			// revisa si es left o right child 
			if(padreUltimo->left == ultimo ){
				padreUltimo->left=nullptr; 
			} else {
				padreUltimo->right=nullptr; 
				open_nodes.push_front(padreUltimo); 
			}
			
			delete ultimo; 
			
			
			heapifyDown(root); 
		}
		
		// SIIIIIIIZE
		int size() const {
			return all_nodes.size(); 
		}
};

int main() {
	TreeHeapWithDeque h;
	vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5};
	for (int x : nums)
		h.push(x);
	
	cout << "Extrayendo elementos en orden descendente:" << endl;
	while (h.size() > 0) {
		cout << h.top() << " ";
		h.pop();
	}
	cout << endl;
	return 0;
}
