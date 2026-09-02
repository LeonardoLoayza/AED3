#include <iostream>
using namespace std;
class CDeque{
public:
	int ** m; 
	int ** blqini; 
	int ** blqfin; 
	int * inival; 
	int * finval; 
	int nelem; 
	int tammap; 
	int tamblq; 
	CDeque(int a, int b){
		tammap = a; 
		tamblq = b;
		m = new int*[tammap];
		blqini = m + (tammap/2);
		blqfin = blqini; 
		inival=nullptr; 
		finval = nullptr; 
		nelem = 0; 
	}
		
	void pushback(int x){
		if (nelem == 0){
			*blqini = new int[tamblq];
			*blqfin = *blqini; 
			inival = *blqini + (tamblq/2);
			
			inival++;
			*inival = x; 
			nelem++; 
			return; 
		}
		
		if (finval = *blqfin + tamblq - 1){
			blqfin++; 
			*blqfin = new int[tamblq]; 
			finval = *blqfin; 
			
			*finval = x; 
			nelem++; 
			return; 
		}
		
		// normal 
		finval++; 
		*finval = x; 
		nelem++; 
		return; 
		
	}
		
	void expand(){
		int newmap = new int*[tammap*2];
		
		
		
	}
		
	
		
		
};
int main(int argc, char *argv[]) {
	CDeque c(3,3); 
	c.pushback(3); 
}

