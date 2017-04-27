#include <iostream>

template <typename T>
class Stack
{
    private:
        static const std::size_t SIZE = 10;
        std::size_t m_top;      //<! Topo da pilha
        std::size_t m_capacity; //<!Tamanho físico
        T * m_data;             //<! Area de armazenamento

        //Amplia a area de armazenamento
        void reserve( std::size_t new_cap);

    public:
        Stack( std::size_t cap = SIZE);
        
        ~Stack();

        Stack( const Stack &) = delete;
        Stack & operator=(const Stack &) = delete;

        void push( const T & value);
        void pop ( void );           //pode lançar std::length_error
        T top( void );  
};

template <typename T>
void DoubleArray ( T * &A , int & currentSize ){

	 T *data = new T[ currentSize * 2]; //Novo vetor

	 std::copy(A, A+currentSize, data);  //Copia para novo vetor

	 delete A;

	 A = data;							//Aponta para o novo endereço
	 currentSize *= 2; //Atualizar tamanho;
}

template <typename T>
Stack<T>::Stack( std::size_t cap)
    : m_top(0), 
    m_capacity(cap), 
    m_data(new T[cap]),
    { /*empty*/}

template <typename T>
Stack<T>::~Stack(){

    delete [] m_data;
}

template <typename T>
void Stack<T>::push(const T & value){

    if(m_top == m_capacity){
        //aumenta vetor
        DoubleArray(m_data, m_capacity);
    }

    m_data[m_top] = value;
    m_top++;

}

template <typename T>
T Stack<T>::top(){

    return m_data[top];

}

int main(){

    Stack<int> v;

    v.push(4);

    std::cout << v.top() << std::endl;

    return EXIT_SUCESS;

}