#include <iostream>
using namespace std;

class CDeque {
public:
	int** m;
	int chunksize, tammap;
	int startchunk, endchunk; 
	int startoffset, endoffset;
	int nelem = 0;

	CDeque(int _tammap, int _chunksize) {
		tammap = _tammap;
		chunksize = _chunksize;

		m = new int* [tammap];
		startchunk = tammap / 2;
		endchunk = tammap / 2;

		startoffset = chunksize / 2;
		endoffset = chunksize / 2;
		nelem = 0;
	}

	~CDeque() {
		if (nelem <= 0) return;
		for (int i = startchunk;i < endchunk;i++) {
			delete[] m[i];
		}
		delete[] m;
	}

	void pushback(int x) { // n=0, edgecase, normal case ,expand
		//if (nelem==0) { // nelem=0
		if(nelem==0){
			startoffset = chunksize / 2;
			endoffset = chunksize / 2;
			m[startchunk] = new int[chunksize];
			m[startchunk][startoffset] = x;
			nelem++;
			return; 
		}
		else if (endoffset ==chunksize-1) {
			endchunk++;
			m[endchunk]=new int[chunksize];
			endoffset=0;
			m[endchunk][endoffset]=x;
			nelem++;
			return; 
		}
		endoffset++;
		m[endchunk][endoffset] = x;
		nelem++;
		return;
	}

	void pushfront(int x) { // 0, normal, edge, expand
		if (nelem == 0) {
			startoffset = chunksize / 2;
			endoffset = chunksize / 2;
			m[startchunk] = new int[chunksize];
			m[startchunk][startoffset] = x;
			nelem++;
			return; 
		}
		else if (startoffset==0){
			startchunk--;
			startoffset = chunksize-1;
			m[startchunk] = new int[chunksize];
			m[startchunk][startoffset] = x;
			nelem++;
			return; 
		}
		startoffset--;
		m[startchunk][startoffset] = x;
		nelem++;
	}

	void popfront() {
		if (nelem == 0)return;
		else if (nelem == 1) {
			delete[] m[startchunk];
			nelem--;
			return;
		}	
		else if (startoffset==chunksize-1){
			delete[] m[startchunk];
			startchunk++; 
			startoffset = 0;
			nelem--;
			return;
		}
		startoffset++;
		nelem--;
		return;
	}

	void popback() { // 0, 1, normal, edge
		if (nelem == 0) return; 
		else if (nelem == 1) {
			delete[] m[startchunk];
			nelem--;
			return;
		}
		else if (endoffset==0) {
			delete[] m[endchunk];
			endchunk--;
			endoffset = chunksize-1;
			nelem--;
			return; 
		}
		endoffset--;
		nelem--;
		return;
	}

	void expand();
	int& operator[](int i);
};

void CDeque::expand() {
	int newtammap = tammap * 2;
	int** nm = new int* [newtammap];

		

}

int& CDeque::operator[](int i) {

}


int main(int argc, char* argv[]) {
	CDeque d(5, 5);
	d.pushback(2);
	d.popback();
	/*d.pushback(3);*/
	/*d.pushfront(2);
	d.pushfront(4);
	d.pushfront(3);
	d.pushfront(8);*/
}

