#include "queue.hpp"

//Construtor padrão: apenas inicializa
template <typename T>
ls::Queue<T>::Queue( std::size_t sz)
: m_f( -1)
, m_r( -1)
, m_size( sz)
, m_data( new T[sz])
{
    /* empty */
}

//Destrutor
template <typename T>
ls::Queue<T>::~Queue()
{
    delete [] m_data;
}

//insere no final da fila
template <typename T>
void ls::Queue<T>::enqueue( const T& value ){   
    int prox_r = (m_r + 1) % m_size;

    if( prox_r == 0 or prox_r != m_f){
        (m_f == -1) ? m_f = 0 : m_f = m_f;
        m_data[prox_r] = value;
        m_r = prox_r;
        
    } else{
        assert(false);
    }
    
}

//remove elemento no começo da fila
template <typename T>
void ls::Queue<T>::dequeue(){
    if( m_f != -1){
        //Se so houver um elemento, f e r voltam pra -1
        if(m_f == m_r){
            m_f = m_r = -1;
        } 
        //Se houver mais de 1 elemento, o f avança circularmente
        else{
            m_f = (m_f + 1) % m_size;
        }
    }else{
        assert(false);
    }
}

//consulta
template <typename T>
T ls::Queue<T>::front(){
    if(m_f != -1 )
        return m_data[m_f];

    assert(false);
}

//Verifica se está vazio
template <typename T>
bool ls::Queue<T>::isEmpty(){
    return (m_f == -1);
} 

//Limpa fila
template <typename T>
void ls::Queue<T>::makeEmpty(){
    m_f = m_r = -1;
    m_size = 0;
}

//Retorna numero de elementos na fila
template <typename T>
T ls::Queue<T>::size() const{
    if( m_r == m_f )
        return 1;
    else if( m_r > m_f)
        return  m_r - m_f + 1;
    else
        return m_f - m_r + 1;
    
}