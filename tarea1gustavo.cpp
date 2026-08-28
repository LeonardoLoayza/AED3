#include <iostream>
#include <vector>
using namespace std;

// las busqueda hacer sin recursividad, usar binary search 
template <class T>
class Asc {
public:
	bool operator()(T a, T b) {
		return a < b;
	}
};

template <class T, class O, int N = 10>
class ListOrd {
public:
	int tam = N; // 10 
	int elem = 0;
	int arr[N];

	int* start = arr;
	int* end = arr + elem;

	O comparar;

	bool full() {
		return elem == tam;
	}

	bool empty() {
		return elem == 0;
	}

	bool add(T e) {
		if (empty()) {
			*start = e;
			elem++;
			end++;

			return true;
		}

		if (full()) {
			return false;
		}

		int* p = arr;

		while (p < (arr + elem) && comparar(*p, e) ) {
			p++; 
		}

		int* q = end;
		int* r = end - 1;
		
		while (q != p) {
			*q = *r; 
			r--;
			q--;
		}

		*p = e; 
		elem++;
		end++;

		return true;
	};

	bool del(T e) {
		if (empty()) {
			return false; 
		}

		int* p = arr;

		while (p < end && *p != e) {
			p++; 
		}

		if (p == end) {
			return false; 
		}

		int* q = p + 1; 

		while (q != end) {
			*p = *q; 
			p++; 
			q++;
		}

		elem--; 
		end--; 

		return true; 
	}

	void llenararr() {
		for (int i = 0; i < 10; i++) {
			arr[i] = i;
		}
		elem = 10; 
	}

	void print() {
		
		start = arr;
		int c = 0; 

		while (c < elem) {
			cout << *start << " "; 
			start++;
			c++;
		}

		cout << endl;
	};
};

int main() {
	ListOrd<int, Asc<int>> l;

	cout << "TEST 1: add en lista vacia\n";
	cout << "add(5): " << l.add(5) << endl;
	l.print();
	cout << endl;


	cout << "TEST 2: add menor que todos\n";
	cout << "add(2): " << l.add(2) << endl;
	l.print();
	cout << endl;


	cout << "TEST 3: add mayor que todos\n";
	cout << "add(10): " << l.add(10) << endl;
	l.print();
	cout << endl;


	cout << "TEST 4: add en medio\n";
	cout << "add(7): " << l.add(7) << endl;
	l.print();
	cout << endl;


	cout << "TEST 5: add otro elemento en medio\n";
	cout << "add(6): " << l.add(6) << endl;
	l.print();
	cout << endl;


	cout << "TEST 6: add duplicado\n";
	cout << "add(7): " << l.add(7) << endl;
	l.print();
	cout << endl;


	cout << "TEST 7: eliminar elemento del inicio\n";
	cout << "del(2): " << l.del(2) << endl;
	l.print();
	cout << endl;


	cout << "TEST 8: eliminar elemento del medio\n";
	cout << "del(7): " << l.del(7) << endl;
	l.print();
	cout << endl;


	cout << "TEST 9: eliminar elemento del final\n";
	cout << "del(10): " << l.del(10) << endl;
	l.print();
	cout << endl;


	cout << "TEST 10: eliminar elemento que no existe\n";
	cout << "del(100): " << l.del(100) << endl;
	l.print();
	cout << endl;


	cout << "TEST 11: llenar la lista\n";
	l.add(1);
	l.add(3);
	l.add(4);
	l.add(5);
	l.add(8);
	l.add(9);
	l.add(11);
	l.add(12);
	l.print();
	cout << endl;


	cout << "TEST 12: intentar agregar estando llena\n";
	cout << "add(50): " << l.add(50) << endl;
	l.print();
	cout << endl;
}
