//matriz
#include <iostream>
using namespace std;

template <class T>
class node{
    public:
        node(int x,int y,T v){
            this->x=x;
            this->y=y;
            this->v=v;
        }
        void set_v(T valor){
            v=valor;
        }
        T get_v(){
            return v;
        }
        T get_y(){
            return y;
        }
        T get_x(){
            return x;
        }
        node<T>* abjo;
        node<T>* drcha;
    private:
        int x;
        int y;
        int v;

};

template <class T, T NE>
class CSMatrix{
    public:
        CSMatrix(int dim_x ,int dim_y){
            Ejex = new node<T>*[dim_x];
            Ejey = new node<T>*[dim_y]; 
            for (int i = 0; i < dim_y; i++)
                Ejey[i] = nullptr;
            for (int i = 0; i < dim_y; i++)
                Ejey[i] = nullptr;
            this->dim_x=dim_x;
            this->dim_y=dim_y;

        }
        
        bool find_x(int x,int y, T value,node<T>** &p);
        bool find_y(int x,int y, T value,node<T>** &q);
        void insertar(int x, int y, T value);
        void remover(int x, int y, T value);
        void set(int x, int y, T value);
        T get(int x, int y);

        void print();
        
    private:
        node<T>** Ejex = NULL ;
        node<T>** Ejey = NULL ;
        int dim_x;
        int dim_y;

};


template <class T, T NE>
bool CSMatrix< T,  NE>::find_x(int x,int y, T value, node<T>** &p){

    if( *(Ejex+x) ){   // verificamos si hay un nodo existente 
        p = (Ejex+x);
        for(  ; (*p) && (*p)->get_y() < y ; p = &( (*p) -> abjo ) );     //recorremos con puntero doble
    }
    return p && (*p) && (*p)->get_y() == y;
}

template <class T, T NE>
bool CSMatrix< T,  NE>::find_y(int x,int y, T value,node<T>** &q){
   
    if( *(Ejey+y) ){   // verificamos si hay un nodo existente 
        q = (Ejey+y);
        for(  ; (*q) && (*q)->get_x() < x ; q = &( (*q) -> drcha ) ); //recorremos con puntero doble
    }
    return q && (*q) && (*q)->get_x() == x ;
}

template <class T, T NE>
void CSMatrix< T,  NE>::insertar(int x, int y, T value){
    
    node<T>** p=nullptr;
    node<T>** q=nullptr;
    bool x_vector = *(Ejex+x);     //  array* eje x [0,0,0,0,0]  
    bool y_vector = *(Ejey+y);     //  array* eje y [0,0,0,0,0]
    
    //////////////// el rango no permitido lo evita ///////////////
    if(x >= dim_x || y >= dim_y) return ; 
    
    //////////////// si existe el nodo x , y /////////////// *Solo basta con encontrarlo de un lado* 
    bool f_x = find_x(x, y, value, p);
    if(f_x){  
        (*p) -> set_v(value);  // se cambia el valor
        return ;
    }
    
    ////////////// Si no existe el nodo ////////////////

    node<T>* tmp = new node<T>(x,y,value); 

    bool f_y = find_y(x, y, value, q);


    if ( !x_vector ){  // si la posicion en el array x es nula 
    
        *(Ejex+x) = tmp;
        tmp->abjo = nullptr;   // se la crea
         
        if(!y_vector){
            *(Ejey+y) = tmp;
            tmp->drcha = nullptr;   // si en la posicion en el array de "y" tambien es nula tambien la crea
            return;
            
        }
        else if(y_vector){     // pero si existe algun nodo en el posicion "y"
            node<T>* q_posterior = *q;
            (*q) = tmp;
            tmp->drcha = q_posterior;
        }
        return ;
    }
    
    if(!y_vector){   // si solo y esta vacio
        *(Ejey+y) = tmp;
        tmp->drcha = nullptr; 
        
        if(x_vector){
            node<T>* p_posterior = *p;
            (*p) = tmp;
            tmp->abjo = p_posterior;   
        }
    // if(!x_vector ) ya se analizo arriba, esta condicion se repetiria
        return ;
    }
    
    // if( x_vector && x_vector )  equivalencia a que ya exisaten nodos 
    node<T>* p_posterior = (*p);
    *p = tmp;                       //equivalencias:
    (*p)->abjo = p_posterior;       // tmp->abjo = p_posterior;
    
    node<T>* q_posterior = (*q);    // inserta al nodo nuevo en la lista de su y
    *q = (*p);                      // *q = tmp; 
    (*q)->drcha = q_posterior;      // tmp->drcha = q_posterior;
    return ;

}


    
   
template <class T, T NE>
void CSMatrix< T,  NE>::remover(int x, int y, T value){
    
    node<T>** p=nullptr;
    node<T>** q=nullptr;
    
    bool x_vector = *(Ejex+x);
    bool y_vector = *(Ejey+y);
    
    if( !x_vector && !y_vector ){
        //cout<<"No se encontro "<< x <<" "<< y <<endl;
        return ;
    }
    
    bool f_x = find_x(x, y, value, p);
    if (f_x){
        //borrar x
        bool f_y = find_y(x, y, value, q);
        node<T>* tmp = (*p);
        *p = tmp->abjo;
        *q = tmp->drcha;
        delete tmp;
    }
    //cout <<"No se encontro "<< x <<" "<< y <<endl;
    
    
    

}

template <class T, T NE>
void CSMatrix< T,  NE>::set(int x, int y, T value){
    
    if(value == NE){
        cout<<"| remover "<< x << ","<< y <<" ";
        remover(x,y,value);
    }
    else{
        cout<<"insertar x = "<< x <<"; y = "<< y <<" | Valor: = "<< value <<" |"<<endl;
        insertar(x,y,value);
    }
}

template <class T, T NE>
T CSMatrix< T,  NE>::get(int x, int y){
    
    T tmp;
    node<T>** p =nullptr;
    node<T>** q =nullptr;
                    
    if( *(Ejex+x) && *(Ejey+y)  ){   // verificamos si hay un nodo existente , el eje x

        p = Ejex+x;
        q = Ejey+y; 

        for(  ; (*p) && (*p)->get_y() < y ; p = &( (*p) -> abjo ) );
        for(  ; (*q) && (*q)->get_x() < x ; q = &( (*q) -> drcha ) );

        if(  !(*p) && (*p) == (*q)  ) return NE;  // si el nodo encontrado coincide con el eje y , se retorna su valor
        // if(  !(*q) && (*p) == (*q)  ) return NE;
        if( (*p) == (*q) ) return (*p)->get_v(); 
        
    }
    return NE;
    

}

template <class T, T NE>
void CSMatrix< T,  NE>::print(){         
    cout<<endl<<"Print() "<<endl;
    for(int i=0; i<dim_y ; i++){
        cout<< "   ";
        for(int j=0; j<dim_x ; j++)
            cout<< " " << get(j,i) << " "; // ejes invertidos
        cout<<endl;
    }
    cout<<endl;
}   


int main(){
    CSMatrix<int,0> m(5,5);
    
    for(int i=0; i<4;i++ ){
        m.set(i,i,1);    
    }
    
    m.print();
    m.set(0,2,1); 
    m.print();
    m.set(0,4,1); 
    m.print();
    
    cout<<"insertar diagonal negativa"<<endl;
    for(int i=0; i<5; i++ ){
        m.set(4-i,i,2);    
    }
    m.print();
    m.set(0,5,1);
    
    for(int i=0; i<5; i++ ){
        for(int j=0; j<5; j++ ){
             m.set(j,i,0);    
        }   
    }
    m.print();
    
    return 0;
}
