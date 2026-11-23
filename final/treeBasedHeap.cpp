#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <stdexcept>

using namespace std;

class Node {
public:
	
};

class TreeHeapWithDeque {
private:

	
	void heapifyUp(Node* node) {
		
	}
	
	void heapifyDown(Node* node) {
		
		}
	}
	
	void clearTree(Node* n) {
		
	}
	
public:
		TreeHeapWithDeque() : root(nullptr) {}
		
		~TreeHeapWithDeque() {
			
		}
		
		// TOOOP 
		int top() const {
			if (!root) throw runtime_error("Heap vacio");
			return root->v;
		}
		
		// PUSHHHHHHHH
		void push(int x) {
			
		}
		
		// POOOOOOOP 
		void pop() {
			
		}
		
		// SIIIIIIIZE
		int size() const {
			
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
