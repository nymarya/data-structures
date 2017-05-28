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
	return ls::ForwardList<T>::iterator (m_head);
}

/*! Retorna iterador que aponta para o final do vetor.*/
template <typename T>
typename ls::ForwardList<T>::iterator ls::ForwardList<T>::end( void ){
	auto tail(m_head);
	while (tail != nullptr)
		tail = tail->next;

	return ls::ForwardList<T>::iterator(tail);
}

/* Retorna iterador constante que aponta para o começo do vetor.*/
template <typename T>
typename ls::ForwardList<T>::const_iterator ls::ForwardList<T>::cbegin( void ) const{
    return ls::ForwardList<T>::const_iterator (m_head);
}

/* Retorna iterador constante que aponta para o final do vetor.*/
template <typename T>
typename ls::ForwardList<T>::const_iterator ls::ForwardList<T>::cend( void ) const{
    auto tail(m_head);
	while (tail != nullptr)
		tail = tail->next;

	return ls::ForwardList<T>::const_iterator(tail);
}

///////////////////////////
//  [III] CAPACITY       //
///////////////////////////

/*! Retorna número de elementos da lista.*/
template <typename T>
typename ls::ForwardList<T>::size_type ls::ForwardList<T>::size() const{
	return m_size;
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
		m_size++; //<! Atualiza tamanho
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

/*! Adiciona valor value depois de pos.*/
template <typename T>
typename ls::ForwardList<T>::iterator ls::ForwardList<T>::insert( ls::ForwardList<T>::iterator pos, const T & value ){
	//<! Cria novo nó
	Node * nNode = new Node(value, pos->next);

	//<! Insere novo nó
	pos->next = nNode; 
	pos++; //<! Avança

	//<! Atualiza tamanho
	m_size++;

	return pos;
}

/*! Insere os elementos do intervalo [first; last) antes de pos.*/
template <typename T>
template<typename InputItr>
typename ls::ForwardList<T>::iterator ls::ForwardList<T>::insert( ls::ForwardList<T>::iterator pos, InputItr first, InputItr last){

	while( first != last){
		auto temp_node = new Node( *first, pos->next); //<! Cria novo nó
		pos->next = temp_node; //<! Insere novo nó apos pos
		++pos;	  //<! Avança na lista
		first++;  //<! Avança no intervalo
		m_size++; //<! Atualiza tamanho
	}

	return pos;
}

/*! Insere elementos de std::initializer_list antes de pos.*/
template <typename T>
typename ls::ForwardList<T>::iterator ls::ForwardList<T>::insert( ls::ForwardList<T>::iterator pos, std::initializer_list< T > ilist){
	
	for( auto &e: ilist){
		auto temp_node = new Node( e, pos->next); //<! Cria novo nó
		pos->next = temp_node;  //<! Insere novo nó após pos
		++pos;       		    //<! Avança na lista
		m_size++;    		   //<! Atualiza tamanho
	}

	return pos;
}

/*! Remove o elemento após a posição pos.*/
template <typename T>
typename ls::ForwardList<T>::iterator ls::ForwardList<T>::erase( ls::ForwardList<T>::iterator pos){
    //<! Acessa o elemento a ser removido
    auto target( pos );
    target++;

    //<! Remove o elemento
    delete pos->next;

    //<! O elemento seguinte a pos será o que segue o removido
    pos->next = target->next;
    m_size--; //<! Atualiza tamanho
    
    //<! Retorna o elemento após o removido
    return ++pos;
}

/*! Remove os elementos no intervalo [first, last).*/
template <typename T>
typename ls::ForwardList<T>::iterator ls::ForwardList<T>::erase( iterator first, iterator last){
    //<! Guarda a posição anterior a first
    auto current( m_head );
    if( first != begin()){
        for(auto it (begin()); ++it != first;)
            current = current->next;
    
    }
    auto n_next(current);
    while( first++ != last){
        auto target( n_next->next);
        n_next = n_next->next;
        if(first != last) delete target;
        m_size--; //<! Atualiza tamanho
    } 
    
    if (current == m_head)
        m_head = n_next;
    else
        current->next = n_next->next;


    return last;
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
	auto value = tail->data;
	delete tail; //<! Remove o último elemento

	m_size--; //<! Atualiza compimento da lista

	return value;
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

/*! Substitui o conteúdo da lista cópias do valor 'value'.*/
template <typename T>
void ls::ForwardList<T>::assign( const T & value ){
	//<! Percorre lista
	auto it( begin() );
	while( it != end()) {
		//<! Insere valor
		it->data = value;
		it++;
	}
}

/*! Substitui o conteúdo da lista por cópias dos elementes no intervalo [first,last).*/
template <typename T>
template < typename InputItr>
void ls::ForwardList<T>::assign( InputItr first, InputItr last){
	//<! Remove quaisquer elementos
	clear();

	//<! Adiciona os valores na lista
	auto n(0ul);
	while( first != last){
		push_back(*first++);
		n++;
	}	
	
	//<! Atualiza tamanho
	m_size = n;
}

/*! Substitui o conteúdo da lista pelos elementos de ilist.*/
template <typename T>
void ls::ForwardList<T>::assign( std::initializer_list<T> ilist ){
	//<! Remove quaisquer elementos
	clear();

	//<! Adiciona os valores na lista
	for(auto &e : ilist )
		push_back(e);
	
	//<! Atualiza tamanho
	m_size = ilist.size();
}

/*! Limpa ForwardList. */
template <typename T>
void ls::ForwardList<T>::clear(){
	//<! Percorre a lista
	auto current( m_head);
	while( current != nullptr){
		//<! Guarda o que será removido
		auto target(current);
		current = current->next; //<! Avança
		//<! Remove elemento
		delete target;
	}

	m_head = current; //<! Atualiza head
	m_size = 0; //<! Atualiza tamanho
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


///////////////////////////
//  [VI] ITERATOR CLASS  //
///////////////////////////
/*! Construtor padrão.*/
template <typename T>
ls::ForwardListIterator<T>::ForwardListIterator(T * current)
: m_current(current)
{/*empty*/}


/*! Retorna uma referência para o objeto lozalizado na posição apontada pelo iterador. */
template <typename T>
typename T::value_type & ls::ForwardListIterator<T>::operator*( ) const{
	assert( m_current != nullptr );                     
	return m_current->data;
}

/*! Avança iterador para a próxima posição na lista. (++it). */
template <typename T>
 ls::ForwardListIterator<T> & ls::ForwardListIterator<T>::operator++( ){
	m_current = m_current->next;                     
	return *this;
}

/*! Avança iterador para a próxima posição na lista. (it++). */
template <typename T>
ls::ForwardListIterator<T> ls::ForwardListIterator<T>::operator++( typename T::value_type ){
	ls::ForwardListIterator<T> temp = *this; 			
	m_current = m_current->next;				
	return temp;
}

/*! Avança iterador step vezes. */
template <typename T>
ls::ForwardListIterator<T>  ls::ForwardListIterator<T>::operator+=( ls::ForwardListIterator<T>::difference_type step ){
	while(step > 0){
		m_current = m_current->next;  
		step--;
	}

	return *this;
}

/*! Retorna verdadeiro se os iteradores fazem referência para o mesmo ponto da lista. */
template <typename T>
bool ls::ForwardListIterator<T>::operator==( const typename ls::ForwardListIterator<T> & rhs ) const{
	return (m_current == rhs.m_current);
}

/*! Retorna verdadeiro se os iteradores fazem referência para pontos diferentes da lista.*/
template <typename T>
bool ls::ForwardListIterator<T>::operator!=( const typename ls::ForwardListIterator<T> & rhs ) const{
	return (m_current != rhs.m_current);
}

/*! Acessa o elemento para o qual o iterator aponta. */
template <typename T>
T* ls::ForwardListIterator<T>::operator->( void ) const {                     
	assert( m_current );                     
	return m_current;                 
}