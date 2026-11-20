
#include <iostream>
#include <string>
using namespace std;

// Nodo de la lista enlazada
struct Node {
    string key;
    string value;
    Node* next;

    // Constructor
    Node(string key, string value) {
        this->key = key;
        this->value = value;
        next = nullptr;
    }
};

// Tabla hash
struct HashMap {
    static const int CAPACITY = 100;

    Node* buckets[CAPACITY]{};
    int numElements = 0;

    // Funcion hash
    int hashFunction(const string& key) {
        unsigned long hash = 0;

        for (char c : key) {
            hash = (hash * 31 + static_cast<unsigned char>(c))
                   % CAPACITY;
        }

        return hash;
    }

    // Insertar elemento
    void insert(const string& key, const string& value) {
        int index = hashFunction(key);

        // Comprobar si la clave ya existe
        Node* current = buckets[index];

        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }

            current = current->next;
        }

        // Crear nuevo nodo e insertarlo al inicio
        Node* newNode = new Node(key, value);
        newNode->next = buckets[index];
        buckets[index] = newNode;

        numElements++;
    }

    // Buscar elemento
    string* search(const string& key) {
        int index = hashFunction(key);

        Node* current = buckets[index];

        while (current != nullptr) {
            if (current->key == key) {
                return &current->value;
            }

            current = current->next;
        }

        return nullptr;
    }

    // Eliminar elemento
    void deleteKey(const string& key) {
        int index = hashFunction(key);

        Node* current = buckets[index];
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->key == key) {

                // Si es el primer nodo
                if (previous == nullptr) {
                    buckets[index] = current->next;
                }
                // Si está en medio o al final
                else {
                    previous->next = current->next;
                }

                delete current;
                numElements--;
                return;
            }

            previous = current;
            current = current->next;
        }
    }

    // Liberar memoria
    ~HashMap() {
        for (int i = 0; i < CAPACITY; i++) {
            Node* current = buckets[i];

            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
};

// Programa principal
int main() {
    HashMap mp;

    // Insertar elementos
    mp.insert("Yogaholic", "Anjali");
    mp.insert("pluto14", "Vartika");
    mp.insert("elite_Programmer", "Manish");
    mp.insert("GFG", "GeeksforGeeks");
    mp.insert("decentBoy", "Mayank");

    // Buscar elementos
    if (string* result = mp.search("elite_Programmer"))
        cout << *result << endl;

    if (string* result = mp.search("Yogaholic"))
        cout << *result << endl;

    if (string* result = mp.search("pluto14"))
        cout << *result << endl;

    if (string* result = mp.search("decentBoy"))
        cout << *result << endl;

    if (string* result = mp.search("GFG"))
        cout << *result << endl;

    // Buscar una clave inexistente
    if (string* result = mp.search("randomKey"))
        cout << *result << endl;
    else
        cout << "No se encontro el elemento." << endl;

    // Eliminar elemento
    cout << "\nDespues de eliminar:\n";

    mp.deleteKey("decentBoy");

    if (string* result = mp.search("decentBoy"))
        cout << *result << endl;
    else
        cout << "No se encontro el elemento." << endl;

    cout << "\nElementos actuales: " << mp.numElements << endl;

    return 0;
}
