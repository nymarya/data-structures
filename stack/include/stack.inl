#include "stack.hpp"
#include <stdexcept>

template <typename T>
void Stack<T>::reserve( std::size_t new_cap ){
	if(new_cap > m_capacity){
		T *temp = new T[ new_cap ]; //Novo vetor

		std::copy(m_data, m_data + new_cap, temp);  //Copia para novo vetor

		delete m_data;

		m_data = temp;							//Aponta para o novo endereço
		m_capacity = new_cap; //Atualizar tamanho;
	}
}

template <typename T>
Stack<T>::Stack( std::size_t cap)
    : m_top(0), 
    m_capacity(cap), 
    m_data(new T[cap])
    { /*empty*/}

template <typename T>
Stack<T>::~Stack()
{ delete [] m_data; }

template <typename T>
void Stack<T>::push(const T & value){
    if(m_top == m_capacity) reserve(m_capacity * 2);

    m_data[m_top++] = value;
}

template <typename T>
void Stack<T>::pop( void ){
    if(m_top == 0) 
        throw std::length_error("[pop()] Cannot recover element from an empty vector.");
    m_top--;
}

template <typename T>
T Stack<T>::top() 
{  return m_data[m_top-1]; }