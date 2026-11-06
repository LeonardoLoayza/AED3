#include <iostream>
#include <queue>
#include <stack> 
#include <string>
using namespace std;

template <class T>
struct CNode {
	T s; 
	CNode<T>* next;
	CNode(T s) {
		this->s = s; 
		next = nullptr; 
	}
};
template <class T>
class Clist {
public:
	CNode<T> * head;
	int n; 
	Clist(int n) {
		head = nullptr; 
		this->n = n; 
	}
	void construir() {
		char c=65;
		int con = 0;
		head = new CNode<T>(c);
		c++; 
		CNode<T>* curr = head;
		while (con < 4) {
			curr->next= new CNode<T>(c); 
			curr = curr->next;
			con++;
			c++;
		}

	}
	void print(){
		CNode<T>* a = head;
		while (a) {
			cout << a->s << "->"; 
			a = a->next; 
		}
	}
	void kill(int salto) {
		Node** p = &head;
		if (n == 0) return;
		while (*p) {
			if (n == 0) return; 

		}
	}
};

int main() {
	Clist<char> mio(6);
	mio.construir(); 
	mio.print(); 
	// el problema es cuando tocamos el head 
	
}
