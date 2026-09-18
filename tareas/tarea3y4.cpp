// usar vector , hacer deque ? 
// el vector de entrada puede ser int, 
// el siguiente vector 
// ---------------------------------------

// tarea 2 : Implementar un vector como base para 
// usar una pila o una cola. 
// multiplicar 27 por cualquier numero y dado eso
// tratar de adivinar el ultimo digito. 

#include <iostream>
#include <vector>
#include <cctype>
#include <string> 

using namespace std;

template <class T>
class Asc {
public:
	bool operator()(T a, T b) {
		return a < b;
	}
};

template<class T, int N=100> 
class Pila {
private:
    T arr[N]; 
    int elem=0;
public: 
    bool empty(){return elem==0;}
    bool full(){return elem==N;}

    bool push(T e){
        if(full()) return false;
        arr[elem]=e;
        elem++;
        return true;
    }

    bool pop(){
        if(empty())return false;
        elem--;
        return true;
    }

    T top(){
        if(!empty()){ return arr[elem-1]; }
        throw runtime_error("vaciooo");
    }
};

int precedencia(char op){
    if (op=='+'||op=='-') return 1;
    if (op=='*'||op=='/') return 2;
    if (op=='^') return 3;
    return 0; 
}

string infijaPostfija(string infija){
    Pila<char> operadores;
    string postfija="";
    string tempNum="";

    for(int i=0;i<infija.length();i++){
        char actual=infija[i];

        if (isdigit(actual)||actual=='.'){
            tempNum+=actual;
        }
        else{
            // se lee algo que no es numero, el numero ya acabó
            if(tempNum!=""){
                postfija+=tempNum+" ";
                tempNum=" ";
            }

            if(actual==' '){
                continue;
            }

            if(actual=='('){
                operadores.push(actual);
            }

            else if(actual==')'){
                while(!operadores.empty() && operadores.top() != '('){
                    postfija+=operadores.top();
                    postfija+=" ";
                    operadores.pop(); 
                }
                if(!operadores.empty()&&operadores.top()!='('){
                    operadores.pop(); 
                }
            }

            else if (actual == '+' || actual == '-' || actual == '*' || actual == '/') {
                while (!operadores.empty() && operadores.top() != '(' && 
                       precedencia(operadores.top()) >= precedencia(actual)) {
                    postfija += operadores.top();
                    postfija += " ";
                    operadores.pop();
                }
                operadores.push(actual);
            }
        }
    }

    if (tempNum!=""){
        postfija+=tempNum+ " ";
    }

    while (!operadores.empty()) {
        postfija += operadores.top();
        postfija += " ";
        operadores.pop();
    }

    return postfija; 
}

int evaluarPostfija(string postfija){
    Pila<int> valores; 
    string tempNum = "";

    for(int i=0;i<postfija.length();i++){
        char actual=postfija[i];
        if(isdigit(actual)){
            tempNum+=actual;
        }
        else if(actual==' '){ 
            if(tempNum!=""){ // ya termino el numero
                valores.push(stoi(tempNum));
                tempNum="";
            }
        }
        else if (actual == '+' || actual == '-' || actual == '*' || actual == '/') {
            int num2=valores.top();
            valores.pop();
            int num1=valores.top();
            valores.pop();
            int resultado=0;

            if (actual == '+') {
                resultado = num1 + num2;
            } else if (actual == '-') {
                resultado = num1 - num2;
            } else if (actual == '*') {
                resultado = num1 * num2;
            } else if (actual == '/') {
                resultado = num1 / num2; 
            }

            valores.push(resultado); 
        }
        return valores.top();
    }
}


int main() {
    // Ecuación de prueba: 45 + (38 * 5) - 7 = 228
    string expresionInfija = "45 + 38 * 5 - 7"; 
    
    cout << "1. Original: " << expresionInfija << endl;

    string expresionPostfija = infijaPostfija(expresionInfija);
    cout << "2. Formato RPN (Postfija): " << expresionPostfija << endl;

    int resultado = evaluarPostfija(expresionPostfija);
    cout << "3. Resultado final: " << resultado << endl;

    return 0;
}