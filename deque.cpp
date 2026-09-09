#include <iostream>
using namespace std;

class CDeque{
public:
	int ** m; 
	int ** iniblq; 
	int ** finblq; 
	int * inival; 
	int * finval; 
	int nelem; 
	int tammap; 
	int tamblq; 

	CDeque(int a, int b){
		tammap = a; 
		tamblq = b;
		m = new int*[tammap];
		iniblq = m + (tammap/2);
		finblq = iniblq; 
		inival=nullptr; 
		finval = nullptr; 
		nelem = 0; 
	}
		
	void pushback(int x){
		if (nelem == 0){
			*iniblq = new int[tamblq];
			*finblq = *iniblq; 
			inival = *iniblq + (tamblq/2);
			
			inival++;
			*inival = x; 
			nelem++; 
			return; 
		}
		
		if (finval = *finblq + tamblq - 1){
			finblq++; 
			*finblq = new int[tamblq]; 
			finval = *finblq; 
			
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

	void pushfront(int x){ // vacio, normal, lleno offset, expand
		if (nelem == 0){
			*iniblq=new int[tamblq];
			inival=*iniblq;
			finval=inival;
			*inival=x;
			nelem++; 
			return;
		}

		else if (inival==*iniblq+(tamblq-1)){
			iniblq++;
			*iniblq=new int[tamblq];
			inival=*iniblq;
			*inival=x;
			nelem++; 
			return;
		}

		inival--;
		*inival=x;
		nelem++;
	}

	void popfront(){//0 elem,  1 elem, normal, cambio 
		if(nelem==0)return;
		else if(nelem==1){
			delete *iniblq;
			*iniblq=nullptr;
			inival=nullptr;
			finval=nullptr;
			nelem--;
			return;
		}

		// cambio
		if (inival==*iniblq+(tamblq-1)){
			delete[] *iniblq;
			*iniblq=nullptr;

			iniblq++;
			inival=*iniblq;
			nelem--;
			return;
		}
		
		inival++;
		nelem--;
	}
		
	void popback(){ // 0, 1, change block, normal
		if(nelem==0)return; 
		else if(nelem==1){
			delete[] *iniblq;
			*iniblq=nullptr;
			inival=nullptr;
			finval=nullptr;
			nelem--;
			return; 
		}

		if (finval==*finblq){
			delete[] *finblq;
			*finblq=nullptr;
			finblq--;
			finval=*finblq+(tamblq-1);
			nelem--;
			return;
		}

		finval--;
		nelem--;
	}

	void expand(){
		// int newmap = new int*[tammap*2];
		
		
		
	}
		
	
		
		
};
int main(int argc, char *argv[]) {
	CDeque c(3,3); 
	c.pushback(3); 
}

