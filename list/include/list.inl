#include "list.h"
#include <cassert>
#include <stdexcept>

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
	clear();
	delete m_head; //<! Remove nó cabeça
	delete m_tail; //<! Remove nó calda
}

/*! Constroi a lista com os elementos do intervalo [first, last). */
template <typename T>
template< typename InputIt >
ls::List<T>::List( InputIt first, InputIt last )
: m_size( 0 )
, m_head( new Node() )
, m_tail( new Node() )
{
	//<! Cria nova lista
	m_head->next = m_tail;
	m_tail->prev = m_head;

	//<! Copia os elementos do intervalo para a nova lista
	while(first != last){
		push_back( *first++);
	}
}

/*! Construtor cópia. */
template <typename T>
ls::List<T>::List( const List & other )
: m_size( 0 )
, m_head( new Node() )
, m_tail( new Node() )
{
	m_head->next = m_tail;
	m_tail->prev = m_head;

	//<! Preenche a lista com o conteúdo de other
	for( auto it( other.cbegin() ); it != other.cend(); ++it)
		push_back(*it);
}

/*! Construtor com conteúdo de initializer list. */
template <typename T>
ls::List<T>::List( std::initializer_list<T> ilist )
: m_size( 0 )
, m_head( new Node() )
, m_tail( new Node() )
{
	m_head->next = m_tail;
	m_tail->prev = m_head;

	//<! Preenche a lista com o conteúdo de ilist
	for( auto it( ilist.begin() ); it != ilist.end(); ++it)
		push_back(*it);
}

/*! Operador de atribuição por cópia. */
template <typename T>
ls::List<T> & ls::List<T>::operator= ( const List & other ){
	if (this == &other) return *this;

	//<! Limpa a lista
	clear();

	//<! Preenche a lista com o conteúdo de other
	for( auto it( other.cbegin() ); it != other.cend(); ++it)
		push_back( *it);

	return *this;
}

/*! Substitui o conteúdo da lista pelos elementos de ilist. */
template <typename T>
ls::List<T>& ls::List<T>::operator=( std::initializer_list<T> ilist ){
	//<! Limpa a lista
	clear();

	//<! Preenche a lista com o conteúdo de ilist
	for( auto it( ilist.begin() ); it != ilist.end(); ++it)
		push_back(*it);

	return *this;
}

///////////////////////////
// [II] ITERADORES       //
///////////////////////////

/*! Retorna iterador que aponta para o começo da lista. */
template <typename T>
typename ls::List<T>::iterator ls::List<T>::begin( ){
	return ls::List<T>::iterator(m_head->next);
}

/* Retorna iterador constante que aponta para o começo da lista.*/
template <typename T>
typename ls::List<T>::const_iterator ls::List<T>::cbegin( ) const{
	return ls::List<T>::const_iterator(m_head->next);
}

/*! Retorna iterador que aponta para o final da lista.*/
template <typename T>
typename ls::List<T>::iterator ls::List<T>::end( ) {
	return ls::List<T>::iterator(m_tail);
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

/*! Retorna uma referência para o primeiro elemento da lista.*/
template <typename T>
T & ls::List<T>::front( ){
	if(empty())
		throw std::out_of_range("[front()] Cannot recover element from an empty list.");

	return m_head->next->data;
}

/*! Retorna uma refrência constante para o primeiro elemento da lista.*/
template <typename T>
const T & ls::List<T>::front( ) const{
	if(empty())
		throw std::out_of_range("[front()] Cannot recover element from an empty list.");

	return m_head->next->data;
}

/*! Retorna uma referência para o último elemento da lista. */
template <typename T>
T & ls::List<T>::back( ){
	if(empty())
		throw std::out_of_range("[back()] Cannot recover element from an empty list.");

	return m_tail->prev->data;
}

/*! Retorna uma referência constante para o último elemento da lista. */
template <typename T>
const T & ls::List<T>::back( ) const{
	if(empty())
		throw std::out_of_range("[back()] Cannot recover element from an empty list.");

	return m_tail->prev->data;
}

///////////////////////////
// [V] MODIFICADORES     //
///////////////////////////

/*! Limpa lista. */
template <typename T>
void ls::List<T>::clear( ){	
	//<! Percorre a lista e remove elementos
	auto it( begin() );
	while( it++ != end() ){
		erase( ls::List<T>::iterator(it.m_ptr->prev) );	
	}
}

/*! Insere elemento no começo da lista.*/
template <typename T>
void ls::List<T>::push_front( const T & value ){

	//<! Cria novo nó 
	Node * n_node = new Node(value, m_head, m_head->next);

	//<! Insere nó na lista
	m_head->next->prev = n_node;
	m_head->next = n_node;

	//<! Atualiza tamanho
	m_size++;
}

/*! Insere elemento no final da lista.*/
template <typename T>
void ls::List<T>::push_back( const T & value ){
	//<! Basta inserir valor antes do end()
	insert(end(), value);
}

/*! Remove o elemento no início da lista.*/
template <typename T>
void ls::List<T>::pop_front( ){
	if(empty())
		throw std::out_of_range("[pop_front()] Cannot remove element from an empty list.");

	erase(begin());
}

/*! Remove o elemento no final da lista.*/
template <typename T>
void ls::List<T>::pop_back( ){
	if(empty())
		throw std::out_of_range("[pop_back()] Cannot remove element from an empty list.");

	erase(  ls::List<T>::iterator(m_tail->prev)  );
}

/*! \brief Substitui o conteúdo da lista por cópias do valor 'value'. */
template <typename T>
void ls::List<T>::assign(const T& value ){
	//<! Substitui todos os valores da lista por value
	for( auto it( begin() ); it != end(); it++)
		*it = value;
}

/*! Substitui o conteúdo da lista por cópias dos elementes no intervalo [first,last). */
template <typename T>
template <class InItr >
void ls::List<T>::assign( InItr first, InItr last ){
	//<! Limpa a lista
	clear();

	//<! Substitui pelo conteudo de ilist
	while(first != last)
		push_back( *first++);
}

/*! Substitui o conteúdo da lista pelos elementos de ilist. */
template <typename T>
void ls::List<T>::assign( std::initializer_list<T> ilist ){
	//<! Limpa a lista
	clear();

	//<! Substitui pelo conteudo de ilist
	for(const auto &e : ilist)
		push_back( e);
}

/*! Adiciona valor value antes de pos.*/
template <typename T>
typename ls::List<T>::iterator ls::List<T>::insert( const_iterator pos, const T & value ){
	//<! Atualiza tamanho
	m_size++;

	//<! Cria novo nó
	Node * n_node = new Node(value, pos.m_ptr->prev, pos.m_ptr);

	//<! Insere novo nó
	(pos.m_ptr->prev)->next = n_node;
	pos.m_ptr->prev = n_node;

	return ls::List<T>::iterator(n_node);
}

/*! Insere os elementos do intervalo [first; last) antes de pos. */
template < typename T>
template < typename InItr>
typename ls::List<T>::iterator ls::List<T>::insert( iterator pos, InItr first, InItr last ){
	//<! Percorre o intervalo e insere cada elemento na lista
	while( first != last){
		insert(pos, *first++);
	}
		
	return pos;
}

/*! Insere elementos de std::initializer_list antes de pos. */
template <typename T>
typename ls::List<T>::iterator ls::List<T>::insert( const_iterator pos, std::initializer_list<T> ilist ){
	//<! Insere cada elemento de ilist antes de pos
	for(const auto &e : ilist)
		insert(pos, e);

	return ls::List<T>::iterator(pos.m_ptr);
}

/*! Remove o elemento na posição pos.*/
template <typename T>
typename ls::List<T>::iterator ls::List<T>::erase( const_iterator pos ){
	if(empty())
		throw std::out_of_range("[erase()] Cannot remove element from an empty list.");

	auto after(pos.m_ptr->next );

	//<! Seguinte aponta para o anterior a pos
	after->prev = pos.m_ptr->prev;

	//<! Anterior aponta para o que segue pos
	pos.m_ptr->prev->next = after;

	//<! Remove elemento apontado por pos
	delete pos.m_ptr;

	//<! Atualiza tamanho
	m_size--;

	return ls::List<T>::iterator(after);
}

/*! Remove os elementos no intervalo [first, last). */
template <typename T>
typename ls::List<T>::iterator ls::List<T>::erase( iterator first, iterator last ){
	if(empty())
		throw std::out_of_range("[erase()] Cannot remove element from an empty list.");

	//<! Remove elementos do intervalo
	while( first != last){
		first++;
		erase( first.m_ptr->prev);
	}

	return last;
}

///////////////////////////
//  [VI] OPERADORES      //
///////////////////////////

/*! Checa se os conteúdos de lhs e rhs são iguais.*/
template <typename T>
bool operator==( const ls::List<T>& lhs, const ls::List<T>& rhs ){
	//<! Checa o número de elementos
	if( lhs.size() != rhs.size() ) return false;
	else{
		//<! Verifica se todos os elementos são iguais
		auto it(lhs.cbegin() );
		auto it2(rhs.cbegin() );
		for (  /*empty*/; it != lhs.cend(); ++it, ++it2)
			if( *it != *it2 ) return false;
	}

	return true;
}

/*! Verifica se os conteúdos de lhs e rhs são iguais.*/
template <typename T>
bool operator!=( const ls::List<T>& lhs, const ls::List<T>& rhs ){
	//<! Checa o número de elementos
	if( lhs.size() != rhs.size() ) return true;
	else{
		//<! Verifica se há algum elemento diferente
		auto it(lhs.cbegin() );
		auto it2(rhs.cbegin() );
		for (  /*empty*/; it != lhs.cend(); ++it, ++it2)
			if( *it != *it2 ) return true;
	}

	return false;
}
///////////////////////////
// CLASSE CONST_ITERATOR //
///////////////////////////
/*! Construtor padrão para classe const_iterator. */
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

/*! Move iterador para a posição anterior na lista. (--it). */
template <typename T>
typename ls::List<T>::const_iterator & ls::List<T>::const_iterator::operator--( ){
	m_ptr = m_ptr->prev;
	return *this;
}

/*! Move iterador para a posição anterior na lista. (it--). */
template <typename T>
typename ls::List<T>::const_iterator ls::List<T>::const_iterator::operator--( int ){
	auto temp = *this;
	m_ptr = m_ptr->prev;
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

/*! Avança iterador step vezes.*/
template <typename T>
typename ls::List<T>::const_iterator ls::List<T>::const_iterator::operator+=( difference_type step ){
	//<! Avança o iterador
	while(step > 0){
		m_ptr = m_ptr->next;  
		step--;
	}
	return *this;
}

/*! Move iterador step vezes para trás.*/
template <typename T>
typename ls::List<T>::const_iterator ls::List<T>::const_iterator::operator-=( difference_type step ){
	//<! Volta com o iterador
	while(step > 0){
		m_ptr = m_ptr->prev;  
		step--;
	}
	return *this;
}

///////////////////////////
// CLASSE ITERATOR       //
///////////////////////////
/*! Construtor padrão para classe const_iterator. */
template <typename T>
ls::List<T>::iterator::iterator( Node * p )
: const_iterator(p) 
{ /* Empty */ }

/*! Retorna uma referência para o objeto lozalizado na posição apontada pelo iterador.*/
template <typename T>
T & ls::List<T>::iterator::operator*( ){
	return const_iterator::m_ptr->data;
}

/*! Avança iterador para a próxima posição na lista. (++it) */
template <typename T>
typename ls::List<T>::iterator & ls::List<T>::iterator::operator++( ){
	const_iterator::m_ptr = const_iterator::m_ptr->next;
	return *this;
}

/*! Move iterador para a posição anterior na lista. (--it) */
template <typename T>
typename ls::List<T>::iterator ls::List<T>::iterator::operator++( int ){
	auto temp = *this;
	const_iterator::m_ptr = const_iterator::m_ptr->next;
	return temp;
}

/*! Move iterador para a posição anterior na lista. (--it) */
template <typename T>
typename ls::List<T>::iterator & ls::List<T>::iterator::operator--( ){
	const_iterator::m_ptr = const_iterator::m_ptr->prev;
	return *this;
}

/*! Move iterador para a posição anterior na lista. (it--) */
template <typename T>
typename ls::List<T>::iterator ls::List<T>::iterator::operator--( int ){
	auto temp = *this;
	const_iterator::m_ptr = const_iterator::m_ptr->prev;
	return temp;
}

/*! Avança iterador step vezes.*/
template <typename T>
typename ls::List<T>::iterator ls::List<T>::iterator::operator+=( typename const_iterator::difference_type step ){
	//<! Avança o iterador
	while(step > 0){
		const_iterator::m_ptr = const_iterator::m_ptr->next;  
		step--;
	}
	return *this;
}

/*! Move iterador step vezes para trás.*/
template <typename T>
typename ls::List<T>::iterator ls::List<T>::iterator::operator-=( typename const_iterator::difference_type step ){
	//<! Avança o iterador
	while(step > 0){
		const_iterator::m_ptr = const_iterator::m_ptr->prev;  
		step--;
	}
	return *this;
}