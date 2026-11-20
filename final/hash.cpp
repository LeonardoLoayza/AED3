#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std; 

struct Node {
	string key;
	string value;
	Node* next;
	
	Node(string key, string value) {
		this->key = key; 
		this->value = value; 
		next = nullptr; 
	}


};

class CHash{
public: 
	static const int CAPACITY = 1000; 
	Node* buckets[CAPACITY]{};
	int nelem = 0; 
	int hashFunction(const string& key) {
		unsigned long hash = 0; 

		for (char c : key) 
			hash = (hash * 31 + static_cast<unsigned char>(c)) % CAPACITY;

		return hash; 
	}

	void insert(const string&key, const string&value) {
		int index = hashFunction(value); 

		Node* current = buckets[index]; 
		
		// posiciona el current
		while (current != nullptr) {
			// cambia valor y zafa
			if (current->key == key) {
				current->value = value;
				return;
			}
			current=current->next; 
		}
		
		
        Node* nuevo=new Node(key,value); 
        nuevo->next=buckets[index];
        buckets[index]=nuevo; 
    
        nelem++; 
		
        return;
	}
	
	string* search(const string& key) {
	    int index=hashFunction(key);
	    
	    Node * c = buckets[index]; 
	    
	    while(c!=nullptr){
	        if(c->key==key){
	            return &c->value; 
	        }
	        c=c->next; 
	    }
	    
	    return nullptr;
	}

};

int main() {
    CHash tabla;

    tabla.insert("A101", "Pedro");
    tabla.insert("B202", "Ana");

    // Prueba 1: Clave existente
    string* resultado1 = tabla.search("A101");
    if (resultado1 != nullptr) {
        cout << "Encontrado: " << *resultado1 << endl; // Imprime: Pedro
    } else {
        cout << "No encontrado" << endl;
    }

    // Prueba 2: Clave inexistente
    string* resultado2 = tabla.search("Z999");
    if (resultado2 != nullptr) {
        cout << "Encontrado: " << *resultado2 << endl;
    } else {
        cout << "No encontrado" << endl; // Imprime: No encontrado
    }

    // Prueba 3: Modificar valor a traves del puntero retornado
    if (resultado1 != nullptr) {
        *resultado1 = "Pedro Pablo"; // Modifica directamente el valor en la tabla
    }
    
    cout << "Nuevo valor de A101: " << *tabla.search("A101") << endl; // Imprime: Pedro Pablo

    return 0;
}
