#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

template <class T, long N>
struct CF1 {
	long operator()(T x) {
		return abs((long)x) % N; 
	}
};

template <class T>
class ListAdapter {
	list<T> data;
public:
	void ins(T x) {
		if (!find(x)) {
			data.push_back(x);
		}
	}
	
	void rem(T x) {
		data.remove(x);
	}
	
	bool find(T x) {
		for (const auto& val : data) {
			if (val == x) return true;
		}
		return false;
	}
	
	void print() {
		if (data.empty()) {
			cout << "NULL";
		} else {
			for (const auto& val : data) {
				cout << val << " -> ";
			}
			cout << "NULL";
		}
	}
};

template <class T>
class VectorAdapter {
	vector<T> data;
public:
	void ins(T x) {
		if (!find(x)) {
			data.push_back(x);
		}
	}
	
	void rem(T x) {
		for (size_t i = 0; i < data.size(); ++i) {
			if (data[i] == x) {
				data[i] = data.back();
				data.pop_back();
				return;
			}
		}
	}
	
	bool find(T x) {
		for (const auto& val : data) {
			if (val == x) return true;
		}
		return false;
	}
	
	void print() {
		cout << "[ ";
		for (const auto& val : data) cout << val << " ";
		cout << "]";
	}
};

template <class T, class F, class S, long N> 
class CHashTable {
	S m_t[N];
	F m_f;    
	
public:
	void ins(T x) {
		m_t[m_f(x)].ins(x);
	}
	void rem(T x) {
		m_t[m_f(x)].rem(x);
	}
	bool find(T x) {
		return m_t[m_f(x)].find(x);
	}
	
	void print() {
		for (long i = 0; i < N; ++i) {
			cout << "Posición " << i << ": ";
			m_t[i].print();
			cout << endl;
		}
	}
};

// ---------------------------------------------------------
// MAIN (Pruebas)
// ---------------------------------------------------------
int main() {
	const long TAMANO = 7;
	
	// --- CASO 1: Hash Table con Listas Enlazadas ---
	// T = int
	// F = CF1<int, 7>
	// S = ListAdapter<int>
	// N = 7
	cout << "=== PRUEBA 1: Adaptador de Lista (Chaining) ===" << endl;
	CHashTable<int, CF1<int, TAMANO>, ListAdapter<int>, TAMANO> hashList;
	
	hashList.ins(10); // 10 % 7 = 3
	hashList.ins(20); // 20 % 7 = 6
	hashList.ins(3);  // 3 % 7 = 3 (COLISIÓN con 10)
	hashList.ins(17); // 17 % 7 = 3 (COLISIÓN con 10 y 3)
	
	hashList.print();
	
	cout << "\nBuscando 17: " << (hashList.find(17) ? "Encontrado" : "No encontrado") << endl;
	
	cout << "Eliminando 3..." << endl;
	hashList.rem(3);
	hashList.print();
	
	
	// --- CASO 2: Hash Table con Vectores ---
	// Solo cambiamos el parámetro S a VectorAdapter<int>
	cout << "\n\n=== PRUEBA 2: Adaptador de Vector ===" << endl;
	CHashTable<int, CF1<int, TAMANO>, VectorAdapter<int>, TAMANO> hashVector;
	
	hashVector.ins(100);
	hashVector.ins(107); // Colisiona en bucket (107%7 = 2) vs (100%7 = 2)
	hashVector.ins(14);  // Bucket 0
	
	hashVector.print();
	
	return 0;
}
