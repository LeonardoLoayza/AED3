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



		}

	}

};


int main() {
}
