#include <iostream>
#include <assert.h>

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
}

void CDeque::push_front(int x)
{
}

void CDeque::pop_front()
{
}

void CDeque::push_back(int x)
{
}

void CDeque::pop_back()
{
}

int& CDeque::operator[](int i)
{
}

int& CDeque::front()
{
}

int& CDeque::back()
{
}

void CDeque::print()
{
}

int main()
{
    CDeque v(5, 7);
    v.push_back(3);
    v.push_back(7);
    v.push_back(6);
    v.push_front(1);
    v.push_front(9);
    v.push_front(2);
    v.print();

    v[3] = 4;
    v.print();

    v.front() = 1;
    v.back() = 1;
    v.print();


    v.pop_back();
    v.pop_front();
    v.print();

    v.pop_back();
    v.pop_front();
    v.print();

    v.pop_back();
    v.pop_front();
    v.print();

    std::cout << "\n";
}