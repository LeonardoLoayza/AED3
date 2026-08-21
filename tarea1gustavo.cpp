#include <iostream>
#include <vector>
using namespace std;

// las busqueda hacer sin recursividad, usar binary search 
template <class T>
class Asc{
public:
	bool operator()(T a, T b){
		return a < b;
	}
};

template <class T, class O, int N=10>
class ListOrd{
public: 
	int tam = N; // 10 
	int elem = 0; 
	// T arr[N];
	int arr[N];
	
	int * start = arr;
	int * end = arr; 
	
	O comparar; 
	// int binarySearch(
	
	bool full(){
		if (tam + (elem -1) ) {
			return true; 
		}
		else {
			return false; 
		}
	}
	bool empty(){
		return elem == 0 ; 
	}
	
	bool add(T e){
		if (empty()){
			*start = e;
			elem++;
			end++;
			
			return true;
		}
		
		if (full()){
			return false;
		}
		
		int * a = arr; 
		int * b = arr+1; 
		
		while (a != b ){
			
		}
		
		
		
		// binary search ?
		
		
		return true; 		
	};
	
	bool del(T e){
		return true; 
	}
	
	void llenararr(){
		for (int i = 0; i < 10; i++){
			arr[i] = i; 
		}
	}

	void print(){
		llenararr(); 
		start = arr; 
		while (start != arr+elem){
			cout << *start << " "; 
			start++;
		}
		cout << endl; 
		
	}; 
};

int main(){
	ListOrd<int, Asc<int> > l;
	l.print(); 
	// l.add(2); 
	
}
