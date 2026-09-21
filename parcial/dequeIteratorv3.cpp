#include <iostream>
#include <assert.h>
using namespace std;
struct CDeque_iterator
{
    int** chunk;
    int* offset;
};

class CDeque
{
public:
    CDeque(int cs, int ms);
    ~CDeque();
    void expand_map();
    void push_front(int x);
    void pop_front();
    void push_back(int x);
    void pop_back();
    int& operator[](int i);
    int& front();
    int& back();
    void print();

private:
    int** map;
    int chunk_size, map_size;
    int nelem;
    CDeque_iterator start, finish;
};

CDeque::CDeque(int cs, int ms)
{
    chunk_size = cs;
    map_size = ms;
    map = new int* [map_size];

    start.chunk = finish.chunk = map + map_size / 2;
    *start.chunk = new int[chunk_size];

    start.offset = finish.offset = *start.chunk + chunk_size / 2;

    nelem = 0;
}

CDeque::~CDeque()
{
    for (int** c = start.chunk; c <= finish.chunk; ++c)
        delete[] * c;
    delete[] map;
}

void CDeque::expand_map()
{
    int newtam = map_size * 2;
    int** newmap = new int* [newtam];

    int offset = (newtam - map_size)/2;

    for (int i = 0;i < map_size;i++) {
        newmap[i + offset] = map[i];
    }
    start.chunk = newmap + (start.chunk-map)+offset;
    finish.chunk = newmap + (finish.chunk-map)+offset;

    delete[] map;
    map = newmap;
    map_size = newtam;
}

void CDeque::push_front(int x)// 0, normal, expand
{
    if (nelem == chunk_size * map_size) {
        expand_map();
    }
    if (start.offset==*start.chunk) {
        start.chunk--;
        *start.chunk = new int[chunk_size];
        start.offset = *start.chunk+chunk_size-1;
        *start.offset = x;
        nelem++;
        return;
    }
    // normal
    start.offset--;
    *start.offset = x;
    return;
}

void CDeque::pop_front()//0,normal,edge
{
    if (start.offset == finish.offset) return;
    if (start.offset == *start.chunk + chunk_size - 1) {
        delete[] *start.chunk;
        start.chunk++;
        start.offset = *start.chunk;
        nelem--;
        return;
    }
    start.offset++;
    nelem--;
}

void CDeque::push_back(int x) // 0, edge, normal, expand 
{
    if (nelem == chunk_size * map_size) {
        expand_map();
    }
    if (finish.offset==*finish.chunk+chunk_size-1) {
        *finish.offset = x;
        finish.chunk++; 
        *finish.chunk= new int[chunk_size];
        finish.offset=*finish.chunk;
        nelem++;
        return;
    }
    
    // normal
    *finish.offset = x;
    finish.offset++;
    nelem++; 
}

void CDeque::pop_back() // 0, normal, edge
{
    if (start.offset == finish.offset) {// 0 elem
        return;
    }

    if (finish.offset == *finish.chunk) { // edge
        delete[] * finish.chunk;
        finish.chunk--;
        finish.offset = *finish.chunk + chunk_size - 1;
        nelem--;
        return;
    }

    finish.offset--;
    nelem--;
}

int& CDeque::operator[](int i)
{
    int startchunk = start.chunk - map;
    int startoffset = start.offset - *start.chunk;

    int pos = chunk_size * map_size + startchunk + i;
    int chunk = pos / chunk_size;
    int offset = pos % chunk_size;
    return map[chunk][offset];
}

int& CDeque::front()
{
    return *start.offset;
}

int& CDeque::back()
{
    return *finish.offset; 
}

void CDeque::print()
{
    for (int** c = start.chunk;c <= finish.chunk;c++) {
        int* a = *c; 

        if (c == start.chunk) {
            a = start.offset; 
        }
        
        while (a < *c + chunk_size) {
            if (a==finish.offset) {
                break;
            }
            cout << *a << " ";
            a++; 
        }
    }
}

int main()
{
    CDeque v(5, 7);
    v.print();

    v.push_back(3);
    v.push_back(7);
    v.push_back(6);
    v.push_front(1);
    v.push_front(9);
    v.push_front(2);
    v.push_front(4);
    v.print();

    //v[3] = 4;
    //v.print();

    //v.front() = 1;
    //v.back() = 1;
    //v.print();


    //v.pop_back();
    //v.pop_front();
    //v.print();

    //v.pop_back();
    //v.pop_front();
    //v.print();

    //v.pop_back();
    //v.pop_front();
    //v.print();

    std::cout << "\n";
}