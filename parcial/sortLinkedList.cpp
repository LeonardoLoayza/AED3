#include <iostream>
#include <vector>
using namespace std;

template<class T>
class Node {
public:
    T val;
    Node<T>* next;

    Node(T v, Node<T>* nxt = nullptr) {
        val = v;
        next = nxt;
    }

};

template<class T>
class LinkedList {

public:
    Node<T>* head = nullptr;

    LinkedList() {}

    void push_front(T val) {

        Node<T>* newNode = new Node<T>(val, head);
        head = newNode;

    }

    void print() {

        cout << "Head -> ";
        for (Node<T>* p = head; p != nullptr; p = p->next) {
            cout << p->val << " -> ";
        }
        cout << "NULL" << endl;

    }


    void sort() {
        // CODEA AQUI :)
        Node<T>* curr = head;
        Node<T>* newhead = nullptr; 
        
        while (curr != nullptr) {
            Node<T>* nextnode = curr->next; 
            Node<T>** p = &newhead; 

            while (*p && (*p)->val < curr->val) {
                p = &((*p)->next);
            }

            curr->next = *p; 
            *p = curr; 
            curr = nextnode; 
        }
        head = newhead; 
    }

};

int main() {

    // TEST 1 ------------------------------

    vector<int> nums1 = { 5, 2, 8, 3, 1, 9, 4, 7, 6, 0 };
    LinkedList<int> list1;

    for (int i = 0; i < nums1.size(); ++i) list1.push_front(nums1[i]);

    cout << "\nOrigin Linked List 1:" << endl;
    list1.print();

    list1.sort();

    cout << "\nSorted Linked List 1:" << endl;
    list1.print();




    // TEST 2 ------------------------------

    vector<float> nums2 = { 12.5, 0.8, 15.6, -3.4, 0.0, -12.5, 1.0, 4.7, 6.9, 8.8 };
    LinkedList<float> list2;

    for (int i = 0; i < nums2.size(); ++i) list2.push_front(nums2[i]);

    cout << "\n\nOrigin Linked List 2:" << endl;
    list2.print();

    list2.sort();

    cout << "\nSorted Linked List 2:" << endl;
    list2.print();


    // TEST 3 ------------------------------

    vector<int> nums3 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    LinkedList<int> list3;

    for (int i = 0; i < nums3.size(); ++i) list3.push_front(nums3[i]);

    cout << "\n\nOrigin Linked List 3:" << endl;
    list3.print();

    list3.sort();

    cout << "\nSorted Linked List 3:" << endl;
    list3.print();


    // TEST 4 ------------------------------

    vector<int> nums4 = { 0 };
    LinkedList<int> list4;

    for (int i = 0; i < nums4.size(); ++i) list4.push_front(nums4[i]);

    cout << "\n\nOrigin Linked List 4:" << endl;
    list4.print();

    list4.sort();

    cout << "\nSorted Linked List 4:" << endl;
    list4.print();


    // TEST 5 ------------------------------

    vector<int> nums5;
    LinkedList<int> list5;

    for (int i = 0; i < nums5.size(); ++i) list5.push_front(nums5[i]);

    cout << "\n\nOrigin Linked List 5:" << endl;
    list5.print();

    list5.sort();

    cout << "\nSorted Linked List 5:" << endl;
    list5.print();

    return 0;
}

