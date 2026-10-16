#include <iostream>
#include <queue>

class CSortedQueue
{
public:
    void pushx(int x);
    void popx();
    int frontx();
    void remx(int x);
    void printx();
    std::queue<int> q;
};
// Soluciones aqui!
//
void CSortedQueue::pushx(int x)
{
    bool insertado = false; 
    int size = q.size(); 
    for (int i = 0;i <size;i++) {
        int current = q.front(); 
        if (insertado==false&&current>x) {
            q.push(x); 
            insertado = true; 
        }
        q.pop();
        q.push(current); 
    }
    if (insertado == false)
        q.push(x); 
}


void CSortedQueue::popx()
{
    if (q.size() > 0) {
        q.pop(); 
    }
}

int CSortedQueue::frontx()
{
    if (q.size()>0)
        return q.front(); 
    return -1; // assert 
}

void CSortedQueue::remx(int x)
{
    int nelem = q.size(); 
    for (int i = 0;i < nelem;i++) {
        int current = q.front();
        
        if (x == current) {
            q.pop(); 
        }
        else {
            q.pop(); 
            q.push(current);
        }
    }
}

void CSortedQueue::printx()
{
    int nelem = q.size(); 
    for (int i = 0; i < nelem;i++) {
        int c = q.front();
        std::cout << c << " ";
        q.push(c);
        q.pop(); 
    }
    std::cout << std::endl;
}

int main()
{
    CSortedQueue sq;
    sq.pushx(40); sq.printx();
    sq.pushx(23);  
    sq.printx();
    sq.pushx(51); 
    sq.printx();
    sq.pushx(12); 
    sq.printx();
    sq.pushx(30); 
    sq.printx();
    sq.pushx(5); 
    sq.printx();
    sq.pushx(40);
    sq.printx();
    sq.pushx(18);
    sq.printx();

    sq.remx(40);  sq.printx();
    sq.remx(23);  sq.printx();
    sq.remx(12);  sq.printx();
    sq.remx(5);  sq.printx();

    std::cout << "\nfront => " << sq.frontx(); sq.popx();
    std::cout << "\nfront => " << sq.frontx(); sq.popx();
    sq.printx();
}