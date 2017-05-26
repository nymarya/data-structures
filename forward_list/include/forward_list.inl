#include "forward_list.h"
#include <cassert>

///////////////////////////
//  [I] SPECIAL MEMBERS  //
///////////////////////////

/*! Construtor padrão*/
template <typename T>
ls::ForwardList<T>::ForwardList(size_type size)
: m_size( size)
, m_head( nullptr)
{/*empty*/}

/*! Constroi a lista com os elementos do intervalo [first, last).*/
template <typename T>
template< typename InputIt >
ls::ForwardList<T>::ForwardList( InputIt first, InputIt last ){

}

/*! Construtor cópia*/
template <typename T>
ls::ForwardList<T>::ForwardList( const ForwardList& other ){

}

/*! Construtor com conteúdo de initializer list.*/
template <typename T>
ls::ForwardList<T>::ForwardList( std::initializer_list<T> init ){

}

/*! Destructor. */
template <typename T>
ls::ForwardList<T>::~ForwardList( ){
    delete m_head;
}

/*! Operador de atribuição por cópia.*/
template <typename T>
ls::ForwardList<T>& ls::ForwardList<T>::operator=( const ForwardList& other ){

}

/*! Substitui o conteúdo da lista pelos elementos de ilist.*/
template <typename T>
ls::ForwardList<T>& ls::ForwardList<T>::operator=( std::initializer_list<T> ilist ){

}

///////////////////////////
//  [II] ITERATORS       //
///////////////////////////

/*! Retorna iterador que aponta para o começo do vetor.*/
template <typename T>
typename ls::ForwardList<T>::iterator ls::ForwardList<T>::begin( void ){

}

/*! Retorna iterador que aponta para o final do vetor.*/
template <typename T>
typename ls::ForwardList<T>::iterator ls::ForwardList<T>::end( void ){

}

/* Retorna iterador constante que aponta para o começo do vetor.*/
template <typename T>
typename ls::ForwardList<T>::const_iterator ls::ForwardList<T>::cbegin( void ) const{

}

/* Retorna iterador constante que aponta para o final do vetor.*/
template <typename T>
typename ls::ForwardList<T>::const_iterator ls::ForwardList<T>::cend( void ) const{

}

///////////////////////////
//  [III] CAPACITY       //
///////////////////////////

/*! Retorna número de elementos da lista.*/
template <typename T>
typename ls::ForwardList<T>::size_type ls::ForwardList<T>::size() const{
	const Node * work (m_head);
	std::size_t count(0);

	while( work != nullptr){
		count++;
		work = work->next;
	}

	return count;
}

/*! Verifica se o vetor não tem elementos.*/
template <typename T>
bool ls::ForwardList<T>::empty ()const{
	return (m_head == nullptr);
}

///////////////////////////
//  [IV] MODIFIERS       //
///////////////////////////

/*! Insere elemento no final da lista.*/
template <typename T>
void ls::ForwardList<T>::push_back(const T & value){
	//<! Cria um "tail"
	auto tail( m_head );

	//<! Percorre a lista
	while( tail != nullptr and tail->next != nullptr )
		tail = tail->next;

	//<! Insere no final
	if ( tail != nullptr ){
		Node * aux = new Node(value, nullptr);
		tail->next = aux;
	}
	else 
		push_front( value );
	
}

/*! Insere elemento no início da lista.*/
template <typename T>
void ls::ForwardList<T>::push_front(const T & value){

	//<! Cria o novo nó
	Node * aux = new Node(value, m_head);

	//<! Novo nó agora é primeiro elemento da lista
	m_head = aux;

	m_size++; //<! Atualiza tamanho
}

/*! Adiciona valor value antes de pos.*/
template <typename T>
ls::ForwardListIterator<T> ls::ForwardList<T>::insert( iterator pos, const T & value ){

}

/*! Insere os elementos do intervalo [first; last) antes de pos.*/
template <typename T>
template<typename InputItr>
ls::ForwardListIterator<T> ls::ForwardList<T>::insert( iterator , InputItr , InputItr ){

}

/*! Insere elementos de std::initializer_list antes de pos.*/
template <typename T>
ls::ForwardListIterator<T> ls::ForwardList<T>::insert( iterator, std::initializer_list< T > ){

}

/*! Remove o elemento na posição pos.*/
template <typename T>
ls::ForwardListIterator<T> ls::ForwardList<T>::erase( iterator ){

}

/*! Remove os elementos no intervalo [first, last).*/
template <typename T>
ls::ForwardListIterator<T> ls::ForwardList<T>::erase( iterator, iterator ){

}

/*! Remove o elemento no final da lista.*/
template <typename T>
T ls::ForwardList<T>::pop_back(){
	//<! Gera erro se lista está vazia
	if( empty())
		assert(false);

	//<! Cria o "tail" e uma variavel que guarda o anterior
	auto tail(m_head);
	auto prev(m_head);

	//<! Percorre a lista
	while(tail->next != nullptr){
		prev = tail;
		tail = tail->next;
	}

	//Nesse ponto, tail é o utlimo elemento e prev é o penultimo
	prev->next = nullptr; //<! Prev agora é o ultimo
	delete tail; //<! Remove o último elemento

	m_size--; //<! Atualiza compimento da lista
}

/*! Remove o elemento no início do array.*/
template <typename T>
void ls::ForwardList<T>::pop_front(){
	//<! Gera erro se lista está vazia
	if( empty())
		assert(false);

	//<! Guarda o segundo
	Node * aux = m_head->next;

	//<! Head agora guarda o segundo
	m_head = aux;	

	m_size--; //<! Atualiza tamanho
}

/*! Substitui o conteúdo da lista por cópias do valor 'value'.*/
template <typename T>
void ls::ForwardList<T>::assign( const T & value ){

}

/*! Substitui o conteúdo da lista por cópias dos elementes no intervalo [first,last).*/
template <typename T>
template < typename InputItr>
void ls::ForwardList<T>::assign( InputItr first, InputItr last){

}

/*! Substitui o conteúdo da lista pelos elementos de ilist.*/
template <typename T>
void ls::ForwardList<T>::assign( std::initializer_list<T> ilist ){

}

/*! Limpa ForwardList. */
template <typename T>
void ls::ForwardList<T>::clear(){

}

///////////////////////////
//  [V] ELEMENT ACCESS   //
///////////////////////////

/*! Imprime ForwardList. */
template <typename T>
void ls::ForwardList<T>::print( ) const{
    
}

/*! Retorna primeiro elemento da lista.*/
template <typename T>
T ls::ForwardList<T>::front() const{
	//<! Retorna erro se estiver vazia
	if(empty())
		assert(false);

	return (m_head->data);
}

/*! Retorna último elemento da lista.*/
template <typename T>
T ls::ForwardList<T>::back() const{
	//<! Retorna erro se estiver vazia
	if( empty() )
		assert(false);

	//<! Cria um "tail"
	auto tail(m_head);
	//<! Percorre a lista
	while( tail->next != nullptr)
		tail = tail->next;

	return (tail->data);
}

///////////////////////////
//  [V] OPERATORS        //
///////////////////////////