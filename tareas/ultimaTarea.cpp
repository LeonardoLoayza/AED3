#include <iostream>
#include <string>

using namespace std;
template <class T> 
struct Node {
	T data;
	Node<T>* next;

	Node(T _data) {
		data = _data;
		next = nullptr;
	}
};

template<class T> 
class Clist {
public:
	int nelem; 
	Node<T>* head;
	Node<T>* tail; 
	Clist(int _nelem) {
		nelem = _nelem;
		int as = 65;
		
		head = new Node<T>(as++);
		tail = head;
		Node<T>* i = head;

		for (int c=1;c <= nelem;c++) {
			i->next = new Node<T>(as++);
			i = i->next;
			tail = i;
		}
		tail->next = head; 


	}
	void print() {
		Node<T>* i = head;
		int c = 0;
		for (;c < nelem;i = i->next, c++)
			cout << i->data << "->";
	}
	void kill(int N) {
		Node<T>** p = &head;
		while (*p && nelem>0) {
			if (nelem == 1) {
				cout << "eliminado: " << (*p)->data << endl;
				Node<T>* d = *p;
				head = nullptr; tail = nullptr;
				nelem--;
				delete d;
				return; 
			}
			int c = 1;
			while (c < N) {
				p = &((*p)->next); 
				c++;
			}
			Node<T>* d = *p; 
			cout << "eliminado: " << (*p)->data << endl;
			*p = d->next;
			delete d;
			nelem--;
		}
	}
};

int main() {
	Clist<char> c(6); 
	c.print(); 
	c.kill(3);

}