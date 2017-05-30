#include "list.h"
#include <cassert>

///////////////////////////
// [I] MEMBROS ESPECIAIS //
///////////////////////////
/*! Construtor padrão. */
template <typename T>
ls::List<T>::List()
:m_size(0)
,m_head(new Node())
,m_tail(new Node())
{
	m_head->next = m_tail;
	m_tail->prev = m_head;
}

/*! Constrói a lista com count cópias de T. */
template <typename T>
ls::List<T>::List(size_type count)
:m_size(count)
,m_head(new Node())
,m_tail(new Node())
{
	m_head->next = m_tail;
	m_tail->prev = m_head;
	auto current(m_head);
	while(count-- > 0){
		//<!Cria novo nó
		auto n_node = new Node(T(), current, current->next);

		//<!O anterior do next aponta para o novo
		current->next->prev = n_node;

		//<! O proximo do current é o novo
		current->next = n_node;
		//<! Avança
		current = current->next;
	}
}

/*! Destrutor. */
template<typename T>
ls::List<T>::~List( ){
	//clear()
	delete m_head; //<! Remove nó cabeça
	delete m_tail; //<! Remove nó calda
}


///////////////////////////
// [II] ITERADORES       //
///////////////////////////

/* Retorna iterador constante que aponta para o começo da lista.*/
template <typename T>
typename ls::List<T>::const_iterator ls::List<T>::cbegin( ) const{
	return ls::List<T>::const_iterator(m_head->next);
}

/* Retorna iterador constante que aponta para o final da lista.*/
template <typename T>
typename ls::List<T>::const_iterator ls::List<T>::cend( ) const{
	return ls::List<T>::const_iterator(m_tail);
}

///////////////////////////
// [III] CAPACIDADE      //
///////////////////////////

/*! Retorna número de elementos da lista. */
template <typename T>
std::size_t ls::List<T>::size( ) const{
	return m_size;
}

/*! Verifica se a lista não tem elementos. */
template <typename T>
bool ls::List<T>::empty( ) const{
	return (m_head->next == m_tail and m_tail->prev == m_head);
}

///////////////////////////
// [IV] CONSULTA         //
///////////////////////////

///////////////////////////
// [V] MODIFICADORES     //
///////////////////////////
/*! Insere elemento no começo da lista.*/
template <typename T>
void push_front( const T & value ){

}

/*! Insere elemento no final da lista.*/
template <typename T>
void push_back( const T & value ){

}


///////////////////////////
// CLASSE CONST_ITERATOR //
///////////////////////////
/*! Construtor padrão para classe iterator. */
template <typename T>
ls::List<T>::const_iterator::const_iterator( Node *p)
:m_ptr(p)
{/*empty*/}

/*! Retorna uma referência para o objeto lozalizado na posição apontada pelo iterador.*/
template <typename T>
const T & ls::List<T>::const_iterator::operator*( ) const{
	assert(m_ptr != nullptr);
	return m_ptr->data;
}

/*! Avança iterador para a próxima posição na lista. (++it)*/
template <typename T>
typename ls::List<T>::const_iterator & ls::List<T>::const_iterator::operator++( ){
	m_ptr = m_ptr->next;
	return *this;
}

/*! Avança iterador para a próxima posição na lista. (it++).*/
template <typename T>
typename ls::List<T>::const_iterator ls::List<T>::const_iterator::operator++( int ){
	auto temp = *this;
	m_ptr = m_ptr->next;
	return temp;
}

/*! Retorna verdadeiro se os iteradores fazem referência para o mesmo ponto da lista.*/    
template <typename T>        
bool ls::List<T>::const_iterator::operator==( const const_iterator & rhs ) const{
	return (m_ptr == rhs.m_ptr);
}

/*! Retorna verdadeiro se os iteradores fazem referência para pontos diferentes da lista.*/
template <typename T>
bool ls::List<T>::const_iterator::operator!=( const const_iterator & rhs ) const{
	return (m_ptr != rhs.m_ptr);
}